#!/usr/bin/env python3
import csv
import json
import re
import xml.etree.ElementTree as ET
import zipfile
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SPRITE = ROOT / "src/poke/SpriteIndex.inc"
OUT = ROOT / "src/tracker/data"

FRLG_METS = {
    "pallet town": [0x00],
    "viridian city": [0x01],
    "pewter city": [0x02],
    "cerulean city": [0x03],
    "lavender town": [0x04],
    "vermilion city": [0x05],
    "celadon city": [0x06],
    "fuchsia city": [0x07],
    "cinnabar island": [0x08],
    "saffron city": [0x0A],
    "route 4": [0x10, 0x0B],
    "route 10": [0x16, 0x0C],
    "route 1": [0x0D],
    "route 2": [0x0E],
    "route 3": [0x0F],
    "route 5": [0x11],
    "route 6": [0x12],
    "route 7": [0x13],
    "route 8": [0x14],
    "route 9": [0x15],
    "route 11": [0x17],
    "route 12": [0x18],
    "route 13": [0x19],
    "route 14": [0x1A],
    "route 15": [0x1B],
    "route 16": [0x1C],
    "route 17": [0x1D],
    "route 18": [0x1E],
    "route 19": [0x1F],
    "route 20": [0x20],
    "route 21": [0x21],
    "route 22": [0x22],
    "route 23": [0x23],
    "route 24": [0x24],
    "route 25": [0x25],
    "viridian forest": [0x26],
    "mt moon": [0x27],
    "ss anne": [0x28],
    "s.s. anne": [0x28],
    "digletts cave": [0x2B],
    "victory road": [0x2C],
    "rocket hideout": [0x2D],
    "silph co": [0x2E],
    "pokemon mansion": [0x2F],
    "safari zone": [0x30],
    "rock tunnel": [0x32],
    "seafoam islands": [0x33],
    "pokemon tower": [0x34],
    "cerulean cave": [0x35],
    "power plant": [0x36],
    "one island": [0x37],
    "two island": [0x38],
    "three island": [0x39],
    "four island": [0x3A],
    "five island": [0x3B],
    "seven island": [0x3C],
    "six island": [0x3D],
}

NS = {"m": "http://schemas.openxmlformats.org/spreadsheetml/2006/main"}
RR_FORM = {"-a": "-alola", "-g": "-galar", "-h": "-hisui", "-p": "-paldea"}


def norm(name):
    s = name.lower().replace("é", "e").replace("pokémon", "pokemon")
    s = s.replace(".", "").replace("'", "").replace(",", "")
    s = re.sub(r"[/_]+", " ", s)
    s = re.sub(r"\s+", " ", s).strip()
    s = s.replace("mt ", "mt ")
    return s


def slugify_id(name):
    s = norm(name).replace(" ", "-")
    s = re.sub(r"[^a-z0-9-]+", "", s)
    s = re.sub(r"-+", "-", s).strip("-")
    return s or "stop"


def parse_sprite_ids():
    ids = {}
    for line in SPRITE.read_text().splitlines():
        m = re.search(r'\{"([^"]+)",\s*(\d+)\}', line)
        if m:
            ids[m.group(1)] = int(m.group(2))
    return ids


def species_id(slug, table):
    key = slugify_id(slug.replace("_", "-"))
    if key in table:
        return table[key]
    if key + "-alola" in table:
        return table[key]
    prefix = key + "-"
    best = None
    for k, v in table.items():
        if k.startswith(prefix) and (best is None or v < best):
            best = v
    return best or 0


def load_name_map(html_path):
    html = Path(html_path).read_text(errors="replace")
    tables = re.findall(r"<table[^>]*>(.*?)</table>", html, re.S)
    if not tables:
        return {}
    t = max(tables, key=len)
    out = {}
    for row in re.findall(r"<tr[^>]*>(.*?)</tr>", t, re.S):
        cells = re.findall(r"<t[dh][^>]*>(.*?)</t[dh]>", row, re.S)
        clean = [re.sub(r"<[^>]+>", "", c) for c in cells]
        clean = [re.sub(r"\s+", " ", c).strip() for c in clean]
        if len(clean) < 3 or not clean[1].startswith("0x"):
            continue
        loc = re.sub(r"<[^>]+>", "", cells[2] if len(clean) > 2 else "")
        loc = re.sub(r"<[^>]+>", "", loc)
        loc = re.sub(r"\s+", " ", clean[2]).strip()
        try:
            hid = int(clean[1], 16)
        except ValueError:
            continue
        key = norm(loc)
        out.setdefault(key, []).append(hid)
    return out


def load_rse(path):
    data = json.loads(Path(path).read_text())
    out = {}
    for i, sec in enumerate(data["map_sections"]):
        key = norm(sec["name"])
        out.setdefault(key, []).append(i)
    return out


