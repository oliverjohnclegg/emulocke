#!/usr/bin/env python3
import csv
import json
import subprocess
import sys
import urllib.request
from pathlib import Path

ROOT = Path(sys.argv[1] if len(sys.argv) > 1 else Path(__file__).resolve().parents[1])
OUT = ROOT / "src" / "poke"
UA = {"User-Agent": "emulocke-dex/1"}
PKHEX = "https://raw.githubusercontent.com/kwsch/PKHeX/master/PKHeX.Core/Resources/byte/personal/"
POKEAPI = "https://raw.githubusercontent.com/PokeAPI/pokeapi/master/data/v2/csv/"


def fetch(url: str) -> bytes:
    req = urllib.request.Request(url, headers=UA)
    with urllib.request.urlopen(req, timeout=120) as response:
        return response.read()


def cstr(s: str) -> str:
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'


def write_names(path: Path, names: list[str]) -> None:
    path.write_text("".join(f"    {cstr(n)},\n" for n in names))
    print(f"wrote {len(names)} names to {path}")


def load_js_table(url: str, export_key: str) -> dict:
    js_path = Path("/tmp") / f"emulocke-{export_key}.js"
    js_path.write_bytes(fetch(url))
    script = (
        "const fs=require('fs');const vm=require('vm');const ctx={exports:{}};"
        "vm.runInNewContext(fs.readFileSync(process.argv[1],'utf8'), ctx);"
        f"process.stdout.write(JSON.stringify(ctx.exports.{export_key}));"
    )
    raw = subprocess.check_output(["node", "-e", script, str(js_path)], text=True)
    return json.loads(raw)


def names_by_num(table: dict, size: int) -> list[str]:
    out = [""] * size
    for row in table.values():
        num = row.get("num")
        name = row.get("name")
        if isinstance(num, int) and 0 <= num < size and name:
            out[num] = name
    return out


def parse_personal(blob: bytes, size: int, n: int, gender_off: int, growth_off: int, ab_off: int):
    rows = []
    count = len(blob) // size
    for i in range(min(n, count)):
        rec = blob[i * size : (i + 1) * size]
        hp, atk, df, spe, spa, spd = rec[0:6]
        rows.append(
            {
                "hp": hp,
                "atk": atk,
                "def": df,
                "spa": spa,
                "spd": spd,
                "spe": spe,
                "gender": rec[gender_off],
                "growth": rec[growth_off],
                "ab0": rec[ab_off],
                "ab1": rec[ab_off + 1],
            }
        )
    return rows


def item_names() -> dict[int, str]:
    names = {}
    text = fetch(POKEAPI + "item_names.csv").decode()
    for row in csv.DictReader(text.splitlines()):
        if row["local_language_id"] == "9":
            names[int(row["item_id"])] = row["name"]
    return names


def item_indices(generation: int) -> dict[int, int]:
    text = fetch(POKEAPI + "item_game_indices.csv").decode()
    out = {}
    for row in csv.DictReader(text.splitlines()):
        if int(row["generation_id"]) == generation:
            out[int(row["game_index"])] = int(row["item_id"])
    return out


def fill_items(generation: int, size: int, showdown: list[str], poke_names: dict[int, str], dest: list[str]) -> None:
    for game_index, item_id in item_indices(generation).items():
        if game_index >= size:
            continue
        name = poke_names.get(item_id, "")
        if generation >= 4 and game_index < len(showdown) and showdown[game_index]:
            name = showdown[game_index]
        dest[game_index] = name


def main() -> None:
    OUT.mkdir(parents=True, exist_ok=True)
    moves = json.loads(fetch("https://play.pokemonshowdown.com/data/moves.json"))
    move_names = names_by_num(moves, 600)
    move_names[0] = ""
    write_names(OUT / "Moves.inc", move_names)

    abilities = load_js_table("https://play.pokemonshowdown.com/data/abilities.js", "BattleAbilities")
    ability_names = names_by_num(abilities, 256)
    ability_names[0] = ""
    write_names(OUT / "Abilities.inc", ability_names)

    items = load_js_table("https://play.pokemonshowdown.com/data/items.js", "BattleItems")
    showdown_items = names_by_num(items, 640)
    poke_names = item_names()
    gen3 = [""] * 377
    fill_items(3, 377, showdown_items, poke_names, gen3)
    write_names(OUT / "Gen3Items.inc", gen3)
    gen45 = [""] * 640
    fill_items(4, 640, showdown_items, poke_names, gen45)
    fill_items(5, 640, showdown_items, poke_names, gen45)
    write_names(OUT / "Gen45Items.inc", gen45)

    fr = parse_personal(fetch(PKHEX + "personal_fr"), 28, 387, 0x10, 0x13, 0x16)
    b2 = parse_personal(fetch(PKHEX + "personal_b2w2"), 76, 650, 0x12, 0x15, 0x18)
    lines = ["    {0, 0, 0, 0, 0, 0, 255, 0, 0, 0},\n"]
    for nat in range(1, 650):
        src = b2[nat] if nat < len(b2) else None
        if src is None:
            lines.append("    {0, 0, 0, 0, 0, 0, 255, 0, 0, 0},\n")
            continue
        ab0, ab1 = src["ab0"], src["ab1"]
        if nat < len(fr):
            ab0, ab1 = fr[nat]["ab0"], fr[nat]["ab1"]
        lines.append(
            f'    {{{src["hp"]}, {src["atk"]}, {src["def"]}, {src["spa"]}, {src["spd"]}, {src["spe"]}, '
            f'{src["gender"]}, {src["growth"]}, {ab0}, {ab1}}},\n'
        )
    (OUT / "SpeciesDex.inc").write_text("".join(lines))
    print(f"wrote 650 species to {OUT / 'SpeciesDex.inc'}")


if __name__ == "__main__":
    main()
