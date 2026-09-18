#!/usr/bin/env python3
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from gen_calc_nds import emit_pack, parse_narc, parse_nds_files, parse_trdata, parse_trpoke
from gen_suite_packs import extract_named, write_registry

OUT = ROOT / "src/calc/data"


def u16(b, o):
    return struct.unpack_from("<H", b, o)[0]


def u32(b, o):
    return struct.unpack_from("<I", b, o)[0]


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
    return "".join(out).strip() or "Trainer"


def parse_gba_party(rom, ptr, flags, count):
    if ptr < 0x08000000:
        return []
    off = ptr - 0x08000000
    mons = []
    for _ in range(count):
        if off + 8 > len(rom):
            break
        iv = u16(rom, off)
        lvl = rom[off + 2]
        if flags in (0, 2):
            species = u16(rom, off + 4)
            item = u16(rom, off + 6) if flags == 2 and off + 8 <= len(rom) else 0
            moves = [0, 0, 0, 0]
            off += 8
        else:
            species = u16(rom, off + 4)
            item = u16(rom, off + 6) if flags & 2 else 0
            move0 = off + (8 if flags & 2 else 6)
            moves = [u16(rom, move0 + j * 2) for j in range(4)] if move0 + 8 <= len(rom) else [0, 0, 0, 0]
            off += 16
        mons.append(
            {
                "species": species & 0x7FF,
                "lvl": max(1, min(lvl, 100)),
                "iv": min(iv & 0xFF, 255),
                "item": item,
                "moves": moves,
            }
        )
    return mons


def extract_gba(rom_path, prefix, title, dmg, table_off, limit):
    rom = Path(rom_path).read_bytes()
    trainers = []
    parties = []
    names = []
    for i in range(limit):
        rec = rom[table_off + i * 40 : table_off + i * 40 + 40]
        if len(rec) < 40:
            break
        flags, cls, size = rec[0] & 3, rec[1], rec[32]
        ptr = u32(rec, 36)
        if size > 6:
            break
        trainers.append({"kind": flags, "cls": cls, "count": size, "items": [0, 0, 0, 0], "ai": u32(rec, 28), "battle": 0})
        names.append(gen3_name(rec[4:16]))
        parties.append(parse_gba_party(rom, ptr, flags, size) if size else [])
    classes = [f"Class {i}" for i in range(256)]
    emit_pack(OUT, prefix, title, dmg, trainers, parties, names, classes)


def write_generated():
    packs = [
        ("Sg", "SACRED GOLD", 4),
        ("Renplat", "RENEGADE PLATINUM", 4),
        ("Ptkaizo", "PLATINUM KAIZO", 4),
        ("Blaze", "BLAZE BLACK", 5),
        ("Volt", "VOLT WHITE", 5),
        ("Vw2", "VOLT WHITE 2 REDUX", 5),
        ("Emkaizo", "EMERALD KAIZO", 3),
        ("Fro", "FIRE RED OMEGA", 3),
        ("Rr", "RADICAL RED", 8),
        ("Unbound", "UNBOUND", 8),
    ]
    lines = []
    for prefix, title, dmg in packs:
        lines += [
            f"constexpr PackMon k{prefix}Mons[] = {{",
            f'#include "calc/data/Pack{prefix}Mons.inc"',
            "};",
            f"constexpr PackTrainer k{prefix}Trainers[] = {{",
            f'#include "calc/data/Pack{prefix}Trainers.inc"',
            "};",
            f"constexpr uint16_t k{prefix}LocIds[] = {{",
            f'#include "calc/data/Pack{prefix}LocIds.inc"',
            "};",
            f"constexpr PackLocation k{prefix}Locs[] = {{",
            f'#include "calc/data/Pack{prefix}Locs.inc"',
            "};",
            f'constexpr CalcPack k{prefix}Pack{{"{title}", {dmg}, {dmg}, {dmg}, k{prefix}Mons, static_cast<int>(sizeof(k{prefix}Mons) / sizeof(k{prefix}Mons[0])), k{prefix}Trainers, static_cast<int>(sizeof(k{prefix}Trainers) / sizeof(k{prefix}Trainers[0])), k{prefix}LocIds, k{prefix}Locs, static_cast<int>(sizeof(k{prefix}Locs) / sizeof(k{prefix}Locs[0]))'
            + (
                ", nullptr, 0, kDrayano31Moves, static_cast<int>(sizeof(kDrayano31Moves) / sizeof(kDrayano31Moves[0]))"
                if prefix in ("Blaze", "Volt")
                else ""
            )
            + "};",
            "",
        ]
    (OUT / "PackGenerated.inc").write_text("\n".join(lines) + "\n")


def write_full_registry():
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
if (uuid == kSacredGoldUuid) {
    return &kSgPack;
}
if (uuid == kRenegadePlatinumUuid) {
    return &kRenplatPack;
}
if (uuid == kPlatinumKaizoUuid) {
    return &kPtkaizoPack;
}
if (uuid == kBlazeBlackUuid) {
    return &kBlazePack;
}
if (uuid == kVoltWhiteUuid) {
    return &kVoltPack;
}
if (uuid == kVoltWhite2ReduxUuid) {
    return &kVw2Pack;
}
if (uuid == kEmeraldKaizoUuid) {
    return &kEmkaizoPack;
}
if (uuid == kFireRedOmegaUuid) {
    return &kFroPack;
}
if (uuid == kRadicalRedUuid) {
    return &kRrPack;
}
if (uuid == kUnboundUuid) {
    return &kUnboundPack;
}
"""
    )


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    extract_gba("/tmp/hack_roms/emkaizo.gba", "Emkaizo", "EMERALD KAIZO", 3, 0x310030, 856)
    extract_gba("/tmp/hack_roms/fro.gba", "Fro", "FIRE RED OMEGA", 3, 0x24BB80 - 414 * 40, 800)
    extract_gba("/tmp/hack_roms/rr.gba", "Rr", "RADICAL RED", 8, 0x23EAC8, 800)
    extract_gba("/tmp/hack_roms/unbound.gba", "Unbound", "UNBOUND", 8, 0x23EAC8, 800)
    write_generated()
    write_full_registry()
    print("hack packs written")


if __name__ == "__main__":
    main()
