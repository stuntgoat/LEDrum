#include <Adafruit_NeoPixel.h>
#include <Coroutines.h>
#include "pong.h"


int DIN = 3;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, DIN);

int PIEZO = A5;
int THRESHOLD = 60; // Piezo sensitivity.

// Flashing behavior.
int BLINK_LEN_COUNT= 25;
int BLINK_DIM_START= 12;
int BLINK_LEN_INCR = 2;

// used by pulser function to cycle colors.
Pong *R;
Pong *G;
Pong *B;

// Values of voltage from the piezo read.
int FIRST;

// global coroutines queue.
Coroutines<5> coroutines;


void setColor(int red, int green, int blue)
{
  uint32_t rgb = strip.Color(red, green, blue);
  for (int i = 0; i < 30; i++) {
    strip.setPixelColor(i, rgb);
  }
  delayMicroseconds(7);
  strip.show();
  delayMicroseconds(7);
}

void update_color()
{
  R = pulser(R);
  G = pulser(G);
  B = pulser(B);
}

void update_off()
{
  setColor(0, 0, 0);
  delayMicroseconds(7);
  strip.show();
  delayMicroseconds(7);
}

void blink(COROUTINE_CONTEXT(coroutine))
{
  COROUTINE_LOCAL(int, i);

  BEGIN_COROUTINE;
  update_color();
  for (i = 5; i < BLINK_LEN_COUNT; i += BLINK_LEN_INCR) {
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


void setup()
{
  Serial.begin(9600);
  pinMode(DIN, OUTPUT);

  randomSeed(analogRead(0));

  R = Initialize_low_high_Pong(10);
  G = Initialize_low_high_Pong(10);
  B = Initialize_low_high_Pong(10);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

int SECOND;
int C = 0;
void loop() {
  unsigned long time = millis();
  coroutines.update(time);


  if (C > 0) {
    C -= 1;
    return;
  }
  FIRST = analogRead(PIEZO);
  C = 0;
  if (FIRST > THRESHOLD) {
    SECOND = analogRead(PIEZO);
    if(SECOND > FIRST + 20) {
      coroutines.start(blink);
      C = 1;
    }
  }
}
