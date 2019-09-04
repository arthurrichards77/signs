#ifndef WORLD_H
#define WORLD_H

// type ORD +++++++++++++++++++++++++++++++++++

typedef unsigned long int ord;

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

class World {
    ord xmax,ymax,clock;
    bool *occ;
  public:
    World(ord,ord);
    ~World();
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
