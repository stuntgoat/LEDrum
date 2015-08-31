#include "pong.h"


// TODO: settings as arguments
Pong* Initialize_low_high_Pong()
{
  Pong* pong = new Pong{};
  int start;

  start = _random(0, MAX_RAND);

  pong->asc = coin();

  if (start == MAX_RAND) {
    pong->high = start;
    pong->low = _random(0, MAX_RAND - 1);
  } else if (start == 0) {
    pong->low = start;
    pong->high = _random(1, MAX_RAND);
  } else {
    bool up = coin();
    for (int i = 0; i < SHIFT_MID; i++) {
      up |= coin();
    }
    if(up) {
      // Low starting point.
      pong->low = start;
      pong->high = _random(start, MAX_RAND);
    } else {
      // High starting point.
      pong->high = start;
      pong->low = _random(0, start);
    }
  }

  // pong->incr = _random(0, INCR_MAX);
  int diff = pong->high - pong->low;
  int jump = diff;
  int numerator = _random(1, diff);
  if (jump > numerator) {
    pong->incr = _random(numerator, jump);
  } else {
    pong->incr = _random(jump, numerator);
  }

  pong->val = _random(pong->low, pong->high);
  return pong;
}

Pong* cycler(Pong *pong)
{
  return pong;
}

Pong* pulser(Pong *pong)
{
  if (pong->asc) {
    pong->val += pong->incr;
  } else {
    pong->val -= pong->incr;
  }

  int curr = pong->val;
  if (curr < pong->low) {
    pong->val = pong->low;
    pong->asc = true;
    return pong;
  }

  if (curr == pong->low) {
    pong->asc = true;
    return pong;
  }

  if (curr > pong->high) {
    pong->val = pong->high;
    pong->asc = false;
    return pong;
  }

  if (curr == pong->high) {
    pong->asc = false;
    return pong;
  }

  return pong;
}
