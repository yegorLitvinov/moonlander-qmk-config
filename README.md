# Moonlander K03 layout

Custom QMK layout for Moonlander Mark I **revision A** (`zsa/moonlander/reva`).
Adapted from the K03 English/Russian layout in `ergohaven-zmk-config`.
Imported K03 source revision: `f750cfc`.

All layer activation keys are momentary: their layers are active only while
held. Keep this behavior for future layout changes. EN/RU language switching is
separate.

## Layer keys

Bottom-row keys activate a layer on the **opposite half**. Thumb-cluster keys
activate a layer on the **same half**. Keep these rules for future layout changes.

| Activation key | Layer | Layer actions |
| --- | --- | --- |
| Bottom row under K, right | Symbols | Left half |
| Bottom row under L, right | Numbers | Left half |
| Bottom row under S, left | System | Right half |
| Left red thumb key | Apps | Left half |
| Right red thumb key | Nav | Right half |

Unassigned keys do nothing on every layer. The five layer activation keys and
the six narrow thumb keys remain available on every layer. Holding multiple
layer keys uses the highest-priority held layer: System, Symbols, Numbers, Nav,
then Apps. Releasing it returns to the next held layer or the base layer.

## Thumb keys

Positions below run left to right as you look down at the keyboard.

| Side | Three narrow keys | Red key above them |
| --- | --- | --- |
| Left | Shift · Command · Backspace | Hold for Apps |
| Right | Enter · Right Control · Space | Hold for Nav |

Each red key activates its layer alone. Holding both red keys does not activate
System; use the bottom-row key under S.

| Thumb keys pressed together | Output |
| --- | --- |
| Right Control + Enter | Shift + Enter |
| Right red + Right Control + Enter | Command + Enter |
| Right red + Space | Hold Right Alt |
| Right red + Right Control + Space | Hold Right Alt + Right Control |
| Left red + Command + Backspace | Command + Backspace |

Press the thumb keys together using the 50 ms combo window on any layer.
Right red + Ctrl + Enter takes priority over Ctrl + Enter.

Command + Backspace sends **Alt + Backspace** to delete a word. Press left red,
Command, and Backspace together for Finder file deletion or whole-line deletion.

## Base layers

English and Russian keep the K03's main key positions, including its punctuation
row, Tab, Escape, and slash. Enter is on the right thumb. Its former position at
the far right of the home row and the former Shift + Enter key left of H are
unassigned. The extra Backspace to the right of P is disabled; use the left thumb
Backspace. The punctuation row starts with an unassigned key, underscore, and
minus, matching the updated K03.

| Position | Action |
| --- | --- |
| Under M | Switch EN/RU |
| Below `/` | `$` |
| Inner key right of G | Ctrl + B |
| Top-left key while holding Apps | Updated `hello_kotify` macro |
| Top-right key | Hold for one second to send Cmd + Ctrl + Q (lock macOS) |

The other spare bottom-row keys are unassigned. Minus and slash keep their base
positions and are also available on Numbers. In English, the three positions
after M remain silent, but two still participate in the K03 combos. Russian
uses them for Б, Ю, and Э.

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

## Apps

Hold the **left red key**.

The left side keeps the K03 application shortcuts: Cmd + Ctrl + Alt with
Q/W/E/R/T, A/S/D/F/G, and Z/X/C/V. B sends Cmd + Shift + 5.
The top-left key runs the `hello_kotify` macro, matching its move off the K03 base
layer. Numbers have their own layer; the right main-body keys do nothing on Apps.

## Numbers

Hold the **right bottom-row key under L**. Numbers are on the left half.

| Physical keys | Output |
| --- | --- |
| W · E · R | 7 · 8 · 9 |
| A · S · D · F | 0 · 4 · 5 · 6 |
| X · C · V | 1 · 2 · 3 |
| `:` · inner key immediately right | `+` · `-` |
| T · inner key immediately right | `*` · `/` |
| G | `=` |
| B | `%` |

Zero is on **A**, under the left pinky. These are regular number-row keycodes,
matching the K03, rather than keypad keycodes. The operators send the same
symbols in English and Russian. The right main-body keys do nothing on Numbers.

## Symbols

