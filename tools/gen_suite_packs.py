#!/usr/bin/env python3
import re
import struct
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from gen_calc_nds import (
    apply_default_moves,
    c_escape,
    emit_pack,
    find_learnsets,
    names_from_rom,
    parse_narc,
    parse_nds_files,
    parse_trdata,
    parse_trpoke,
)
from gen5_text import parse_gen5_text
from trainer_locs import overlay_locs, species_names_from_rom

ROMS = Path.home() / "test_roms"
OUT = ROOT / "src/calc/data"


def u16(b, o):
    return struct.unpack_from("<H", b, o)[0]


def slugify(token):
    s = token.replace("SPECIES_", "").replace("MOVE_", "").replace("TRAINER_", "")
    return s.replace("_", " ").title()


def load_list(path, prefix):
    names = []
    if not path.exists():
        return names
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        token = line.strip().split()[0] if line.strip() else ""
        if not token or token.startswith("//") or token.startswith("#"):
            continue
        if prefix and not token.startswith(prefix):
            continue
        names.append(slugify(token))
    return names


def load_trainer_defines(path):
    names = {}
    if not path.exists():
        return names
    for m in re.finditer(r"#define\s+(TRAINER_\w+)\s+(\d+)", path.read_text(encoding="utf-8", errors="replace")):
        names[int(m.group(2))] = slugify(m.group(1))
    return names


def map_type(t, gen5):
    if gen5 and t >= 9:
        return t + 1
    return t


def emit_dex_and_moves():
    files = parse_nds_files((ROMS / "platinum-U.nds").read_bytes())
    personal = parse_narc(files["/poketool/personal/pl_personal.narc"])
    waza = parse_narc(files["/poketool/waza/pl_waza_tbl.narc"])
    b2 = parse_nds_files((ROMS / "black2-U.nds").read_bytes())
    b2_personal = parse_narc(b2["/a/0/1/6"])
    species_names = load_list(Path("/tmp/pret/pokeplatinum/generated/species.txt"), "SPECIES_")
    move_names = load_list(Path("/tmp/pret/pokeplatinum/generated/moves.txt"), "MOVE_")
    nat = ["    {0},"]
    for i in range(1, 650):
        rec = None
        gen5 = False
        if i < len(personal) and len(personal[i]) >= 24:
            rec = personal[i]
        elif i < len(b2_personal) and len(b2_personal[i]) >= 28:
            rec = b2_personal[i]
            gen5 = True
        if rec is None:
            nat.append("    {0},")
            continue
        name = species_names[i].replace(" ", "-").lower() if i < len(species_names) else f"species-{i}"
        name = name.replace(".", "").replace("'", "")
        t1 = map_type(rec[6], gen5)
        t2 = map_type(rec[7], gen5)
        if gen5:
            a1, a2 = rec[24], rec[25]
        else:
            a1, a2 = rec[22], rec[23]
        nat.append(
            f'    {{{i}, "{name}", {t1}, {t2}, {rec[0]}, {rec[1]}, {rec[2]}, {rec[4]}, {rec[5]}, {rec[3]}, {a1}, {a2}, 0}},'
        )
    (OUT / "SpeciesNat.inc").write_text("\n".join(nat) + "\n")
    extra = []
    for i in range(355, len(waza)):
        rec = waza[i]
        if len(rec) < 12:
            extra.append("    {0},")
            continue
        name = move_names[i] if i < len(move_names) else f"Move {i}"
        split = rec[2]
        extra.append(
            f'    {{{i}, "{name}", {rec[4]}, {rec[3]}, {struct.unpack_from("b", rec, 10)[0] if len(rec) > 10 else 0}, '
            f"{9 if rec[3] == 0 else 0}, 1, {1 if rec[11] & 1 else 0}, {split}}},"
        )
    (OUT / "MovesNat.inc").write_text("\n".join(extra) + "\n")
    print("dex", 649, "moves+", len(extra))


def move_names_from_rom(files):
    msg = files.get("/a/0/0/2")
    if not msg or msg[:4] != b"NARC":
        return []
    for blob in parse_narc(msg):
        names = parse_gen5_text(blob)
        if len(names) > 500 and names[1].lower() == "pound":
            return names
    return []


def find_waza(files):
    blob = files.get("/a/0/2/1")
    if blob and blob[:4] == b"NARC":
        entries = parse_narc(blob)
        if len(entries) > 500 and entries and len(entries[1]) == 36:
            return entries
    for data in files.values():
        if data[:4] != b"NARC":
            continue
        entries = parse_narc(data)
        if 500 <= len(entries) <= 800 and entries and len(entries[1]) == 36:
            return entries
    return []


