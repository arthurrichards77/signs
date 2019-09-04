#include "world.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// class LOCATION ++++++++++++++++++++++++++++++++++++

Location::Location() {
    x=0;
    y=0;
}

Location::Location(ord x_in,ord y_in) {
    x=x_in;
    y=y_in;
}

void Location::set_xy(ord x_in,ord y_in) {
    x=x_in;
    y=y_in;
}

// class WORLD ++++++++++++++++++++++++++++++++++++

World::World(ord x, ord y) {
  xmax = x;
  ymax = y;
  occ = (bool*) malloc(sizeof(bool)*xmax*ymax);
  memset(occ,false,sizeof(bool)*xmax*ymax);
}

World::~World(){
  free (occ);
}

void World::check_coords(ord x, ord y) {
  assert(x<xmax);
  assert(x>=0);
  assert(y<ymax);
  assert(y>=0);
}

bool World::get_occ(ord x, ord y) {
  check_coords(x,y);
  return(occ[x*ymax + y]);
}

void World::take_occ(ord x, ord y) {
  check_coords(x,y);
  occ[x*ymax + y] = true;
}

void World::free_occ(ord x, ord y) {
  check_coords(x,y);
  occ[x*ymax + y] = false;
}

void World::print() {
  ord xx,yy;
  std::cout << "Occupancy map" << std::endl;
  for (yy=0;yy<ymax;yy++) {
    for (xx=0;xx<xmax;xx++) {
      std::cout << get_occ(xx,yy);
    }
    std::cout << std::endl;
  }
  std::cout << "End" << std::endl;
}


