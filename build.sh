#!/usr/bin/env bash
set -euo pipefail

repo_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
qmk_dir="$repo_dir/.build/qmk_firmware"
qmk_revision="$(cat "$repo_dir/qmk-revision")"
keymap_dir="$qmk_dir/keyboards/zsa/moonlander/keymaps/egor"

command -v qmk >/dev/null || { echo "Install QMK first: brew install qmk/qmk/qmk" >&2; exit 1; }
command -v arm-none-eabi-gcc >/dev/null || { echo "Install the ARM compiler: brew install qmk/qmk/arm-none-eabi-gcc@8" >&2; exit 1; }

if [[ ! -d "$qmk_dir/.git" ]]; then
    git clone --depth 1 --single-branch --branch firmware25 \
        https://github.com/zsa/qmk_firmware.git "$qmk_dir"
fi

if [[ "$(git -C "$qmk_dir" rev-parse HEAD)" != "$qmk_revision" ]]; then
    git -C "$qmk_dir" fetch --depth 1 origin "$qmk_revision"
    git -C "$qmk_dir" checkout --detach "$qmk_revision"
fi

git -C "$qmk_dir" submodule update --init --depth 1 \
    lib/chibios lib/chibios-contrib lib/printf modules/zsa

mkdir -p "$keymap_dir" "$repo_dir/dist"
cp "$repo_dir/keymap.c" "$repo_dir/keymap.h" "$repo_dir/keymap.json" \
    "$repo_dir/config.h" "$repo_dir/rules.mk" "$keymap_dir/"

QMK_HOME="$qmk_dir" make -C "$qmk_dir" -j"${JOBS:-4}" zsa/moonlander/reva:egor
cp "$qmk_dir/zsa_moonlander_reva_egor.bin" "$repo_dir/dist/moonlander-reva.bin"
echo "Firmware: $repo_dir/dist/moonlander-reva.bin"