def fill_gen5_nat(files):
    species = species_names_from_rom(files)
    blob = files.get("/a/0/1/6")
    personal = parse_narc(blob) if blob and blob[:4] == b"NARC" else []
    path = OUT / "SpeciesNat.inc"
    kept = []
    for line in path.read_text(encoding="utf-8").splitlines():
        m = re.match(r"\s+\{(\d+)", line)
        if m and int(m.group(1)) >= 494:
            continue
        if line:
            kept.append(line)
    last = min(649, len(personal) - 1) if personal else 493
    for i in range(494, last + 1):
        rec = personal[i] if i < len(personal) else b""
        slug = species[i] if i < len(species) and species[i] else f"species-{i}"
        slug = slug.replace(".", "").replace("'", "")
        if len(rec) < 26:
            kept.append(
                f'    {{{i}, "{c_escape(slug)}", 0, 0, 10, 10, 10, 10, 10, 10, 0, 0, 0}},'
            )
            continue
        t1 = map_type(rec[6], True)
        t2 = map_type(rec[7], True)
        kept.append(
            f'    {{{i}, "{c_escape(slug)}", {t1}, {t2}, {rec[0]}, {rec[1]}, {rec[2]}, '
            f"{rec[4]}, {rec[5]}, {rec[3]}, {rec[24]}, {rec[25]}, 0}},"
        )
    path.write_text("\n".join(kept) + "\n")
    moves = move_names_from_rom(files)
    waza = find_waza(files)
    if not moves or not waza:
        return
    cat_to_split = {0: 2, 1: 0, 2: 1}
    splits = ["255"] * max(len(waza), 1)
    splits[0] = "255"
    for i, rec in enumerate(waza):
        if i == 0 or len(rec) < 3:
            continue
        splits[i] = str(cat_to_split.get(rec[2], 255))
    (OUT / "MovesSplit.inc").write_text(",\n".join(splits) + ",\n")
    kept = []
    for line in (OUT / "MovesNat.inc").read_text(encoding="utf-8").splitlines():
        m = re.match(r"\s+\{(\d+),", line)
        if m and int(m.group(1)) >= 468:
            continue
        if line:
            kept.append(line)
    for i in range(468, len(waza)):
        rec = waza[i]
        if len(rec) < 8:
            kept.append("    {0},")
            continue
        name = moves[i] if i < len(moves) and moves[i] else f"Move {i}"
        split = cat_to_split.get(rec[2], 2)
        kind = 9 if rec[3] == 0 or rec[2] == 0 else 0
        prio = struct.unpack_from("b", rec, 6)[0]
        kept.append(
            f'    {{{i}, "{c_escape(name)}", {map_type(rec[0], True)}, {rec[3]}, {prio}, '
            f"{kind}, 1, 0, {split}}},"
        )
    (OUT / "MovesNat.inc").write_text("\n".join(kept) + "\n")


def names_for(prefix):
    if prefix == "Pt" or prefix == "Dp":
        lst = load_list(Path("/tmp/pret/pokeplatinum/generated/trainers.txt"), "TRAINER_")
        return lst
    if prefix == "Hgss":
        defs = load_trainer_defines(Path("/tmp/pret/pokeheartgold/include/constants/trainers.h"))
        n = max(defs) + 1 if defs else 0
        return [defs.get(i, f"Trainer {i}") for i in range(n)]
    return []


def extract_named(rom, prefix, title, dmg, trdata_path, trpoke_path):
    files = parse_nds_files(Path(rom).read_bytes())
    trdata = parse_narc(files[trdata_path])
    trpoke = parse_narc(files[trpoke_path])
    trainers = parse_trdata(trdata)
    parties = []
    for i, meta in enumerate(trainers):
        if not meta:
            parties.append([])
            continue
        raw = trpoke[i] if i < len(trpoke) else b""
        parties.append(parse_trpoke(raw, meta["kind"], meta["count"], dmg))
    apply_default_moves(trainers, parties, find_learnsets(files))
    names, classes = names_from_rom(files, trainers, "")
    preset = names_for(prefix)
    if preset:
        names = preset
    locs = overlay_locs(ROOT, prefix, trainers, parties, names, files)
    if dmg >= 5:
        fill_gen5_nat(files)
    emit_pack(OUT, prefix, title, dmg, trainers, parties, names, classes, locs)


def write_registry():
    (OUT / "PackRegistry.inc").write_text(
        """
if (isFrlg(uuid)) {
    return &kFrlgPack;
}
if (uuid == kRubyUsUuid || uuid == kRubyUs11Uuid || uuid == kSapphireUsUuid) {
    return &kRsPack;
}
if (uuid == kEmeraldUsUuid) {
    return &kEmPack;
}
if (uuid == kDiamondUsUuid || uuid == kPearlUsUuid) {
    return &kDpPack;
}
if (uuid == kPlatinumUsUuid || uuid == kPlatinumUs11Uuid) {
    return &kPtPack;
}
if (uuid == kHeartGoldUsUuid || uuid == kSoulSilverUsUuid) {
    return &kHgssPack;
}
if (uuid == kBlackUsUuid || uuid == kWhiteUsUuid) {
    return &kBwPack;
}
if (uuid == kBlack2UsUuid || uuid == kWhite2UsUuid) {
    return &kB2w2Pack;
}
"""
    )


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    emit_dex_and_moves()
    extract_named(ROMS / "diamond-1_13-U.nds", "Dp", "DIAMOND / PEARL", 4, "/poketool/trainer/trdata.narc", "/poketool/trainer/trpoke.narc")
    extract_named(ROMS / "platinum-U.nds", "Pt", "PLATINUM", 4, "/poketool/trainer/trdata.narc", "/poketool/trainer/trpoke.narc")
    extract_named(ROMS / "heartgold-U.nds", "Hgss", "HEARTGOLD / SOULSILVER", 4, "/a/0/5/5", "/a/0/5/6")
    extract_named(ROMS / "black-U.nds", "Bw", "BLACK / WHITE", 5, "/a/0/9/2", "/a/0/9/3")
    extract_named(ROMS / "black2-U.nds", "B2w2", "BLACK 2 / WHITE 2", 5, "/a/0/9/1", "/a/0/9/2")
    write_registry()
    print("packs written")


if __name__ == "__main__":
    main()
