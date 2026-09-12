# Emulocke

A desktop Pokemon nuzlocking suite. One window runs the game on the left. The nuzlocke tools will live on the right later. V1 is the playable host: no tracker, no damage calc.

```
emulocke /path/to/game.gba
emulocke /path/to/game.nds
```

Or File > Open Game. Battery saves are written next to the game as `.sav`. DS boots with FreeBIOS. Do not put Nintendo BIOS, firmware, or ROMs in this repo.

## Layout

- Two-screen games: stacked screens. Mouse on the bottom pane is the stylus.
- One-screen games: one left pane.
- Right column: empty field log until the suite exists.

## Menus

- File: open or close a game
- Emulation: pause and reset
- View: fullscreen, screen scale (Fit / 1x / 2x / 3x / 4x), restore default window
- Audio: mute and volume
- Help: controls and about

Window size, scale, mute, and volume persist across launches.

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

| Action | Keyboard |
| --- | --- |
| D-pad | Arrows |
| A / B | X / Z |
| L / R | A / S |
| Start | Enter |
| Select | Shift |
| Stylus | Mouse on the bottom screen |

Gamepad uses the standard SDL map. Pause and reset are under Emulation.

## CI artifacts

Every push runs `.github/workflows/build.yml` on Ubuntu and Windows. Download `emulocke-linux-x64` or `emulocke-windows-x64` from the Actions run. Keep the `assets/` folder next to the binary.

## License

Emulocke is GPL-3.0-or-later (melonDS). mGBA files stay MPL-2.0. See [LICENSE](LICENSE). Product decisions live in [PRD.md](PRD.md).
