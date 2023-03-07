#!/bin/sh

# users/frobiac should be a separate repo/submodule
USERDIR=$(git rev-parse --show-toplevel)
QMKROOT=$USERDIR/../..

# Crude test to see if we are called from within QMK or VIAL repo
is_vial_repo() {
    test -f "$QMKROOT/quantum/vial.h"
}

qmk_c() {
    qmk compile -c -j 8 "$@" || { echo "ERROR: $@ failed"; exit 1; }
}

build_json() {
    cd $USERDIR/keymaps
    for j in *.json; do
        qmk_c -c $j
    done
}

build_keymaps() {
    for kb in blackflat blackbowl hypernano redtilt; do
        cd $QMKROOT/keyboards/frobiac/$kb/keymaps/
        for kmdir in *; do
            test -d $kmdir || continue
            km=$(basename $kmdir);

            echo "BUILDING qmk_c -kb frobiac/$kb -km $km"
            qmk_c -kb frobiac/$kb -km $km
        done
    done
}

# Build all boards with all keymaps in `keyboards/frobiac`
build_keymaps

# currently fails in VIAL?!
if is_vial_repo; then
    echo "Detected VIAL repo ?!"
    echo "Not trying to compile JSON keymaps from userspace"
else
    build_json
fi
