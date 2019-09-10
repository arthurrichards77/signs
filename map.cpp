#include "map.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

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

    // coding is:
    // 0 | 1 | 2 -> +X
    // ---------
    // 7 |   | 3
    // ---------
    // 6 | 5 | 4
    // 
    // ^
    // |
    // +Y

    if ((move_code&5)==0) ny+=1;
    else if ((move_code&6)==0) ny+=1;
    else if ((move_code&6)==4) ny+=-1;
    else if ((move_code&5)==4) ny+=-1;

    if ((move_code&6)==2) nx+=1;
    else if (move_code==4) nx+=1;
    else if ((move_code&6)==6) nx+=-1;
    else if (move_code==0) nx+=-1;

    return(Location(nx,ny));
}

void Location::print() {
    std::cout << "(" << x << "," << y << ")";
}

// class Map ++++++++++++++++++++++++++++++++++++

Map::Map() {
  // zero size map if constructed empty
  xmax = 0;
  ymax = 0;
  occ = NULL;
}

void Map::init_occ(ord x, ord y) {
  // size of the Map
  xmax = x;
  ymax = y;
  // empty occupancy grid
  occ = (bool*) malloc(sizeof(bool)*xmax*ymax);
  memset(occ,false,sizeof(bool)*xmax*ymax);
}

Map::Map(ord x, ord y) {
  init_occ(x,y);
}

Map::~Map(){
  free (occ);
}

ord Map::get_xmax() {
  return(xmax);
}

ord Map::get_ymax() {
  return(ymax);
}

bool Map::check_coords(ord x, ord y) {
  return((x<xmax)&&(x>=0)&&(y<ymax)&&(y>=0));
}

bool Map::check_location(Location loc) {
  return(check_coords(loc.x,loc.y));
}

bool Map::get_occ(ord x, ord y) {
  assert(check_coords(x,y));
  return(occ[x*ymax + y]);
}

void Map::take_occ(ord x, ord y) {
  assert(check_coords(x,y));
  assert(!occ[x*ymax + y]);
  occ[x*ymax + y] = true;
}

void Map::free_occ(ord x, ord y) {
  assert(check_coords(x,y));
  occ[x*ymax + y] = false;
}

void Map::print() {
  ord xx,yy;
  std::cout << "Occupancy map at time " << clock << std::endl;
  for (yy=0;yy<ymax;yy++) {
    for (xx=0;xx<xmax;xx++) {
      std::cout << get_occ(xx,yy);
    }
    std::cout << std::endl;
  }
  std::cout << "End" << std::endl;
}

void Map::add_sign(id a1,id a2,id x1,id x2,id y1,id y2, 
                               id xd1,id xd2,id yd1,id yd2,
                               mv m1, mv m2){
  signs.push_back(Sign(a1,a2,x1,x2,y1,y2,xd1,xd2,yd1,yd2,m1,m2));
}

bool Map::check_move(id a, id x, id y, id xd, id yd, mv m) {
  bool result;
  int ii;

  result = true;

  for (ii=0; ii<signs.size(); ii++) {
    if (!signs.at(ii).check_move(a,x,y,xd,yd,m)) {
      result = false;
      break;
    }
  }

  return(result);
}
