from warnings import warn

class SimBuilder:

  def __init__(self,x,y):
    self.xmax = x;
    self.ymax = y;
    print "W,{},{}".format(x,y)
    self.pos_list = []

  def make_agent(self,pos,circuit):
    x = int(pos[0])
    y = int(pos[1])
    if x<0 or y<0 or x>=self.xmax or y>=self.ymax:
      warn("Can't spawn agent off map at {},{}".format(x,y))
    elif (x,y) in self.pos_list:
      warn("Can't spawn second agent at {},{}".format(x,y))
    else:
      self.pos_list.append((x,y))
      print "A,{},{}".format(x,y)
      for gpos in circuit:
        gx = int(gpos[0])
        gy = int(gpos[1])
        if gx>=self.xmax or gx<0 or gy>=self.ymax or gy<0:
          warn("Setting unreachable goal at {},{}".format(gx,gy))
        print "G,{},{}".format(gpos[0],gpos[1])

  def spread_agents_on_line(self,pos1,pos2,circuit,num_agents):
    dx = (pos2[0]-pos1[0])/num_agents
    dy = (pos2[1]-pos1[1])/num_agents
    for ii in range(num_agents):
      self.make_agent((pos1[0]+ii*dx,pos1[1]+ii*dy),circuit)

  def spread_agents_on_circuit(self,circuit,num_agents):
    for ii in range(len(circuit)):
      self.spread_agents_on_line(circuit[ii-1],circuit[ii],circuit[ii:]+circuit[:ii],num_agents)

  def two_way_trunk(self,pos1,pos2,num_agents):
    self.spread_agents_on_line(pos1,pos2,[pos2,pos1],num_agents)
    self.spread_agents_on_line(pos2,pos1,[pos1,pos2],num_agents)
