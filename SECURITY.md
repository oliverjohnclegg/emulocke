# Security

This page is only for vulnerabilities: a crafted dump, save, patch, PNG, or prefs file that crashes the host, corrupts memory, or bypasses the catalog.

Email: olliejaclegg@gmail.com

Don't file those as public GitHub issues. Don't send Nintendo dumps with the report.

Crashes in normal play, wrong tracker facts, a title that won't import, and feature requests go in [GitHub Issues](https://github.com/oliverjohnclegg/emulocke/issues).

## Scope

The Emulocke desktop host and its GitHub Actions workflows. Untrusted input is user dumps, `.sav` files, patches, HTTPS PNGs, `prefs.ini`, run metadata, and emulator RAM.

## What CI already gates

Parsers fail closed: size caps, bounds checks, checksums. Every PR runs `linux-x64`, `win-x64`, `linux-asan-ubsan`, `clang-tidy`, and `libfuzzer-smoke`. A Vanguard or Stable zip waits on those jobs. The 14 September 2026 audit is [docs/security/audit-2026-09-14.md](docs/security/audit-2026-09-14.md). Agent C++ work follows `.cursor/rules/securitystandards.mdc`.

## Out of scope

Nintendo ROMs, BIOS, and firmware. Don't send dumps. Don't ask this project to host them.

Bugs in [mGBA](https://github.com/mgba-emu/mgba) or [melonDS](https://github.com/melonDS-emu/melonDS) belong with those projects unless the glue in this tree is at fault.
