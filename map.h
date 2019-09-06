#ifndef MAP_H
#define MAP_H

// type ORD +++++++++++++++++++++++++++++++++++

typedef unsigned long int ord;

int d(ord, ord);

// class LOCATION ++++++++++++++++++++++++++++++++++++

class Location {
  public:
    ord x, y;
    Location();
    Location(ord,ord);
    void set_xy(ord,ord);
    float distance(Location);
    bool eq(Location);
    Location decode_move(unsigned int);
    void print();
};

// class WORLD ++++++++++++++++++++++++++++++++++++

class Map {
    ord xmax,ymax,clock;
    bool *occ;
  public:
    Map(ord,ord);
    ~Map();
    ord get_time();
    ord get_xmax();
    ord get_ymax();
    bool check_coords(ord,ord);
    bool check_location(Location);
    bool get_occ(ord,ord);
    void take_occ(ord,ord);
    void free_occ(ord,ord);
    void print();
    void update();
};

#endif
