#ifndef AGENT_H
#define AGENT_H

#include "world.h"

// type def for agent ID
typedef unsigned long int aid;

class Agent {
    World *p_world;
    aid id;
  public:
    Location current_location;
    Location goal;
    Agent();
    Agent(World *,ord,ord);
    void set_goal(ord,ord);
    void print();
};

#endif
