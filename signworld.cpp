#include "world.h"
#include "agent.h"
#include <vector>
#include <iostream>
#include <stdio.h>


World w(100,100);

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

int spawn_mgr(ord x1, ord y1, ord x2, ord y2, int n) {
  // spawn a "merry go round" fleet: n agents roughly evenly spaced
  // transiting between two sites
  int num_spawned = 0;
  int dx,dy,ii;
  // careful with the arithmetic, as the ords are unsigned and don't subtract cleanly
  dx = (2*d(x2,x1))/n;
  dy = (2*d(y2,y1))/n;
  //std::cout << "dx,dy= " << dx << "," << dy << std::endl;
  // half outbound
  for (ii=0; ii<0.5*n; ii++) {
    //std::cout << "Spawning " << ii << " of MGR at " << x1+ii*dx << "," << y1+ii*dy << std::endl;
    if(spawn_agent(x1+ii*dx,y1+ii*dy,x2,y2)) {
      agents.back().add_goal(x1,y1);
      num_spawned++;
    }
  }
  // rest on the way back
  for (ii=0; (num_spawned<n)&&(ii<n); ii++) {
    //std::cout << "Spawning " << ii << " of MGR at " << x2-ii*dx << "," << y2-ii*dy << std::endl;
    if(spawn_agent(x2-ii*dx,y2-ii*dy,x1,y1)) {
      agents.back().add_goal(x2,y2);
      num_spawned++;
    }
  }
  return(num_spawned);
}

// SPAWNING ++++++++++++++++++++++++++++++++++++

void spawn_agents() {
  unsigned long int ii;

  for (ii=0;ii<8;ii++) {
    if(spawn_agent(15+2*ii,43+ii,2,3*ii)) {
      //std::cout << "Agent " << agents.back().get_id() << " spawned" << std::endl;
      agents.back().add_goal(17,17);
      agents.back().add_goal(11,32);
    } 
  }
  for (ii=0;ii<4;ii++) {
    if(spawn_agent(17+ii,13,1,3*ii)) {
      //std::cout << "Agent " << agents.back().get_id() << " spawned" << std::endl;
      agents.back().add_goal(17,17);
      agents.back().add_goal(81,27);
      agents.back().add_goal(67,19);
    } 
  }

  for (ii=0;ii<4;ii++) {
    if(spawn_agent(3+ii,83,1,3*ii)) {
      //std::cout << "Agent " << agents.back().get_id() << " spawned" << std::endl;
      agents.back().add_goal(17,17);
      agents.back().add_goal(4,55);
      agents.back().add_goal(50,34+3*ii);
    } 
  }

  ii = spawn_mgr(54,81,93,71,9);
  //std::cout << "MGR of " << ii << " agents spawned" << std::endl;

  ii = spawn_mgr(5,55,87,50,23);

  // star topology
  ii = spawn_mgr(60,60,93,90,1);
  ii = spawn_mgr(60,80,93,90,1);
  ii = spawn_mgr(80,60,93,90,1);
  ii = spawn_mgr(70,65,93,90,1);
  ii = spawn_mgr(40,55,93,90,1);

  // star topology
  ii = spawn_mgr(50,50,3,90,13);
  ii = spawn_mgr(60,60,50,50,5);

  // long distance agent
  if(spawn_agent(20,80,60,5)) {
    //std::cout << "Agent " << agents.back().get_id() << " spawned" << std::endl;
    agents.back().add_goal(20,80);
    agents.back().add_goal(4,55);
    agents.back().add_goal(20,80);
    agents.back().add_goal(75,66);
    agents.back().add_goal(20,80);
    agents.back().add_goal(20,33);
    agents.back().add_goal(20,80);    
  } 
  
  // long distance agent
  if(spawn_agent(54,12,30,15)) {
    //std::cout << "Agent " << agents.back().get_id() << " spawned" << std::endl;
    agents.back().add_goal(80,15);
    agents.back().add_goal(80,65);
    agents.back().add_goal(20,75);
    agents.back().add_goal(54,12);
  } 
  if(spawn_agent(80,15,30,15)) {
    //std::cout << "Agent " << agents.back().get_id() << " spawned" << std::endl;
    agents.back().add_goal(80,15);
    agents.back().add_goal(80,65);
    agents.back().add_goal(20,75);
    agents.back().add_goal(54,12);
    agents.back().add_goal(80,15);
  } 
  if(spawn_agent(80,65,30,15)) {
    //std::cout << "Agent " << agents.back().get_id() << " spawned" << std::endl;
    agents.back().add_goal(20,75);
    agents.back().add_goal(54,12);
    agents.back().add_goal(80,15);
    agents.back().add_goal(80,65);
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
  unsigned long int kk;
  unsigned long int ii;

  read_agents();

  //spawn_agents();

  std::cout << w.get_xmax() << "," << w.get_ymax() << std::endl;

  for (kk=1;kk<=500;kk++) {

    w.update();
    //w.print();

    // forward update
    for (ii=0;ii<agents.size();ii++) {
      agents.at(ii).print();
      agents.at(ii).update();
    }

    w.update();
    //w.print();

    // backward update
    for (ii=0;ii<agents.size();ii++) {
      agents.at(agents.size()-1-ii).print();
      agents.at(agents.size()-1-ii).update();
    }


  }

  return(0);
};
