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


