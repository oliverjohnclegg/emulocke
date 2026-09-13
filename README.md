<p align="center">
  <img src="assets/icons/emulocke.svg" width="96" height="96" alt="Emulocke">
</p>

# Emulocke

A desktop Pokemon nuzlocking suite. One window runs the game on the left. The nuzlocke tools will live on the right later. V1 is the playable host: no tracker, no damage calc.

Import a verified baseline dump (File > Import Game). New Run scopes the expedition. Battery saves live in the app data `runs/` folder, never beside the ROM. DS boots with FreeBIOS. Do not put Nintendo BIOS, firmware, or ROMs in this repo.

```
emulocke /path/to/firered.gba
```

That imports a known dump and opens New Run. It does not silent-boot.

## Layout

- Two-screen games: stacked screens. Mouse on the bottom pane is the stylus.
- One-screen games: one left pane.
- With no run seated, the left column lists expeditions. Right column: Logs tab until more suite tools exist.

## Menus

- File: import a dump, start a new run, load a run, start a new attempt, close the seated run
- Emulation: pause, reset, speed-up (2x-8x, default 3x), Hold Tab or tap to toggle
- View: fullscreen, screen scale (Fit / 1x / 2x / 3x / 4x), restore default window
- Audio: mute and volume
- Help: controls and about

Window size, scale, mute, volume, and speed-up persist across launches.

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
| Speed-up | Tab |

Gamepad uses the standard SDL map. Pause, reset, and speed-up are under Emulation. Hold Tab is the default; uncheck it to tap Tab on and off.

## CI artifacts

Every push runs `.github/workflows/build.yml` on Ubuntu and Windows. Download `emulocke-linux-x64` or `emulocke-windows-x64` from the Actions run. Keep the `assets/` folder next to the binary.

## License

Emulocke is GPL-3.0-or-later (melonDS). mGBA files stay MPL-2.0. See [LICENSE](LICENSE). Product decisions live in [PRD.md](PRD.md).
