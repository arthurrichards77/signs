#include <stdio.h>
#include "gray.h"

int main() {
  unsigned long int n;
  char binstr[10];

  for (n=0;n<16;n++) {
    printf("%02X : %02X : ",n,gray(n));
    num2binstr(n,4,binstr);
    printf("%s : ",binstr);
    num2binstr(gray(n),4,binstr);
    printf("%s\n",binstr);
  }
  return(0);
}