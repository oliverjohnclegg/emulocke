#!/usr/bin/env bash
set -euo pipefail

build_dir=${1:-build-fuzz}
seconds=${2:-60}
root=$(cd "$(dirname "$0")/../.." && pwd)
work=${EMULOCKE_FUZZ_WORK:-/tmp/emulocke-fuzz}
mkdir -p "$work/artifacts"
status=0

for seeds in "$root"/src/fuzz/corpus/*/; do
    name=$(basename "$seeds")
    mkdir -p "$work/$name"
    echo "== $name for ${seconds}s"
    if ! "$build_dir/$name" "$work/$name" "$seeds" \
        -max_total_time="$seconds" -rss_limit_mb=2048 -print_final_stats=1 \
        -artifact_prefix="$work/artifacts/$name-"; then
        echo "!! $name crashed; reproducer under $work/artifacts"
        status=1
    fi
done

exit $status
