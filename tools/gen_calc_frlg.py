#!/usr/bin/env python3
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(sys.argv[1] if len(sys.argv) > 1 else "/tmp/pret/pokefirered")
OUT = Path(sys.argv[2] if len(sys.argv) > 2 else "src/calc/data")


def read(rel):
    return (ROOT / rel).read_text(encoding="utf-8", errors="replace")


def defines(rel, prefix):
    out = {}
    for m in re.finditer(rf"#define\s+({prefix}\w+)\s+(\d+)", read(rel)):
        out[m.group(1)] = int(m.group(2))
    return out


def pretty(token):
    s = token.split("_", 1)[-1] if token.startswith("MOVE_") or token.startswith("SPECIES_") else token
    s = s.replace("TRAINER_CLASS_", "").replace("TRAINER_", "")
    return s.replace("_", " ")


def parse_c_array_blocks(text, start_pat):
    blocks = {}
    for m in re.finditer(start_pat, text):
        name = m.group(1)
        i = m.end()
        depth = 1
        while i < len(text) and depth:
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
            i += 1
        blocks[name] = text[m.end() : i - 1]
    return blocks


def keyed_structs(text, key_prefix):
    out = {}
    for m in re.finditer(rf"\[({key_prefix}\w+)\]\s*=\s*{{", text):
        i = m.end()
        depth = 1
        while i < len(text) and depth:
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
            i += 1
        out[m.group(1)] = text[m.end() : i - 1]
    return out


def species_stats():
    stats = {}
    for key, body in keyed_structs(read("src/data/pokemon/species_info.h"), "SPECIES_").items():
        def num(field, default=0):
            x = re.search(rf"\.{field}\s*=\s*(\d+)", body)
            return int(x.group(1)) if x else default

        if ".baseHP" not in body:
            continue
        types = re.search(r"\.types\s*=\s*\{([^}]+)\}", body)
        abilities = re.search(r"\.abilities\s*=\s*\{([^}]+)\}", body)
        t1 = t2 = "TYPE_NORMAL"
        a1 = a2 = "ABILITY_NONE"
        if types:
            parts = [p.strip() for p in types.group(1).split(",")]
            t1 = parts[0]
            t2 = parts[1] if len(parts) > 1 else parts[0]
        if abilities:
            parts = [p.strip() for p in abilities.group(1).split(",")]
            a1 = parts[0]
            a2 = parts[1] if len(parts) > 1 else "ABILITY_NONE"
        stats[key] = {
            "hp": num("baseHP"),
            "atk": num("baseAttack"),
            "def": num("baseDefense"),
            "spa": num("baseSpAttack"),
            "spd": num("baseSpDefense"),
            "spe": num("baseSpeed"),
            "t1": t1,
            "t2": t2,
            "a1": a1,
            "a2": a2,
        }
    return stats


def weights():
    w = {}
    for key, body in keyed_structs(read("src/data/pokemon/pokedex_entries.h"), "NATIONAL_DEX_").items():
        x = re.search(r"\.weight\s*=\s*(\d+)", body)
        if x:
            w[key.replace("NATIONAL_DEX_", "SPECIES_")] = int(x.group(1))
    return w


def battle_moves():
    moves = {}
    for key, body in keyed_structs(read("src/data/battle_moves.h"), "MOVE_").items():
        def grab(field, default="0"):
            x = re.search(rf"\.{field}\s*=\s*([^,\n]+)", body)
            return x.group(1).strip() if x else default

        moves[key] = {
            "effect": grab("effect"),
            "power": int(re.sub(r"\D", "", grab("power", "0")) or 0),
            "type": grab("type", "TYPE_NORMAL"),
            "priority": int(grab("priority", "0").replace(" ", "") or 0),
            "flags": grab("flags", "0"),
        }
    return moves


def learnsets():
    text = read("src/data/pokemon/level_up_learnsets.h")
    sets = {}
    for m in re.finditer(
        r"static const u16 s(\w+)LevelUpLearnset\[\] = \{(.*?)\};", text, re.S
    ):
        entries = []
        for lv, mv in re.findall(r"LEVEL_UP_MOVE\(\s*(\d+)\s*,\s*(MOVE_\w+)\)", m.group(2)):
            entries.append((int(lv), mv))
        sets[m.group(1)] = entries
    ptrs = {}
    ptext = read("src/data/pokemon/level_up_learnset_pointers.h")
    for sp, name in re.findall(r"\[(SPECIES_\w+)\]\s*=\s*s(\w+)LevelUpLearnset", ptext):
        ptrs[sp] = name
    return {sp: sets.get(name, []) for sp, name in ptrs.items()}


