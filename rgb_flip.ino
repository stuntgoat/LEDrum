#include <Coroutines.h>
#include "pong.h"

int redPin = 6;
int greenPin = 3;
int bluePin = 5;

int PIEZO = A0;
int THRESHOLD = 50; // Piezo sensitivity.

// Flashing behavior.
int BLINK_LEN_COUNT= 40;
int BLINK_DIM_START= 10;
int BLINK_LEN_INCR = 5;

// pulser settings.
int R_LOW;
int R_HIGH;
int G_LOW;
int G_HIGH;
int B_LOW;
int B_HIGH;

// used by pulser function to cycle colors.
Pong *R;
Pong *G;
Pong *B;


// Values of voltage from the piezo read.
int FIRST;
int SECOND;

// global coroutines queue.
Coroutines<5> coroutines;


void setColor(int red, int green, int blue)
{
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void update_color()
{
  R = pulser(R, R_LOW, R_HIGH);
  G = pulser(G, G_LOW, G_HIGH);
  B = pulser(B, B_LOW, B_HIGH);
}

void update_off()
{
  setColor(0, 0, 0);
}

void blink(COROUTINE_CONTEXT(coroutine))
{
  COROUTINE_LOCAL(int, i);

  BEGIN_COROUTINE;

  for (i = 5; i < BLINK_LEN_COUNT; i += BLINK_LEN_INCR) {
    update_color();
    if (i >= BLINK_DIM_START) {
      setColor(R->val / 2, G->val / 2, B->val / 2);
    } else {
      setColor(R->val, G->val, B->val);
    }
    coroutine.wait(i);
    COROUTINE_YIELD;
    update_off();
    coroutine.wait(i);
    COROUTINE_YIELD;
  }
  update_off();
  END_COROUTINE;
}

void initialize_pulser_settings()
{
  // pulser settings.
  R_LOW = random(0, 50);
  R_HIGH = random(51, 200);
  G_LOW = random(0, 50);
  G_HIGH = random(51, 200);
  B_LOW = random(0, 50);
  B_HIGH = random(51, 200);
}

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  update_off();
  randomSeed(analogRead(0));

  R = new Pong{0, true, 2};
  G = new Pong{0, true, 3};
  B = new Pong{0, true, 4};

  initialize_pulser_settings();
}



void loop() {
  unsigned long time = millis();
  coroutines.update(time);

  FIRST = analogRead(PIEZO);

  if (FIRST > THRESHOLD) {
    delay(5);
    SECOND = analogRead(PIEZO);
    if (SECOND > FIRST) {
      coroutines.start(blink);
    }
  }
}
