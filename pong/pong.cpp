#include "pong.h"

bool coin()
{
  return ((random(100000) % 2) == 0);
}

int MAX_RAND = 256;

// Typical values of average low and high for SHIFT_MID:
// o-------------------------|
// 0 = 62, 128
// 1 = 94, 159
// 2 = 110, 175
// 3 = 118, 183
// 4 = 122, 187
// --------------------------|

int SHIFT_MID = 4;
Pong* Initialize_low_high_Pong(int max_incr)
{
  Pong* pong = new Pong{};
  int start;

  start = random(0, MAX_RAND);

  pong->asc = coin();

  if (start == MAX_RAND) {
    pong->high = start;
    pong->low = random(0, MAX_RAND - 1);
  } else if (start == 0) {
    pong->low = start;
    pong->high = random(1, MAX_RAND);
  } else {
    bool up = coin();
    for (int i = 0; i < SHIFT_MID; i++) {
      up |= coin();
    }
    if(up) {
      // Low starting point.
      pong->low = start;
      pong->high = random(start, MAX_RAND);
    } else {
      // High starting point.
      pong->high = start;
      pong->low = random(0, start);
    }
  }

  pong->incr = random(0, max_incr);
  pong->val = random(pong->low, pong->high);
  return pong;
}

Pong* cycler(Pong *pong)
{
  if (pong->asc) {
    pong->val += pong->incr;
  } else {
    pong->val -= pong->incr;
  }

  int curr = pong->val;
  if (curr < pong->low) {
    pong->val = pong->high;
    return pong;
  }

  if (curr == pong->low) {
    pong->val = pong->high;
    return pong;
  }

  if (curr > pong->high) {
    pong->val = pong->low;
    return pong;
  }

  if (curr == pong->high) {
    pong->val = pong->low;
    return pong;
  }

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
