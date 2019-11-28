#ifndef AGENT_H
#define AGENT_H

#include "map.h"
#include "types.h"

#include<vector>

class Agent {
    Map *p_map;
    aid id;
    void move(ord,ord);
    bool valid_move(Location);
    std::vector<Location> goal_list;
    int current_goal;
    int num_trips;
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
    int get_num_trips();
};

#endif
