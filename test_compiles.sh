#!/bin/sh


qmk_c() {
    qmk compile -c -j 8 "$@" || { echo "ERROR: $@ failed"; exit 1; }
}

qmk_c keymaps/blackflat.json
qmk_c keymaps/blackbowl.json
qmk_c keymaps/hypernano.json

for kb in blackflat blackbowl hypernano redtilt; do
    qmk_c -kb frobiac/$kb -km default
    qmk_c -kb frobiac/$kb -km frobiac
done
