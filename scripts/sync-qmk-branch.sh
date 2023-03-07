#!/usr/bin/env bash
#

REM=local-qmk-firmware
BR=vial

set -euo pipefail

# this is in git submodule
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
VIAL_DIR=$( cd "$SCRIPT_DIR" && git rev-parse --show-superproject-working-tree )

cd "$VIAL_DIR"

if [ -z "$(git status --porcelain frobiac/keyboards)" ]; then
    echo "Ok. frobiac/keyboards seems clean"
else
    echo "ERROR: frobiac/keyboards *not* clean. Please commit before running sync script." >&2
    exit 1
fi

git fetch $REM

REV=$(git describe $REM/$BR)

# Now in separate submodule
# git checkout $REM/$BR -- users/frobiac
git checkout $REM/$BR -- keyboards/frobiac
git commit -a -m "[SYNC qmk] $REM/$BR $REV"
git tag sync-qmk-$(date "+%y%m%d-%H%M") -a -m "[SYNC qmk] $REM/$BR $REV"

