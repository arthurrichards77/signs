#include "types.h"
#include "sign.h"
#include "sim.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

typedef std::vector<Sign> signset;

// population size
const unsigned int pop_size(10);

// lazy: keep population in a global
signset *pop[pop_size];

unsigned long int eval(signset *st, unsigned long int num_steps) {

  // initialize simulator
  Sim s;
  s.read_agents();

  // add signs
  unsigned int ii;
  for (ii=0;ii<st->size();ii++) s.add_sign(st->at(ii));

  // run and return trip count
  s.run(num_steps);
  return(s.total_trips());

}

void add_random_sign(signset *st, aid amax, ord xmax, ord ymax) {
  aid a1 = (aid) (rand() % amax); 
  aid a2 = ((aid) (rand() % amax) & a1); 
  ord x1 = (ord) (rand() % xmax); 
  ord x2 = ((ord) (rand() % xmax) & x1); 
  ord y1 = (ord) (rand() % ymax); 
  ord y2 = ((ord) (rand() % ymax) & y1); 
  ord xd1 = (ord) (rand() % xmax); 
  ord xd2 = ((ord) (rand() % xmax) & xd1); 
  ord yd1 = (ord) (rand() % ymax); 
  ord yd2 = ((ord) (rand() % ymax) & yd1);
  mv m1 = (mv) (rand() % 8);
  mv m2 = ((mv) (rand() % 8) & m1);
  st->push_back(Sign(Mask<aid>(a1,a2),
                    Mask<ord>(x1,x2),Mask<ord>(y1,y2),
                    Mask<ord>(xd1,xd2),Mask<ord>(yd1,yd2),
                    Mask<mv>(m1,m2)
                   )
              ); 
}

void init_pop() {

  unsigned int ii,jj,num_signs;

  for (ii=0;ii<pop_size;ii++) {
    num_signs = 10 + (rand() % 30);
    pop[ii]=new(signset);
    for (jj=0;jj<num_signs;jj++) {
      add_random_sign(pop[ii],256,128,128);
    }
  }

}

void eval_pop() {
  unsigned long int res;

  unsigned int ii;
  for (ii=0;ii<pop_size;ii++) {
    std::cout << "Member " << ii << " has " << pop[ii]->size() << " signs" << std::endl;
    res = eval(pop[ii],500);
    std::cout << "Member " << ii << " scores " << res << std::endl;
  }

}

int main() {

  unsigned int gg;

  srand(time(NULL));

  init_pop();

  for (gg=0;gg<1;gg++) {

    eval_pop();
    //select_pop();
    //crossover_pop();
    //mutate_pop();

  }

  return(0);

}
