#!/usr/bin/env python3
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DATA = ROOT / "src/tracker/data"

ALIASES = {
    "barry": ["rival"],
    "may": ["rival"],
    "brendan": ["rival"],
    "gary": ["rival"],
    "blue": ["rival"],
    "silver": ["rival"],
    "wally": ["wally"],
    "shelly": ["shelly"],
    "tabitha": ["tabitha"],
    "courtney": ["courtney"],
    "maxie": ["maxie"],
    "archie": ["archie"],
    "steven": ["steven"],
    "wallace": ["wallace"],
    "sidney": ["sidney", "sydney"],
    "saturn": ["saturn"],
    "mars": ["mars"],
    "jupiter": ["jupiter"],
    "cynthia": ["cynthia"],
    "aaron": ["aaron"],
    "bertha": ["bertha"],
    "flint": ["flint"],
    "lucian": ["lucian"],
    "will": ["will"],
    "koga": ["koga"],
    "bruno": ["bruno"],
    "karen": ["karen"],
    "lance": ["lance"],
    "lorelei": ["lorelei"],
    "agatha": ["agatha"],
    "giovanni": ["giovanni"],
}


def parse_enum(text):
    flags = {}
    n = 0
    for raw in text.splitlines():
        line = raw.split("//")[0].strip()
        if not line or (line.startswith("#") and "define" not in line):
            continue
        mdef = re.match(r"#define\s+(\w+)\s+(.+)$", line)
        if mdef:
            name, rhs = mdef.group(1), mdef.group(2).strip().split()[0]
            if rhs.startswith("0x") or rhs.isdigit():
                val = int(rhs, 0)
            elif rhs.startswith("(") and "+" in rhs:
                inner = rhs.strip("()")
                parts = [p.strip() for p in inner.split("+")]
                if parts[0] in flags:
                    try:
                        val = flags[parts[0]] + int(parts[1], 0)
                    except ValueError:
                        continue
                else:
                    continue
            elif rhs in flags:
                val = flags[rhs]
            else:
                continue
            flags[name] = val
            n = val + 1
            continue
        if "=" in line:
            left, right = [x.strip() for x in line.split("=", 1)]
            right = right.split()[0]
            if right.startswith("0x") or right.isdigit():
                val = int(right, 0)
            elif right in flags:
                val = flags[right]
            else:
                continue
            flags[left] = val
            n = val + 1
        elif re.match(r"^[A-Z0-9_]+$", line):
            flags[line] = n
            n += 1
    return flags


def load_flags():
    tables = {
        "em": parse_enum((Path("/tmp/pret/pokeemerald/include/constants/flags.h")).read_text()),
        "pt": parse_enum((Path("/tmp/pret/pokeplatinum/generated/vars_flags.txt")).read_text()),
        "hgss": parse_enum((Path("/tmp/pret/pokeheartgold/include/constants/flags.h")).read_text()),
        "fr": parse_enum((Path("/tmp/pret/pokefirered/include/constants/flags.h")).read_text()),
    }
    rs = Path("/tmp/pret/pokeruby/include/constants/flags.h")
    tables["rs"] = parse_enum(rs.read_text()) if rs.exists() else tables["em"]
    return tables


def tokens(s):
    skip = {"the", "and", "of", "to", "a", "at"}
    return [t for t in re.split(r"[^a-z0-9]+", s.lower()) if t and t not in skip]


def want_tokens(stop):
    name = stop.get("name") or ""
    locale = stop.get("locale") or ""
    out = tokens(name) + tokens(locale)
    for t in list(out):
        out.extend(ALIASES.get(t, []))
    return out


def best_flag(flags, stop):
    want = set(want_tokens(stop))
    name_toks = tokens(stop.get("name") or "")
    if not want:
        return None
    best = None
    best_score = 0
    for flag, val in flags.items():
        if "REMATCH" in flag:
            continue
        if not flag.startswith("FLAG_DEFEATED") and not flag.startswith("FLAG_BEAT"):
            continue
        ftok = set(tokens(flag.replace("FLAG_DEFEATED_TRAINER", "").replace("FLAG_DEFEATED", "").replace("FLAG_BEAT", "")))
        score = len(want & ftok)
        if name_toks and all(t in ftok or t in ALIASES.get(t, []) for t in name_toks if t not in {"optional"}):
            score += 1
        if score > best_score:
            best_score = score
            best = (flag, val)
    if best_score < 2:
        return None
    return best


