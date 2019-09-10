#include <stdio.h>
#include "gray.h"

int main() {
  unsigned long int n;
  char binstr[10];

  for (n=0;n<256;n++) {
    printf("%02lu : %02lu : ",n,gray(n));
    printf("%02lX : %02lX : ",n,gray(n));
    num2binstr(n,8,binstr);
    printf("%s : ",binstr);
    num2binstr(gray(n),8,binstr);
    printf("%s\n",binstr);
  }
  return(0);
}
