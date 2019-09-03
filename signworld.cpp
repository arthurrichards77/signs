#include <iostream>
#include <vector>

//size of the world grid
#define XMAX 10
#define YMAX 10

typedef unsigned long int ord;

// class LOCATION ++++++++++++++++++++++++++++++++++++

class Location {
  public:
    ord x, y;
    Location();
    Location(ord,ord);
    set_xy(ord,ord);
};

Location::Location() {
    x=0;
    y=0;
}

Location::Location(ord x_in,ord y_in) {
    x=x_in;
    y=y_in;
}

Location::set_xy(ord x_in,ord y_in) {
    x=x_in;
    y=y_in;
}

// class WORLD ++++++++++++++++++++++++++++++++++++

class World {
  public:
    bool occ[XMAX][YMAX] = {0};
    void print();
};

void World::print() {
  ord xx,yy;
  for (yy=0;yy<YMAX;yy++) {
    for (xx=0;xx<XMAX;xx++) {
      std::cout << occ[xx][yy];
    }
    std::cout << std::endl;
  }
}

// class AGENT ++++++++++++++++++++++++++++++++++++

class Agent {
    World *p_par_wrl;
  public:
    Location current_location;
    Location goal;
    Agent();
    Agent(World *,ord,ord);
    void set_goal(ord,ord);
    void time_step();
};

Agent::Agent() {}

Agent::Agent(World *p_wrl,ord x, ord y) {
    p_par_wrl = p_wrl;    
    current_location.set_xy(x,y);
    (*p_wrl).occ[x][y] = true;
}

void Agent::set_goal(ord x, ord y){
    goal.set_xy(x,y);
}

void Agent::time_step() {
    std::cout << "Agent at " << current_location.x << "," << current_location.y << 
      " heading to " << goal.x << "," << goal.y << std::endl;
}

// class MODEL ++++++++++++++++++++++++++++++++++++

class Model {
  public:
    World wrl;
    std::vector<Agent> agents;
    void time_step();
    Agent *add_agent(ord,ord);
};

void Model::time_step() {
  for (Agent a : agents) {
    a.time_step();
  }
}

Agent *Model::add_agent(ord x,ord y) {
  Agent a(&wrl,x,y);
  agents.push_back(a);
  return(&a);
}

// MAIN ++++++++++++++++++++++++++++++++++++

int main() {
  Model mdl;
  Agent *a;
  a = mdl.add_agent(3,4);
  (*a).set_goal(7,8);
  a = mdl.add_agent(5,6);
  (*a).set_goal(9,10);
  mdl.time_step();
  mdl.wrl.print();
  return(0);
};
