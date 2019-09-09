#include "sign.h"

#include <iostream>

Sign::Sign() {
  agent_and_mask = 0;
  agent_xor_mask = 1;
  xloc_and_mask = 0;
  xloc_xor_mask = 1;
  yloc_and_mask = 0;
  yloc_xor_mask = 1;
}

Sign::Sign(id a1,id a2,id x1,id x2,id y1,id y2, mv m1, mv m2){
  agent_and_mask = a1;
  agent_xor_mask = a2;
  xloc_and_mask = x1;
  xloc_xor_mask = x2;
  yloc_and_mask = y1;
  yloc_xor_mask = y2;
  move_and_mask = m1;
  move_xor_mask = m2;
}

bool Sign::applies(id a,id x,id y) {
  bool result = false;
  if (((a&agent_and_mask)^agent_xor_mask)==0)
    if (((x&xloc_and_mask)^xloc_xor_mask)==0)
      if (((y&yloc_and_mask)^yloc_xor_mask)==0) { 
        result = true;
        std::cout << "Sign [" << agent_and_mask <<","<< agent_xor_mask <<","
                              << xloc_and_mask <<","<< xloc_xor_mask <<","
                              << yloc_and_mask <<","<< yloc_xor_mask <<"] applies to ("
                              << a << "," << x << "," << y << ")" << std::endl; 
      }
  return(result);
}

bool Sign::permits(mv m) {
  bool result = true;
  if (((m&move_and_mask)^move_xor_mask)==0) {
    result = false;
//    std::cout << "Mask [" << move_and_mask << "," << move_xor_mask << "] permits move " << m << " " << (m&move_and_mask) << " " << ((m&move_and_mask)^move_xor_mask) << std::endl;
  }
//  else {
//    std::cout << "Mask [" << move_and_mask << "," << move_xor_mask << "] blocks move " << m << " " << (m&move_and_mask) << " " << ((m&move_and_mask)^move_xor_mask) << std::endl;
//  }
  return(result);
};

bool Sign::check_move(id a, id x, id y, mv m) {
  bool result = true;
  if (applies(a,x,y)) result = permits(m);
  return(result);
}

