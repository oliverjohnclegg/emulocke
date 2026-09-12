#!/usr/bin/env bash
set -euo pipefail

display=":99"
if ! xdpyinfo -display "$display" >/dev/null 2>&1; then
  Xvfb "$display" -screen 0 1600x1000x24 >/tmp/xvfb.log 2>&1 &
fi
