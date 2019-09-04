#include "world.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

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

float Location::distance(Location other) {
    return(sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y)));
}

bool Location::eq(Location other) {
    return((x==other.x)&&(y==other.y));
}

Location Location::decode_move(unsigned int move_code) {
    ord nx,ny;
    nx = x;
    ny = y;

    nx -= move_code & 0x01;
    move_code = move_code >> 1;
    nx += move_code & 0x01;
    move_code = move_code >> 1;
    ny -= move_code & 0x01;
    move_code = move_code >> 1;
    ny += move_code & 0x01;

    return(Location(nx,ny));
}

void Location::print() {
    std::cout << "(" << x << "," << y << ")";
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

ord World::get_xmax() {
  return(xmax);
}

ord World::get_ymax() {
  return(ymax);
}

bool World::check_coords(ord x, ord y) {
  return((x<xmax)&&(x>=0)&&(y<ymax)&&(y>=0));
}

bool World::check_location(Location loc) {
  return(check_coords(loc.x,loc.y));
}

bool World::get_occ(ord x, ord y) {
  assert(check_coords(x,y));
  return(occ[x*ymax + y]);
}

void World::take_occ(ord x, ord y) {
  assert(check_coords(x,y));
  assert(!occ[x*ymax + y]);
  occ[x*ymax + y] = true;
}

void World::free_occ(ord x, ord y) {
  assert(check_coords(x,y));
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


