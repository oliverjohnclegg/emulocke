#!/usr/bin/env python3
import struct

_PKMN = 0x2486
_PKMN2 = 0x2487
_MALE = 0x246D
_FEMALE = 0x246E
_TERM = 0xFFFF
_BREAK = 0xFFFE


def _u16(data, off):
    return struct.unpack_from("<H", data, off)[0]


def _u32(data, off):
    return struct.unpack_from("<I", data, off)[0]


def _glyph(code):
    if code == _PKMN:
        return "PKMN"
    if code == _PKMN2:
        return ""
    if code == _MALE:
        return "M"
    if code == _FEMALE:
        return "F"
    if code in (0x2018, 0x2019):
        return "'"
    if code == 0x2014:
        return "-"
    if code == _BREAK:
        return " "
    if 32 <= code < 0xF000:
        return chr(code)
    return ""


def parse_gen5_text(data):
    if len(data) < 16:
        return []
    line_count = _u16(data, 2)
    if line_count == 0 or line_count > 4000:
        return []
    sect_off = _u32(data, 0x0C)
    if sect_off > len(data) or len(data) - sect_off < 4 + line_count * 8:
        return []
    table = sect_off + 4
    out = []
    for i in range(line_count):
        off, slen = struct.unpack_from("<IH", data, table + i * 8)[:2]
        abs_off = sect_off + off
        if slen > 1024 or abs_off > len(data) or (len(data) - abs_off) // 2 < slen:
            out.append("")
            continue
        key = (0x7C89 + 0x2983 * i) & 0xFFFF
        chars = []
        skip_pkmn = False
        for j in range(slen):
            code = _u16(data, abs_off + j * 2) ^ key
            key = ((key << 3) | (key >> 13)) & 0xFFFF
            if code == _TERM:
                break
            if skip_pkmn:
                skip_pkmn = False
                if code == _PKMN2:
                    continue
            if code == _PKMN:
                skip_pkmn = True
            chars.append(_glyph(code))
        out.append("".join(chars).strip())
    return out


def pick_trainer_names(entries, expect):
    best = []
    best_named = -1
    for blob in entries:
        strings = parse_gen5_text(blob)
        if abs(len(strings) - expect) > 8:
            continue
        named = sum(1 for s in strings if s and s[0].isalpha() and len(s) <= 16)
        if named > best_named:
            best = strings
            best_named = named
    return best if best_named > expect // 4 else []


def pick_class_names(entries):
    for blob in entries:
        strings = parse_gen5_text(blob)
        if 80 <= len(strings) <= 160 and "Youngster" in strings and "Lass" in strings:
            return strings
    return []
