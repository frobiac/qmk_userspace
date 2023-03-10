#!/bin/sh

set -euo pipefail

# This script under users/frobiac should be a separate repo/submodule
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SUPER_DIR=$( cd "$SCRIPT_DIR" && git rev-parse --show-superproject-working-tree )
USER_DIR=$( cd "$SCRIPT_DIR" && git rev-parse --show-toplevel )

cd "$SUPER_DIR"

# Crude test to see if we are called from within QMK or VIAL repo
is_vial_repo() {
    test -f "$SUPER_DIR/quantum/vial.h"
}

qmk_c() {
    qmk compile -c -j 8 "$@" || { echo "ERROR: $@ failed"; exit 1; }
}

build_json() {
    cd $USER_DIR/keymaps
    for j in *.json; do
        qmk_c -c $j
    done
}


build_keymap() {
    km=$1
    for kb in blackflat blackbowl hypernano redtilt; do
        qmk_c -kb frobiac/$kb -km $km
    done
}

build_all_keymaps() {
    for kb in blackflat blackbowl hypernano redtilt; do
        cd $SUPER_DIR/keyboards/frobiac/$kb/keymaps/
        for kmdir in *; do
            test -d $kmdir || continue
            km=$(basename $kmdir);

            echo "BUILDING qmk_c -kb frobiac/$kb -km $km"
            qmk_c -kb frobiac/$kb -km $km
        done
    done
}

# Build all boards with all keymaps in `keyboards/frobiac`

# currently fails in VIAL?!
if is_vial_repo; then
    echo "Detected VIAL repo ?!"
    echo "Not trying to compile JSON keymaps from userspace, nor default keymaps"
    # @TODO blackbowl -km default does not build in VIAL
    build_keymap vial
else
    build_json
    build_all_keymaps
fi
