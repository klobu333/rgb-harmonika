// RGB Harmonika - prototype (3 LEDs + 3 buttons, "wait mode")
// The LED of the next button lights up and stays on until that button is pressed,
// then the sequence moves to the next note (Guitar Hero style, but it waits for you).
//
// Wiring:
//   LEDs:    pins 2, 3, 4  -> 220 ohm resistor -> LED -> GND
//   Buttons: pins 9, 11, 13 -> button -> GND (internal pull-up, pressed = LOW)

const int NUM_BUTTONS = 3;
const int ledPins[NUM_BUTTONS]    = {2, 3, 4};
const int buttonPins[NUM_BUTTONS] = {9, 11, 13};

// Fixed practice sequence (indexes 0-2). Replace with a real melody later.
const int sequence[] = {0, 1, 2, 1, 0, 2, 2, 1, 0};
const int SEQ_LENGTH = sizeof(sequence) / sizeof(sequence[0]);

const unsigned long DEBOUNCE_MS = 30;

int step = 0;
bool lastState[NUM_BUTTONS];
unsigned long lastChange[NUM_BUTTONS];

void showStep(int s) {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    digitalWrite(ledPins[i], i == sequence[s] ? HIGH : LOW);
  }
}

void celebrate() {
  // Short blink of all LEDs when the sequence is finished
  for (int r = 0; r < 3; r++) {
    for (int i = 0; i < NUM_BUTTONS; i++) digitalWrite(ledPins[i], HIGH);
    delay(150);
    for (int i = 0; i < NUM_BUTTONS; i++) digitalWrite(ledPins[i], LOW);
    delay(150);
  }
}

// Returns the index of a newly pressed button, or -1 if none
int readPress() {
  unsigned long now = millis();
  for (int i = 0; i < NUM_BUTTONS; i++) {
    bool pressed = digitalRead(buttonPins[i]) == LOW;
    if (pressed != lastState[i] && now - lastChange[i] > DEBOUNCE_MS) {
      lastChange[i] = now;
      lastState[i] = pressed;
      if (pressed) return i;
    }
  }
  return -1;
}

void setup() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastState[i] = false;
    lastChange[i] = 0;
  }
  Serial.begin(9600);
  showStep(step);
}

void loop() {
  int pressed = readPress();
  if (pressed < 0) return;

  if (pressed == sequence[step]) {
    step++;
    if (step >= SEQ_LENGTH) {
      Serial.println("Sequence complete!");
      celebrate();
      step = 0;
    }
    showStep(step);
  } else {
    Serial.print("Wrong button: ");
    Serial.println(pressed);
  }
}
