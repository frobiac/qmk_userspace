#!/usr/bin/env bash
#
# Setup QMK and VIAL submodules:
# Currently not in use, link of userspace repo into upstream much easier
#
# Note: initial clone from local repos needs full path and extra option
#     git -c protocol.file.allow=always submodule add $PWD/../qmk_firmware deps/qmk_firmware
# Also rename local remote to `local`
#

set -eu
set -x
REPO=$(git rev-parse --show-toplevel)
QMK=qmk_firmware
VIAL=vial-qmk

init_submodules() {
    if [ ! -f .gitmodules ]; then
        test -d $REPO/../$QMK || { echo "QMK repo not found: $REPO/../$QMK"; exit 10; }
        test -d $REPO/../$VIAL || { echo "VIAL repo not found: $REPO/../$VIAL"; exit 11; }

        # git -c protocol.file.allow=always submodule add $REPO/../$QMK deps/qmk_firmware
        # git -c protocol.file.allow=always submodule add $REPO/../$VIAL deps/vial_firmware
    fi
}

init_qmk() {
    pushd deps/qmk_firmware
    git -c protocol.file.allow=always submodule update --init --recursive
    qmk setup
    # echo "users/frobiac" >> .gitignore
    qmk git-submodule
    popd
}

init_vial() {
    pushd deps/vial_firmware
    git -c protocol.file.allow=always submodule update --init --recursive
    qmk setup
    make git-submodule
    echo "users/frobiac" >> .gitignore
    popd
}

build_qmk() {
    # Link userspace into QMK repo.
    # Keyboards should be upstream. Otherwise copy over in the future.
    cd $REPO/deps/qmk_firmware
    # @TODO infinite link recursion in deps
    ln -sf $REPO users/frobiac
    qmk compile -c -kb frobiac/blackflat -km default
    qmk compile -c users/frobiac/keymaps/hypernano.json

}

build_vial() {
    # Link userspace into QMK repo.
    # Keyboards should be upstream. Otherwise copy over in the future.
    cd $REPO/deps/vial_firmware
    # @TODO infinite link recursion in deps
    ln -sf $REPO users/frobiac
    qmk compile -c -kb frobiac/blackflat -km default
    qmk compile -c users/frobiac/keymaps/hypernano.json

}

init_submodules
test -d deps/qmk_firmware/users/frobiac || init_qmk
test -d deps/vial_firmware/users/frobiac || init_vial

# build_qmk
build_vial








