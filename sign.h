#ifndef SIGN_H
#define SIGN_H

#include "types.h"
#include "gray.h"
#include <stdlib.h>

template <class T>
class Mask {
    T xor_mask;
    T and_mask;
  public:
    Mask ();
    Mask (T, T);
    T get_xor() {return(xor_mask);};
    T get_and() {return(and_mask);};
    bool match(T);
    void mutate(unsigned int);
};

template <class T>
Mask<T>::Mask (T a, T x) {
  and_mask = a;
  xor_mask = x;
}

template <class T>
Mask<T>::Mask () {
  and_mask = 0;
  xor_mask = 1;
}

template <class T>
bool Mask<T>::match (T u) {
  bool res = false;
  if (((gray(u)&and_mask)^xor_mask)==0) res=true;
  return(res);
}

template <class T>
void Mask<T>::mutate(unsigned int max_bit) {
  unsigned int mut_bit = rand() % max_bit;
  T mut = 1 << mut_bit;
  if (rand()<(RAND_MAX/2)) {
    and_mask = and_mask ^ mut;
  }
  else {
    xor_mask = xor_mask ^ mut;
    and_mask = and_mask | mut;
  }
}

class Sign{
    Mask <aid> agent_mask;
    Mask <ord> xloc_mask;
    Mask <ord> yloc_mask;
    Mask <ord> xdst_mask;
    Mask <ord> ydst_mask;
    Mask <mv> move_mask;
  public:
    Sign(Mask <aid>,Mask <ord>,Mask <ord>,Mask <ord>,Mask <ord>,Mask <mv>);
    bool applies(aid,ord,ord,ord,ord);
    bool permits(mv);
    bool check_move(aid,ord,ord,ord,ord,mv);
    void print();
    void mutate(int,int);
};

#endif
