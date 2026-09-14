# Contributing

Nobody commits onto `main` or `dev`, not outsiders and not Oliver: put the work on a `feature/` or `bugfix/` branch, then open a pull request.

Branch off `dev`. Open the pull request against `dev`. `main` is Stable and maintainer-only; a PR that targets `main` from anyone except [oliverjohnclegg](https://github.com/oliverjohnclegg) is closed.

Once the branch rulesets are on, GitHub rejects `git push` to `main` and `dev`. Oliver's bypass is PR-merge only, so he can merge a PR he authored. It does not let him push commits straight onto those branches.

AI-authored commits and PRs are allowed. They don't merge until Oliver has read the diff and both GitHub Actions jobs are green. For someone else's PR that means an Approve from `@oliverjohnclegg`. GitHub won't let him Approve a PR he authored (including agent PRs under his login); those he merges after reading.

Don't add Nintendo dumps, BIOS, firmware, or secrets. `.gitignore` already blocks `*.gba`, `*.nds`, `*.bin`, and the BIOS names. Live boot checks stay on your machine.

Product scope lives in [PRD.md](PRD.md). This is a nuzlocke host. General emulator extras that don't directly contribute to that experience aren't a priority.

## Tests and CI

Merge gate: `linux-x64` and `win-x64` green, including `ctest`. No coverage number.

Changes to adapters, catalog SHA or patch apply, calc math, the run library, or the snapshot contract need a check that would fail without the change. Extend an existing `emulocke-*-check`. Don't add a second test framework.

UI chrome, copy, layout, and default keybinds don't need a new test.

Public CI doesn't hold ROMs. `emulocke-boot-check` and `emulocke-frlg-live-check` are local only.

Untrusted input is user dumps, saves, and patch bytes. Workflows stay `contents: read` except the main-PR guard, which must not check out PR code.
