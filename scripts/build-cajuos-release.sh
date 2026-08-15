#!/bin/sh
set -eu

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
SOURCE="$ROOT/source/CajuOS-GB300-v4.0"
OVERLAY="$ROOT/overlay"
WORK="$ROOT/build/cajuos-sdcard"
RELEASE="$ROOT/release"
VERSION=${CAJUOS_VERSION:-4.0}
ZIP="$RELEASE/CajuOS-GB300-v${VERSION}-sdcard.zip"

if [ ! -f "$SOURCE/output/sdcard/unifrog/firmware/unifrog.bin" ]; then
  echo "CajuOS firmware output uses the GB300 boot-compatible unifrog/ path" >&2
  echo "missing compiled firmware; run make in $SOURCE first" >&2
  exit 1
fi

rm -rf "$WORK"
mkdir -p "$WORK" "$RELEASE"
cp -a "$SOURCE/output/sdcard/." "$WORK/"
# The CajuOS build owns firmware and cores. Copy only CajuOS-owned files here;
# copying overlay/unifrog wholesale would silently replace the new firmware.
cp -a "$OVERLAY/bios" "$WORK/"
cp -a "$OVERLAY/ROMS" "$WORK/"
cp -f "$OVERLAY/README-CAJUOS.txt" "$WORK/README-CAJUOS.txt"
cp -f "$OVERLAY/REPRODUCE-CAJUOS.txt" "$WORK/REPRODUCE-CAJUOS.txt"

# The CajuOS build owns the firmware and cores. CajuOS owns the language,
# theme, settings, diagnostics and user-facing metadata.
mkdir -p "$WORK/unifrog_data/languages" "$WORK/unifrog_data/scripts" \
  "$WORK/unifrog_data/cajuos/assets" "$WORK/unifrog_data/cajuos/diagnostics"
cp -a "$OVERLAY/unifrog_data/languages/." "$WORK/unifrog_data/languages/"
cp -a "$OVERLAY/unifrog_data/scripts/." "$WORK/unifrog_data/scripts/"
cp -a "$OVERLAY/unifrog_data/cajuos/." "$WORK/unifrog_data/cajuos/"
cp -f "$OVERLAY/unifrog_data/settings.ini" "$WORK/unifrog_data/settings.ini"
cp -f "$OVERLAY/unifrog_data/cajuos-manifest.ini" "$WORK/unifrog_data/cajuos-manifest.ini"
cp -f "$OVERLAY/unifrog_data/controls-test.txt" "$WORK/unifrog_data/controls-test.txt"

FW_SHA=$(sha256sum "$WORK/unifrog/firmware/unifrog.bin" | awk '{print $1}')
sed -i "s/^firmware_sha256=.*/firmware_sha256=$FW_SHA/" \
  "$WORK/unifrog_data/cajuos-manifest.ini"
sed -i "s/^firmware_build=.*/firmware_build=compiled-performance-manager/" \
  "$WORK/unifrog_data/cajuos-manifest.ini"

rm -f "$ZIP"
(
  cd "$WORK"
  zip -q -r -9 "$ZIP" .
)
sha256sum "$ZIP" > "$RELEASE/CAJUOS-SDCARD-SHA256SUMS.txt"
(
  cd "$WORK"
  find . -type f -print0 | sort -z | xargs -0 sha256sum
) > "$RELEASE/CAJUOS-SDCARD-FILES-SHA256SUMS.txt"
printf 'created=%s\nsha256=%s\n' "$ZIP" "$(cut -d' ' -f1 "$RELEASE/CAJUOS-SDCARD-SHA256SUMS.txt")"
