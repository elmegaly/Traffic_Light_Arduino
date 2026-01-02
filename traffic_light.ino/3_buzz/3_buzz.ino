// Super Mario (intro phrase) with POT (A0) controlling SPEED (tempo)
// + Smooth tempo (no jitter) + Auto STOP when pot is near zero
// Pot: left->5V, middle->A0, right->GND
// Passive buzzer on D3

const int buz = 3;
const int pot = A0;

// Notes (Hz)
#define NOTE_E7 2637
#define NOTE_C7 2093
#define NOTE_G7 3136
#define NOTE_G6 1568
#define NOTE_E6 1319
#define NOTE_A6 1760
#define NOTE_B6 1976
#define NOTE_AS6 1865
#define NOTE_A7 3520
#define NOTE_F7 2794
#define NOTE_D7 2349
#define NOTE_REST 0

// Mario melody (common intro phrase)
int melody[] = {
  NOTE_E7, NOTE_E7, NOTE_E7,
  NOTE_C7, NOTE_E7, NOTE_G7,
  NOTE_G6,

  NOTE_C7, NOTE_G6, NOTE_E6,
  NOTE_A6, NOTE_B6, NOTE_AS6, NOTE_A6,
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7,
  NOTE_F7, NOTE_G7,
  NOTE_E7, NOTE_C7, NOTE_D7, NOTE_B6
};

// Durations (relative): 12=short, 6=longer, 3=long, etc.
int durations[] = {
  12, 12, 12,
  12, 12, 12,
  6,

  12, 12, 12,
  12, 12, 12, 12,
  9, 9, 9, 12,
  12, 12,
  12, 12, 12, 6
};

void setup() {
  pinMode(buz, OUTPUT);
  pinMode(pot, INPUT);
}

void loop() {
  int potValue = analogRead(pot);

  // STOP if knob is almost at zero
  if (potValue < 50) {
    noTone(buz);
    delay(50);
    return;
  }

  // Map pot to tempo: bigger = slower
  // Adjust these two numbers to taste (min/max speed)
  int targetBase = map(potValue, 0, 1023, 80, 260);

  // Smooth the tempo so turning the pot doesn't cause jumpy timing
  static int smoothBase = 150;
  smoothBase = smoothBase + (targetBase - smoothBase) / 5;
  int baseMs = smoothBase;

  int notes = sizeof(melody) / sizeof(melody[0]);

  for (int i = 0; i < notes; i++) {
    // Update tempo while playing (so it responds mid-song)
    potValue = analogRead(pot);

    // If user turns it down to zero, stop immediately
    if (potValue < 50) {
      noTone(buz);
      return;
    }

    targetBase = map(potValue, 0, 1023, 80, 260);
    smoothBase = smoothBase + (targetBase - smoothBase) / 5;
    baseMs = smoothBase;

    // Convert duration units into milliseconds
    int noteMs = (baseMs * 12) / durations[i];

    if (melody[i] != NOTE_REST) {
      tone(buz, melody[i], noteMs);
    } else {
      noTone(buz);
    }

    // Gap between notes (also follows tempo)
    delay((int)(noteMs * 1.30));
    noTone(buz);
  }

  delay(800); // pause then repeat
}