def parse_routes(path):
    starters = []
    stops = []
    used = {}
    for raw in Path(path).read_text().splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        if line.startswith("Starter|") or line.startswith("Starter,"):
            parts = line.split("|", 1)
            tail = parts[1] if len(parts) > 1 else ""
            starters = [slugify_id(x) for x in tail.split(",") if x.strip()]
            continue
        if line.startswith("--"):
            bits = line[2:].split("|")
            locale = bits[0].strip() if bits else ""
            bid = bits[1].strip() if len(bits) > 1 else ""
            kind = bits[2].strip() if len(bits) > 2 else ""
            name = bits[3].strip() if len(bits) > 3 else bid
            boss = {
                "gym-leader": "gym",
                "rival": "rival",
                "elite-four": "elitefour",
                "evil-team": "evilteam",
                "mini-boss": "miniboss",
            }.get(kind, "miniboss" if "mini" in kind else "rival")
            gym = 0
            sid = slugify_id(bid)
            if boss == "gym" and re.fullmatch(r"\d+", bid.split("_")[0]):
                gym = int(bid.split("_")[0])
                sid = f"gym-{gym}" if gym else sid
            if not sid:
                sid = slugify_id(name)
            if sid in used:
                used[sid] += 1
                sid = f"{sid}-{used[sid]}"
            else:
                used[sid] = 1
            stops.append(
                {
                    "id": sid,
                    "kind": "boss",
                    "name": name or sid,
                    "locale": locale,
                    "boss": boss,
                    "gym": gym,
                    "battle": bid,
                }
            )
            continue
        loc, *rest = line.split("|")
        sid = slugify_id(loc)
        if sid in used:
            used[sid] += 1
            sid = f"{sid}-{used[sid]}"
        else:
            used[sid] = 1
        stops.append({"id": sid, "kind": "encounter", "name": loc.strip(), "catch": "met", "loc": loc})
    return starters, stops


def parse_league(path):
    teams = {}
    if not Path(path).exists():
        return teams
    cur = None
    lock_map = {"grass": "grass", "fire": "fire", "water": "water"}
    for raw in Path(path).read_text().splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        if line.startswith("--"):
            bits = line[2:].split("|")
            cur = bits[0].strip()
            teams[cur] = []
            continue
        if line.startswith("==") or cur is None or "|" not in line:
            continue
        parts = line.split("|")
        slug = slugify_id(re.split(r"[/>]", parts[0], 1)[0])
        lock = 0
        if len(parts) >= 6:
            token = parts[5].strip().lower()
            if token in lock_map:
                lock = token
        teams[cur].append({"slug": slug, "lock": lock})
    return teams


def apply_mets(stops, table):
    for stop in stops:
        if stop.get("kind") != "encounter":
            continue
        if stop.get("catch") == "starter" or stop.get("id") == "starter":
            stop["catch"] = "starter"
            continue
        key = norm(stop.get("loc") or stop["name"])
        mets = table.get(key)
        if not mets:
            for alias in (
                key.replace("pokemon ", ""),
                key.replace("centre", "center"),
            ):
                mets = table.get(alias)
                if mets:
                    break
        if mets:
            stop["mets"] = mets
        stop["catch"] = "met"


STARTER_TYPES = {
    "grass": {1, 152, 252, 387, 495, 650, 722, 810},
    "fire": {4, 155, 255, 390, 498, 653, 725, 813},
    "water": {7, 158, 258, 393, 501, 656, 728, 816},
}


def attach_teams(stops, league, starters, sprite):
    for stop in stops:
        bid = stop.pop("battle", None)
        stop.pop("loc", None)
        if stop.get("kind") != "boss":
            continue
        rows = league.get(bid) or []
        team = []
        for mon in rows:
            lock = mon["lock"]
            if isinstance(lock, str):
                want = STARTER_TYPES.get(lock, set())
                matched = [sid for sid in starters if sid in want]
                if not matched:
                    team.append({"slug": mon["slug"], "lock": 0})
                    continue
                for sid in matched:
                    team.append({"slug": mon["slug"], "lock": sid})
                continue
            team.append({"slug": mon["slug"], "lock": lock})
        if team:
            stop["team"] = team


def add_starter_stop(stops, starters):
    if any(s.get("id") == "starter" for s in stops):
        return
    stops.insert(
        0,
        {"id": "starter", "kind": "encounter", "name": "Starter", "catch": "starter"},
    )


def colrow(ref):
    col = "".join(c for c in ref if c.isalpha())
    row = int("".join(c for c in ref if c.isdigit()))
    n = 0
    for c in col:
        n = n * 26 + ord(c) - 64
    return n, row


