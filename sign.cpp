#include "sign.h"

#include "gray.h"
#include <iostream>

#include <stdlib.h>

Sign::Sign(Mask <aid> a,Mask <ord> x,Mask <ord> y,Mask <ord> xd,Mask <ord> yd,Mask <mv> m){
  agent_mask = a;
  xloc_mask = x;
  yloc_mask = y;
  xdst_mask = xd;
  ydst_mask = yd;
  move_mask = m;
}

void Sign::mutate(int max_aid_bit,int max_ord_bit) {
  int r = rand();
  if (r<RAND_MAX/6) agent_mask.mutate(max_aid_bit);
  else if (r<RAND_MAX/3) xloc_mask.mutate(max_ord_bit);
  else if (r<RAND_MAX/2) yloc_mask.mutate(max_ord_bit);
  else if (r<(RAND_MAX/3)*2) xdst_mask.mutate(max_ord_bit);
  else if (r<(RAND_MAX/6)*5) ydst_mask.mutate(max_ord_bit);
  else move_mask.mutate(3);
}

void Sign::print() {
  std::cout << "(" << agent_mask.get_and() << "," << agent_mask.get_xor() << ") ";
  std::cout << "(" << xloc_mask.get_and() << "," << xloc_mask.get_xor() << ") ";
  std::cout << "(" << yloc_mask.get_and() << "," << yloc_mask.get_xor() << ") ";
  std::cout << "(" << xdst_mask.get_and() << "," << xdst_mask.get_xor() << ") ";
  std::cout << "(" << ydst_mask.get_and() << "," << ydst_mask.get_xor() << ") ";
  std::cout << "(" << move_mask.get_and() << "," << move_mask.get_xor() << ") ";
  std::cout << std::endl;
}

bool Sign::applies(aid a,ord x,ord y,ord xd,ord yd) {
  bool result = false;
  if (agent_mask.match(a))
    if (xloc_mask.match(x))
      if (yloc_mask.match(y))  
        if (xdst_mask.match(xd))
          if (ydst_mask.match(yd)) { 
            result = true;
          }
  return(result);
}

bool Sign::permits(mv m) {
  bool result = true;
  if (move_mask.match(m)) {
    result = false;
  }
  return(result);
};

bool Sign::check_move(aid a, ord x, ord y, ord xd, ord yd, mv m) {
  bool result = true;
  if (applies(a,x,y,xd,yd)) result = permits(m);
//  if (!result) {
//        std::cout << "Sign [" << agent_and_mask <<","<< agent_xor_mask <<","
//                              << xloc_and_mask <<","<< xloc_xor_mask <<","
//                              << yloc_and_mask <<","<< yloc_xor_mask <<","
//                              << xdst_and_mask <<","<< xdst_xor_mask <<","
//                              << ydst_and_mask <<","<< ydst_xor_mask 
//                              <<"] blocking move " << m 
//                              << " at (" 
//                              << a << "," << x << "," << y << "," << xd << "," << yd << ")" 
//                              << std::endl; 
//  }
  return(result);
}