Hold the **right bottom-row key under K**. Symbols are on the left half:

```text
Q  W  E  R  T       ·  ·  {  }  ·
A  S  D  F  G       @  #  [  ]  &
Z  X  C  V  B       ^  |  <  >  ·
```

Dots mark unassigned keys. Dollar is on the base layers below `/`; arithmetic
operators and percent are on Numbers. The Russian variant sends the same symbols
by temporarily selecting English.
The right main-body keys do nothing on Symbols.

## Nav

Hold the **right red key**. Navigation stays on the right half. Symbols have
their own layer; the left main-body keys do nothing on Nav.

| Physical keys | Navigation output |
| --- | --- |
| Y · U · I · O | Right Alt + Left · Page Down · Page Up · Right Alt + Right |
| H · J · K · L | Left · Down · Up · Right |
| N · M · next key · next key | Cmd + Left · Cmd + Down · Cmd + Up · Cmd + Right |
| Top-row keys above U and I | Right Ctrl + Shift + Tab · Right Ctrl + Tab |

## System

Hold the **left bottom-row key under S**. All System actions are on the right
half. System takes priority over every other held layer.

| Physical key | Action |
| --- | --- |
| H | Play/pause |
| J / K | Volume down/up |
| M / key right of M | Screen brightness down/up |
| Y | RGB on/off |
| U / I | RGB brightness down/up |
| O / P | Previous/next RGB effect |
| Top-right key | Enter bootloader mode for flashing |

Other main-body keys do nothing on System.

## RGB

Hold System and use **O / P** to cycle backward / forward through four modes:

| Mode | Behavior |
| --- | --- |
| Key roles (default) | Colors come from each key's current action. Transparent keys use their inherited action; unused keys stay dark. |
| Heatmap | Repeated presses build brightness on each key, then fade. |
| Quick fade | Each press lights the key for about 300 ms. Repeated presses restart the fade without building brightness. |
| Finger zones | Fixed colors by finger, mirrored across the two halves. |

Heatmap and quick fade use the active layer's color. Finger zones and key roles
use fixed RGB palettes, scaled by the current brightness.

Both thumb clusters, including the red keys, always show the active layer:

| Layer | Color |
| --- | --- |
| English | White |
| Russian | Blue |
| Apps | Purple |
| Nav | Cyan |
| Numbers | Green |
| Symbols (EN/RU) | Orange |
| System | Red |

The highest-priority held layer determines the indicator color. Temporary
English input for Russian symbols does not change the selected layer's color.
The separate status LEDs are disabled.

**System + Y** toggles the main backlight. Thumb indicators stay visible, with a
small minimum brightness. **System + U / I** adjusts brightness. Mode, backlight
state, and brightness are saved across reconnects.

The palettes are constants in [rgb.c](rgb.c). Key-role colors are assigned from
the current keymap and need no per-key color table. Letters are white, numbers
green, symbols yellow, modifiers blue, editing keys orange, navigation cyan,
layer keys orange-red, shortcuts magenta, media purple, and system controls red.
Finger zones use pink for pinkies, yellow for ring fingers, green for middle
fingers, and cyan for index fingers.

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

Letter and punctuation combos work only on the base layers. Thumb combos work
on every layer. The red keys still activate their layers when held alone.

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
physical reset button, or hold the bottom-row key under S and press the top-right
key after this layout is installed. Revision A appears as **STM32 Bootloader**.

Building does not flash the keyboard. The firmware still needs to be tried on
the physical keyboard, especially thumb reach, combo timing, and the computer's
language and brightness shortcuts.

## Source files

- [keymap.c](keymap.c): physical layers, combos, language handling, and macros.
- [keymap.h](keymap.h): layer names and custom keycodes.
- [config.h](config.h): timing settings.
- [rgb.c](rgb.c): RGB palettes, dynamic key roles, and thumb layer indicators.
- [rgb_matrix_user.inc](rgb_matrix_user.inc): custom finger-zone effect.
- [rules.mk](rules.mk): enabled QMK features.
- [keymap.json](keymap.json): ZSA's default hardware support module.
- [qmk-revision](qmk-revision): pinned ZSA QMK commit.
- [build.sh](build.sh): local revision A build.
