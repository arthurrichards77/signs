#include <iostream>
#include <assert.h>
#include "agent.h"

Agent::Agent() {}

Agent::Agent(World *p_wrl,ord x, ord y) {
    p_world = p_wrl;    
    current_location.set_xy(x,y);
    p_world->take_occ(x,y);
}

Agent::Agent(World *p_wrl,Location loc) {
    p_world = p_wrl;    
    current_location.set_xy(loc.x,loc.y);
    p_world->take_occ(loc.x,loc.y);
}

Agent::Agent(World *p_wrl,Location loc,aid set_id) {
    id = set_id;
    p_world = p_wrl;    
    current_location.set_xy(loc.x,loc.y);
    p_world->take_occ(loc.x,loc.y);
}

void Agent::move(ord x, ord y){
    p_world->free_occ(current_location.x,current_location.y);
    current_location.set_xy(x,y);
    p_world->take_occ(x,y);
}

void Agent::set_goal(ord x, ord y){
    goal.set_xy(x,y);
}

void Agent::print() {
    std::cout << "Agent " << id << " at " << current_location.x << "," << current_location.y << 
      " heading to " << goal.x << "," << goal.y << std::endl;
}

bool Agent::valid_move(Location newloc) {
    //always OK to stay put
    if (current_location.eq(newloc)) {
      return(true);
    }
    // can't go off the map
    if (!p_world->check_location(newloc)) {
      return(false);
    }
    // can't already be occupied 
    if (p_world->get_occ(newloc.x,newloc.y)) {
      return(false);
    } 
    return(true);
} 

void Agent::update() {
    unsigned int mv;
    float best_cost=1e9,new_cost;
    Location best_loc,new_loc;
    // try all moves
    for (mv=0;mv<16;mv++) {
      new_loc = current_location.decode_move(mv);
      if (valid_move(new_loc)) {
        new_cost = new_loc.distance(goal);
        if (new_cost<best_cost) {
          //new_loc.print();
          //std::cout << " gives improved cost= " << new_cost << std::endl;
          best_cost = new_cost;
          best_loc = new_loc;
        }
      }
    }
    // execute the move
    move(best_loc.x,best_loc.y);
}
