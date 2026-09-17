#!/usr/bin/env python3
import json
from collections import defaultdict
from pathlib import Path

from gen5_text import parse_gen5_text
from gen_calc_nds import parse_narc


def species_names_from_rom(files):
    msg = files.get("/a/0/0/2")
    if not msg or msg[:4] != b"NARC":
        return []
    for blob in parse_narc(msg):
        names = parse_gen5_text(blob)
        if len(names) > 500 and names[1].lower() == "bulbasaur":
            return [n.lower().replace(" ", "-").replace("é", "e") for n in names]
    return []


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


def from_atlas(path, trainers, parties, names, species_names):
    data = json.loads(Path(path).read_text(encoding="utf-8"))
    by_name = defaultdict(list)
    for tid, meta in enumerate(trainers):
        if not meta or not parties[tid]:
            continue
        key = names[tid].lower() if tid < len(names) and names[tid] else ""
        if key:
            by_name[key].append(tid)
    locs = {}
    atlas_order = defaultdict(list)
    for stop in data.get("stops") or []:
        if stop.get("kind") != "boss":
            continue
        locale = (stop.get("locale") or "").strip()
        name = (stop.get("name") or "").strip().lower()
        if not locale or not name:
            continue
        atlas_order[name].append(locale)
        cands = by_name.get(name, [])
        if len(cands) == 1:
            locs[cands[0]] = locale
            continue
        want = [(m.get("slug") or "").lower() for m in stop.get("team") or []]
        for tid in cands:
            have = []
            for mon in parties[tid]:
                sid = mon["species"]
                have.append(species_names[sid] if 0 <= sid < len(species_names) else "")
            if have == want or _fold(have) == _fold(want):
                locs[tid] = locale
    for name, tids in by_name.items():
        remain_t = [tid for tid in tids if tid not in locs]
        used = {locs[tid] for tid in tids if tid in locs}
        remain_l = [loc for loc in atlas_order.get(name, []) if loc not in used]
        if not remain_t or not remain_l:
            continue
        for tid, loc in zip(remain_t, remain_l):
            locs[tid] = loc
        for tid in remain_t[len(remain_l) :]:
            locs[tid] = remain_l[-1]
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
        for tid, loc in from_atlas(atlas, trainers, parties, names, species_names).items():
            locs.setdefault(tid, loc)
    return locs
