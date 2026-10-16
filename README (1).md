# RGB Harmonika

An LED practice aid for the **diatonic button accordion** (frajtonarica / Steirische Harmonika), the traditional instrument played across Slovenia, Austria and Bavaria.

LEDs light up the button the player should press. In **wait mode** (similar to Guitar Hero, but it waits for you) the light stays on until the correct button is pressed, then moves on to the next note.

## Why

I teach diatonic accordion. The hardest part for beginners is learning which of the 30+ buttons to press, and in which bellows direction. There is no illuminated learning tool for this instrument, so I'm building one, first for my own pupils and then as an open project other teachers and makers can build.

## Current status

- [x] Concept and architecture (one LED per button, button matrix, USB power)
- [x] 3-LED + 3-button wait-mode prototype, validated in simulation (Tinkercad)
- [ ] Physical prototype with real buttons
- [ ] Full 36-button board (6x6 matrix, 12 pins)
- [ ] Move from Arduino Nano/Uno to Raspberry Pi Pico
- [ ] Load real songs (from tablature) instead of a fixed sequence

## Prototype wiring

| Part      | Pins        | Notes                                    |
|-----------|-------------|------------------------------------------|
| LEDs      | 2, 3, 4     | each through a 220 Ω resistor to GND     |
| Buttons   | 9, 11, 13   | to GND, using internal pull-up           |

Code: [`rgb_harmonika_prototip.ino`](rgb_harmonika_prototip.ino)

## Target hardware

- 3-row, 36-button diatonic accordion layout (tested on C-F-B tuning)
- ~19 mm button spacing, ~15 mm button diameter
- Tact/micro switch + 3D-printed translucent cap + separate LED (WS2812B addressable LEDs planned)

## Prior work

Mi(di)atonerca (PIFcamp / MITTELAB, 2017), an early prototype that used photointerrupters and WS2812 LEDs under translucent button rings.

## License

MIT
