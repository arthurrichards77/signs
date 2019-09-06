#ifndef AGENT_H
#define AGENT_H

#include<vector>

#include "map.h"

// type def for agent ID
typedef unsigned long int aid;

class Agent {
    Map *p_map;
    aid id;
    void move(ord,ord);
    bool valid_move(Location);
    std::vector<Location> goal_list;
    int current_goal;
  public:
    Location current_location;
    Location goal;
    Agent();
    Agent(Map *,Location);
    Agent(Map *,Location,aid);
    Agent(Map *,ord,ord);
    aid get_id();
    void set_goal(ord,ord);
    void add_goal(ord,ord);
    void update();
    void print();
};

#endif
