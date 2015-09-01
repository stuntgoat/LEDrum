#include <Adafruit_NeoPixel.h>
#include <Coroutines.h>


#include "pong.h"

int DIN = 3;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, DIN);

int PIEZO = A5;
int THRESHOLD = 300; // Piezo sensitivity.

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
  uint32_t rgb = strip.Color(red, green, blue);
  for (int i = 0; i < 30; i++) {
    strip.setPixelColor(i, rgb); 
  }
  strip.show();
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
  strip.show();
}

void fake_blink()
{
  update_color();
  for (int i = 5; i < BLINK_LEN_COUNT; i += BLINK_LEN_INCR) {

    if (i >= BLINK_DIM_START) {
      setColor(R->val / 2, G->val / 2, B->val / 2);
    } else {
      setColor(R->val, G->val, B->val);
    }
    delay(10);
    update_off();
    delay(10);

  }
  update_off();
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
  Serial.begin(9600);
  pinMode(DIN, OUTPUT);
 
  randomSeed(analogRead(0));

  R = new Pong{0, true, 2};
  G = new Pong{0, true, 3};
  B = new Pong{0, true, 4};
  initialize_pulser_settings();
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}



void loop() {
  unsigned long time = millis();
  coroutines.update(time);

  FIRST = analogRead(PIEZO);

  if (FIRST > THRESHOLD) {
    coroutines.start(blink);
    //fake_blink();
    delay(1);
    SECOND = analogRead(PIEZO);
    Serial.print("hit first");
    if (SECOND > FIRST) {
      Serial.print("second hit!");
      //coroutines.start(blink);
      //delay(0);
      //fake_blink();
    }
  }
}
