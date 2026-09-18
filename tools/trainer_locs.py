#!/usr/bin/env python3
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

from gen5_text import parse_gen5_text
from gen_calc_nds import c_escape, parse_narc


def species_names_from_rom(files):
    msg = files.get("/a/0/0/2")
    if not msg or msg[:4] != b"NARC":
        return []
    for blob in parse_narc(msg):
        names = parse_gen5_text(blob)
        if len(names) > 500 and names[1].lower() == "bulbasaur":
            return [n.lower().replace(" ", "-").replace("é", "e") for n in names]
    return []


def species_names_from_nat(path):
    names = []
    for line in Path(path).read_text(encoding="utf-8").splitlines():
        m = re.match(r"\s+\{(\d+)(?:,\s*\"([^\"]+)\")?", line)
        if not m:
            continue
        sid = int(m.group(1))
        while len(names) <= sid:
            names.append("")
        if m.group(2):
            names[sid] = m.group(2).lower()
    return names


def from_npoint(path):
    data = json.loads(Path(path).read_text(encoding="utf-8"))
    locs = {}
    for groups in (data.get("formatted_sets") or {}).values():
        if not isinstance(groups, dict):
            continue
        for name, payload in groups.items():
            if not isinstance(payload, dict) or " - " not in name:
                continue
            tid = payload.get("tr_id")
            loc = name.split(" - ", 1)[1].strip()
            if tid is not None and loc and int(tid) not in locs:
                locs[int(tid)] = loc
    return locs


def _fold(slugs):
    return [s.split("-", 1)[0] for s in slugs]


def _bags_equal(have, want):
    if sorted(have) == sorted(want):
        return True
    return sorted(_fold(have)) == sorted(_fold(want))


def _variant_parties(team):
    rows = team or []
    locks = sorted({int(m.get("lock") or 0) for m in rows if int(m.get("lock") or 0)})
    if not locks:
        return [[(m.get("slug") or "").lower() for m in rows]]
    variants = []
    for lock in locks:
        variants.append(
            [(m.get("slug") or "").lower() for m in rows if int(m.get("lock") or 0) in (0, lock)]
        )
    return variants


def _party_slugs(party, species_names):
    have = []
    for mon in party:
        sid = mon["species"]
        have.append(species_names[sid] if 0 <= sid < len(species_names) else "")
    return have


def _free_slugs(team):
    return [(m.get("slug") or "").lower() for m in team or [] if int(m.get("lock") or 0) == 0]


def _common_with_free(cands, parties, species_names, free):
    bags = []
    for tid in cands:
        have = _party_slugs(parties[tid], species_names)
        if set(free).issubset(set(have)):
            bags.append(set(have))
    if not bags:
        return set()
    shared = set(bags[0])
    for bag in bags[1:]:
        shared &= bag
    return shared


def _hits_variant(have, want, common):
    if _bags_equal(have, want):
        return True
    extra = list(want)
    for slug in common:
        if slug not in extra:
            extra.append(slug)
    return extra != want and _bags_equal(have, extra)


def from_atlas(path, trainers, parties, names, species_names):
    data = json.loads(Path(path).read_text(encoding="utf-8"))
    by_name = defaultdict(list)
    for tid, meta in enumerate(trainers):
        if not meta or tid >= len(parties) or not parties[tid]:
            continue
        key = names[tid].lower() if tid < len(names) and names[tid] else ""
        if key:
            by_name[key].append(tid)
    locs = {}
    for stop in data.get("stops") or []:
        if stop.get("kind") != "boss":
            continue
        locale = (stop.get("locale") or "").strip()
        name = (stop.get("name") or "").strip().lower()
        if not locale or not name:
            continue
        cands = by_name.get(name, [])
        if len(cands) == 1:
            locs.setdefault(cands[0], locale)
            continue
        team = stop.get("team") or []
        variants = _variant_parties(team)
        free = _free_slugs(team)
        common = _common_with_free(cands, parties, species_names, free) if free else set()
        for tid in cands:
            if tid in locs:
                continue
            have = _party_slugs(parties[tid], species_names)
            if any(_hits_variant(have, want, common) for want in variants):
                locs[tid] = locale
    return locs


