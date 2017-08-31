#include "jhash.h"

size_t jenkins_hash(const uint32_t &num){
    return (size_t) jhash_3words (num, 0, 0, 86245);
}

/* NOTE: Arguments are modified. */
#define __jhash_mix(a, b, c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

uint32_t
jhash_3words (uint32_t a, uint32_t b, uint32_t c, uint32_t initval)
{
  a += JHASH_GOLDEN_RATIO;
  b += JHASH_GOLDEN_RATIO;
  c += initval;

  __jhash_mix (a, b, c);

  return c;
}
