# Moonlander K03 layout

Custom QMK layout for Moonlander Mark I **revision A** (`zsa/moonlander/reva`).
Adapted from the K03 English/Russian layout in `ergohaven-zmk-config`.
Imported K03 source revision: `f750cfc`.

## Thumb keys

Positions below run left to right as you look down at the keyboard.

| Side | Three narrow keys | Red key above them |
| --- | --- | --- |
| Left | Shift · Command · Backspace | Hold for App–Num |
| Right | Right Alt · Right Control · Space | Hold for Nav–Symbol |

Hold **both red keys** for System. Release either key to return to the layer
controlled by the other key. Thumb modifiers, Backspace, and Space remain
available on every layer.

Command + Backspace sends **Alt + Backspace** to delete a word. Releasing Command
first does not send an extra plain Backspace.

## Base layers

English and Russian keep the K03's main key positions, including its punctuation
row, Tab, Escape, Enter, and slash. The extra Backspace to the right of P is
disabled; use the left thumb Backspace. The punctuation row starts with an
unassigned key, underscore, and minus, matching the updated K03.

| Position | Action |
| --- | --- |
| Under M | Switch EN/RU |
| Inner key left of H | Shift + Enter |
| Inner key right of G | Ctrl + B |
| Top-left key while holding App–Num | Updated `hello_kotify` macro |
| Top-right key | Hold for one second to send Cmd + Ctrl + Q (lock macOS) |

The old bottom-row layer keys are replaced by the red keys. The other spare
bottom-row keys are unassigned. In English, the three positions after M remain
silent, but two still participate in the K03 combos. Russian uses them for Б, Ю,
and Э.

### Language switching

The computer must have these same shortcuts configured as with the K03:

- **Ctrl + Shift + 1:** select English.
- **Ctrl + Shift + 2:** select Russian.

The keyboard starts on its English base layer. Keep the computer's input source
in English when connecting it. Switching EN/RU changes both the keyboard layer
and the computer's input source.

Russian letters keep the K03's HID keycodes. English symbols temporarily select
English while held, then restore Russian after the last symbol is released.
Held modifiers are preserved around input-source shortcuts. The `hello_kotify`
macro searches for `kotify ser`, then sends the original greeting. It restores
the current keyboard language when finished.

## App–Num

Hold the **left red key**.

The left side keeps the K03 application shortcuts: Cmd + Ctrl + Alt with
Q/W/E/R/T, A/S/D/F/G, and Z/X/C/V. B sends Cmd + Shift + 5.
The top-left key runs the `hello_kotify` macro, matching its move off the K03 base
layer.

| Physical keys | Output |
| --- | --- |
| U · I · O | 7 · 8 · 9 |
| H · J · K · L | 0 · 4 · 5 · 6 |
| M · next key · next key | 1 · 2 · 3 |

These are regular number-row keycodes, matching the K03, rather than keypad
keycodes.

## Nav–Symbol

Hold the **right red key**. The left side keeps the K03 symbol block:

```text
Q  W  E  R  T       <  >  =  {  }
A  S  D  F  G       +  *  %  [  ]
Z  X  C  V  B       @  $  #  ^  |
```

`&` moves to the inner key right of G because Moonlander has no key beside B.

| Physical keys | Navigation output |
| --- | --- |
| Y · U · I · O | Right Alt + Left · Page Down · Page Up · Right Alt + Right |
| H · J · K · L | Left · Down · Up · Right |
| N · M · next key · next key | Cmd + Left · Cmd + Down · Cmd + Up · Cmd + Right |
| Top-row keys above U and I | Right Ctrl + Shift + Tab · Right Ctrl + Tab |

The Russian variant sends the same symbols by temporarily selecting English.

## System

Hold **both red keys**. System takes priority over App–Num and Nav–Symbol.

| Physical key | Action |
| --- | --- |
| H | Play/pause |
| J / K | Volume down/up |
| M / key right of M | Screen brightness down/up |
| Q | RGB on/off |
| W / E | RGB brightness down/up |
| A / S | Previous/next RGB effect |
| Top-right key | Enter bootloader mode for flashing |

Other main-body keys are silent on System, so application shortcuts and symbols
do not fall through from the layers beneath it.

## Combos

The combo window is 50 ms. Positions below use their English base labels.

| Keys pressed together | Output | Language |
| --- | --- | --- |
| Top-row `.` + `,` | `;` | EN/RU |
| Top-row grave + quote | `"` | EN/RU |
| Top-row quote + `?` | `!` | EN/RU |
| `/` + key immediately to its left | Backslash | EN/RU |
| U + I | Х | RU |
| M + key immediately to its right | Ъ | RU |
| R + T | Original K03 Ё binding (`KC_BSLS`) | RU |

Letter combos operate only on the base layers. The original exclamation combo
also remains available on App–Num and Nav–Symbol. System disables these combos.
The old symbol-layer combo is replaced by holding the right red key.

## Local build

Requires Git, QMK CLI, and the ARM compiler. On macOS, install the QMK toolchain
if it is not already installed:

```sh
brew install qmk/qmk/qmk
```

Build from this directory:

```sh
./build.sh
```

The script downloads ZSA QMK into `.build/qmk_firmware`, uses the commit recorded
in `qmk-revision`, copies the layout there, and compiles it locally. It does not
change the global QMK configuration or any other QMK checkout. Subsequent builds
reuse the local checkout and its dependencies.

Output: [dist/moonlander-reva.bin](dist/moonlander-reva.bin).

Open Keymapp, choose Flash, and select that file. Enter bootloader mode with the
physical reset button, or hold both red keys and press the top-right key after
this layout is installed. Revision A appears as **STM32 Bootloader**.

Building does not flash the keyboard. The firmware still needs to be tried on
the physical keyboard, especially thumb reach, combo timing, and the computer's
language and brightness shortcuts.

## Source files

- [keymap.c](keymap.c): physical layers, combos, language handling, and macros.
- [keymap.h](keymap.h): layer names and custom keycodes.
- [config.h](config.h): timing settings.
- [rules.mk](rules.mk): enabled QMK features.
- [keymap.json](keymap.json): ZSA's default hardware support module.
- [qmk-revision](qmk-revision): pinned ZSA QMK commit.
- [build.sh](build.sh): local revision A build.
