#include "world.h"
#include "agent.h"
#include <vector>
#include <iostream>

World w(30,50);

std::vector<Agent> agents;

bool spawn_agent(ord x, ord y, ord gx, ord gy) {
  if (w.get_occ(x,y)) {
    return(false);
  } else {
    agents.push_back(Agent(&w,Location(x,y),agents.size()));
    agents.back().set_goal(gx,gy);
    return(true);
  }
}

// MAIN ++++++++++++++++++++++++++++++++++++

int main() {
  unsigned long int ii;
  unsigned long int kk;

  for (ii=0;ii<4;ii++) {
    spawn_agent(15+ii,43,2,3*ii);
  }
  for (ii=0;ii<4;ii++) {
    spawn_agent(17+ii,43,1,3*ii);
  }

  for (kk=1;kk<=100;kk++) {

    w.print();

    // forward update
    for (ii=0;ii<agents.size();ii++) {
      agents.at(ii).print();
      agents.at(ii).update();
    }

    w.print();

    // backward update
    for (ii=0;ii<agents.size();ii++) {
      agents.at(agents.size()-1-ii).print();
      agents.at(agents.size()-1-ii).update();
    }


  }

  return(0);
};
