#!/usr/bin/env python3
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DATA = ROOT / "src/tracker/data"
OUT = ROOT / "src/tracker/generated"
FAMILY = {
    "rs": "rse",
    "em": "rse",
    "dp": "dp",
    "pt": "pt",
    "hgss": "hgss",
    "bw": "bw",
    "b2w2": "b2w2",
    "blaze": "blazevolt",
    "volt": "blazevolt",
    "blazevolt2": "vw2",
    "blazevolt2-challenge": "vw2",
    "sacredgold": "sacredgold",
    "renplat": "renegade",
    "emkaizo": "emkaizo",
    "emrunbun": "runbun",
    "incem": "incem",
    "rr": "rr",
    "rr-hardcore": "rr",
    "rr-easy": "rr",
    "unbound": "unbound",
    "unbound-easy": "unbound",
    "unbound-expert": "unbound",
    "unbound-insane": "unbound",
    "fro": "fro",
    "platinum-kaizo": "pkaizo",
}


def ident(s):
    out = []
    for c in s:
        if c.isalnum():
            out.append(c)
        else:
            out.append("_")
    t = "".join(out)
    if t and t[0].isdigit():
        t = "n" + t
    return t or "x"


def cpp_str(s):
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'


def boss_kind(s):
    return {
        "gym": "Gym",
        "rival": "Rival",
        "elitefour": "EliteFour",
        "evilteam": "EvilTeam",
        "miniboss": "MiniBoss",
    }.get(s, "None")


def emit_atlas(data):
    aid = data["id"]
    prefix = ident(aid)
    teams = []
    team_lines = []
    stops_pre = []
    met_names = {}
    met_i = 0
    stop_rows = []
    for i, stop in enumerate(data["stops"]):
        team = stop.get("team") or []
        team_sym = "nullptr"
        team_count = 0
        if team:
            team_sym = f"kTeam_{prefix}_{i}"
            team_count = len(team)
            rows = []
            for mon in team:
                slug = mon["slug"]
                lock = int(mon.get("lock") or 0)
                rows.append(f'    {{{cpp_str(slug)}, {lock}}}')
            team_lines.append(f"constexpr emulocke::BossMon {team_sym}[] = {{")
            team_lines.append(",\n".join(rows))
            team_lines.append("};")
            teams.append(team_sym)
        mets = stop.get("mets") or []
        met_sym = "nullptr"
        met_count = 0
        if mets:
            key = tuple(int(x) for x in mets)
            if key not in met_names:
                name = f"kMet_{prefix}_{met_i}"
                met_i += 1
                met_names[key] = name
                stops_pre.append(
                    f"constexpr uint16_t {name}[] = {{{', '.join(str(x) for x in key)}}};"
                )
            met_sym = met_names[key]
            met_count = len(mets)
        kind = "Boss" if stop.get("kind") == "boss" else "Encounter"
        catch = {"starter": "Starter", "met": "Met"}.get(stop.get("catch"), "None")
        bk = boss_kind(stop.get("boss") or "")
        defeat = int(stop.get("defeat") or 0)
        span = int(stop.get("span") or 0)
        gym = int(stop.get("gym") or 0)
        stop_rows.append(
            "    {"
            f"{cpp_str(stop['id'])}, emulocke::TrackerStopKind::{kind}, {cpp_str(stop['name'])}, "
            f"{cpp_str(stop.get('locale') or '')}, emulocke::BossKind::{bk}, "
            f"emulocke::CatchKind::{catch}, {met_sym}, {met_count}, {team_sym}, {team_count}, "
            f"{defeat}, {span}, {gym}"
            "}"
        )
    starters = [int(x) for x in data.get("starters") or []]
    if starters:
        stops_pre.append(
            f"constexpr uint16_t kStarters_{prefix}[] = {{{', '.join(str(x) for x in starters)}}};"
        )
    stops_pre.append(f"constexpr emulocke::TrackerStop kStops_{prefix}[] = {{")
    stops_pre.append(",\n".join(stop_rows))
    stops_pre.append("};")
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT / f"{aid}_teams.inc").write_text("\n".join(team_lines) + "\n")
    (OUT / f"{aid}_stops.inc").write_text("\n".join(stops_pre) + "\n")
    family = FAMILY.get(aid, aid.replace("-", ""))
    wrap_dir = ROOT / "src/tracker" / family
    wrap_dir.mkdir(parents=True, exist_ok=True)
    fn = ident(aid)
    wrap = f'''#include "tracker/Atlas.hpp"

namespace emulocke {{
namespace {{
#include "tracker/generated/{aid}_teams.inc"
#include "tracker/generated/{aid}_stops.inc"
}}

const TrackerAtlas& {fn}Atlas() {{
    static const TrackerAtlas atlas{{"{aid}", kStops_{prefix},
        {f"kStarters_{prefix}" if starters else "{{}}" }}};
    return atlas;
}}

}}
'''
    (wrap_dir / f"{fn}.cpp").write_text(wrap)
    return fn, aid


def main():
    decls = []
    for path in sorted(DATA.glob("*.json")):
        data = json.loads(path.read_text())
        fn, aid = emit_atlas(data)
        decls.append(f"const TrackerAtlas& {fn}Atlas();")
    header = "#pragma once\n\n#include \"tracker/Atlas.hpp\"\n\nnamespace emulocke {\n\n"
    header += "\n".join(decls) + "\n\n}\n"
    (ROOT / "src/tracker/Atlases.hpp").write_text(header)
    print(f"wrote {len(decls)} atlases")


if __name__ == "__main__":
    main()