def default_moves(learned, level):
    got = []
    for lv, mv in learned:
        if lv <= level and mv != "MOVE_NONE":
            got.append(mv)
    return (got[-4:] + ["MOVE_NONE"] * 4)[:4]


def parse_parties():
    text = read("src/data/trainer_parties.h")
    parties = {}
    for m in re.finditer(
        r"static const struct TrainerMon\w+ sParty_(\w+)\[\] = \{(.*?)\n\};", text, re.S
    ):
        mons = []
        for body in re.split(r"\n    \},", m.group(2)):
            if ".species" not in body:
                continue
            iv = re.search(r"\.iv\s*=\s*(\d+)", body)
            lv = re.search(r"\.lvl\s*=\s*(\d+)", body)
            sp = re.search(r"\.species\s*=\s*(SPECIES_\w+)", body)
            item = re.search(r"\.heldItem\s*=\s*(ITEM_\w+)", body)
            moves = re.findall(r"MOVE_\w+", body)
            if not lv or not sp:
                continue
            mons.append(
                {
                    "iv": int(iv.group(1)) if iv else 0,
                    "lvl": int(lv.group(1)),
                    "species": sp.group(1),
                    "item": item.group(1) if item else "ITEM_NONE",
                    "moves": moves[:4] if len(moves) >= 4 else [],
                }
            )
        parties[m.group(1)] = mons
    return parties


def parse_trainers():
    trainers = {}
    for key, body in keyed_structs(read("src/data/trainers.h"), "TRAINER_").items():
        name = re.search(r'\.trainerName\s*=\s*_\("([^"]*)"\)', body)
        cls = re.search(r"\.trainerClass\s*=\s*(TRAINER_CLASS_\w+)", body)
        party = re.search(r"\.party\s*=\s*\w+\(sParty_(\w+)\)", body)
        if not party:
            continue
        trainers[key] = {
            "name": name.group(1) if name else "",
            "cls": cls.group(1) if cls else "TRAINER_CLASS_NONE",
            "party": party.group(1),
        }
    return trainers


def loc_label(raw):
    s = raw.replace("scripts", "").replace(".inc", "")
    s = s.replace("_", " ")
    s = re.sub(r"([a-z])([A-Z])", r"\1 \2", s)
    s = re.sub(r"(Route)(\d+)", r"\1 \2", s)
    s = re.sub(r"\s+", " ", s).strip()
    return s


def trainer_locations():
    loc = {}
    maps = ROOT / "data" / "maps"
    if maps.exists():
        for scripts in maps.glob("*/scripts.inc"):
            label = loc_label(scripts.parent.name)
            for tid in re.findall(r"trainerbattle_\w+\s+(TRAINER_\w+)", scripts.read_text(encoding="utf-8", errors="replace")):
                loc.setdefault(tid, label)
    trainers_inc = ROOT / "data" / "scripts" / "trainers.inc"
    if trainers_inc.exists():
        text = trainers_inc.read_text(encoding="utf-8", errors="replace")
        for tid, prefix in re.findall(r"trainerbattle_\w+\s+(TRAINER_\w+),\s+(\w+)_Text_", text):
            loc.setdefault(tid, loc_label(prefix))
    return loc


def class_names():
    names = {}
    text = read("src/data/text/trainer_class_names.h")
    for cls, raw in re.findall(r"\[(TRAINER_CLASS_\w+)\]\s*=\s*_\(\"([^\"]*)\"\)", text):
        names[cls] = raw.replace("{PKMN}", "PKMN").replace("♂", "M").replace("♀", "F")
    return names


def c_escape(s):
    return s.replace("\\", "\\\\").replace('"', '\\"')


