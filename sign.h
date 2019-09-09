#ifndef SIGN_H
#define SIGN_H

#include "agent.h"
#include "map.h"

class Sign{
    aid agent_and_mask;
    aid agent_xor_mask;
    ord xloc_and_mask;
    ord xloc_xor_mask;
    ord yloc_and_mask;
    ord yloc_xor_mask;
    unsigned int move_and_mask;
    unsigned int move_xor_mask;
  public:
    Sign();
    Sign(aid,aid,ord,ord,ord,ord);
    bool applies(aid,ord,ord);
    bool permits(unsigned int);
    bool check_move(aid,ord,ord,unsigned int);
};

#endif
