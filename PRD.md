# Emulocke PRD

Living product document. Update when decisions change. This file only records Emulocke. Other projects and prior chats do not set requirements.

## Vision

Emulocke is a Pokemon nuzlocking emulator. One desktop window runs the game and, later, the nuzlocke tools beside it. GBA games run on mGBA. DS games run on melonDS. The suite is native, not a separate website.

## User

Someone playing a Pokemon nuzlocke on GBA or DS who wants the game and the tools in one place, without alt-tabbing to a tracker or calculator.

## Problem

Stock emulators play the game and nothing else. Existing nuzlocke tools live in a browser. The run is split across two programs. Emulocke puts both in one field kit.

## Layout

Left column is the console. Right column is the suite.

- NDS: two stacked screens (256x192), top then bottom. Mouse on the bottom pane is the stylus.
- GBA: one left pane (240x160). No empty bottom tile.
- Right column spans the full height. While a run is loaded, V1 is an empty field-log placeholder.

With no run loaded, home lists saved runs grouped by game. With none, it shows "No save files found" and a Start Run button.

Fixed split. Integer-scale nearest-neighbor. Letterbox, do not smear pixels.

## V1 (this pass)

A playable host. No suite.

- File > New Run and File > Load Run (no Open ROM)
- Drop Pokemon `.gba` / `.nds` dumps in `roms/`; New Run lists titles detected from the header game code
- New Run modal scopes the game and nuzlocke rules (Regular / Hardcore preset dropdown, then editable toggles)
- One game can have many runs; a run can have many attempts
- Start New Attempt clones the same game, ROM, and rules with a fresh ID and save, ticks the attempt counter, and replaces the previous attempt of that lineage. No settings modal.
- Home lists the latest attempt per lineage, grouped by game as `Pokemon Fire Red: Hardcore Nuzlocke  |  Attempt #2`, with NEW ATTEMPT on the row
- File > Start New Attempt sits above New Run and is enabled while a run is seated
- Click a home row to load that attempt
- CLI `emulocke /path/to/rom` opens New Run for a supported Pokemon dump; it does not silent-boot
- 60fps video in the left column once a run is seated
- Audio
- Keyboard and SDL gamepad
- DS touch on the bottom pane
- Battery saves live in the run folder (`battery.sav`), never beside the ROM
- Pause and reset
- One run at a time; ROM extension picks the core
- Rules are stored on the run. The cores do not enforce them.

## V1 non-goals

- Any nuzlocke suite UI (damage calc, tracker, QoL, nuzlocke.app-adjacent tools)
- DSi NAND, WiFi, cheats, rewind, save states, fast-forward
- GB/GBC
- OpenGL 3D upscaling
- Requiring the user to dump DS BIOS/firmware
- macOS as a V1 target

## Later suite (not V1)

Recorded so later work does not invent the product twice:

- Integrated damage calculator
- Progression tracker
- QoL tools
- More as decided in this project
- A native tracker adjacent to nuzlocke.app (encounter/route tracking UX), built in Emulocke. Not a fork. Not a webview of another app.

## Platforms

Linux/WSL is the development gate. Windows is a CI gate: the same CMake tree must produce `emulocke.exe` on `windows-latest`. GitHub Actions uploads both binaries as artifacts on push. Native compile on each OS, not cross-compile.

## Tech

| Piece | Choice |
| --- | --- |
| Language | C++20 |
| Build | CMake |
| Window / audio / input | SDL3 |
| UI | Dear ImGui (custom theme, not stock gray) |
| GBA | mGBA as a library |
| NDS | melonDS `core` + our `Platform.h` implementation |
| NDS boot | FreeBIOS + generated firmware + direct boot |
| Renderer | Software framebuffers uploaded as SDL textures |

## Legal

- Emulocke source: GPL-3.0-or-later (required by linking melonDS).
- mGBA files stay MPL-2.0 (incompatible with secondary licenses). Do not relicense those files as GPL. Ship both licenses.
- Do not ship Nintendo BIOS, firmware, or ROMs. Users supply their own dumps and games.
- V1 boots DS games with FreeBIOS so a BIOS dump is not required to play.

## Default input

No settings UI in V1.

| Control | Keyboard |
| --- | --- |
| D-pad | Arrow keys |
| A / B | X / Z |
| L / R | A / S |
| Start | Enter |
| Select | Shift |
| Touch (NDS) | Mouse on bottom screen |

Gamepad: standard SDL mapping.

## Design

Locked field kit. Charcoal metal, inset glass screens, deep crimson accent, tabular type. Suite pane reads as an empty log, not a fake dashboard.

## Decisions

| Decision | Why |
| --- | --- |
| SDL3 + Dear ImGui, themed | Low-latency emulator host. Suite can grow in the right pane later. Qt is the stock emulator look. Tauri adds IPC latency. |
| Native cores, not libretro | This project named the standalone melonDS and mGBA repos. Native APIs also expose RAM/save for a later suite. |
| Software 3D (no melonDS GL renderer) | Avoid sharing a GL context with ImGui. Fine for V1 on PC. |
| GBA uses one left pane | A 2x2 grid leaves a dead bottom-left tile. |
| FreeBIOS / generated firmware | Play DS Pokemon without shipping or requiring dumps. |
| One session at a time | No dual-core process. Extension selects GBA or NDS. |
| Saves scoped to the run | A nuzlocke is an attempt, not a ROM. Multiple runs of one game must not share a `.sav`. |
| `roms/` plus header detection | Users drop dumps in a known folder. Dropdown is detected Pokemon titles, not a file picker. |
| Windows via MSVC in CI | Same CMake tree. Dynlib uses LoadLibrary. Pref path is SDL. JIT off on MSVC (no GNU `.S` assembler). |
| Other chats are out of scope | Greenfield. Only this document and this repo set requirements. |

## V1 success

1. The tree builds on the Linux/WSL machine used for development.
2. GitHub Actions builds Linux and Windows artifacts on push (`emulocke` and `emulocke.exe`).
3. Home lists runs grouped by game as game, preset, and attempt. Empty home is "No save files found" plus Start Run.
4. New Run scopes a detected Pokemon game and nuzlocke rules (preset dropdown plus toggles), then boots that run.
5. Start New Attempt clones settings, ticks the attempt counter, uses a fresh ID and `battery.sav`, and replaces the last attempt of that lineage.
6. Two runs of the same game use separate `battery.sav` files under the app data `runs/` folder.
7. Video, audio, keyboard, gamepad, pause, reset, and run-scoped `.sav` creation work.
8. NDS shows both screens; clicks on the bottom pane map to touch.
9. GBA uses a single left pane; the suite placeholder stays visible.

## Changelog

- 2026-09-12: Initial PRD. V1 is the playable 2-pane shell. Suite is specified, not built.
- 2026-09-12: Windows MSVC `.exe` plus GitHub Actions artifacts on push. Same sources, two native builds.
- 2026-09-12: Run-scoped saves. New Run / Load Run replace Open ROM. Home lists runs grouped by game.
- 2026-09-12: Attempts. Start New Attempt clones a run's settings with a new ID and a ticked attempt counter.
- 2026-09-12: New attempts replace the previous attempt of that lineage. Presets are a dropdown. Empty home is Start Run, not an expedition log.
