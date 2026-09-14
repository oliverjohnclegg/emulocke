## Base

This PR targets `dev`, from a feature or bugfix branch. Do not commit onto `main` or `dev`. PRs against `main` are closed unless the author is the maintainer.

## Change

<!-- what landed, and why -->

## Checks

- [ ] No ROMs, BIOS, firmware, or secrets
- [ ] `linux-x64`, `win-x64`, `linux-asan-ubsan`, `clang-tidy`, `libfuzzer-smoke`
- [ ] Adapter / catalog / calc / run / snapshot / parser changes extend an `emulocke-*-check`; byte parsers add a fuzz seed
- [ ] AI authored some or all of this: yes / no
