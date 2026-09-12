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

- NDS: two stacked screens (256x192), top then bottom, 5px between them. Mouse on the bottom pane is the stylus.
- GBA: one left pane (240x160). No empty bottom tile. Bezel is only as tall as the scaled screen.
- 21px charcoal around the screen cluster. Not between the two DS screens. Same 21px below and to the right of the field log.
- Console column sizes to the integer-scaled screens. Default window hugs 2x NDS plus a 460px suite.
- Right column is the suite. Tabs hold each function. V1 ships a Logs tab.

Integer-scale nearest-neighbor. Letterbox outside the bezels, never inside them. Do not smear pixels.

## V1 (this pass)

A playable host. No suite.

- Open `.gba` / `.nds` from File > Open and from the CLI (`emulocke /path/to/rom`)
- 60fps video in the left column
- Audio
- Keyboard and SDL gamepad
- DS touch on the bottom pane
- Battery saves next to the ROM as `.sav`
- Pause and reset
- One game at a time; extension picks the core

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

Locked field kit. Charcoal metal, inset glass screens, deep crimson accent, tabular type. Suite pane is tabbed; Logs is the first tab.

## Decisions

| Decision | Why |
| --- | --- |
| SDL3 + Dear ImGui, themed | Low-latency emulator host. Suite can grow in the right pane later. Qt is the stock emulator look. Tauri adds IPC latency. |
| Native cores, not libretro | This project named the standalone melonDS and mGBA repos. Native APIs also expose RAM/save for a later suite. |
| Software 3D (no melonDS GL renderer) | Avoid sharing a GL context with ImGui. Fine for V1 on PC. |
| GBA uses one left pane | A 2x2 grid leaves a dead bottom-left tile. |
| FreeBIOS / generated firmware | Play DS Pokemon without shipping or requiring dumps. |
| One session at a time | No dual-core process. Extension selects GBA or NDS. |
| Windows via MSVC in CI | Same CMake tree. Dynlib uses LoadLibrary. Pref path is SDL. JIT off on MSVC (no GNU `.S` assembler). |
| Other chats are out of scope | Greenfield. Only this document and this repo set requirements. |

## V1 success

1. The tree builds on the Linux/WSL machine used for development.
2. GitHub Actions builds Linux and Windows artifacts on push (`emulocke` and `emulocke.exe`).
3. A homebrew `.gba` and `.nds` run (not Pokemon, not committed).
4. Video, audio, keyboard, gamepad, pause, reset, and `.sav` creation work.
5. NDS shows both screens; clicks on the bottom pane map to touch.
6. GBA uses a single left pane; the suite placeholder stays visible.

## Changelog

- 2026-09-12: Initial PRD. V1 is the playable 2-pane shell. Suite is specified, not built.
- 2026-09-12: Windows MSVC `.exe` plus GitHub Actions artifacts on push. Same sources, two native builds.
- 2026-09-12: Compact DeSmuME-like shell. Console hugs screens with a 5px DS gap, suite 460px, default window 990x820.
- 2026-09-12: 21px charcoal around the screen cluster. DS split stays 5px.
- 2026-09-12: 21px charcoal below and to the right of the field log.
- 2026-09-12: Suite header is a tab bar. Logs is the first tab.