EXPLICIT = {
    ("em", "r1"): (0x82, 3),
    ("em", "r4"): (0x353, 1),
    ("em", "r5"): (0x3CB, 1),
    ("em", "as1"): (0x520, 1),
    ("em", "as2"): (0x521, 1),
    ("em", "aqarc"): (0x522, 1),
    ("em", "c1"): (0x864, 1),
    ("emkaizo", "as1"): (0x520, 1),
    ("emkaizo", "as2"): (0x521, 1),
    ("emkaizo", "aqarc"): (0x522, 1),
    ("emkaizo", "r2"): (0x353, 1),
    ("emkaizo", "b2"): (0x353, 1),
    ("emkaizo", "r3"): (0x3CB, 1),
    ("emkaizo", "b3"): (0x3CB, 1),
    ("rs", "r1"): (0x82, 3),
    ("rs", "r2"): (0x7D, 3),
    ("rs", "c"): (0x864, 1),
    ("fro", "r1"): (0x646, 3),
    ("fro", "r2"): (0x649, 3),
    ("fro", "r3"): (0x64C, 3),
    ("fro", "r4"): (0x6AA, 3),
    ("fro", "r5"): (0x6AD, 3),
    ("fro", "r6"): (0x6B0, 3),
    ("fro", "r7"): (0x6B3, 3),
    ("fro", "c"): (0x4BC, 1),
    ("hgss", "r1"): (0x19C, 1),
    ("hgss", "proton1"): (0x7B, 1),
    ("hgss", "r3"): (0x1C6, 1),
    ("hgss", "eusine"): (0x1C7, 1),
    ("hgss", "r5"): (0x20A, 1),
    ("hgss", "c"): (0xE7, 1),
    ("hgss", "k1"): (0x9A6, 1),
    ("hgss", "k2"): (0x182, 1),
    ("hgss", "k3"): (0x124, 1),
    ("hgss", "k4"): (0x12D, 1),
    ("hgss", "k5"): (0x180, 1),
    ("hgss", "k6"): (0x17F, 1),
    ("hgss", "k7"): (0x17D, 1),
    ("hgss", "k8"): (0x17E, 1),
    ("sacredgold", "proton1"): (0x7B, 1),
    ("sacredgold", "rn2"): (0x1C6, 1),
    ("sacredgold", "eusine"): (0x1C7, 1),
    ("sacredgold", "r2"): (0x20A, 1),
    ("sacredgold", "c"): (0xE7, 1),
    ("sacredgold", "k1"): (0x9A6, 1),
    ("sacredgold", "k2"): (0x182, 1),
    ("sacredgold", "k3"): (0x124, 1),
    ("sacredgold", "k4"): (0x12D, 1),
    ("sacredgold", "k5"): (0x180, 1),
    ("sacredgold", "k6"): (0x17F, 1),
    ("sacredgold", "k7"): (0x17D, 1),
    ("sacredgold", "k8"): (0x17E, 1),
    ("hgss", "li"): (0x2E3, 1),
    ("hgss", "r2"): (0x310, 1),
    ("hgss", "petrel1"): (0x1F4, 1),
    ("hgss", "ariana1"): (0x1F3, 1),
    ("hgss", "r4"): (0x1BD, 1),
    ("hgss", "kimono"): (0x23C, 1),
    ("hgss", "r6"): (0x250, 1),
    ("hgss", "red"): (0x654, 1),
    ("sacredgold", "li"): (0x2E3, 1),
    ("sacredgold", "rn1"): (0x310, 1),
    ("sacredgold", "petrel1"): (0x1F4, 1),
    ("sacredgold", "ariana1"): (0x1F3, 1),
    ("rs", "r3"): (0x353, 1),
    ("rs", "r4"): (0x3CB, 1),
    ("rs", "ruby2"): (0x37D, 1),
    ("rs", "ruby4"): (0x33D, 1),
    ("rs", "max2"): (0x33D, 1),
    ("incem", "as1"): (0x520, 1),
    ("incem", "as2"): (0x521, 1),
    ("incem", "aa1"): (0x522, 1),
    ("incem", "aa2"): (0x33C, 1),
    ("incem", "am1"): (0x33F, 1),
    ("incem", "r4b"): (0x3CB, 1),
    ("incem", "r4m"): (0x3CB, 1),
    ("emrunbun", "r3"): (0x353, 1),
    ("emrunbun", "aq4"): (0x520, 1),
    ("emrunbun", "aq5"): (0x522, 1),
    ("emrunbun", "aq7"): (0x33C, 1),
    ("bw", "gh"): (2400, 1),
    ("blaze", "gh"): (2400, 1),
    ("volt", "gh"): (2400, 1),
    ("b2w2", "ghetsis"): (2400, 1),
    ("blazevolt2", "ghetsis"): (2400, 1),
    ("blazevolt2", "ghetsis-n"): (2400, 1),
    ("blazevolt2-challenge", "ghetsis-c"): (2400, 1),
    ("rr", "3r"): (0x5A0, 1),
    ("rr-hardcore", "3r-hard"): (0x5A0, 1),
    ("renplat", "sat1"): (1589, 1),
    ("incem", "c"): (0x864, 1),
    ("emrunbun", "ec"): (0x864, 1),
    ("emkaizo", "am1"): (0x33F, 1),
    ("rr", "r2"): (0x649, 3),
    ("rr", "r3"): (0x64C, 3),
    ("rr", "r4"): (0x6B0, 3),
    ("rr", "r5"): (0x6B3, 3),
    ("rr", "ec"): (0x6B6, 3),
    ("rr-hardcore", "r2-hard"): (0x649, 3),
    ("rr-hardcore", "r3-hard"): (0x64C, 3),
    ("rr-hardcore", "r4-hard"): (0x6B0, 3),
    ("rr-hardcore", "r5-hard"): (0x6B3, 3),
    ("rr-hardcore", "ec-hard"): (0x6B6, 3),
    ("unbound", "r1"): (0x646, 3),
    ("unbound", "r2"): (0x649, 3),
    ("unbound", "r3"): (0x64C, 3),
    ("unbound", "r4"): (0x6AA, 3),
    ("unbound", "r5"): (0x6B3, 3),
    ("unbound-expert", "r1-exp"): (0x646, 3),
    ("unbound-expert", "r2-exp"): (0x649, 3),
    ("unbound-expert", "r3-exp"): (0x64C, 3),
    ("unbound-expert", "r4-exp"): (0x6AA, 3),
    ("unbound-expert", "r5-exp"): (0x6B3, 3),
    ("sacredgold", "r1"): (0x19C, 1),
    ("sacredgold", "r3"): (0x250, 1),
    ("sacredgold", "kimono"): (0x23C, 1),
    ("sacredgold", "red"): (0x654, 1),
    ("sacredgold", "archer"): (0xC6, 1),
    ("sacredgold", "ariana2"): (0x1F3, 1),
    ("sacredgold", "petrel2"): (0x1F4, 1),
    ("renplat", "e3b"): (181, 1),
    ("renplat", "e3c"): (181, 1),
    ("renplat", "e3d"): (181, 1),
    ("renplat", "e4b"): (182, 1),
    ("renplat", "e4c"): (182, 1),
    ("renplat", "e4d"): (182, 1),
}


