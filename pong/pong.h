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

Pong* Initialize_low_high_Pong(int max_incr);

Pong* pulser(Pong *pong);

Pong* cycler(Pong *pong);

bool coin(void);

#endif // PONG_
