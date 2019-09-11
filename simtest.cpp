#include "sim.h"

#include "sign.h"

#include "gray.h"

#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]) {
  Sim s;

  // read agent settings
  aid num_agents = s.read_agents();
  std::cout << num_agents << " agents initialized" << std::endl;

  // test - add signs
  //Sign sn(Mask<aid>(0,0),Mask<ord>(48,32),Mask<ord>(128,128),Mask<ord>(255,gray(50)),Mask<ord>(255,gray(5)),Mask<mv>(5,5));
  Sign sn(Mask<aid>(0,0),
          Mask<ord>(0,0),Mask<ord>(0,0),
          Mask<ord>(255,gray(50)),Mask<ord>(255,gray(120)),
          Mask<mv>(6,0));
  s.add_sign(sn);

  FILE *pFile = NULL;
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

  unsigned long int n = s.run(1000);
  std::cout << n << " steps simulated" << std::endl;

  std::cout << s.total_trips() << " trips completed overall" << std::endl;

  if (pFile!=NULL) fclose(pFile);

  return(0);
};