def fill_gyms(data):
    used = set()
    for stop in data["stops"]:
        if stop.get("gym"):
            used.add(int(stop["gym"]))
    n = 1
    changed = 0
    for stop in data["stops"]:
        if stop.get("kind") != "boss" or stop.get("boss") != "gym" or stop.get("gym"):
            continue
        name = (stop.get("name") or "").lower()
        sid = stop.get("id") or ""
        if "rematch" in name or sid.endswith("r"):
            continue
        if sid.startswith("k") and sid[1:2].isdigit():
            continue
        while n in used and n <= 8:
            n += 1
        if n > 8:
            break
        stop["gym"] = n
        used.add(n)
        n += 1
        changed += 1
    return changed


HACK_ROMS = {
    "rr": Path("/tmp/hack_roms/rr.gba"),
    "rr-hardcore": Path("/tmp/hack_roms/rr.gba"),
    "rr-easy": Path("/tmp/hack_roms/rr.gba"),
    "unbound": Path("/tmp/hack_roms/unbound.gba"),
    "unbound-expert": Path("/tmp/hack_roms/unbound.gba"),
    "unbound-easy": Path("/tmp/hack_roms/unbound.gba"),
    "unbound-insane": Path("/tmp/hack_roms/unbound.gba"),
    "fro": Path("/tmp/hack_roms/fro.gba"),
}

