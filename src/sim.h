#ifndef SIM_H
#define SIM_H

#include "types.h"
#include "map.h"
#include "agent.h"
#include <vector>
#include <stdio.h>

class Sim {
    unsigned long int clock;
    Map m;
    FILE *out_file;
  public:
    Sim();
    std::vector<Agent> agents;
    bool spawn_agent(ord,ord,ord,ord);
    aid read_agents();
    aid reset();
    int read_signs(char *);
    FILE *open_output(char *);
    aid forward_update();
    aid reverse_update();
    aid print_status();
    ord get_xmax();
    ord get_ymax();
    aid get_amax();
    unsigned int total_trips();
    void add_sign(Sign);
    unsigned long int run(unsigned long int);
};

#endif
