# Setup QMK/VIAL with personal submodule for userspace

    git clone --recurse-submodules https://github.com/vial-kb/vial-qmk.git
    cd vial-qmk
    git remote rename origin upstream-vial

    git -c protocol.file.allow=always submodule add --name local-qmk-userspace /home/suka/src/keyboard/qmk_userspace_frobiac users/frobiac

    git remote rename origin local-userspace
    git co -t local-userspace/vial

# Setup VIAL with subdirectory of QMK's keyboards/frobiac

Since VIAL changes are not accepted in upstream repo, no need to have a generic two-way sync. Either

* generate a subtree only containing QMK keyboards/frobiac folder via `split --rejoin` (see other doc) and
  add it here
* or more simple, add local QMK repo as remote, and checkout only that folder from its branch(es) when needed.
  The (seldomly expected) sync back is then trivial either via cherry-pick onto a QMK branch, or other patches directly to local QMK repo

    git remote add local-qmk /home/suka/src/keyboard/qmk_firmware/
    git co local-qmk/vial -- keyboards/frobiac

Together with sanity checks and automatic tagging, a complete sync can be performed
with the [script](../scripts/sync-qmk-branch.sh)

Note that previous local changes still need to be replayed manually

