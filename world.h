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
};

// class WORLD ++++++++++++++++++++++++++++++++++++

class World {
    ord xmax,ymax;
    bool *occ;
  public:
    World(ord,ord);
    ~World();
    void check_coords(ord,ord);
    bool get_occ(ord,ord);
    void take_occ(ord,ord);
    void free_occ(ord,ord);
    void print();
};

#endif