def load_xlsx(path):
    z = zipfile.ZipFile(path)
    ss = []
    root = ET.fromstring(z.read("xl/sharedStrings.xml"))
    for si in root.findall("m:si", NS):
        texts = []
        for t in si.iter("{http://schemas.openxmlformats.org/spreadsheetml/2006/main}t"):
            texts.append(t.text or "")
        ss.append("".join(texts))
    wb = ET.fromstring(z.read("xl/workbook.xml"))
    rels = ET.fromstring(z.read("xl/_rels/workbook.xml.rels"))
    rid_to_target = {rel.attrib["Id"]: rel.attrib["Target"] for rel in rels}
    sheets = {}
    for sh in wb.find("m:sheets", NS):
        name = sh.attrib["name"]
        rid = sh.attrib["{http://schemas.openxmlformats.org/officeDocument/2006/relationships}id"]
        target = rid_to_target[rid]
        if not target.startswith("xl/"):
            target = "xl/" + target.lstrip("/")
        sheets[name] = target
    return z, ss, sheets


def sheet_grid(z, ss, target):
    root = ET.fromstring(z.read(target))
    grid = defaultdict(dict)
    for row in root.findall("m:sheetData/m:row", NS):
        for c in row.findall("m:c", NS):
            ref = c.attrib.get("r", "")
            t = c.attrib.get("t")
            v = c.find("m:v", NS)
            if v is None or v.text is None:
                continue
            val = ss[int(v.text)] if t == "s" else v.text
            col, r = colrow(ref)
            grid[r][col] = val
    return grid


def rr_slug(name, sprite):
    raw = name.strip().split("\n")[0].strip()
    if not raw or raw in {"-", "X"}:
        return ""
    lower = raw.lower()
    key = slugify_id(lower)
    if key in sprite:
        return key
    for token, suf in RR_FORM.items():
        if lower.endswith(token) and len(lower) > len(token) + 2:
            base = slugify_id(lower[: -len(token)])
            cand = base + suf
            if cand in sprite:
                return cand
            if base in sprite:
                return base
    if "-" not in key:
        for k in sprite:
            if k.startswith(key + "-"):
                return k
    return key


def parse_rr_sheet(grid, sprite):
    trainers = []
    lock = 0
    lock_species = {"squirtle": 1, "charmander": 7, "bulbasaur": 4}
    rows = sorted(grid)
    for r in rows:
        for val in grid[r].values():
            text = str(val).replace("\n", " ")
            m = re.search(r"IF RIVAL HAS ([A-Z]+)", text, re.I)
            if m:
                lock = lock_species.get(m.group(1).lower(), 0)
        name = str(grid[r].get(3, "")).replace("\n", " ").strip()
        if not name:
            continue
        mons = []
        for col in range(5, 36, 5):
            cell = str(grid[r].get(col, "")).strip()
            if not cell or cell.replace(".", "", 1).isdigit():
                continue
            if cell.startswith("(!)") or "BASE STAT" in cell or cell in {"HP", "ATK", "DEF"}:
                continue
            slug = rr_slug(cell, sprite)
            if slug:
                mons.append({"slug": slug, "lock": lock})
        if mons:
            trainers.append({"name": name, "team": mons, "lock": lock})
    return trainers


def overlay_rr(stops, xlsx, sprite):
    if not Path(xlsx).exists():
        return
    z, ss, sheets = load_xlsx(xlsx)
    all_trainers = []
    for tab in (
        "Kanto Leaders",
        "Johto Leaders",
        "Rivals",
        "Team Rocket",
        "Mini Bosses",
        "Indigo League",
    ):
        if tab not in sheets:
            continue
        all_trainers.extend(parse_rr_sheet(sheet_grid(z, ss, sheets[tab]), sprite))
    by_name = {}
    for t in all_trainers:
        key = norm(t["name"])
        by_name.setdefault(key, []).append(t)
    for stop in stops:
        if stop.get("kind") != "boss":
            continue
        key = norm(stop["name"])
        hit = None
        for k, rows in by_name.items():
            last = k.split()[-1]
            if key == k or key.endswith(last) and last == key.split()[-1]:
                hit = rows[0]
                break
            if key and key == last:
                hit = rows[0]
                break
        if hit:
            stop["team"] = hit["team"]


def write_atlas(aid, starters, stops, sprite):
    ids = [species_id(s, sprite) for s in starters]
    ids = [i for i in ids if i]
    payload = {"id": aid, "starters": ids, "stops": []}
    for stop in stops:
        row = {k: v for k, v in stop.items() if k not in {"loc", "battle"} and v}
        payload["stops"].append(row)
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT / f"{aid}.json").write_text(json.dumps(payload, indent=2) + "\n")


