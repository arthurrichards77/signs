#include "gray.h"

unsigned long int gray(unsigned long int bin) {
  unsigned long int res;

  /* convert to Gray code: R = N XOR (N/2) */
  res = bin >> 1;
  res = res ^ bin;
  return(res);
}

unsigned long int num2binstr(unsigned long int n, int nbits, char *s) {
  int ii;

  /* terminating zero after last bit */
  s[nbits]=0;
  
  /* work backwards through bits from LSB to nbits */
  for (ii=1;ii<=nbits;ii++) {
    if ((n&1)==1) {
      s[nbits-ii]='1';
    } else {
      s[nbits-ii]='0';
    }
    n = n >> 1;
  }

  /* return anything leftover - zero if you got the whole value */
  return(n);
}