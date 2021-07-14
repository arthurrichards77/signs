#include "types.h"
#include "sign.h"
#include "sim.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>

// ***** UTILITIES *****

bool random_choice(float prob_true) {
  bool res = false;
  float r = rand();
  if (r<(RAND_MAX*prob_true)) res=true;
  return(res);
}

// ***** GA STUFF *****

typedef std::vector<Sign> signset;

// population size
unsigned int pop_size=60;
// lazy: keep population in a global
std::vector<signset*> pop;

// storage of fitness evaluations
typedef struct {
  double fitness; 
  unsigned int n_trips;
  unsigned int n_signs;
  unsigned int n_bits;
  aid n_agents;
  ord x_max;
  ord y_max;
} evaluation;
evaluation baseline_eval;
std::vector<evaluation> evals;

// index for sorting
std::vector<unsigned int> rank;

const unsigned int min_signs = 10;
const unsigned int max_signs = 30;

// ***** INDIVIDUAL STUFF *****

// weight on number of signs
double alpha = 0.0001;
// and on number of bits
double beta = 0.0001;

evaluation eval(signset *st, unsigned long int num_steps) {

  evaluation e;

  // initialize simulator
  Sim s;
  s.read_agents();
  // record problem dimensions
  e.n_agents = s.get_amax();
  e.x_max = s.get_xmax();
  e.y_max = s.get_ymax();

  // add signs
  unsigned int ii;
  for (ii=0;ii<st->size();ii++) s.add_sign(st->at(ii));

  // fitness combines:
  e.n_signs = st->size();
  e.n_bits = 0;
  for (ii=0;ii<st->size();ii++) e.n_bits += st->at(ii).num_bits();

  std::cout << "Evaluating " << e.n_signs << " signs with " << e.n_bits << " bits: ";

  // run and return trip count
  s.run(num_steps);
  e.n_trips = s.total_trips();


  // store baseline if this is the empty signset
  if (e.n_signs==0) {
    baseline_eval = e;
    std::cout << "(baseline) ";
  }

  // maximize number of trips
  // minimize number of signs
  e.fitness = (e.n_trips*1.0/baseline_eval.n_trips);
  if (alpha!=0.0) e.fitness *= pow(min_signs*1.0/(min_signs+e.n_signs),alpha);
  if (beta!=0.0) e.fitness *= pow(min_signs*48.0/(min_signs*48.0+e.n_bits),beta);

  std::cout << s.total_trips() << " trips scoring " << e.fitness << std::endl;

  return(e);

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
    std::cout << "[" << getpid() << "] Saving new best sign set to " << fn << std::endl;
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
    st->at(r).openup();
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

void refresh(signset *ch) {

  unsigned int jj,num_signs;

  // wipe the child signs
  ch->clear();
  // add all new signs
  num_signs = min_signs + (rand() % (max_signs-min_signs));
  for (jj=0;jj<num_signs;jj++) {
    // TODO: problem size is hard-coded here
    // should automatically size with the scenario
    // which is loaded in the sim class
    add_random_sign(ch,256,128,128);
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

  unsigned int ii;
  evaluation e;

  for (ii=0;ii<pop_size;ii++) {
    pop.push_back(new(signset));
    evals.push_back(e);
    rank.push_back(ii);
    // leave first one empty as baseline
    if (ii>=1) {
      refresh(pop[ii]);
    }
  }
}

bool comp (unsigned int ii, unsigned int jj) {
  return (evals[ii].fitness>evals[jj].fitness);
}

void eval_pop() {
  evaluation e;
  unsigned int ii;

  evals.clear();
  for (ii=0;ii<pop_size;ii++) {
    e = eval(pop[ii],500);
    // store for sorting
    evals.push_back(e);
  }
  std::sort(rank.begin(),rank.end(),comp);
  for (ii=0;ii<pop_size;ii++) {
    std::cout << "Place " << ii+1 << " is member " << rank.at(ii) << " with fitness " << evals.at(rank.at(ii)).fitness << std::endl;
  }
}

unsigned int keepers=1;
unsigned int newbies=1;

void breed_pop() {
  int p1,p2,ii;

  for (ii=keepers;ii<pop_size-newbies;ii++) {
    p1 = rand() % keepers;
    p2 = rand() % keepers;
    while (p1==p2) p2 = rand() % keepers;
    std::cout << "Replacing " << rank[ii] << "(" << evals[rank[ii]].fitness << ")"
              <<  " with child of " << rank[p1]  << "(" << evals[rank[p1]].fitness << ")"
              << " and " << rank[p2]   << "(" << evals[rank[p2]].fitness << ")" << std::endl; 
    crossover(pop[rank[ii]],pop[rank[p1]],pop[rank[p2]]);
  }
}

void renew_pop() {
  int ii;

  for (ii=pop_size-newbies;ii<pop_size;ii++) {
    std::cout << "Replacing " << rank[ii] << "(" << evals[rank[ii]].fitness << ")"
              <<  " with fresh talent" << std::endl; 
    refresh(pop[rank[ii]]);
  }
}

float prob_exch = 0.05;

void pop_exchange() {

   char fn[]="traveller.csv";

   FILE * pFile;
   char buffer [100];
   char c;
   int num_signs = 0;
   unsigned int d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12;

  if (random_choice(prob_exch)) {
    // send best as a traveller
    save_signs(pop[rank.front()],fn);
  }
  else if (random_choice(prob_exch)) {
    // receive traveller

    pFile = fopen (fn , "r");
    if (pFile == NULL) perror ("Failed to open traveller file");
    else
    {
      // wipe the child signs
      pop[rank.back()]->clear();
      while ( ! feof (pFile) )
      {
        if ( fgets (buffer , 100 , pFile) == NULL ) break;
        sscanf(buffer,"%c,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u",&c,
               &d1,&d2,&d3,&d4,&d5,&d6,&d7,&d8,&d9,&d10,&d11,&d12);
        if (c=='S') {
          pop[rank.back()]->push_back(Sign(Mask<aid>(d1,d2),
                                           Mask<ord>(d3,d4),Mask<ord>(d5,d6),
                                           Mask<ord>(d7,d8),Mask<ord>(d9,d10),
                                           Mask<mv>(d11,d12)));
          num_signs++;
        }
      }
      std::cout << "Read " << num_signs << " signs from traveller" << std::endl;
      fclose (pFile);
    }
  }
}

float prob_mut = 0.1;

void mutate_pop() {

  unsigned int ii,jj;
  // leave the top-ranked unchanged
  for (jj=1;jj<pop_size-newbies;jj++) {
    ii = rank[jj];
    float prob_each = prob_mut/8.0;
    if (random_choice(prob_each)) {
      std::cout << "Adding random sign to member " << ii << std::endl; 
      add_random_sign(pop[ii],256,128,128);
    }
    if (random_choice(prob_each)) {
      std::cout << "Adding two random signs to member " << ii << std::endl; 
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
    }
    if (random_choice(prob_each)) {
      std::cout << "Adding four random signs to member " << ii << std::endl; 
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
    }
    if (random_choice(prob_each)) {
      std::cout << "Adding eight random signs to member " << ii << std::endl; 
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
      add_random_sign(pop[ii],256,128,128);
    }
    if (random_choice(prob_each)) {
      std::cout << "Dropping random sign from member " << ii << std::endl; 
      drop_random_sign(pop[ii]);
    }
    if (random_choice(prob_each)) {
      std::cout << "Dropping two random signs from member " << ii << std::endl; 
      drop_random_sign(pop[ii]);
      drop_random_sign(pop[ii]);
    }
    if (random_choice(prob_each)) {
      std::cout << "Mutating single sign in member " << ii << std::endl; 
      mutate_one_sign(pop[ii]);
    }
    if (random_choice(prob_each)) {
      std::cout << "Opening up single sign in member " << ii << std::endl; 
      openup_one_sign(pop[ii]);
    }
  }
}

// ***** MAIN LOOP

void process_command_line(int argc, char *argv[]) {
  int ii;
  if (argc!=8) {
    std::cout << argv[0] << " popsize probmut probsel probrep alpha beta probexch" << std::endl;
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
  // selection probability
  float prob_sel;
  sscanf(argv[3],"%f",&prob_sel);
  keepers = prob_sel*pop_size;
  std::cout << "Probability of selection: " << prob_sel << "(" 
            << keepers << "/" << pop_size << ")" << std::endl;
  assert(prob_sel<=1.0);
  assert(prob_sel>=0.0);
  // replacement probability
  float prob_rep;
  sscanf(argv[4],"%f",&prob_rep);
  newbies = prob_rep*pop_size;
  std::cout << "Probability of replacement: " << prob_rep << "(" 
            << newbies << "/" << pop_size << ")" << std::endl;
  assert(prob_rep<=1.0);
  assert(prob_rep>=0.0);
  // weights
  sscanf(argv[5],"%lf",&alpha);
  sscanf(argv[6],"%lf",&beta);
  std::cout << "Weights are alpha=" << alpha << " (signs) and beta=" << beta << " (bits)." << std::endl;
  // exchange (traveller) probability
  sscanf(argv[7],"%f",&prob_exch);
  std::cout << "Probability of exchange: " << prob_exch << std::endl;
  assert(prob_exch<=1.0);
  assert(prob_exch>=0.0);

}

int main(int argc, char *argv[]) {

  char fn[100];

  process_command_line(argc, argv);

  double fittest = 0.0;

  std::cout << "Randomizing with seed " << getpid() << std::endl;
  srand(getpid());
  init_pop();
  eval_pop();

  std::cout << "World is " << evals[0].x_max << "x" << evals[0].y_max << " with " << evals[0].n_agents << " agents." << std::endl;

  unsigned int gg;
  for (gg=0;gg<50000;gg++) {
    std::cout << "GENERATION " << gg << std::endl;
    if (evals[rank.front()].fitness>fittest) {
      //print_signs(pop[rank.front()]);
      sprintf(fn,"res_%u_%03u_%06u_%6.0f.csv",evals[rank.front()].n_trips,evals[rank.front()].n_signs,evals[rank.front()].n_bits,1e6*evals[rank.front()].fitness);
      save_signs(pop[rank.front()],fn);
      fittest = evals[rank.front()].fitness;
    }

    breed_pop();
    renew_pop();
    pop_exchange();
    mutate_pop();
    eval_pop();

  }

  return(0);

}
