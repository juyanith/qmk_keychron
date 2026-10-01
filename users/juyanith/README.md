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

The two user keymaps share the same five-layer design:

```text
MAC_BASE, MAC_FN, WIN_BASE, WIN_FN, SYMBOL
```

`MAC_BASE` uses native QMK home-row mod-taps. Their tap keys are the normal
letters, while holds provide the Mac physical modifier arrangement: Control,
Option, Command, Shift on A/S/D/F and Shift, Command, Option, Control on
J/K/L/semicolon. QMK's `PERMISSIVE_HOLD`, `CHORDAL_HOLD`, and a 200 ms tapping term provide
release-sensitive roll behavior while treating same-hand rolls as taps.

Space taps Space and holds SYMBOL. Tab taps Tab and holds Hyper. Caps Lock taps
Escape and Enter taps Enter; both hold CAG (Ctrl+Alt+GUI). Tab hold emits
Hyper (Shift+CAG). On SYMBOL, Tab sends Enter and
Caps/Enter remain transparent. The layer provides the number, navigation,
delete, punctuation, and screenshot mappings documented in envmgr's
`layers.txt`. Unassigned keys use `KC_NO`; function-row, arrow, navigation, and
physical modifier keys pass through.

`WIN_BASE` remains a plain fallback layer with no home-row mods. The function
layers retain the vendor lighting, media, battery, and connection controls.

The userspace no longer contains HOTKEY or SYSTEM layers, editor shortcut
handlers, movement override tables, or application-specific logic. The only
custom keycode is the SYMBOL screenshot action, which emits Print Screen on
Linux/Windows and Command+Shift+3 on macOS.

Build:

```sh
qmk compile -kb keychron/k2_he/ansi -km juyanith
qmk compile -kb keychron/k3_max/ansi/rgb -km juyanith
```
