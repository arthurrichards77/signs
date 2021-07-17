#include <iostream>
#include <assert.h>
#include "agent.h"

Agent::Agent() {}

Agent::Agent(Map *p_wrl,ord x, ord y) {
    p_map = p_wrl;
    starting_location.set_xy(x,y);
    current_location.set_xy(x,y);
    p_map->take_occ(x,y);
    current_goal=0;
    num_trips=0;
}

Agent::Agent(Map *p_wrl,Location loc) {
    p_map = p_wrl;
    starting_location.set_xy(loc.x,loc.y);
    current_location.set_xy(loc.x,loc.y);
    p_map->take_occ(loc.x,loc.y);
    current_goal=0;
    num_trips=0;
}

Agent::Agent(Map *p_wrl,Location loc,aid set_id) {
    id = set_id;
    p_map = p_wrl;    
    starting_location.set_xy(loc.x,loc.y);
    current_location.set_xy(loc.x,loc.y);
    p_map->take_occ(loc.x,loc.y);
    current_goal=0;
    num_trips=0;
}

aid Agent::get_id(){
    return(id);
}

void Agent::reset(){
    current_location.set_xy(starting_location.x,starting_location.y);
    p_map->take_occ(starting_location.x,starting_location.y);
    current_goal=0;
    num_trips=0;
    goal.set_xy(goal_list.at(current_goal).x,goal_list.at(current_goal).y);
}

void Agent::move(ord x, ord y){
    p_map->free_occ(current_location.x,current_location.y);
    current_location.set_xy(x,y);
    p_map->take_occ(x,y);
}

void Agent::set_goal(ord x, ord y){
    add_goal(x,y);
    goal.set_xy(x,y);
    current_goal = goal_list.size()-1;
}

void Agent::add_goal(ord x, ord y){
    goal_list.push_back(Location(x,y));
}

void Agent::print() {
    std::cout << "Agent " << id << " at " << current_location.x << "," << current_location.y << 
      " heading to " << goal.x << "," << goal.y << " after " << num_trips << " trips completed" << std::endl;
}

unsigned int Agent:: get_num_trips() {
    return(num_trips);
}

bool Agent::valid_move(Location newloc) {
    //always OK to stay put
    if (current_location.eq(newloc)) {
      return(true);
    }
    // can't go off the map
    if (!p_map->check_location(newloc)) {
      return(false);
    }
    // can't already be occupied 
    if (p_map->get_occ(newloc.x,newloc.y)) {
      return(false);
    } 
    // prevent diagonal cutting across another agent
    if (newloc.x!=current_location.x) {
      if (p_map->get_occ(newloc.x,current_location.y)) {
        return(false);
      } 
    }
    if (newloc.y!=current_location.y) {
      if (p_map->get_occ(current_location.x,newloc.y)) {
        return(false);
      } 
    }
    return(true);
} 

void Agent::update() {
    unsigned int mv;
    ord best_cost,new_cost;
    Location best_loc,new_loc;
    // start with staying put
    best_loc = Location(current_location.x,current_location.y);
    best_cost = current_location.distance(goal)+2; // slight penalty for not moving
    // try all other moves
    for (mv=0;mv<8;mv++) {
      // first check against signs
      if (p_map->check_move(id,
                            current_location.x,current_location.y,
                            goal.x,goal.y, mv)
                           ) {
        new_loc = current_location.decode_move(mv);
        // check against other agents and end of world
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
    }
    // execute the move
    move(best_loc.x,best_loc.y);
    // have I reached my goal?
    if (current_location.eq(goal)) {
      //std::cout << "Agent " << id << " reached goal!" << std::endl;
      // move on to next goal if there is one
      if (goal_list.size()>1) {
        num_trips++;
        current_goal++;
        if (current_goal==goal_list.size()) current_goal=0;
        goal.set_xy(goal_list.at(current_goal).x,goal_list.at(current_goal).y);
      }
    }
}
