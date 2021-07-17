from warnings import warn
from math import ceil

class SimBuilder:

  def __init__(self,x,y):
    self.xmax = x;
    self.ymax = y;
    print("W,{},{}".format(x,y))
    self.pos_list = []

  def is_available(self,x,y):
    res = True
    if x<0 or y<0 or x>=self.xmax or y>=self.ymax:
      res = False
    elif (x,y) in self.pos_list:
      res = False
    return(res)

  def nearest_available(self,x,y,n):
    rx = range(x-n,x+n)
    ry = range(y-n,y+n)
    clo_dist = 2*n*n
    clo_pt = None
    for tx in rx:
      for ty in ry:
        if self.is_available(tx,ty):
          this_dist = (tx-x)*(tx-x) + (ty-y)*(ty-y)
          if this_dist<clo_dist:
            clo_dist = this_dist
            clo_pt = (tx,ty)
    return(clo_pt)

  def make_agent(self,pos,circuit):
    x = int(pos[0])
    y = int(pos[1])
    if not self.is_available(x,y):
      warn("Can't spawn agent at {},{}".format(x,y))
      clo_pt = self.nearest_available(x,y,10)
      if clo_pt:
        x = clo_pt[0]
        y = clo_pt[1]
        warn("Will spawn instead at {},{}".format(x,y))
    if self.is_available(x,y):
      self.pos_list.append((x,y))
      print("A,{},{}".format(x,y))
      for gpos in circuit:
        gx = int(gpos[0])
        gy = int(gpos[1])
        if gx>=self.xmax or gx<0 or gy>=self.ymax or gy<0:
          warn("Setting unreachable goal at {},{}".format(gx,gy))
        print("G,{},{}".format(gpos[0],gpos[1]))
    else:
      warn("Could not spawn agent")

  def spread_agents_on_line(self,pos1,pos2,circuit,num_agents):
    dx = ceil((pos2[0]-pos1[0])*1.0/num_agents) # the 1.0 is important for Python2/3 compatibility
    dy = ceil((pos2[1]-pos1[1])*1.0/num_agents)
    # warn("dx={}, dy={}".format(dx,dy))
    for ii in range(num_agents):
      self.make_agent((pos1[0]+ii*dx,pos1[1]+ii*dy),circuit)

  def spread_agents_on_circuit(self,circuit,num_agents):
    for ii in range(len(circuit)):
      self.spread_agents_on_line(circuit[ii-1],circuit[ii],circuit[ii:]+circuit[:ii],num_agents)

  def two_way_trunk(self,pos1,pos2,num_agents):
    self.spread_agents_on_line(pos1,pos2,[pos2,pos1],num_agents)
    self.spread_agents_on_line(pos2,pos1,[pos1,pos2],num_agents)
