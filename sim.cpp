#include "sim.h"

#include "sign.h"
#include <iostream>

Sim::Sim() {
  clock = 0;
  out_file = NULL;
}

void Sim::add_sign(id a1,id a2,id x1,id x2,id y1,id y2, mv m1, mv m2){
  m.add_sign(a1,a2,x1,x2,y1,y2,m1,m2);
}

FILE *Sim::open_output(char *file_name) {
  out_file = fopen(file_name , "w");
  return(out_file);
}

bool Sim::spawn_agent(ord x, ord y, ord gx, ord gy) {
  // spawn agent with specified position and goal location
  // returns false if failed because on top of another agent
  if (!m.check_coords(x,y)) {
     return(false);
  }
  else if (m.get_occ(x,y)) {
    return(false);
  } 
  // or if trying to spawn off the map
  else {
    agents.push_back(Agent(&m,Location(x,y),agents.size()));
    agents.back().set_goal(gx,gy);
    return(true);
  }
}

aid Sim::read_agents() {
   FILE * pFile;
   char buffer [100];
   int parse_mode = 0;
   char c;
   ord px,py,gx,gy;
   aid num_agents = 0;

   pFile = fopen ("setup.txt" , "r");
   if (pFile == NULL) perror ("Error opening file");
   else
   {
     while ( ! feof (pFile) )
     {
       if ( fgets (buffer , 100 , pFile) == NULL ) break;
       sscanf(buffer,"%c,%lu,%lu",&c,&gx,&gy);
       if (parse_mode==0) {
         if (c=='W') {
           m.init_occ(gx,gy);
           parse_mode=1;
         }         
       } else if (parse_mode==1) {
         if (c=='A') {
           px=gx;
           py=gy;
           parse_mode=2;
         }         
       } else if (parse_mode==2) {
         if (c=='G') {
           if(spawn_agent(px,py,gx,gy)) {
             num_agents++;
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
   return(num_agents);
}

ord Sim::get_xmax() {
  return(m.get_xmax());
}

ord Sim::get_ymax() {
  return(m.get_ymax());
}

aid Sim::forward_update() {
    aid ii;
    for (ii=0;ii<agents.size();ii++) {
      agents.at(ii).update();
    }
    clock++;
    return(ii);
}

aid Sim::reverse_update() {
    aid ii,jj;
    for (ii=0;ii<agents.size();ii++) {
      jj=agents.size()-1-ii;
      agents.at(jj).update();
    }
    clock++;
    return(ii);
}

aid Sim::print_status() {
    aid ii;
    if (out_file!=NULL) {
      for (ii=0;ii<agents.size();ii++) {
        fprintf(out_file,"%lu,%lu,%lu,%lu,%lu,%lu\n", clock, 
                                     agents.at(ii).get_id(),
                                     agents.at(ii).current_location.x,
                                     agents.at(ii).current_location.y,
                                     agents.at(ii).goal.x,
                                     agents.at(ii).goal.y);
      }
    }
    return(ii);
}

int Sim::total_trips() {
    int ii,n=0;

    for (ii=0;ii<agents.size();ii++) {
      n+=agents.at(ii).get_num_trips();
    }
    return(n);
}
