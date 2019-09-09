#include "sign.h"

Sign::Sign() {
  agent_and_mask = 0;
  agent_xor_mask = 1;
  xloc_and_mask = 0;
  xloc_xor_mask = 1;
  yloc_and_mask = 0;
  yloc_xor_mask = 1;
}

Sign::Sign(aid a1,aid a2,ord x1,ord x2,ord y1,ord y2){
  agent_and_mask = a1;
  agent_xor_mask = a2;
  xloc_and_mask = x1;
  xloc_xor_mask = x2;
  yloc_and_mask = y1;
  yloc_xor_mask = y2;
}

bool Sign::applies(aid a,ord x,ord y) {
  bool result = false;
  if ((a&agent_and_mask)^agent_xor_mask==0)
    if ((x&xloc_and_mask)^xloc_xor_mask==0)
      if ((y&yloc_and_mask)^yloc_xor_mask==0) { result = true; }
  return(result);
}

bool Sign::permits(unsigned int mv) {
  bool result = false;
  if ((mv&move_and_mask)^move_xor_mask==0) result = true;
  return(result);
};

bool Sign::check_move(aid a, ord x, ord y, unsigned int mv) {
  bool result = true;
  if (applies(a,x,y)) result = permits(mv);
  return(result);
}

