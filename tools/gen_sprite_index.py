#!/usr/bin/env python3
import json
import sys
import urllib.request
from pathlib import Path

req = urllib.request.Request(
    "https://pokeapi.co/api/v2/pokemon?limit=20000",
    headers={"User-Agent": "emulocke-sprite-index/1"},
)
with urllib.request.urlopen(req, timeout=120) as response:
    payload = json.load(response)

rows = []
for item in payload["results"]:
    pid = int(item["url"].rstrip("/").split("/")[-1])
    rows.append((item["name"], pid))
rows.sort()

out = Path(sys.argv[1] if len(sys.argv) > 1 else "src/poke/SpriteIndex.inc")
out.parent.mkdir(parents=True, exist_ok=True)
text = "".join(f'    {{"{slug}", {pid}}},\n' for slug, pid in rows)
out.write_text(text)
print(f"wrote {len(rows)} entries to {out}")
