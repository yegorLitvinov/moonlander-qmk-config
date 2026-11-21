# Moonlander English/Russian layout

Custom QMK layout for Moonlander Mark I **revision A** (`zsa/moonlander/reva`).
Adapted from `ergohaven-zmk-config` at revision `f750cfc`.

Hold a layer key to use its layer. Piano can also stay on after a triple tap.
EN/RU language switching is separate.

Every digit and symbol has its own key, so Shift only changes letters. When
Shift is the only modifier held, digits and symbols are typed without it.
Shortcuts that add Command, Control, or Alt keep Shift.

## Layer keys

Symbols, Numbers, and System act on the **opposite half** from their activation
keys. App-Nav and Piano use both halves.

| Activation key | Layer | Layer actions |
| --- | --- | --- |
| Bottom row under K, right | Symbols | Left half |
| Bottom row under L, right | Numbers | Left half |
| Bottom row under S, left | System | Right half |
| Bottom row under V or M | App-Nav | Apps on the left, navigation and media on the right |
| Second key from the left on the bottom row, under Z | Piano | Both halves |

Unassigned keys do nothing. Outside Piano, the layer activation keys and the
thumb keys remain available. If several layer keys are held, the priority is
System, Symbols, Numbers, then App-Nav. Piano takes priority over all of them.

## Thumb keys

Positions below run left to right as you look down at the keyboard.

| Side | Three narrow keys | Red key above them |
| --- | --- | --- |
| Left | One-shot Shift · Command · Unassigned | Backspace |
| Right | Right Alt · Right Control · Space | Enter |

Tap Shift to capitalize the next letter, or hold it as a regular Shift. A
one-shot Shift is canceled by any key that is not a letter (language keys
excepted) and after 3 seconds.

| Thumb keys pressed together | Output |
| --- | --- |
| Left Shift + Backspace | Alt + Backspace (delete a word) |
| Space + Enter | Shift + Enter |
| Right Control + Enter | Command + Enter |
| Command + Backspace | Command + Backspace |
| Right Alt + Right Control | Hold Right Alt + Right Control |

The Enter and word-delete combos use nearby keys on the same thumb cluster.
Press each pair within 40 ms to send a single tap outside Piano.

## Base layers

The keys right of P and above `/` are unassigned. The punctuation row starts
with an unassigned key, underscore, and minus.

| Position | Action |
| --- | --- |
| Outermost right key on the bottom row | Select English |
| Outermost left key on the bottom row | Select Russian |
| Left of the backtick | `$` |
| Right of `:` | `@` |
| Top-row comma | Comma followed by a space. With a modifier, acts as a regular comma key. |
| Right of M | Plain comma in English, Б in Russian |
| Inner key right of G | Ctrl + B |
| Left of H | Cmd + Space |
| Top-right key | Hold for one second to send Cmd + Ctrl + Q (lock macOS) |

The other spare bottom-row keys are unassigned. Minus and slash keep their base
positions and are also available on Numbers. The two keys between the comma
right of M and `/` are blank in English and type Ю and Э in Russian.

### Language switching

Configure **Ctrl + Shift + 1** to select English and **Ctrl + Shift + 2** to
select Russian on the computer.

The keyboard starts on its English base layer. Keep the computer's input source
in English when connecting it. Each language key selects the keyboard layer
and the computer's input source.

English symbols temporarily select English while held, then restore Russian
after the last symbol is released.
Held modifiers are preserved around input-source shortcuts. The `hello_kotify`
macro searches for `kotify ser`, then sends the original greeting. It restores
the current keyboard language when finished.

## App-Nav

Hold either **bottom-row key under V or M**. The layer stays active while at
least one of the two keys is held.

On the left, Q/W/E/R/T, A/S/D/F/G, and Z/X/C/V send their letters with
Cmd + Ctrl + Alt. B sends Cmd + Shift + 5. The top-left key runs the
`hello_kotify` macro.

Navigation and media controls are on the right half.

| Physical keys | Action |
| --- | --- |
| Leftmost column, top to bottom | Play/pause · Volume up · Volume down |
| Y · U · I · O | Right Alt + Left · Page Down · Page Up · Right Alt + Right |
| H · J · K · L | Left · Down · Up · Right |
| N · M · next key · next key | Cmd + Left · Cmd + Down · Cmd + Up · Cmd + Right |
| Top-row keys above U and I | Right Ctrl + Shift + Tab · Right Ctrl + Tab |

## Numbers

Hold the **right bottom-row key under L**. Numbers are on the left half.

