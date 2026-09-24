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
- juyanith/k2_he
- juyanith/k3_max

--------------------------------------------------
One-time setup:

git fetch keychron --prune
git fetch origin --prune

git branch -f vendor/2025q3 keychron/2025q3
git branch -f vendor/wireless_playground keychron/wireless_playground

git push origin vendor/2025q3 --force
git push origin vendor/wireless_playground --force

git switch -c juyanith/k2_he vendor/2025q3
# add users/juyanith and K2 HE keymap
git commit -m "Add juyanith userspace and keymap for K2 HE"
git push -u origin juyanith/k2_he

git switch -c juyanith/k3_max vendor/wireless_playground
# add users/juyanith and K3 Max keymap
git commit -m "Add juyanith userspace and keymap for K3 Max"
git push -u origin juyanith/k3_max

--------------------------------------------------
Daily work:

git switch juyanith/k2_he 
# edit, commit, push

# cherry pick common code in users/juyanith
git switch juyanith/k3_max
git cherry-pick <commit>
git push

Note on submodules:
- Ensure submodules are updated and initialized before compiling.
- Use `git submodule update --init --recursive` to initialize and update submodules.

--------------------------------------------------
Update from Keychron:

git fetch keychron --prune

git branch -f vendor/2025q3 keychron/2025q3
git branch -f vendor/wireless_playground keychron/wireless_playground

git push origin vendor/2025q3 --force
git push origin vendor/wireless_playground --force

git switch juyanith/k2_he
git rebase vendor/2025q3
git push --force-with-lease

git switch juyanith/k3_max
git rebase vendor/wireless_playground
git push --force-with-lease

--------------------------------------------------
Build:

git switch juyanith/k2_he
qmk compile -kb keychron/k2_he/ansi -km juyanith

git switch juyanith/k3_max
qmk compile -kb keychron/k3_max/ansi/rgb -km juyanith

--------------------------------------------------
K2 HE and K3 Max layout policy:

- Mac mode is the customized layout. On MAC_BASE, Tab taps Tab and holds
  Super+Alt+Ctrl+Shift (Hyper), using the default 200 ms tapping term.
- Windows mode is the stock typing fallback: plain letters, punctuation, Tab,
  Caps Lock, and Space; no mod-taps or Space navigation layer. Caps Word is
  disabled in Windows mode. Stock Fn, media, lighting, and connection controls remain.
- VIA saved mappings can override firmware defaults after flashing; update the
  saved assignments or reset the dynamic keymap after preserving custom mappings.
- On K3 Max, Windows mode uses the Mac keycap modifier positions: left
  Control, Option (Alt), Command (Super); right Command (Super), Fn, Control.

--------------------------------------------------
Primary editing layer (hold Space):

Space still taps Space. Tab still taps Tab and holds Hyper outside this layer;
Space+Tab sends Enter. Caps/Escape, OS detection, and tap/hold timing are unchanged.
Spatial movement uses QMK key overrides to preserve native held-key repeat
and Shift/Alt changes during a hold. Editor mod-taps retain their existing
tap/hold handling.
The keyboard's Windows mode remains a plain fallback; use the customized Mac
switch position for these shortcuts on any OS. Output follows detected host OS.

| Key | Base | Shift | Alt/Option | Alt+Shift |
| --- | --- | --- | --- | --- |
| J / semicolon | Left / Right | Select | Word movement | Select word |
| K / L | Down / Up | Select | Scroll line | Reserved |
| U / P | Line start / end | Select | Document start / end | Select document boundary |
| I / O | Page Down / Up | Select page | Same as base | Same as Shift |
| H | Backspace | Delete | Delete previous word | Delete next word |
| M | F3: next search match | Shift+F3: previous match | Primary+F3: next occurrence | Primary+Shift+F3: previous occurrence |
| B | Back location | Forward location | Same as base | Same as Shift |
| Slash | Add cursor down | Add cursor up | Backslash | Backslash |
| Apostrophe | Reserved | Reserved | Grave | Grave |
| Z | Undo | Redo | Undo | Redo |
| X / C / V | Cut / Copy / Paste | Same as base | Same as base | Same as base |

Q/W/E/R/T/A/S/D/F/G and comma/period taps are reserved (no output).
Z/X/C/V retain left Super/Alt/Shift/Ctrl holds. M/comma/period/slash retain
right Ctrl/Shift/Alt/Super holds. Y, N, right bracket, and backslash emit no output on this layer;
Enter passes through. Other
function, connection, lighting, and number-row editor commands remain intact.

Primary means Command on macOS and Ctrl elsewhere. macOS uses Option+arrows
for words, Command+Left/Right for line boundaries, Command+Up/Down for document
boundaries, and Ctrl+Page Up/Down for line scrolling. Windows/Linux use
Ctrl+arrows, Home/End, Ctrl+Home/End, and Ctrl+Up/Down respectively. Word deletion
uses Option on macOS and Ctrl elsewhere. Redo emits Cmd+Shift+Z on macOS and
Ctrl+Y elsewhere.

Existing back/forward shortcuts are preserved: Cmd+Minus / Cmd+Shift+Minus on
macOS, Ctrl+Alt+Minus / Ctrl+Shift+Minus elsewhere. Existing multicursor outputs
are Cmd+Option+Down/Up on macOS and Alt+Shift+Down/Up elsewhere. The latter match
VS Code Linux defaults; Windows defaults use Ctrl+Alt+Down/Up, so a Windows
editor binding is needed to retain these existing outputs. Search/occurrence
shortcuts and navigation history may also depend on editor customizations.
No synthetic function keys are used.

Resolver checks:
`cc -std=c99 -Wall -Wextra -Werror users/juyanith/tests/test_primary_editing.c -o /tmp/primary-test && /tmp/primary-test`
