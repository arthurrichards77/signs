#ifndef SIGN_H
#define SIGN_H

typedef unsigned long int id;
typedef unsigned int mv;

class Sign{
    id agent_and_mask;
    id agent_xor_mask;
    id xloc_and_mask;
    id xloc_xor_mask;
    id yloc_and_mask;
    id yloc_xor_mask;
    id xdst_and_mask;
    id xdst_xor_mask;
    id ydst_and_mask;
    id ydst_xor_mask;
    mv move_and_mask;
    mv move_xor_mask;
  public:
    Sign();
    Sign(id,id,id,id,id,id,id,id,id,id,mv,mv);
    bool applies(id,id,id,id,id);
    bool permits(mv);
    bool check_move(id,id,id,id,id,mv);
};

#endif
