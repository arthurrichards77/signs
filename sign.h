#ifndef SIGN_H
#define SIGN_H

#include "types.h"

class Sign{
    aid agent_and_mask;
    aid agent_xor_mask;
    ord xloc_and_mask;
    ord xloc_xor_mask;
    ord yloc_and_mask;
    ord yloc_xor_mask;
    ord xdst_and_mask;
    ord xdst_xor_mask;
    ord ydst_and_mask;
    ord ydst_xor_mask;
    mv move_and_mask;
    mv move_xor_mask;
  public:
    Sign();
    Sign(aid,aid,ord,ord,ord,ord,ord,ord,ord,ord,mv,mv);
    bool applies(aid,ord,ord,ord,ord);
    bool permits(mv);
    bool check_move(aid,ord,ord,ord,ord,mv);
};

#endif
