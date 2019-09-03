#include <iostream>
#include <vector>

typedef unsigned long int ord;



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



class World {
    Location extreme;
  public:
    World();
    World(ord,ord);
};

World::World() {
    extreme.set_xy(10,10);
}

World::World(ord max_x, ord max_y) {
    extreme.set_xy(max_x,max_y);
}



class Agent {
    Location current_location;
    Location goal;
  public:
    Agent(ord,ord);
    void set_goal(ord,ord);
    void time_step(World);
};

Agent::Agent(ord x, ord y) {
    current_location.set_xy(x,y);
}

void Agent::set_goal(ord x, ord y){
    goal.set_xy(x,y);
}

void Agent::time_step(World w) {
    std::cout << "Agent at " << current_location.x << "," << current_location.y << 
      " heading to " << goal.x << "," << goal.y << std::endl;
}



class Model {
    World wrl;
    std::vector<Agent> agents;
  public:
    void time_step();
    void add_agent(Agent);
    void set_limits(ord,ord);
};

void Model::time_step() {
  for (Agent a : agents) {
    a.time_step(wrl);
  }
}

void Model::add_agent(Agent a) {
  agents.push_back(a);
}



int main() {
  Model mdl;
  mdl.add_agent(Agent(3,4));
  mdl.add_agent(Agent(5,6));
  mdl.time_step();
  return(0);
};
