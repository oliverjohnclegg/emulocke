# Emulocke

A desktop Pokemon nuzlocking emulator. One window runs GBA (mGBA) or DS (melonDS) on the left. The nuzlocke suite will live on the right later. V1 is the playable host: no tracker, no damage calc.

```
emulocke /path/to/game.gba
emulocke /path/to/game.nds
```

Or File > Open ROM. Battery saves are written next to the ROM as `.sav`. DS boots with FreeBIOS. Do not put Nintendo BIOS, firmware, or ROMs in this repo.

## Layout

- NDS: two stacked screens. Mouse on the bottom pane is the stylus.
- GBA: one left pane.
- Right column: empty suite pane until the tools exist.

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
| Touch (NDS) | Mouse on the bottom screen |

Gamepad uses the standard SDL map. Pause and reset are under Emulation.

## CI artifacts

Every push runs `.github/workflows/build.yml` on Ubuntu and Windows. Download `emulocke-linux-x64` or `emulocke-windows-x64` from the Actions run. Keep the `assets/` folder next to the binary.

## License

Emulocke is GPL-3.0-or-later (melonDS). mGBA files stay MPL-2.0. See [LICENSE](LICENSE). Product decisions live in [PRD.md](PRD.md).
