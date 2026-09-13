# Emulocke PRD

Living product document. Update when decisions change. This file only records Emulocke. Other projects and prior chats do not set requirements.

## Vision

Emulocke is a Pokemon nuzlocking suite. One desktop window runs the game and, later, the nuzlocke tools beside it. The suite is native, not a separate website.

## Framing

This is the filter for every menu, setting, and tool decision.

- The product is a field kit for Pokemon nuzlockes, not a general DS+GBA emulator. Do not market or draw it as one.
- The user imports a Pokemon dump. `.gba` and `.nds` pick a core. The UI does not split GBA vs DS: no dual file-type identity, no GBA slot, no LCD layout, no firmware or BIOS chores.
- Cores (mGBA, melonDS) are implementation. They are not product surfaces.
- Emulator lab tools stay out: save states, rewind, cheats, disassemblers, memory viewers, movie recording, Lua, scanline filters, HUD counters.
- Cherry-pick later, only when named: frame skip under Emulation. Do not stub empty items.

DeSmuME is an analog for host comfort (window size, sound), not a menu to clone.

## User

Someone playing a Pokemon nuzlocke who wants the game and the tools in one place, without alt-tabbing to a tracker or calculator.

## Problem

Stock emulators play the game and nothing else. Existing nuzlocke tools live in a browser. The run is split across two programs. Emulocke puts both in one window.

## Layout

Left column is the game. Right column is the suite.

- Two-screen games: stacked screens (256x192), top then bottom, 5px between them. Mouse on the bottom pane is the stylus.
- One-screen games: one left pane (240x160). No empty bottom tile. Bezel is only as tall as the scaled screen.
- 21px graphite around the screen cluster. Not between the two screens. Same 21px below and to the right of the suite.
- Game column sizes to the integer-scaled screens. Default window hugs 2x two-screen plus a 460px suite.
- Right column is the suite. Tabs hold each function. V1 ships a Logs tab. Supported games fill Logs with adapter facts (trainer, map, party, badges). Unsupported carts keep the empty log.
- With no run seated, the left column is home. Empty home centers a START RUN hero. When plates exist, START RUN is a compact full-width stamp rail (plus + name) in the same graphite chrome as the plates. Each plate is `GAME - Preset`, a subtitle of host playtime as `HH:MM` • Attempt #N • Deaths • Badges, title art, and six party sockets. NEW ATTEMPT is a plus icon with a hover name. Click a plate to load. The right column stays Logs.

Integer-scale nearest-neighbor. Letterbox outside the bezels, never inside them. Do not smear pixels.

## V1 (this pass)

A playable host. Suite is a Logs tab only.

- File > Import Game copies a verified baseline dump into the SDL pref library as `roms/baselines/<uuid>.gba` (or `.nds`). SHA-1 must match a catalog row. Hacks are never imported.
- File > Import Game / Start New Attempt / Close Run. No New Run or Load Run in the menu. No Open Game. No `roms/` drop folder.
- Home START RUN opens New Run. New Run lists every catalog title as a strip (art, name with version in the title, region), including the 12 hacks as games. Missing baselines and hacks whose prerequisite is missing stay listed, greyed, with hover copy and click-to-import. `START RUN` stays disabled until the dump is in the library.
- Blaze Black and Volt White show Optional Patches (Full default, or Clean). The choice is stored on the run. Other hacks have a single bundled patch.
- Starting a hack run applies the bundled IPS/UPS/BPS/xdelta onto the imported baseline if `roms/derived/<uuid>[-option].ext` is not already there.
- One game can have many runs; a run can have many attempts. NEW ATTEMPT clones settings, ticks the counter, and replaces the previous attempt of that lineage.
- CLI `emulocke /path/to/dump` imports a known baseline and opens New Run. It does not silent-boot.
- 60fps video in the left column once a run is seated
- Audio
- Keyboard and SDL gamepad
- Stylus on the bottom pane for two-screen games
- Battery saves live in the run folder (`battery.sav`), never beside the ROM
- Pause, reset, and speed-up (Tab, default 3x). Emulation > Speed-up holds the 2x-8x slider and Hold Tab vs toggle.
- One run at a time; ROM extension picks the core
- View: fullscreen, screen scale Fit / 1x / 2x / 3x / 4x, restore default window
- Audio: mute and volume
- Help: controls (read-only) and about
- Prefs persist in the SDL pref path as `prefs.ini`
- Rules are stored on the run. The cores do not enforce them.

