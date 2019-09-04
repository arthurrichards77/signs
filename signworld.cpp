#include "world.h"
#include "agent.h"
#include <vector>

World w(30,50);

//std::vector<Agent> agents;

// MAIN ++++++++++++++++++++++++++++++++++++

int main() {
  w.print();

  Agent b(&w,Location(28,48));

  Agent a(&w,15,44);
  a.print();
  w.print();

  a.move(5,44);
  a.print();
  w.print();

  return(0);
};
