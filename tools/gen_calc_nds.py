#!/usr/bin/env python3
import argparse
import struct
import sys
from collections import defaultdict
from pathlib import Path

_TOOLS = Path(__file__).resolve().parent
if str(_TOOLS) not in sys.path:
    sys.path.insert(0, str(_TOOLS))
from gen5_text import pick_class_names, pick_trainer_names

LEARNED_MOVES = 4


def u16(b, o):
    return struct.unpack_from("<H", b, o)[0]


def u32(b, o):
    return struct.unpack_from("<I", b, o)[0]


def parse_narc(blob):
    if blob[:4] != b"NARC":
        return []
    fat_off = 0x10
    if blob[fat_off : fat_off + 4] != b"BTAF":
        return []
    count = u16(blob, fat_off + 8)
    entries = []
    fimg = blob.find(b"GMIF")
    if fimg < 0:
        return []
    data_off = fimg + 8
    for i in range(count):
        start = u32(blob, fat_off + 12 + i * 8)
        end = u32(blob, fat_off + 16 + i * 8)
        entries.append(blob[data_off + start : data_off + end])
    return entries


def parse_nds_files(rom):
    fnt_off, fnt_size = u32(rom, 0x40), u32(rom, 0x44)
    fat_off = u32(rom, 0x48)
    fat_size = u32(rom, 0x4C)
    fnt = rom[fnt_off : fnt_off + fnt_size]
    fat = rom[fat_off : fat_off + fat_size]
    dir_count = u16(fnt, 6) if len(fnt) >= 8 else 1
    files = {}

    def walk(dir_id, prefix):
        idx = dir_id & 0xFFF
        off = u32(fnt, idx * 8)
        file_id = u16(fnt, idx * 8 + 4)
        p = off
        while p < len(fnt):
            typ = fnt[p]
            p += 1
            if typ == 0:
                break
            nlen = typ & 0x7F
            name = fnt[p : p + nlen].decode("ascii", "replace")
            p += nlen
            if typ & 0x80:
                sub = u16(fnt, p)
                p += 2
                walk(sub, prefix + name + "/")
            else:
                if file_id * 8 + 8 <= len(fat):
                    start, end = struct.unpack_from("<II", fat, file_id * 8)
                    files[prefix + name] = rom[start:end]
                file_id += 1

    walk(0xF000, "/")
    return files


def find_narc(files, *needles):
    for path, blob in files.items():
        low = path.lower()
        if all(n in low for n in needles) and blob[:4] == b"NARC":
            return parse_narc(blob)
    return []


def parse_trdata(entries):
    trainers = []
    for i, raw in enumerate(entries):
        if len(raw) < 20:
            trainers.append(None)
            continue
        kind, cls, sprite, count = raw[0], raw[1], raw[2], raw[3]
        items = [u16(raw, 4 + j * 2) for j in range(4)]
        ai = u32(raw, 12)
        battle = u32(raw, 16) if len(raw) >= 20 else 0
        trainers.append(
            {
                "kind": kind,
                "cls": cls,
                "count": min(count, 6),
                "items": items,
                "ai": ai,
                "battle": battle,
            }
        )
    return trainers


def parse_trpoke5(raw, kind, count):
    has_moves = bool(kind & 1)
    has_item = bool(kind & 2)
    mons = []
    off = 0
    for _ in range(count):
        if off + 8 > len(raw):
            break
        iv = raw[off]
        level = u16(raw, off + 2)
        species = u16(raw, off + 4) & 0x7FF
        off += 8
        item = 0
        moves = [0, 0, 0, 0]
        if has_item:
            if off + 2 > len(raw):
                break
            item = u16(raw, off)
            off += 2
        if has_moves:
            if off + 8 > len(raw):
                break
            moves = [u16(raw, off + j * 2) for j in range(4)]
            off += 8
        mons.append({"iv": iv, "lvl": level, "species": species, "item": item, "moves": moves})
    return mons


