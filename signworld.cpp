#include "world.h"
#include "agent.h"
#include <vector>

World w(30,50);

std::vector<Agent> agents;

bool spawn_agent(ord x, ord y, ord gx, ord gy) {
  if (w.get_occ(x,y)) {
    return(false);
  } else {
    agents.push_back(Agent(&w,Location(x,y)));
    agents.back().set_goal(gx,gy);
    return(true);
  }
}

// MAIN ++++++++++++++++++++++++++++++++++++

int main() {
  unsigned long int ii;

  for (ii=0;ii<4;ii++) {
    spawn_agent(15+ii,43,2,3*ii);
  }
  for (ii=0;ii<4;ii++) {
    spawn_agent(17+ii,43,1,3*ii);
  }
  w.print();

  for (ii=0;ii<agents.size();ii++) {
    agents.at(ii).print();
  }

  agents.back().update();

  return(0);
};