def overlay_locs(root, prefix, trainers, parties, names, files=None):
    locs = {}
    if prefix != "Blaze":
        return locs
    npoint = Path("/tmp/blaze_npoint.json")
    if npoint.exists():
        locs.update(from_npoint(npoint))
    atlas = Path(root) / "src/tracker/data/blaze.json"
    if atlas.exists():
        species_names = species_names_from_rom(files or {})
        if not species_names:
            species_names = species_names_from_nat(Path(root) / "src/calc/data/SpeciesNat.inc")
        locs.update(from_atlas(atlas, trainers, parties, names, species_names))
    return locs


_TRAINER_RE = re.compile(
    r'\s+\{(\d+), "((?:\\.|[^"\\])*)", "((?:\\.|[^"\\])*)", "((?:\\.|[^"\\])*)", '
    r"(\d+), (\d+), (\d+), (\d+)\},"
)
_MON_RE = re.compile(
    r"\s+\{(\d+), (\d+), (\d+), (\d+), \{(\d+), (\d+), (\d+), (\d+)\}\},"
)


def parse_pack_trainers(path):
    rows = []
    for line in Path(path).read_text(encoding="utf-8").splitlines():
        m = _TRAINER_RE.match(line)
        if not m:
            continue
        rows.append(
            {
                "id": int(m.group(1)),
                "name": m.group(2).replace('\\"', '"'),
                "cls": m.group(3).replace('\\"', '"'),
                "location": m.group(4).replace('\\"', '"'),
                "count": int(m.group(5)),
                "monOff": int(m.group(6)),
                "mandatory": int(m.group(7)),
                "ai": int(m.group(8)),
                "line": line,
            }
        )
    return rows


def parse_pack_mons(path):
    mons = []
    for line in Path(path).read_text(encoding="utf-8").splitlines():
        m = _MON_RE.match(line)
        if not m:
            continue
        mons.append(
            {
                "species": int(m.group(1)),
                "lvl": int(m.group(2)),
                "iv": int(m.group(3)),
                "item": int(m.group(4)),
                "moves": [int(m.group(i)) for i in range(5, 9)],
            }
        )
    return mons


def write_loc_files(out, prefix, rows):
    loc_map = defaultdict(list)
    for row in rows:
        if row["location"]:
            loc_map[row["location"]].append(row["id"])
    if loc_map:
        id_rows = []
        loc_rows = []
        loc_off = 0
        for name, ids in sorted(loc_map.items(), key=lambda x: x[0].lower()):
            id_rows.extend(f"    {i}," for i in ids)
            loc_rows.append(f'    {{"{c_escape(name)}", {len(ids)}, {loc_off}}},')
            loc_off += len(ids)
    else:
        id_rows = ["    0,"]
        loc_rows = ['    {"", 0, 0},']
    (out / f"Pack{prefix}LocIds.inc").write_text("\n".join(id_rows) + "\n")
    (out / f"Pack{prefix}Locs.inc").write_text("\n".join(loc_rows) + "\n")


def relabel_pack(root, prefix, atlas_rel):
    root = Path(root)
    out = root / "src/calc/data"
    trainers_path = out / f"Pack{prefix}Trainers.inc"
    rows = parse_pack_trainers(trainers_path)
    mons = parse_pack_mons(out / f"Pack{prefix}Mons.inc")
    max_tid = max((row["id"] for row in rows), default=0)
    trainers = [None] * (max_tid + 1)
    parties = [[] for _ in range(max_tid + 1)]
    names = [""] * (max_tid + 1)
    for row in rows:
        tid = row["id"]
        trainers[tid] = {"count": row["count"]}
        names[tid] = row["name"]
        parties[tid] = mons[row["monOff"] : row["monOff"] + row["count"]]
    atlas = root / atlas_rel
    species_names = species_names_from_nat(out / "SpeciesNat.inc")
    matched = from_atlas(atlas, trainers, parties, names, species_names)
    lines = []
    for row in rows:
        loc = matched.get(row["id"], row["location"])
        row["location"] = loc
        lines.append(
            f'    {{{row["id"]}, "{c_escape(row["name"])}", "{c_escape(row["cls"])}", '
            f'"{c_escape(loc)}", {row["count"]}, {row["monOff"]}, {row["mandatory"]}, {row["ai"]}}},'
        )
    trainers_path.write_text("\n".join(lines) + "\n")
    write_loc_files(out, prefix, rows)
    print(f"{prefix} relabeled {len(matched)} atlas trainers")


def main():
    root = Path(__file__).resolve().parents[1]
    relabel_pack(root, "Blaze", "src/tracker/data/blaze.json")


if __name__ == "__main__":
    sys.exit(main() or 0)