def emit_dex(species, stats, wtab, abilities, types):
    rows = []
    max_id = max(species.values())
    by_id = {v: k for k, v in species.items() if not k.startswith("SPECIES_UNOWN_")}
    for sid in range(max_id + 1):
        key = by_id.get(sid)
        if not key or key not in stats:
            rows.append("    {0},")
            continue
        st = stats[key]
        t1 = types.get(st["t1"], 0)
        t2 = types.get(st["t2"], t1)
        a1 = abilities.get(st["a1"], 0)
        a2 = abilities.get(st["a2"], 0)
        kg10 = wtab.get(key, 0)
        slug = key.replace("SPECIES_", "").replace("_", "-").lower()
        if slug == "none":
            rows.append("    {0},")
            continue
        rows.append(
            f'    {{{sid}, "{c_escape(slug)}", {t1}, {t2}, {st["hp"]}, {st["atk"]}, {st["def"]}, '
            f'{st["spa"]}, {st["spd"]}, {st["spe"]}, {a1}, {a2}, {kg10}}},'
        )
    (OUT / "Species.inc").write_text("\n".join(rows) + "\n")
    print(f"species {len(rows)}")


def emit_moves(moves, move_ids, types):
    kind = {
        "EFFECT_LEVEL_DAMAGE": 1,
        "EFFECT_DRAGON_RAGE": 2,
        "EFFECT_SONICBOOM": 3,
        "EFFECT_SUPER_FANG": 4,
        "EFFECT_OHKO": 5,
        "EFFECT_MULTI_HIT": 6,
        "EFFECT_DOUBLE_HIT": 7,
        "EFFECT_TWINEEDLE": 7,
        "EFFECT_TRIPLE_KICK": 8,
    }
    rows = []
    max_id = max(move_ids.values())
    by_id = {v: k for k, v in move_ids.items()}
    for mid in range(max_id + 1):
        key = by_id.get(mid)
        if not key or key not in moves:
            rows.append("    {0},")
            continue
        mv = moves[key]
        name = pretty(key).title().replace(" ", "")
        # keep spaces for UI: "Comet Punch"
        name = pretty(key).title()
        if key == "MOVE_NONE":
            rows.append("    {0},")
            continue
        contact = 1 if "FLAG_MAKES_CONTACT" in mv["flags"] else 0
        hits = 3 if kind.get(mv["effect"], 0) == 6 else (2 if kind.get(mv["effect"], 0) == 7 else (3 if kind.get(mv["effect"], 0) == 8 else 1))
        rows.append(
            f'    {{{mid}, "{c_escape(name)}", {types.get(mv["type"], 0)}, {mv["power"]}, '
            f'{mv["priority"]}, {kind.get(mv["effect"], 0)}, {hits}, {contact}}},'
        )
    (OUT / "Moves.inc").write_text("\n".join(rows) + "\n")
    print(f"moves {len(rows)}")


def emit_pack(species, move_ids, items, trainer_ids, classes, parties, trainers, learned, loc, class_label):
    real = []
    for tid_name, meta in trainers.items():
        tid = trainer_ids.get(tid_name)
        if tid is None or tid < 89:
            continue
        mons = parties.get(meta["party"], [])
        if not mons:
            continue
        if all(m["species"] == "SPECIES_EKANS" and m["lvl"] == 5 for m in mons) and not meta["name"]:
            continue
        real.append((tid, tid_name, meta, mons))
    real.sort()

    mon_rows = []
    trainer_rows = []
    loc_map = defaultdict(list)
    mon_off = 0
    for tid, tid_name, meta, mons in real:
        start = mon_off
        for mon in mons:
            mv = mon["moves"]
            if len(mv) < 4:
                mv = default_moves(learned.get(mon["species"], []), mon["lvl"])
            while len(mv) < 4:
                mv.append("MOVE_NONE")
            sid = species.get(mon["species"], 0)
            item = items.get(mon["item"], 0)
            mids = [move_ids.get(x, 0) for x in mv[:4]]
            mon_rows.append(
                f"    {{{sid}, {mon['lvl']}, {mon['iv']}, {item}, {{{mids[0]}, {mids[1]}, {mids[2]}, {mids[3]}}}}},"
            )
            mon_off += 1
        label = loc.get(tid_name, "Unknown")
        loc_map[label].append(tid)
        tname = meta["name"] if meta["name"] else pretty(tid_name).title()
        cls = class_label.get(meta["cls"], pretty(meta["cls"]).title())
        mandatory = 1 if meta["cls"] in (
            "TRAINER_CLASS_LEADER",
            "TRAINER_CLASS_ELITE_FOUR",
            "TRAINER_CLASS_CHAMPION",
            "TRAINER_CLASS_RIVAL",
            "TRAINER_CLASS_BOSS",
        ) else 0
        trainer_rows.append(
            f'    {{{tid}, "{c_escape(tname)}", "{c_escape(cls)}", "{c_escape(label)}", '
            f"{len(mons)}, {start}, {mandatory}}},"
        )

    loc_rows = []
    id_rows = []
    loc_off = 0
    for name, ids in sorted(loc_map.items(), key=lambda x: x[0].lower()):
        id_rows.extend(f"    {i}," for i in ids)
        loc_rows.append(f'    {{"{c_escape(name)}", {len(ids)}, {loc_off}}},')
        loc_off += len(ids)

    (OUT / "PackFrlgMons.inc").write_text("\n".join(mon_rows) + "\n")
    (OUT / "PackFrlgTrainers.inc").write_text("\n".join(trainer_rows) + "\n")
    (OUT / "PackFrlgLocIds.inc").write_text("\n".join(id_rows) + "\n")
    (OUT / "PackFrlgLocs.inc").write_text("\n".join(loc_rows) + "\n")
    print(f"trainers {len(trainer_rows)} mons {len(mon_rows)} locs {len(loc_rows)}")