def parse_trpoke(raw, kind, count, gen=4):
    if gen >= 5:
        return parse_trpoke5(raw, kind, count)
    mons = []
    off = 0

    def take(n):
        nonlocal off
        if off + n > len(raw):
            return None
        chunk = raw[off : off + n]
        off += n
        return chunk

    for _ in range(count):
        if kind == 0:
            chunk = take(8)
            if not chunk:
                break
            iv, level, species = u16(chunk, 0), u16(chunk, 2), u16(chunk, 4) & 0x3FF
            mons.append({"iv": iv, "lvl": level, "species": species, "item": 0, "moves": [0, 0, 0, 0]})
        elif kind == 1:
            chunk = take(8 + LEARNED_MOVES * 2 + 2)
            if not chunk:
                break
            iv, level, species = u16(chunk, 0), u16(chunk, 2), u16(chunk, 4) & 0x3FF
            moves = [u16(chunk, 6 + j * 2) for j in range(4)]
            mons.append({"iv": iv, "lvl": level, "species": species, "item": 0, "moves": moves})
        elif kind == 2:
            chunk = take(10)
            if not chunk:
                break
            iv, level, species = u16(chunk, 0), u16(chunk, 2), u16(chunk, 4) & 0x3FF
            item = u16(chunk, 6)
            mons.append({"iv": iv, "lvl": level, "species": species, "item": item, "moves": [0, 0, 0, 0]})
        else:
            chunk = take(8 + 2 + LEARNED_MOVES * 2 + 2)
            if not chunk:
                break
            iv, level, species = u16(chunk, 0), u16(chunk, 2), u16(chunk, 4) & 0x3FF
            item = u16(chunk, 6)
            moves = [u16(chunk, 8 + j * 2) for j in range(4)]
            mons.append({"iv": iv, "lvl": level, "species": species, "item": item, "moves": moves})
    return mons


def parse_personal(entries, rec_size):
    rows = []
    for raw in entries:
        if len(raw) < 10:
            rows.append(None)
            continue
        rec = raw[:rec_size] if rec_size else raw
        rows.append(
            {
                "hp": rec[0],
                "atk": rec[1],
                "def": rec[2],
                "spe": rec[3],
                "spa": rec[4],
                "spd": rec[5],
                "t1": rec[6],
                "t2": rec[7],
                "a1": rec[22] if len(rec) > 23 else 0,
                "a2": rec[23] if len(rec) > 23 else 0,
            }
        )
    return rows


def learnset_at(raw, level):
    got = []
    off = 0
    while off + 4 <= len(raw):
        mv = u16(raw, off)
        lv = u16(raw, off + 2)
        off += 4
        if mv == 0xFFFF or lv == 0xFFFF:
            break
        if lv <= level and mv:
            got.append(mv)
    if len(got) > 4:
        got = got[-4:]
    while len(got) < 4:
        got.append(0)
    return got


def find_learnsets(files):
    blob = files.get("/a/0/1/8")
    if blob and blob[:4] == b"NARC":
        entries = parse_narc(blob)
        if len(entries) > 290 and len(entries[290]) >= 8 and u16(entries[290], 0) == 10:
            return entries
    for data in files.values():
        if data[:4] != b"NARC":
            continue
        entries = parse_narc(data)
        if 640 <= len(entries) <= 720 and len(entries) > 290 and len(entries[290]) >= 8:
            if u16(entries[290], 0) == 10 and u16(entries[290], 2) == 1:
                return entries
    return []


def apply_default_moves(trainers, parties, learnsets):
    if not learnsets:
        return
    for tid, meta in enumerate(trainers):
        if not meta or (meta["kind"] & 1) or tid >= len(parties):
            continue
        for mon in parties[tid]:
            if any(mon["moves"]):
                continue
            sid = mon["species"]
            raw = learnsets[sid] if sid < len(learnsets) else b""
            mon["moves"] = learnset_at(raw, mon["lvl"])


def c_escape(s):
    return s.replace("\\", "\\\\").replace('"', '\\"')


def pretty_trainer(idx, names):
    if 0 <= idx < len(names) and names[idx]:
        return names[idx]
    return f"Trainer {idx}"


def names_from_rom(files, trainers, names_path=""):
    names = load_names(names_path)
    msg = files.get("/a/0/0/2")
    entries = parse_narc(msg) if msg and msg[:4] == b"NARC" else []
    if not names:
        names = pick_trainer_names(entries, len(trainers))
    classes = pick_class_names(entries)
    if not classes:
        classes = [f"Class {i}" for i in range(256)]
    return names, classes