HACK_TABLE = {
    "rr": 0x23EAC8,
    "rr-hardcore": 0x23EAC8,
    "rr-easy": 0x23EAC8,
    "unbound": 0x23EAC8,
    "unbound-expert": 0x23EAC8,
    "unbound-easy": 0x23EAC8,
    "unbound-insane": 0x23EAC8,
    "fro": 0x24BB80 - 414 * 40,
}

SKIP_NAME = {"rival", "admin", "executive", "shadow", "boss", "leader", "gym", "the", "and"}


def gen3_name(raw):
    out = []
    for code in raw:
        if code == 0xFF:
            break
        if code == 0:
            out.append(" ")
        elif 0xA1 <= code <= 0xAA:
            out.append(chr(ord("0") + code - 0xA1))
        elif 0xBB <= code <= 0xD4:
            out.append(chr(ord("A") + code - 0xBB))
        elif 0xD5 <= code <= 0xEE:
            out.append(chr(ord("a") + code - 0xD5))
    return "".join(out).strip().lower()


def load_hack_names(aid):
    path = HACK_ROMS.get(aid)
    off = HACK_TABLE.get(aid)
    if not path or not off or not path.exists():
        return {}
    rom = path.read_bytes()
    by_name = {}
    for i in range(800):
        rec = rom[off + i * 40 : off + i * 40 + 40]
        if len(rec) < 40:
            break
        if rec[32] > 6:
            break
        name = gen3_name(rec[4:16])
        if not name:
            continue
        by_name.setdefault(name, []).append(i)
    return by_name


def boss_name_keys(stop):
    parts = tokens(stop.get("name") or "")
    keys = [p for p in parts if p not in SKIP_NAME]
    if not keys:
        keys = parts
    extra = []
    for k in keys:
        extra.extend(ALIASES.get(k, []))
    return keys + extra


def fill_hack_trainers(data, names):
    changed = 0
    if not names:
        return 0
    for stop in data["stops"]:
        if stop.get("kind") != "boss":
            continue
        if stop.get("defeat") or stop.get("gym") or stop.get("onStarter"):
            continue
        ids = []
        for key in boss_name_keys(stop):
            ids.extend(names.get(key, []))
        if not ids:
            continue
        tid = min(ids)
        stop["defeat"] = 0x500 + tid
        if stop.get("boss") == "rival":
            stop["span"] = 3
        changed += 1
    return changed


def fill_file(path, tables, hack_names):
    data = json.loads(path.read_text())
    aid = data["id"]
    table = None
    if aid in ("em", "emkaizo", "emrunbun", "incem"):
        table = tables["em"]
    elif aid in ("rs",):
        table = tables["rs"]
    elif aid in ("dp", "pt", "renplat", "platinum-kaizo"):
        table = tables["pt"]
    elif aid in ("hgss", "sacredgold"):
        table = tables["hgss"]
    elif aid in ("fro",):
        table = tables["fr"]
    changed = fill_gyms(data)
    for stop in data["stops"]:
        if stop.get("kind") != "boss":
            continue
        if stop.get("id") in ("b1", "c1") and aid in ("blaze", "volt", "bw"):
            if not stop.get("onStarter"):
                stop["onStarter"] = True
                changed += 1
        if stop.get("id") in ("r1", "r0-n", "r0-c") and aid in ("b2w2", "blazevolt2", "blazevolt2-challenge"):
            if not stop.get("onStarter"):
                stop["onStarter"] = True
                changed += 1
        key = (aid, stop.get("id"))
        if key in EXPLICIT and not stop.get("defeat"):
            flag, span = EXPLICIT[key]
            stop["defeat"] = flag
            if span > 1:
                stop["span"] = span
            changed += 1
            continue
        if stop.get("defeat") or stop.get("gym") or stop.get("onStarter"):
            continue
        if table is None:
            continue
        hit = best_flag(table, stop)
        if not hit:
            continue
        flag, val = hit
        stop["defeat"] = val
        if "RIVAL" in flag:
            stop["span"] = 3
        changed += 1
    changed += fill_hack_trainers(data, hack_names.get(aid, {}))
    path.write_text(json.dumps(data, indent=2) + "\n")
    return changed


def main():
    tables = load_flags()
    hack_names = {aid: load_hack_names(aid) for aid in HACK_ROMS}
    total = 0
    for path in sorted(DATA.glob("*.json")):
        n = fill_file(path, tables, hack_names)
        print(path.name, n)
        total += n
    print("updated", total)


if __name__ == "__main__":
    main()
