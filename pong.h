#include "Arduino.h"

#ifndef PONG_   /* Include guard */
#define PONG_

typedef struct Pong {
  int val;
  bool asc;
  int incr;

  int low;
  int high;

} Pong;

Pong* pulser(Pong *pong);

pulser_settings* get_pulser_settings(pulser_settings *settings);

#endif // PONG_
