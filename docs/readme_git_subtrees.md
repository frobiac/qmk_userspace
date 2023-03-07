# Not used currently !!!

**NOTE** Currently using submodule for `users/frobiac` in both QMK and VIAL.
**NOTE** `keyboards/frobiac` is manually checked out from local QMK repo to sync

# About

How to get VIAL working on custom boards with separate repos for
- QMK firmware
- QMK userspace

Trying out 'git subtree's instead of submodules or manual merges.

The strategy is to only use the vial-qmk repo for compiling a VIAL-enabled
firmware for custom keyboards.
Hardware support will be obtained as `keyboards/frobiac/` from a QMK firmware clone.
Userspace features will be taken from a QMK userspace clone as `userspace/frobiac`.

All VIAL-related changes to the custom keyboards should be contributed back to those two repos,
but taking care that any change not applicable to pristine QMK is clearly marked as a 'VIAL' commit.
This should allow to maintain only to VIAL-specific branches on top of possibly upstreamed
development branches for QMK proper.




# git subtree

Notes following https://www.atlassian.com/git/tutorials/git-subtree

Add subtrees for the local checkouts

## Userspace

Import the 'vial' branch of a locally checked out QMK userspace.
Note '--squash' option mentioned in guide above was not used for now

    cd vial-qmk
    git subtree add --prefix users/frobiac ../qmk_userspace_frobiac vial

To later update `userspace/frobiac` :

    git subtree pull --prefix users/frobiac ../qmk_userspace_frobiac vial # [--squash]

Or via remotes (shorter when using URLs not local paths):

    git remote  add qmk-userspace-frobiac ../qmk_userspace_frobiac
    git subtree add --prefix users/frobiac qmk-userspace-frobiac vial
    git fetch qmk-userspace-frobiac
    git subtree pull --prefix users/frobiac qmk-userspace-frobiac vial # [--squash]

Later on, use `git subtree merge` to incorporate changes

Contribute back:

    git subtree push --prefix users/frobiac ../qmk_userspace_frobiac vial

## keyboards/frobiac

Adding a *subfolder* of QMK-firmware is slightly more complicated.
See section 3. [git subtree](https://stackoverflow.com/questions/23937436/add-subdirectory-of-remote-repo-with-git-subtree)

First, split off the source folder in the original repo as a separate branch `vial-for-subtree`:
Use `--rejoin` for faster splits later on, as this will take a minute initially.
Create a separate branch for the subtree on which to pick changes, as `--rejoin`
clutters the source branch with merge commits that are not desirable in the main branch.

    cd qmk_firmware/
    git co -b vial-for-subtree
    git subtree split --rejoin -P keyboards/frobiac -b vial-subtree-kb-frobiac

    # Then use that branch as source in the VIAL repo while setting up the subtree
    cd vial-qmk/
    git subtree add --prefix keyboards/frobiac qmk-fw-frobiac vial-subtree-kb-frobiac

To update later on changes in QMK:

Pick changes destined for VIAL to the now cluttered source branch `vial-for-subtree`.
Then execute the split-command again.


