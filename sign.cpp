#include "sign.h"

#include "gray.h"
#include <iostream>

Sign::Sign() {
  agent_and_mask = 0;
  agent_xor_mask = 1;
  xloc_and_mask = 0;
  xloc_xor_mask = 1;
  yloc_and_mask = 0;
  yloc_xor_mask = 1;
  xdst_and_mask = 0;
  xdst_xor_mask = 1;
  ydst_and_mask = 0;
  ydst_xor_mask = 1;
}

Sign::Sign(aid a1,aid a2,ord x1,ord x2,ord y1,ord y2,ord xd1,ord xd2,ord yd1,ord yd2, mv m1, mv m2){
  agent_and_mask = a1;
  agent_xor_mask = a2;
  xloc_and_mask = x1;
  xloc_xor_mask = x2;
  yloc_and_mask = y1;
  yloc_xor_mask = y2;
  xdst_and_mask = xd1;
  xdst_xor_mask = xd2;
  ydst_and_mask = yd1;
  ydst_xor_mask = yd2;
  move_and_mask = m1;
  move_xor_mask = m2;
}

bool Sign::applies(aid a,ord x,ord y,ord xd,ord yd) {
  bool result = false;
  if (((gray(a)&agent_and_mask)^agent_xor_mask)==0)
    if (((gray(x)&xloc_and_mask)^xloc_xor_mask)==0)
      if (((gray(y)&yloc_and_mask)^yloc_xor_mask)==0)  
        if (((gray(xd)&xdst_and_mask)^xdst_xor_mask)==0)
          if (((gray(yd)&ydst_and_mask)^ydst_xor_mask)==0) { 
            result = true;
          }
  return(result);
}

bool Sign::permits(mv m) {
  bool result = true;
  if (((gray(m)&move_and_mask)^move_xor_mask)==0) {
    result = false;
  }
  return(result);
};

bool Sign::check_move(aid a, ord x, ord y, ord xd, ord yd, mv m) {
  bool result = true;
  if (applies(a,x,y,xd,yd)) result = permits(m);
  if (!result) {
        std::cout << "Sign [" << agent_and_mask <<","<< agent_xor_mask <<","
                              << xloc_and_mask <<","<< xloc_xor_mask <<","
                              << yloc_and_mask <<","<< yloc_xor_mask <<","
                              << xdst_and_mask <<","<< xdst_xor_mask <<","
                              << ydst_and_mask <<","<< ydst_xor_mask 
                              <<"] blocking move " << m 
                              << " at (" 
                              << a << "," << x << "," << y << "," << xd << "," << yd << ")" 
                              << std::endl; 
  }
  return(result);
}

