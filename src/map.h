#ifndef MAP_H
#define MAP_H

#include <vector>
#include "sign.h"
#include "types.h"

int d(ord, ord);

// class LOCATION ++++++++++++++++++++++++++++++++++++

class Location {
  public:
    ord x, y;
    Location();
    Location(ord,ord);
    void set_xy(ord,ord);
    ord distance(Location);
    bool eq(Location);
    Location decode_move(unsigned int);
    void print();
};

// class MAP ++++++++++++++++++++++++++++++++++++

class Map {
    ord xmax,ymax;
    bool *occ;
    std::vector<Sign> signs;
  public:
    Map();
    void init_occ(ord,ord);
    void reset_occ();
    Map(ord,ord);
    ~Map();
    ord get_xmax();
    ord get_ymax();
    bool check_coords(ord,ord);
    bool check_location(Location);
    bool get_occ(ord,ord);
    void take_occ(ord,ord);
    void free_occ(ord,ord);
    void print();
    void update();
    void add_sign(Sign);
    void wipe_signs();
    bool check_move(aid,ord,ord,ord,ord,mv);
};

#endif
