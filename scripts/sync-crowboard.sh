#!/bin/bash
#

set -euo pipefail

# cb-qmk	https://github.com/doesntfazer/qmk_firmware.git (fetch)
# cb-vial	https://github.com/doesntfazer/vial-qmk (fetch)
REM=cb-qmk
BR=master


git commit -a -m "DUMP prior to $0 with $BR/$REM" || true

git fetch $REM

REV=$(git describe $REM/$BR)

git checkout $REM/$BR -- keyboards/crowboard

git commit -a -m "[SYNC cb] $REM/$BR $REV"


