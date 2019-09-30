#include "types.h"
#include "sign.h"
#include "sim.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef std::vector<Sign> signset;

// population size
unsigned int pop_size=60;
// lazy: keep population in a global
std::vector<signset*> pop;

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

void print_signs2(signset *st) {
  int ii;
  for (ii=0;ii<st->size();ii++) {
    st->at(ii).print();
  }
}

void print_signs(signset *st) {
  int ii;
  char s[1000];
  for (ii=0;ii<st->size();ii++) {
    st->at(ii).c_str(s);
    std::cout << s << std::endl;
  }
}

void save_signs(signset *st, char *fn) {
  int ii;
  char s[1000];
  FILE *outfile;
  outfile = fopen(fn,"w");
  if (outfile!=NULL) {
    for (ii=0;ii<st->size();ii++) {
      st->at(ii).c_str(s);
      fprintf(outfile,"%s\n",s);
    }
    fclose(outfile);
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

void openup_one_sign(signset *st) {
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
      ch->push_back(Sign(pa->at(ii))); 
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
    pop.push_back(new(signset));
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
    std::cout << "Member " << ii << " has " << pop[ii]->size() << " signs";
    e.id = ii;
    e.fitness = eval(pop[ii],500);
    std::cout << " and scores " << e.fitness << std::endl;
    // store for sorting
    evals.push_back(e);
  }
  std::sort(evals.begin(),evals.end(),comp);
  for (ii=0;ii<pop_size;ii++) {
    std::cout << "Place " << ii+1 << " is member " << evals.at(ii).id << " with fitness " << evals.at(ii).fitness << std::endl;
  }

}

unsigned int keepers=1;

void breed_pop() {
  int p1,p2,ii;

  for (ii=keepers;ii<pop_size;ii++) {
    p1 = rand() % keepers;
    p2 = rand() % keepers;
    while (p1==p2) p2 = rand() % keepers;
    std::cout << "Replacing " << evals[ii].id << "(" << evals[ii].fitness << ")"
              <<  " with child of " << evals[p1].id  << "(" << evals[p1].fitness << ")"
              << " and " << evals[p2].id   << "(" << evals[p2].fitness << ")" << std::endl; 
    crossover(pop[evals[ii].id],pop[evals[p1].id],pop[evals[p2].id]);
  }
}

float prob_mut = 0.1;

void mutate_pop() {

  unsigned int ii;
  for (ii=0;ii<pop_size;ii++) {
    if (random_choice(prob_mut)) {
      std::cout << "Adding random sign to member " << ii << std::endl; 
      add_random_sign(pop[ii],256,128,128);
    }
    if (random_choice(prob_mut)) {
      std::cout << "Adding two random signs to member " << ii << std::endl; 
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
    }
    if (random_choice(prob_mut)) {
      std::cout << "Dropping random sign from member " << ii << std::endl; 
      drop_random_sign(pop[ii]);
    }
    if (random_choice(prob_mut)) {
      std::cout << "Dropping two random signs from member " << ii << std::endl; 
      drop_random_sign(pop[ii]);
      drop_random_sign(pop[ii]);
    }
    if (random_choice(prob_mut)) {
      std::cout << "Mutating single sign in member " << ii << std::endl; 
      mutate_one_sign(pop[ii]);
    }
    if (random_choice(prob_mut)) {
      std::cout << "Opening up single sign in member " << ii << std::endl; 
      openup_one_sign(pop[ii]);
    }
  }
}

// ***** MAIN LOOP

void process_command_line(int argc, char *argv[]) {
  int ii;
  if (argc!=4) {
    std::cout << argv[0] << " popsize probmut probsel" << std::endl;
    exit(1);
  }
  for (ii=0;ii<argc;ii++) {
    std::cout << argv[ii] << " ";
  }
  std::cout << std::endl;
  // population size
  sscanf(argv[1],"%u",&pop_size);
  std::cout << "Population size: " << pop_size << std::endl;
  assert(pop_size>0);
  // mutation probability
  sscanf(argv[2],"%f",&prob_mut);
  std::cout << "Probability of mutation: " << prob_mut << std::endl;
  assert(prob_mut<=1.0);
  assert(prob_mut>=0.0);
  // mutation probability
  float prob_sel;
  sscanf(argv[3],"%f",&prob_sel);
  keepers = prob_sel*pop_size;
  std::cout << "Probability of selection: " << prob_sel << "(" 
            << keepers << "/" << pop_size << ")" << std::endl;
  assert(prob_sel<=1.0);
  assert(prob_sel>=0.0);

}

int main(int argc, char *argv[]) {

  char fn[100];

  process_command_line(argc, argv);

  unsigned int gg;

  srand(time(NULL));

  init_pop();
  eval_pop();

  for (gg=0;gg<50000;gg++) {
    std::cout << "GENERATION " << gg << std::endl;
    print_signs(pop[evals.front().id]);
    sprintf(fn,"res_%u_%u.csv",gg,evals.front().fitness);
    save_signs(pop[evals.front().id],fn);
    breed_pop();
    mutate_pop();
    eval_pop();

  }

  return(0);

}
