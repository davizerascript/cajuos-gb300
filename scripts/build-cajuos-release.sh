#!/bin/sh
set -eu

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
SOURCE="$ROOT/source/CajuOS-GB300-v4.1"
OVERLAY="$ROOT/overlay"
WORK="$ROOT/build/cajuos-sdcard"
RELEASE="$ROOT/release"
VERSION=${CAJUOS_VERSION:-4.1}
ZIP="$RELEASE/CajuOS-GB300-v${VERSION}-sdcard.zip"

if [ ! -f "$SOURCE/output/sdcard/cajuos/firmware/cajuos.bin" ]; then
  echo "CajuOS firmware output is missing the GB300 boot-compatible Caju OS path" >&2
  echo "missing compiled firmware; run make in $SOURCE first" >&2
  exit 1
fi

rm -rf "$WORK"
mkdir -p "$WORK" "$RELEASE"
cp -a "$SOURCE/output/sdcard/." "$WORK/"
# The build uses space-free staging names; the public SD layout uses the branded names.
mv "$WORK/cajuos" "$WORK/Caju OS"
mv "$WORK/cajuos_data" "$WORK/Caju OS Data"
# The CajuOS build owns firmware and cores. Copy only CajuOS-owned files here;
# copying the overlay wholesale would silently replace the new firmware.
cp -a "$OVERLAY/bios" "$WORK/"
cp -a "$OVERLAY/ROMS" "$WORK/"
cp -f "$OVERLAY/README-CAJUOS.txt" "$WORK/README-CAJUOS.txt"
cp -f "$OVERLAY/REPRODUCE-CAJUOS.txt" "$WORK/REPRODUCE-CAJUOS.txt"

# The CajuOS build owns the firmware and cores. CajuOS owns the language,
# theme, settings, diagnostics and user-facing metadata.
mkdir -p "$WORK/Caju OS Data/languages" "$WORK/Caju OS Data/scripts" \
  "$WORK/Caju OS Data/cajuos/assets" "$WORK/Caju OS Data/cajuos/diagnostics"
cp -a "$OVERLAY/Caju OS Data/languages/." "$WORK/Caju OS Data/languages/"
cp -a "$OVERLAY/Caju OS Data/scripts/." "$WORK/Caju OS Data/scripts/"
cp -a "$OVERLAY/Caju OS Data/cajuos/." "$WORK/Caju OS Data/cajuos/"
cp -f "$OVERLAY/Caju OS Data/settings.ini" "$WORK/Caju OS Data/settings.ini"
cp -f "$OVERLAY/Caju OS Data/cajuos-manifest.ini" "$WORK/Caju OS Data/cajuos-manifest.ini"
cp -f "$OVERLAY/Caju OS Data/controls-test.txt" "$WORK/Caju OS Data/controls-test.txt"

FW_SHA=$(sha256sum "$WORK/Caju OS/firmware/cajuos.bin" | awk '{print $1}')
sed -i "s/^firmware_sha256=.*/firmware_sha256=$FW_SHA/" \
  "$WORK/Caju OS Data/cajuos-manifest.ini"
sed -i "s/^firmware_build=.*/firmware_build=compiled-performance-manager/" \
  "$WORK/Caju OS Data/cajuos-manifest.ini"

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