## V1 non-goals

- Any nuzlocke suite UI (damage calc, tracker, QoL, nuzlocke.app-adjacent tools)
- Emulator lab tools (save states, rewind, cheats, disassemblers, memory viewers, movies, Lua, filters, HUD)
- Frame skip (later cherry-pick)
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
- On-demand sprite cache (`SpriteCache`, `emulocke-sprite-check`): nuzlocke-style slugs, box + 2D front + 2D back. Missing box/front use a bundled `?`. Missing back uses that Pokemon's front. Home plates use box sprites. No suite UI in V1.
- On-demand game art cache (`GameArtCache`, `emulocke-game-art-check`): slug-keyed 256x192 title PNG. Missing uses a generated black plate. New Run shows this art at 64x48. Home plates use title art.

## Adapter

Each supported game+revision has a `GameAdapter` that translates save bytes and live memory into a common `GameSnapshot`. The suite only reads that snapshot.

- One adapter per game and revision. FireRed/LeafGreen US 1.0 and 1.1 share one FRLG implementation (`firered-us-1.0`, `firered-us-1.1`, and the LeafGreen twins). Live RAM layouts match for the fields we read. Unknown revisions are refused.
- Latest revision we have is the live identity. When a newer dump ships, older revisions move to `src/adapter/archive/`.
- Read-only for now. RAM writes (QoL cheats) are a separate interface later.
- Nuzlocke rules, damage math, and encounter tracking are suite concerns, not adapter concerns.
- Adding a pure virtual on `GameAdapter` is how a new suite data need flags every adapter in CI.
- If the suite needs a cart fact, add it to `GameSnapshot` and fill it in the adapter. A missing field is work, not a reason to drop the surface. Unimplemented titles leave the new fields zero.

## Later host (not V1)

- Frame skip

## Platforms

Linux/WSL is the development gate. Windows is a CI gate: the same CMake tree must produce a Windows instance on `windows-latest`. `main` is Stable; `dev` is Vanguard. GitHub Actions stamps and uploads both OS instances on push. Native compile on each OS, not cross-compile.

Stable instance names: `emulocke-vX.X.X-win-x64.exe` and `emulocke-vX.X.X-linux-x64`. Vanguard: `emulocke-vanguard-<commit>-win-x64.exe` and `emulocke-vanguard-<commit>-linux-x64`. Window caption is `Emulocke vX.X.X` (Stable) or `Emulocke VANGUARD [<commit>]` (Vanguard); a seated run appends ` - Pokémon <title>`.

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
- Do not ship Nintendo BIOS, firmware, or ROMs. Users import their own baseline dumps. Bundled IPS/UPS/BPS/xdelta files in `assets/patches/` are patches only. Vendored xdelta3 is Apache 2.0.
- Do not ship Pokemon sprite PNGs. `SpriteCache` downloads box/front/back art on demand into the SDL pref cache. Bundled `assets/sprites/missing-*.png` are original question-mark art, not TPC sprites.
- Do not ship Nintendo game title PNGs. `GameArtCache` downloads official 256x192 title art on demand into the SDL pref cache, keyed by slug. Optional `assets/game-art/<slug>.png` may hold original hack title stills. Missing art is a generated black plate with the game title.
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
| Speed-up | Tab |

Gamepad: standard SDL mapping.

## Design

Graphite clamshell. Matte graphite chassis, inset screen wells, parchment-metal hairlines, scarce crimson for pause. M PLUS Rounded 1c display, Fira Sans body. Suite tabs sit on a recessed rail; Logs is first. Compact chrome: primary actions stay named; secondary actions in dense chrome are icons with the name on hover.

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
| Game art cache downloads at runtime | Slug in, 256x192 PNG out. Official titles from libretro Named_Titles, letterboxed. Hacks use bundled stills if present, otherwise a black title plate. Pref cache, not git. |
| Host playtime per title and per run | New Attempt deletes the old folder, so title totals cannot be summed from leftover runs. Unpaused seated wall clock. Home plates show `HH:MM`. Speed-up does not count. No suite UI. |