def rse_flags(stops, emerald):
    badge1 = 0x867 if emerald else 0x807
    e4 = [0x4FB, 0x4FC, 0x4FD, 0x4FE] if emerald else []
    e4_i = 0
    for stop in stops:
        if stop.get("boss") == "gym" and stop.get("gym"):
            stop["defeat"] = badge1 + stop["gym"] - 1
        if stop.get("boss") == "elitefour" and e4_i < len(e4):
            stop["defeat"] = e4[e4_i]
            e4_i += 1


def build_one(aid, route, league, mets, sprite, extra=None, emerald=False):
    starters, stops = parse_routes(route)
    add_starter_stop(stops, starters)
    apply_mets(stops, mets)
    attach_teams(stops, parse_league(league) if league else {}, [species_id(s, sprite) for s in starters], sprite)
    if extra:
        extra(stops)
    if aid in {"rs", "em", "emkaizo", "emrunbun", "incem"}:
        rse_flags(stops, emerald or aid != "rs")
    write_atlas(aid, starters, stops, sprite)


def main():
    nuz = Path("/tmp/nuz/nuzlocke.data")
    sprite = parse_sprite_ids()
    rse = load_rse("/tmp/srcdocs/em_region.h")
    gen4 = load_name_map("/tmp/srcdocs/loc4.html")
    gen5 = load_name_map("/tmp/srcdocs/loc5.html")
    jobs = [
        ("rs", nuz / "routes/ruby.txt", nuz / "leagues/rs.txt", rse, False),
        ("em", nuz / "routes/em.txt", nuz / "leagues/em.txt", rse, True),
        ("dp", nuz / "routes/dp.txt", nuz / "leagues/dp.txt", gen4, False),
        ("pt", nuz / "routes/pt.txt", nuz / "leagues/plat.txt", gen4, False),
        ("hgss", nuz / "routes/hg.txt", nuz / "leagues/hgss.txt", gen4, False),
        ("bw", nuz / "routes/bl.txt", nuz / "leagues/bw.txt", gen5, False),
        ("b2w2", nuz / "routes/bl2.txt", nuz / "leagues/b2w2.txt", gen5, False),
        ("blaze", nuz / "routes/blaze.txt", nuz / "leagues/blazevolt.txt", gen5, False),
        ("volt", nuz / "routes/volt.txt", nuz / "leagues/blazevolt.txt", gen5, False),
        ("blazevolt2", nuz / "routes/blazevolt2.txt", nuz / "leagues/blazevolt2.txt", gen5, False),
        ("blazevolt2-challenge", nuz / "routes/blazevolt2_c.txt", nuz / "leagues/blazevolt2.txt", gen5, False),
        ("sacredgold", nuz / "routes/sacredgold.txt", nuz / "leagues/sssg.txt", gen4, False),
        ("renplat", nuz / "routes/renplat.txt", nuz / "leagues/renplat.txt", gen4, False),
        ("emkaizo", nuz / "routes/emkaizo.txt", nuz / "leagues/emkaizo.txt", rse, True),
        ("emrunbun", nuz / "routes/emrunbun.txt", nuz / "leagues/emrunbun.txt", rse, True),
        ("incem", nuz / "routes/incem.txt", nuz / "leagues/incem.txt", rse, True),
        ("rr", nuz / "routes/radred.txt", nuz / "leagues/radred.txt", FRLG_METS, False),
        ("rr-hardcore", nuz / "routes/radred_hard.txt", nuz / "leagues/radred.txt", FRLG_METS, False),
        ("unbound", nuz / "routes/unbound.txt", nuz / "leagues/unbound.txt", {}, False),
        ("unbound-expert", nuz / "routes/unbound_exp.txt", nuz / "leagues/unbound.txt", {}, False),
        ("fro", nuz / "routes/fr.txt", nuz / "leagues/frlg.txt", FRLG_METS, False),
        ("platinum-kaizo", nuz / "routes/pt.txt", nuz / "leagues/plat.txt", gen4, False),
    ]
    for aid, route, league, mets, em in jobs:
        table = dict(mets)
        if aid.startswith("unbound"):
            starters, ub_stops = parse_routes(route)
            table = {}
            order = []
            for stop in ub_stops:
                for name in (stop.get("name"), stop.get("locale"), stop.get("loc")):
                    key = norm(name or "")
                    if key and key not in table:
                        table[key] = [len(order)]
                        order.append(key)
        extra = None
        if aid == "rr":
            extra = lambda stops: overlay_rr(stops, "/tmp/srcdocs/rr41_normal.xlsx", sprite)
        elif aid == "rr-hardcore":
            extra = lambda stops: overlay_rr(stops, "/tmp/srcdocs/rr41_hard.xlsx", sprite)
        build_one(aid, route, league, table, sprite, extra, em)
        print("wrote", aid)
    print("done")


if __name__ == "__main__":
    main()