def emit_pack(out, prefix, title, dmg_gen, trainers, parties, names, classes, locs=None):
    mon_rows = []
    trainer_rows = []
    loc_map = defaultdict(list)
    mon_off = 0
    locs = locs or {}
    for tid, meta in enumerate(trainers):
        if not meta or meta["count"] == 0:
            continue
        mons = parties[tid] if tid < len(parties) else []
        if not mons:
            continue
        start = mon_off
        for mon in mons:
            mv = mon["moves"] + [0, 0, 0, 0]
            iv = min(int(mon["iv"]) & 0xFF, 255)
            lvl = min(max(int(mon["lvl"]) & 0xFF, 1), 100)
            mon_rows.append(
                "    {%d, %d, %d, %d, {%d, %d, %d, %d}},"
                % (mon["species"] & 0x7FF, lvl, iv, mon["item"] & 0xFFFF,
                   mv[0] & 0xFFFF, mv[1] & 0xFFFF, mv[2] & 0xFFFF, mv[3] & 0xFFFF)
            )
            mon_off += 1
        tname = pretty_trainer(tid, names)
        cls = classes[meta["cls"]] if meta["cls"] < len(classes) else "Trainer"
        mandatory = 1 if meta["cls"] in (2, 3, 4, 5, 6, 7, 8, 9, 10) else 0
        loc = locs.get(tid, "")
        trainer_rows.append(
            f'    {{{tid}, "{c_escape(tname)}", "{c_escape(cls)}", "{c_escape(loc)}", '
            f"{len(mons)}, {start}, {mandatory}, {meta['ai']}}},"
        )
        if loc:
            loc_map[loc].append(tid)
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
    out.mkdir(parents=True, exist_ok=True)
    (out / f"Pack{prefix}Mons.inc").write_text("\n".join(mon_rows) + "\n")
    (out / f"Pack{prefix}Trainers.inc").write_text("\n".join(trainer_rows) + "\n")
    (out / f"Pack{prefix}LocIds.inc").write_text("\n".join(id_rows) + "\n")
    (out / f"Pack{prefix}Locs.inc").write_text("\n".join(loc_rows) + "\n")
    print(f"{prefix} trainers {len(trainer_rows)} mons {len(mon_rows)}")


def load_names(path):
    if not path or not Path(path).exists():
        return []
    names = []
    for line in Path(path).read_text(encoding="utf-8", errors="replace").splitlines():
        token = line.strip()
        if not token or token.startswith("#"):
            continue
        pretty = token.replace("TRAINER_", "").replace("_", " ").title()
        names.append(pretty)
    return names


def extract(rom_path, out, prefix, title, dmg_gen, names_path, rec_size=44):
    rom = Path(rom_path).read_bytes()
    files = parse_nds_files(rom)
    trdata = find_narc(files, "trdata")
    trpoke = find_narc(files, "trpoke")
    if not trdata:
        trdata = find_narc(files, "tr/trdata")
    if not trdata or not trpoke:
        for path, blob in files.items():
            if blob[:4] != b"NARC":
                continue
            entries = parse_narc(blob)
            if len(entries) > 200 and entries and 16 <= len(entries[1]) <= 80:
                sizes = {len(e) for e in entries[1:20]}
                if len(sizes) <= 3 and min(sizes) >= 16:
                    if not trdata:
                        trdata = entries
                    elif not trpoke:
                        trpoke = entries
    if not trdata or not trpoke:
        raise SystemExit(f"no trainer narc in {rom_path}")
    trainers = parse_trdata(trdata)
    parties = []
    for i, meta in enumerate(trainers):
        if not meta:
            parties.append([])
            continue
        raw = trpoke[i] if i < len(trpoke) else b""
        parties.append(parse_trpoke(raw, meta["kind"], meta["count"], dmg_gen))
    apply_default_moves(trainers, parties, find_learnsets(files))
    names, classes = names_from_rom(files, trainers, names_path)
    emit_pack(Path(out), prefix, title, dmg_gen, trainers, parties, names, classes)


def main():
    p = argparse.ArgumentParser()
    p.add_argument("rom")
    p.add_argument("out")
    p.add_argument("--prefix", required=True)
    p.add_argument("--title", default="")
    p.add_argument("--dmg", type=int, default=4)
    p.add_argument("--names", default="")
    args = p.parse_args()
    extract(args.rom, args.out, args.prefix, args.title, args.dmg, args.names)


if __name__ == "__main__":
    main()
