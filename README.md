# Emulocke

A desktop Pokemon nuzlocking emulator. One window runs GBA (mGBA) or DS (melonDS) on the left. The nuzlocke suite will live on the right later. V1 is the playable host: no tracker, no damage calc.

Play is scoped to a **run**, not the ROM file. One game can have many runs. Each run keeps the ROM path, nuzlocke rules, and its own battery save. A run can have many attempts: Start New Attempt copies the same settings, gives the attempt a fresh ID and save, ticks the counter, and replaces the previous attempt.

```
emulocke
emulocke /path/to/firered.gba
```

With no run loaded, home lists the latest attempt of each run, grouped by game, as `Pokemon Fire Red: Hardcore Nuzlocke  |  Attempt #1`. If there are no saves, it shows "No save files found" and a Start Run button. NEW ATTEMPT on a row replaces that run's last attempt with the same settings. File > Start New Attempt (above New Run) does the same while a run is seated. File > New Run opens a modal to pick the game and a Regular / Hardcore preset, then edit the toggles. File > Load Run switches runs. Drop Pokemon dumps in the `roms/` folder next to the binary (or `./roms`). Emulocke detects titles from the ROM header. Unknown dumps are ignored. A CLI ROM path opens New Run for that game if it is a supported Pokemon dump. DS boots with FreeBIOS. Do not put Nintendo BIOS, firmware, or ROMs in this repo.

## Layout

- No run: home. Saved runs grouped by game, or Start Run if none.
- NDS: two stacked screens. Mouse on the bottom pane is the stylus.
- GBA: one left pane.
- Right column: empty field log until the suite exists.

## Build

CMake 3.25+, C++20, Git. First configure fetches SDL3.

```bash
git clone --recurse-submodules https://github.com/oliverjohnclegg/emulocke.git
cd emulocke
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
./build/emulocke_run_test
```

Linux binary: `build/emulocke`  
Windows (MSVC): `build/Release/emulocke.exe`

Put dumps in `build/roms/` (created next to the binary) or `./roms`.

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

Every push runs `.github/workflows/build.yml` on Ubuntu and Windows. Download `emulocke-linux-x64` or `emulocke-windows-x64` from the Actions run. Keep the `assets/` and `roms/` folders next to the binary.

## License

Emulocke is GPL-3.0-or-later (melonDS). mGBA files stay MPL-2.0. See [LICENSE](LICENSE). Product decisions live in [PRD.md](PRD.md).