## V1 success

1. The tree builds on the Linux/WSL machine used for development.
2. GitHub Actions builds stamped Linux and Windows instances on push (Stable from `main`, Vanguard from `dev`).
3. A verified Fire Red US 1.0 dump imports as its catalog UUID. Unknown files are refused.
4. Video, audio, keyboard, gamepad, pause, reset, speed-up, and run-folder `battery.sav` creation work.
5. Two-screen games show both screens; clicks on the bottom pane map to stylus.
6. One-screen games use a single left pane; FRLG fills Logs from the adapter snapshot.
7. View, Audio, and Help work. Prefs survive a relaunch.

## Changelog

- 2026-09-12: Initial PRD. V1 is the playable 2-pane shell. Suite is specified, not built.
- 2026-09-12: Windows MSVC `.exe` plus GitHub Actions artifacts on push. Same sources, two native builds.
- 2026-09-12: Product is a Pokemon nuzlocking suite, not a general DS+GBA emulator. V1 menu bar gets View, Audio, Help with persisted prefs.
- 2026-09-12: Compact DeSmuME-like shell. Console hugs screens with a 5px DS gap, suite 460px, default window 990x820.
- 2026-09-12: 21px charcoal around the screen cluster. DS split stays 5px.
- 2026-09-12: 21px charcoal below and to the right of the field log.
- 2026-09-12: Suite header is a tab bar. Logs is the first tab.
- 2026-09-12: Visual lock is onyx clamshell with cream command chips, not field kit.
- 2026-09-12: Palette returns to classy graphite and parchment metal. Cream command boxes dropped.
- 2026-09-12: GameAdapter contract and FRLG US 1.0/1.1 read-only snapshot (save + live RAM). Field log shows trainer, map, party.
- 2026-09-12: On-demand sprite cache for box, 2D front, and 2D back. No suite picture yet. Missing back uses front.
- 2026-09-12: On-demand game art cache. Slug-keyed 256x192 title PNG, black title plate on miss. No suite picture yet.
- 2026-09-12: Import library in the SDL pref path. Runs store catalog UUIDs. Battery saves live under `runs/`. Radical Red and Unbound are patched from Fire Red 1.0 on first run create.
- 2026-09-13: New Run game picker uses art strips, type-to-search, and click-to-import for missing dumps. Versions sit in the title as FIRE RED (1.0). Subtext is region. Hack hover names the prerequisite.
- 2026-09-13: Host playtime persisted per catalog title (`playtime.ini`) and per run (`playMs` in meta.ini). Counts unpaused seated time only. No suite UI.
- 2026-09-13: Speed-up cherry-pick. Tab holds 3x by default. Emulation > Speed-up submenu holds 2x-8x and Hold Tab vs toggle.
- 2026-09-13: Home is last-played run plates (title art, party sockets, gym pips). FRLG snapshot grows gyms. Compact chrome: secondary actions are icons, names on hover.
- 2026-09-13: Home-only start and load. File drops New Run and Load Run. Plate title is `GAME - Preset`. Subtitle is playtime, Attempt #N, Deaths, and badges, joined by •. Party sprites crop to opaque pixels and sit centered in the wells.
- 2026-09-13: When home has run plates, START RUN is a compact full-width stamp rail, not the empty-home hero button.
- 2026-09-13: Twelve ROM hacks in the catalog as games. Bundled IPS/UPS/BPS/xdelta. xdelta3 decode. Optional Patches for Blaze Black and Volt White. Hack art is a plate unless a bundled still exists.
- 2026-09-13: Home playtime is host wall clock as `HH:MM`, not the in-game save clock. Tab speed-up does not advance it.
- 2026-09-13: `main` is Stable, `dev` is Vanguard. Stamped instance names and window captions: version on Stable, commit hash on Vanguard.
