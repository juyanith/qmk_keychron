# Keychron QMK Userspace Setup (juyanith)

GitHub repo: git@github.com:juyanith/qmk_keychron.git
Vendor repo: https://github.com/Keychron/qmk_firmware.git

Keyboards:
- K2 HE  → vendor branch: 2025q3
- K3 Max → vendor branch: wireless_playground

Remotes:
- keychron = vendor
- origin   = juyanith github

Branch layout:
- vendor/2025q3
- vendor/wireless_playground
- my/k2_he
- my/k3_max

--------------------------------------------------
One-time setup:

git fetch keychron --prune
git fetch origin --prune

git branch -f vendor/2025q3 keychron/2025q3
git branch -f vendor/wireless_playground keychron/wireless_playground

git push origin vendor/2025q3 --force
git push origin vendor/wireless_playground --force

git switch -c my/k2_he vendor/2025q3
# add users/juyanith and K2 HE keymap
git commit -m "Add juyanith userspace and keymap for K2 HE"
git push -u origin my/k2_he

git switch -c my/k3_max vendor/wireless_playground
# add users/juyanith and K3 Max keymap
git commit -m "Add juyanith userspace and keymap for K3 Max"
git push -u origin my/k3_max

--------------------------------------------------
Daily work:

git switch my/k2_he
# edit, commit, push

# cherry pick common code in users/juyanith
git switch my/k3_max
git cherry-pick <commit>
git push

--------------------------------------------------
Update from Keychron:

git fetch keychron --prune

git branch -f vendor/2025q3 keychron/2025q3
git branch -f vendor/wireless_playground keychron/wireless_playground

git push origin vendor/2025q3 --force
git push origin vendor/wireless_playground --force

git switch my/k2_he
git rebase vendor/2025q3
git push --force-with-lease

git switch my/k3_max
git rebase vendor/wireless_playground
git push --force-with-lease

--------------------------------------------------
Build:

git switch my/k2_he
qmk compile -kb keychron/k2_he -km juyanith

git switch my/k3_max
qmk compile -kb keychron/k3_max -km juyanith

