from warnings import warn

xmax = 256;
ymax = 256;

print "W,{},{}".format(xmax,ymax)

pos_list = []

def make_agent(pos,circuit):
  x = int(pos[0])
  y = int(pos[1])
  if x<0 or y<0 or x>=xmax or y>=ymax:
    warn("Can't spawn agent off map at {},{}".format(x,y))
  elif (x,y) in pos_list:
    warn("Can't spawn second agent at {},{}".format(x,y))
  else:
    pos_list.append((x,y))
    print "A,{},{}".format(x,y)
    for gpos in circuit:
      gx = int(gpos[0])
      gy = int(gpos[1])
      if gx>=xmax or gx<0 or gy>=ymax or gy<0:
        warn("Setting unreachable goal at {},{}".format(gx,gy))
      print "G,{},{}".format(gpos[0],gpos[1])

def each_point_on_circuit(circuit):
  for ii in range(len(circuit)):
    make_agent(circuit[ii],circuit[ii+1:]+circuit[0:ii]+[circuit[ii]])

def each_spoke_to_hub(home,spokes):
  for sp in spokes:
    make_agent(sp,[home,sp])

def spread_agents_on_line(pos1,pos2,circuit,num_agents):
  dx = (pos2[0]-pos1[0])/num_agents
  dy = (pos2[1]-pos1[1])/num_agents
  for ii in range(num_agents):
    make_agent((pos1[0]+ii*dx,pos1[1]+ii*dy),circuit)

def two_way_trunk(pos1,pos2,num_agents):
  spread_agents_on_line(pos1,pos2,[pos2,pos1],num_agents)
  spread_agents_on_line(pos2,pos1,[pos1,pos2],num_agents)

make_agent((10,10),[(20,10),(10,10)])

each_point_on_circuit([(30,30),(40,40),(40,50),(30,40)])

each_spoke_to_hub((10,50),[(50,50),(10,70),(10,10)])

spread_agents_on_line((90,90),(90,60),[(90,60),(10,60),(140,70)],12)

two_way_trunk((50,5),(50,250),10)

two_way_trunk((100,100),(130,200),10)

two_way_trunk((100,100),(90,20),10)

two_way_trunk((100,100),(10,90),10)

two_way_trunk((100,100),(220,120),10)