| Physical keys | Output |
| --- | --- |
| W · E · R | 7 · 8 · 9 |
| A · S · D · F | 0 · 4 · 5 · 6 |
| X · C · V | 1 · 2 · 3 |
| `:` | `%` |
| T · inner key immediately right | `*` · `/` |
| G · inner key immediately right | `+` · `-` |
| B | `=` |

Zero is on **A**, under the left pinky. The digits use regular number-row
keycodes. The operators send the same symbols in English and Russian.

## Symbols

Hold the **right bottom-row key under K**. Symbols are on the left half:

```text
Q  W  E  R  T       ·  &  {  }  ·
A  S  D  F  G       #  |  [  ]  ·
Z  X  C  V  B       ·  ^  <  >  ·
```

Dots mark unassigned keys. In Russian, each symbol temporarily selects English.
The right main-body keys do nothing on Symbols.

## System

Hold the **left bottom-row key under S**. All System actions are on the right
half.

| Physical key | Action |
| --- | --- |
| M / key right of M | Screen brightness down/up |
| Y | RGB on/off |
| U / I | RGB brightness down/up |
| O / P | Previous/next RGB effect |
| Key left of the top-right key | Flash with Keymapp: open it (Cmd + Ctrl + Alt + Q), select `moonlander-reva.bin`, then enter bootloader mode |
| Top-right key | Enter bootloader mode for flashing |

Other main-body keys do nothing on System.

## Sound and Piano

At startup, the keyboard plays the Piano notes under **A D G D A Z**, with a
pause before Z. It plays the opening phrase of Adele's “Hello” when the
`hello_kotify` macro starts and two falling notes before entering flashing mode.

- Hold the **bottom-row key under Z** to play Piano. It activates after 200 ms
  or as soon as you press another key. Release it to return to typing.
- Tap the same key three times quickly to keep Piano on. Tap it once to exit.
- In Piano, all other keys play notes on the keyboard's speaker. Notes rise
  from left to right and from the bottom rows to the top.

## RGB

Hold System and use **O / P** to cycle backward / forward through four modes:

| Mode | Behavior |
| --- | --- |
| Key roles (default) | Colors come from each key's current action. Transparent keys use their inherited action; unused keys stay dark. |
| Heatmap | Repeated presses build brightness and move the key's color from blue through green to red. The effect fades over time. |
| Quick fade | Each press lights the key for about 300 ms. Repeated presses restart the fade without building brightness. |
| Finger zones | Fixed colors by finger, mirrored across the two halves. |

Quick fade uses the active layer's color. Finger zones and key roles
use fixed RGB palettes, scaled by the current brightness.

With RGB on, both thumb clusters show the active layer:

| Layer | Color |
| --- | --- |
| English | White |
| Russian | Blue |
| App-Nav | Purple |
| Numbers | Green |
| Symbols | Orange |
| System | Red |
| Piano | Yellow |

The highest-priority active layer determines the indicator color. Temporary
English input for Russian symbols does not change the selected layer's color.
The six status LEDs, left to right, are blue, green, red, blue, green, red; they
can only be on or off. Both blue LEDs are on while Russian is selected. The other status LEDs
only show the startup animation.

**System + Y** toggles all RGB, including the thumb indicators.
**System + U / I** adjusts brightness. Mode, RGB state, and brightness are saved
across reconnects.

The palettes are constants in [rgb.c](rgb.c). Key-role colors are assigned from
the current keymap and need no per-key color table. Letters are white, numbers
green, symbols yellow, modifiers blue, editing keys orange, navigation cyan,
layer keys orange-red, shortcuts magenta, media purple, and system controls red.
Finger zones use pink for pinkies, yellow for ring fingers, green for middle
fingers, and cyan for index fingers.

## Combos

The combo window is 40 ms. Positions below use their English base labels.

| Keys pressed together | Output | Language |
| --- | --- | --- |
| Top-row `.` + `-` | Period, space, then one-shot Shift | EN/RU |
| Top-row `,` + `.` | `,` | EN/RU |
| Top-row `,` + `:` | `;` | EN/RU |
| Top-row quote + `?` | `"` | EN/RU |
| Top-row `?` + `(` | `!` | EN/RU |
| `/` + key immediately to its left | Backslash | EN/RU |
| U + I | Х | RU |
| M + key immediately to its right | Ъ | RU |
| R + T | Ё via the Backslash keycode (`KC_BSLS`) | RU |

Letter and punctuation combos work only on the base layers. Thumb combos work
on every layer except Piano.

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
