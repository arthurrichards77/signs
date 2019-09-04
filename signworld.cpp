#include "world.h"
#include "agent.h"

// MAIN ++++++++++++++++++++++++++++++++++++

int main() {
  World w(30,50);
  w.print();

  Agent a(&w,15,44);
  a.print();
  w.print();

  return(0);
};
