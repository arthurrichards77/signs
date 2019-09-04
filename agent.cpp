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

void Agent::move(ord x, ord y){
    p_world->free_occ(current_location.x,current_location.y);
    current_location.set_xy(x,y);
    p_world->take_occ(x,y);
}

void Agent::set_goal(ord x, ord y){
    goal.set_xy(x,y);
}

void Agent::print() {
    std::cout << "Agent at " << current_location.x << "," << current_location.y << 
      " heading to " << goal.x << "," << goal.y << std::endl;
}

bool Agent::valid_move(Location newloc) {
    if (current_location.eq(newloc)) {
      return(true);
    }
    if (!p_world->check_location(newloc)) {
      return(false);
    } 
    if (p_world->get_occ(newloc.x,newloc.y)) {
      return(false);
    } 
    return(true);
} 

void Agent::update() {
    unsigned int mv;
    float best_cost=1e9;
    Location best_loc;
    // try all moves
    for (mv=0;mv<16;mv++) {
      best_loc = current_location.decode_move(mv);
      if (valid_move(best_loc)) {
        best_loc.print();
        std::cout << std::endl;
      }
    }
}
