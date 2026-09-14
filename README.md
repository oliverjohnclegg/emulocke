<p align="center">
  <img src="assets/icons/emulocke.svg" width="96" height="96" alt="Emulocke">
</p>

# Emulocke

A desktop Pokemon nuzlocking suite. One window runs the game on the left. Tracker, Pokémon, Logs, and Calculator live on the right.

Import a verified baseline dump (File > Import Game). Home START RUN scopes the expedition. Battery saves live in the app data `runs/` folder, never beside the ROM. DS boots with FreeBIOS. Do not put Nintendo BIOS, firmware, or ROMs in this repo.

```
emulocke /path/to/firered.gba
```

That imports a known dump and opens New Run. It does not silent-boot.

```
emulocke --preview-calc
```

Opens the Calculator tab on the Fire Red pack with a fixture party. No ROM required.

## Layout

- Two-screen games: stacked screens. Mouse on the bottom pane is the stylus.
- One-screen games: stacked screens. Bottom pane is the party LCD. View > Bottom Screen hides it and centers the game in the left pane.
- With no run seated, the left column lists expeditions. Right column: Tracker, Pokémon, Logs, then Calculator.

## Menus

- File: import a dump, start a new attempt, close the seated run. Start and load from home.
- Emulation: pause, reset, Speed-up submenu (2x-8x, default 3x, Hold Tab or tap to toggle)
- View: fullscreen, right pane (F8), screen scale (Fit / 1x / 2x / 3x / 4x), bottom screen, restore default window
- Audio: mute and volume
- Config: controls
- Help: about

Window size, scale, right pane, bottom screen, mute, volume, speed-up, and keyboard bindings persist across launches.

## Build

CMake 3.25+, C++20, Git. First configure fetches SDL3.

```bash
git clone --recurse-submodules https://github.com/oliverjohnclegg/emulocke.git
cd emulocke
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
```

Linux binary: `build/emulocke`  
Windows (MSVC): `build/Release/emulocke.exe`

## Controls

Config > Controls remaps the keyboard. Defaults:

| Action | Keyboard |
| --- | --- |
| D-pad | Arrow keys |
| B | Z |
| A | X |
| Y | A |
| X | S |
| L | Q |
| R | W |
| Start | Enter |
| Select | RShift |
| Stylus | Mouse on the bottom screen |
| Speed-up | Tab |
| Right pane | F8 |

Gamepad uses the standard SDL map. Pause, reset, and speed-up are under Emulation. Hold Tab is the default; uncheck it to tap Tab on and off.

## Instances

`main` is Stable. `dev` is Vanguard.

Every push runs `.github/workflows/build.yml` on Ubuntu and Windows. Keep `assets/` next to the binary.

Stable:

- `emulocke-vX.X.X-win-x64.exe`
- `emulocke-vX.X.X-linux-x64`

Vanguard:

- `emulocke-vanguard-<commit>-win-x64.exe`
- `emulocke-vanguard-<commit>-linux-x64`

Window caption is `Emulocke vX.X.X` on Stable and `Emulocke VANGUARD [<commit>]` on Vanguard. A seated run appends ` - Pokémon <title>`.

## License

Emulocke is GPL-3.0-or-later (melonDS). mGBA files stay MPL-2.0. See [LICENSE](LICENSE). Product decisions live in [PRD.md](PRD.md).
