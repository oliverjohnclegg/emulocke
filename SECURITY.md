# Security

Report host bugs privately. Don't open a public issue for a vulnerability in dump import, patch apply, save handling, PNG fetch, prefs, or CI.

Email: olliejaclegg@gmail.com

## Scope

The Emulocke desktop host and its GitHub Actions workflows. Untrusted input is user dumps, `.sav` files, patches, HTTPS PNGs, `prefs.ini`, run metadata, and emulator RAM.

## What CI already gates

Parsers fail closed: size caps, bounds checks, checksums. Every PR runs `linux-x64`, `win-x64`, `linux-asan-ubsan`, `clang-tidy`, and `libfuzzer-smoke`. A Vanguard or Stable zip waits on those jobs. The 14 September 2026 audit is [docs/security/audit-2026-09-14.md](docs/security/audit-2026-09-14.md). Agent C++ work follows `.cursor/rules/securitystandards.mdc`.

## Out of scope

Nintendo ROMs, BIOS, and firmware. Don't send dumps. Don't ask this project to host them.

Bugs in [mGBA](https://github.com/mgba-emu/mgba) or [melonDS](https://github.com/melonDS-emu/melonDS) belong with those projects unless the glue in this tree is at fault.
