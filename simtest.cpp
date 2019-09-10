#include "sim.h"

#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]) {
  Sim s;

  FILE *pFile = NULL;

  aid num_agents = 0;

  unsigned long int kk;

  num_agents = s.read_agents();
  std::cout << num_agents << " agents initialized" << std::endl;

  // test - add signs
  //s.add_sign(0,0,0,0,0,0,7,3);
  s.add_sign(0,0,48,32,255,135,4,4);
  s.add_sign(0,0,48,32,255,135,6,0);

  if (argc>1) {
    pFile = s.open_output(argv[1]);
  }
  if (pFile == NULL) {
    std::cout << "Error opening output file: sim won't be logged" << std::endl;
  }
  else {
    std::cout << "Logging results to " << argv[1] << std::endl;
  }

  std::cout << "World is " << s.get_xmax() << "x" << s.get_ymax() << std::endl;
  if (pFile!=NULL) fprintf(pFile,"%lu,%lu\n", s.get_xmax(), s.get_ymax());

  for (kk=0;kk<500;kk++) {
     s.forward_update();
     s.print_status();
     s.reverse_update();
     s.print_status();
  }

  std::cout << s.total_trips() << " trips completed overall" << std::endl;

  if (pFile!=NULL) fclose(pFile);

  return(0);
};
