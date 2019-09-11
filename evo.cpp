#include "types.h"
#include "sign.h"
#include "sim.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>

typedef std::vector<Sign> signset;

// population size
const unsigned int pop_size=50;

// lazy: keep population in a global
signset *pop[pop_size];

// storage of fitness evaluations
typedef struct {
  unsigned int id;
  unsigned long int fitness; 
} evaluation;
std::vector<evaluation> evals;

// ***** UTILITIES *****

bool random_choice(float prob_true) {
  bool res = false;
  float r = rand();
  if (r<(RAND_MAX*prob_true)) res=true;
  return(res);
}

// ***** INDIVIDUAL STUFF *****

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

void print_signs(signset *st) {
  int ii;
  for (ii=0;ii<st->size();ii++) {
    st->at(ii).print();
  }
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

void drop_random_sign(signset *st) {
  int r;
  if (st->size()>0) {
    r = rand() % st->size();
    st->erase(st->begin()+r);
  }
}

void mutate_one_sign(signset *st) {
  int r;
  if (st->size()>0) {
    r = rand() % st->size();
    st->at(r).mutate(8,7);
  }
}


void copy_half_signs(signset *ch, signset *pa) {
  unsigned int ii;
  for (ii=0;ii<pa->size();ii++) {
    if (random_choice(0.5)) {
      ch->push_back(pa->at(ii)); 
    }
  }
}

void crossover(signset *ch, signset *p1, signset *p2) {
  // wipe the child signs
  ch->clear();
  copy_half_signs(ch,p1);
  copy_half_signs(ch,p2);
}

// ***** POPULATION STUFF

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

bool comp (evaluation e1, evaluation e2) {
  return (e1.fitness>e2.fitness);
}

void eval_pop() {
  evaluation e;
  unsigned int ii;

  evals.clear();
  for (ii=0;ii<pop_size;ii++) {
    std::cout << "Member " << ii << " has " << pop[ii]->size() << " signs" << std::endl;
    e.id = ii;
    e.fitness = eval(pop[ii],500);
    std::cout << "Member " << ii << " scores " << e.fitness << std::endl;
    // store for sorting
    evals.push_back(e);
  }
  std::sort(evals.begin(),evals.end(),comp);
  for (ii=0;ii<pop_size;ii++) {
    std::cout << "Place " << ii+1 << " is member " << evals.at(ii).id << " with fitness " << evals.at(ii).fitness << std::endl;
  }

}

void breed_pop() {
  int keepers = 20;
  int p1,p2,ii;

  for (ii=keepers;ii<pop_size;ii++) {
    p1 = rand() % (keepers-1);
    p2 = p1 + 1 + (rand() % (keepers-p1-1));
    std::cout << "Replacing " << evals[ii].id << " with child of " 
              << evals[p1].id << " and " << evals[p2].id << std::endl; 
    crossover(pop[evals[ii].id],pop[evals[p1].id],pop[evals[p2].id]);
  }
}

void mutate_pop() {

  unsigned int ii;
  for (ii=0;ii<pop_size;ii++) {
    if (random_choice(0.2)) {
      std::cout << "Adding random sign to member " << ii << std::endl; 
      add_random_sign(pop[ii],256,128,128);
    }
    if (random_choice(0.2)) {
      std::cout << "Dropping random sign from member " << ii << std::endl; 
      drop_random_sign(pop[ii]);
    }
    if (random_choice(0.2)) {
      std::cout << "Mutating single sign in member " << ii << std::endl; 
      mutate_one_sign(pop[ii]);
    }
  }
}

// ***** MAIN LOOP

int main() {

  unsigned int gg;

  srand(time(NULL));

  init_pop();
  eval_pop();

  for (gg=0;gg<500;gg++) {
    std::cout << "GENERATION " << gg << std::endl;
    print_signs(pop[evals.front().id]);
    breed_pop();
    mutate_pop();
    eval_pop();

  }

  return(0);

}
