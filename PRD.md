# Emulocke PRD

Living product document. Update when decisions change. This file only records Emulocke. Other projects and prior chats do not set requirements.

## Vision

Emulocke is a Pokemon nuzlocking suite. One desktop window runs the game and, later, the nuzlocke tools beside it. The suite is native, not a separate website.

## Framing

This is the filter for every menu, setting, and tool decision.

- The product is a field kit for Pokemon nuzlockes, not a general DS+GBA emulator. Do not market or draw it as one.
- The user opens a Pokemon game. `.gba` and `.nds` pick a core. The UI does not split GBA vs DS: no dual file-type identity, no GBA slot, no LCD layout, no firmware or BIOS chores.
- Cores (mGBA, melonDS) are implementation. They are not product surfaces.
- Emulator lab tools stay out: save states, rewind, cheats, disassemblers, memory viewers, movie recording, Lua, scanline filters, HUD counters.
- Cherry-pick later, only when named: speed-up and frame skip under Emulation. Do not stub empty items.

DeSmuME is an analog for host comfort (window size, sound), not a menu to clone.

## User

Someone playing a Pokemon nuzlocke who wants the game and the tools in one place, without alt-tabbing to a tracker or calculator.

## Problem

Stock emulators play the game and nothing else. Existing nuzlocke tools live in a browser. The run is split across two programs. Emulocke puts both in one field kit.

## Layout

Left column is the game. Right column is the suite.

- Two-screen games: stacked screens (256x192), top then bottom, 5px between them. Mouse on the bottom pane is the stylus.
- One-screen games: one left pane (240x160). No empty bottom tile. Bezel is only as tall as the scaled screen.
- 21px charcoal around the screen cluster. Not between the two screens. Same 21px below and to the right of the field log.
- Game column sizes to the integer-scaled screens. Default window hugs 2x two-screen plus a 460px suite.
- Right column is the suite. Tabs hold each function. V1 ships a Logs tab.

Integer-scale nearest-neighbor. Letterbox outside the bezels, never inside them. Do not smear pixels.

## V1 (this pass)

A playable host. Suite is a Logs tab only.

- Open a game (`.gba` / `.nds`) from File > Open Game and from the CLI (`emulocke /path/to/game`)
- 60fps video in the left column
- Audio
- Keyboard and SDL gamepad
- Stylus on the bottom pane for two-screen games
- Battery saves next to the game as `.sav`
- Pause and reset
- One game at a time; extension picks the core
- View: fullscreen, screen scale Fit / 1x / 2x / 3x / 4x, restore default window
- Audio: mute and volume
- Help: controls (read-only) and about
- Prefs persist in the SDL pref path as `prefs.ini`

## V1 non-goals

- Any nuzlocke suite UI (damage calc, tracker, QoL, nuzlocke.app-adjacent tools)
- Emulator lab tools (save states, rewind, cheats, disassemblers, memory viewers, movies, Lua, filters, HUD)
- Speed-up and frame skip (later cherry-pick)
- Input remapping
- Treating GBA and DS as separate products in the UI
- DSi NAND, WiFi
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
- On-demand sprite cache (`SpriteCache`, `emulocke-sprite-check`): nuzlocke-style slugs, box + 2D front + 2D back. Missing box/front use a bundled `?`. Missing back uses that Pokemon's front. No suite UI in V1.

## Later host (not V1)

- Speed-up
- Frame skip

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
- Do not ship Pokemon sprite PNGs. `SpriteCache` downloads box/front/back art on demand into the SDL pref cache. Bundled `assets/sprites/missing-*.png` are original question-mark art, not TPC sprites.
- V1 boots DS games with FreeBIOS so a BIOS dump is not required to play.

## Default input

Bindings are fixed in V1. Help > Controls lists them. Remapping is later.

| Control | Keyboard |
| --- | --- |
| D-pad | Arrow keys |
| A / B | X / Z |
| L / R | A / S |
| Start | Enter |
| Select | Shift |
| Stylus | Mouse on bottom screen |

Gamepad: standard SDL mapping.

## Design

Locked field kit. Charcoal metal, inset glass screens, deep crimson accent, tabular type. Suite pane is tabbed; Logs is the first tab.

## Decisions

| Decision | Why |
| --- | --- |
| Pokemon suite, not a general emulator | UI never splits GBA vs DS. Cores are an implementation detail. |
| SDL3 + Dear ImGui, themed | Low-latency host. Suite can grow in the right pane later. Qt is the stock emulator look. Tauri adds IPC latency. |
| Native cores, not libretro | This project named the standalone melonDS and mGBA repos. Native APIs also expose RAM/save for a later suite. |
| Software 3D (no melonDS GL renderer) | Avoid sharing a GL context with ImGui. Fine for V1 on PC. |
| One-screen games use one left pane | A 2x2 grid leaves a dead bottom-left tile. |
| FreeBIOS / generated firmware | Play DS Pokemon without shipping or requiring dumps. |
| One session at a time | No dual-core process. Extension selects the core. |
| Baseline View/Audio prefs in V1 | Window, scale, mute, and volume are how you play, not lab tools. |
| No emulator lab tools | Save states, memory, and disassembly stay out unless explicitly cherry-picked. |
| Windows via MSVC in CI | Same CMake tree. Dynlib uses LoadLibrary. Pref path is SDL. JIT off on MSVC (no GNU `.S` assembler). |
| Other chats are out of scope | Greenfield. Only this document and this repo set requirements. |
| Sprite cache downloads at runtime | PokeAPI/PokéSprite/bamq host the pixels. Pref cache, not git. Box: PokéSprite then bamq Gen 9 then PokeAPI gen8 icons. Front/back: PokeAPI BW-style. Credits: PokeAPI, msikma/pokesprite, National Dex Version Delta (bamq), Smogon for fan 2D past 649. |

## V1 success

1. The tree builds on the Linux/WSL machine used for development.
2. GitHub Actions builds Linux and Windows artifacts on push (`emulocke` and `emulocke.exe`).
3. A homebrew `.gba` and `.nds` run (not Pokemon, not committed).
4. Video, audio, keyboard, gamepad, pause, reset, and `.sav` creation work.
5. Two-screen games show both screens; clicks on the bottom pane map to stylus.
6. One-screen games use a single left pane; the suite placeholder stays visible.
7. View, Audio, and Help work. Prefs survive a relaunch.

## Changelog

- 2026-09-12: Initial PRD. V1 is the playable 2-pane shell. Suite is specified, not built.
- 2026-09-12: Windows MSVC `.exe` plus GitHub Actions artifacts on push. Same sources, two native builds.
- 2026-09-12: Product is a Pokemon nuzlocking suite, not a general DS+GBA emulator. V1 menu bar gets View, Audio, Help with persisted prefs.
- 2026-09-12: Compact DeSmuME-like shell. Console hugs screens with a 5px DS gap, suite 460px, default window 990x820.
- 2026-09-12: 21px charcoal around the screen cluster. DS split stays 5px.
- 2026-09-12: 21px charcoal below and to the right of the field log.
- 2026-09-12: Suite header is a tab bar. Logs is the first tab.
- 2026-09-12: On-demand sprite cache for box, 2D front, and 2D back. No suite picture yet. Missing back uses front.
