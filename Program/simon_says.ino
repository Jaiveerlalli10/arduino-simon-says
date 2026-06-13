int leds[] = {10, 11, 12, 13};
int buttons[] = {2, 3, 4, 5};
int sequence[100];
int buzzer = 6;
int level = 1;
int notes[] = {262, 330, 392, 523};
boolean gameStarted = false;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
  }

  pinMode(buzzer, OUTPUT);

  randomSeed(analogRead(0));

  for (int i = 0; i < 100; i++) {
    sequence[i] = random(0, 4);
  }
}

void waitForStart() {
  // wait until ANY button is pressed
  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttons[i]) == LOW) {

        // wait release
        while (digitalRead(buttons[i]) == LOW);

        return;
      }
    }
  }
}

// the loop function runs over and over again forever
void flash(int i) {
  tone(buzzer, notes[i]);

  digitalWrite(leds[i], HIGH);
  delay(300);

  digitalWrite(leds[i], LOW);
  noTone(buzzer);

  delay(200);
}

void successSound() {
  tone(buzzer, 800);
  delay(100);
  tone(buzzer, 1000);
  delay(100);
  noTone(buzzer);
}

void loop() {

  if (!gameStarted) {
    waitForStart();
    gameStarted = true;
  }

  showSequence();

  for (int i = 0; i < level; i++) {
    int input = getButtonPress();

    if (input != sequence[i]) {
      wrongSound();
      resetGame();
      delay(1000);
      return;
    } 
  }

  successSound();
  level++;
  delay(500);
}

void resetGame() {
  gameOverFlash();
  level = 1;
  gameStarted = false;
}

void gameOverFlash() {
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) digitalWrite(leds[i], HIGH);
    tone(buzzer, 150);
    delay(150);

    for (int i = 0; i < 4; i++) digitalWrite(leds[i], LOW);
    noTone(buzzer);
    delay(150);
  }
}

void showSequence() {
  for (int i = 0; i < level; i++) {
    flash(sequence[i]);
  }
}

int getButtonPress() {
  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttons[i]) == LOW) {
        flash(i);
        while (digitalRead(buttons[i]) == LOW); // wait for release
        return i;
      }
    }
  }
}

void wrongSound() {
  tone(buzzer, 400);
  delay(200);

  tone(buzzer, 300);
  delay(200);

  tone(buzzer, 200);
  delay(400);

  noTone(buzzer);
}

