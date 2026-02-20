#!/bin/bash
# Render all Corne keymap layouts → SVG → PNG
#
# Usage: ./scripts/draw.sh
# Requires: keymap-drawer (pip install keymap-drawer), rsvg-convert
#
# Keymap YAML files are maintained directly in keymap-drawer/*.yaml
# (keymap.c files in layouts/ are human-readable reference copies)

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
CONFIG="$REPO_ROOT/keymap_drawer.config.yaml"
LAYOUT_JSON="$REPO_ROOT/corne.json"
OUT_DIR="$REPO_ROOT/keymap-drawer"

LAYERS="base lower raise adjust"

for layout in qwerty gallium; do
    echo "=== Rendering $layout ==="

    YAML="$OUT_DIR/${layout}.yaml"
    SVG="$OUT_DIR/${layout}.svg"
    PNG="$OUT_DIR/${layout}.png"

    # Draw full SVG from YAML
    echo "  Drawing full SVG..."
    keymap -c "$CONFIG" draw "$YAML" -j "$LAYOUT_JSON" -o "$SVG"

    # Full PNG
    echo "  Rendering full PNG..."
    rsvg-convert "$SVG" -o "$PNG" -w 1400

    # Per-layer PNGs
    for layer in $LAYERS; do
        echo "  Rendering $layer layer..."
        TMP_SVG="/tmp/corne-${layout}-${layer}.svg"
        keymap -c "$CONFIG" draw "$YAML" -j "$LAYOUT_JSON" -s "$layer" -o "$TMP_SVG"
        rsvg-convert "$TMP_SVG" -o "$OUT_DIR/${layout}-${layer}.png" -w 1200
    done

    echo "  Done: $layout"
    echo ""
done

echo "All layouts rendered to $OUT_DIR/"
