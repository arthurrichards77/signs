#include "world.h"
#include "agent.h"
#include <vector>
#include <iostream>
#include <stdio.h>

World w(256,256);

std::vector<Agent> agents;

int d(ord x2, ord x1) {
  int dx;
  if (x2>x1) {
    dx = x2-x1;
  } else {
    dx = x1-x2;
    dx = -dx;
  }   
  return(dx);
}

bool spawn_agent(ord x, ord y, ord gx, ord gy) {
  // spawn agent with specified position and goal location
  // returns false if failed because on top of another agent
  if (!w.check_coords(x,y)) {
     return(false);
  }
  else if (w.get_occ(x,y)) {
    return(false);
  } 
  // or if trying to spawn off the map
  else {
    agents.push_back(Agent(&w,Location(x,y),agents.size()));
    agents.back().set_goal(gx,gy);
    return(true);
  }
}

int read_agents() {
   FILE * pFile;
   char buffer [100];
   int parse_mode = 1;
   char c;
   ord px,py,gx,gy;

   pFile = fopen ("setup.txt" , "r");
   if (pFile == NULL) perror ("Error opening file");
   else
   {
     while ( ! feof (pFile) )
     {
       if ( fgets (buffer , 100 , pFile) == NULL ) break;
       sscanf(buffer,"%c,%lu,%lu",&c,&gx,&gy);
       if (parse_mode==1) {
         if (c=='A') {
           px=gx;
           py=gy;
           parse_mode=2;
         }         
       } else if (parse_mode==2) {
         if (c=='G') {
           if(spawn_agent(px,py,gx,gy)) {
             parse_mode=3;
           } else {
             parse_mode=1;
           }
         }
       } else if (parse_mode==3) {
         if (c=='G') {
           agents.back().add_goal(gx,gy);
         } else if (c=='A') {
           px=gx;
           py=gy;
           parse_mode=2;           
         }
       }
     }
     fclose (pFile);
   }
   return 0;
}

// MAIN ++++++++++++++++++++++++++++++++++++

int main() {
  FILE *pFile;
  unsigned long int kk;
  unsigned long int ii,jj;

  read_agents();

  pFile = fopen ("result.csv" , "w");
  if (pFile == NULL) return(1);

  std::cout << w.get_xmax() << "," << w.get_ymax() << std::endl;
  fprintf(pFile,"%lu,%lu\n", w.get_xmax(), w.get_ymax());

  for (kk=1;kk<=500;kk++) {

    w.update();

    // forward update
    for (ii=0;ii<agents.size();ii++) {
      agents.at(ii).print();
      agents.at(ii).update();
      fprintf(pFile,"%lu,%lu,%lu,%lu,%lu,%lu\n", w.get_time(), 
                                     agents.at(ii).get_id(),
                                     agents.at(ii).current_location.x,
                                     agents.at(ii).current_location.y,
                                     agents.at(ii).goal.x,
                                     agents.at(ii).goal.y);
    }

    w.update();

    // backward update
    for (ii=0;ii<agents.size();ii++) {
      jj=agents.size()-1-ii;
      agents.at(jj).print();
      agents.at(jj).update();
      fprintf(pFile,"%lu,%lu,%lu,%lu,%lu,%lu\n", w.get_time(), 
                                     agents.at(jj).get_id(),
                                     agents.at(jj).current_location.x,
                                     agents.at(jj).current_location.y,
                                     agents.at(jj).goal.x,
                                     agents.at(jj).goal.y);
    }


  }

  fclose(pFile);

  return(0);
};