def emit_types(types):
    triples = []
    text = read("src/battle_main.c")
    m = re.search(r"gTypeEffectiveness\[336\]\s*=\s*\{(.*?)\};", text, re.S)
    body = m.group(1)
    toks = [t.strip() for t in body.split(",") if t.strip()]
    for i in range(0, len(toks) - 2, 3):
        a, d, mul = toks[i], toks[i + 1], toks[i + 2]
        if "FORESIGHT" in a or "ENDTABLE" in a:
            continue
        triples.append((types[a], types[d], {"TYPE_MUL_NO_EFFECT": 0, "TYPE_MUL_NOT_EFFECTIVE": 5, "TYPE_MUL_NORMAL": 10, "TYPE_MUL_SUPER_EFFECTIVE": 20}[mul]))
    n = 19
    chart = [[10] * n for _ in range(n)]
    for a, d, mul in triples:
        if a < n and d < n:
            chart[a][d] = mul
    fairy = 18
    chart6 = [row[:] for row in chart]
    chart6[fairy][16] = 20
    chart6[fairy][1] = 20
    chart6[fairy][17] = 20
    chart6[fairy][10] = 5
    chart6[fairy][3] = 5
    chart6[fairy][8] = 5
    chart6[16][fairy] = 0
    chart6[8][fairy] = 20
    chart6[3][fairy] = 20
    chart6[1][fairy] = 5
    chart6[6][fairy] = 5
    chart6[17][fairy] = 5
    chart6[7][8] = 10
    chart6[17][8] = 10

    def dump(name, grid):
        lines = [f"constexpr int8_t {name}[19][19] = {{"]
        for row in grid:
            lines.append("    {" + ", ".join(str(x) for x in row) + "},")
        lines.append("};")
        return "\n".join(lines)

    (OUT / "TypeChart.inc").write_text(dump("kChartAdv", chart) + "\n" + dump("kChartXy", chart6) + "\n")


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    species = defines("include/constants/species.h", "SPECIES_")
    moves = defines("include/constants/moves.h", "MOVE_")
    types = defines("include/constants/pokemon.h", "TYPE_")
    abilities = defines("include/constants/abilities.h", "ABILITY_")
    items = defines("include/constants/items.h", "ITEM_")
    trainer_ids = defines("include/constants/opponents.h", "TRAINER_")
    classes = defines("include/constants/trainers.h", "TRAINER_CLASS_")
    types["TYPE_FAIRY"] = 18
    emit_types(types)
    emit_dex(species, species_stats(), weights(), abilities, types)
    emit_moves(battle_moves(), moves, types)
    emit_pack(
        species,
        moves,
        items,
        trainer_ids,
        classes,
        parse_parties(),
        parse_trainers(),
        learnsets(),
        trainer_locations(),
        class_names(),
    )


if __name__ == "__main__":
    main()
