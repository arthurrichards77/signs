from warnings import warn

pos_list = []

def make_agent(pos,circuit):
  x = int(pos[0])
  y = int(pos[1])
  if (x,y) in pos_list:
    warn("Can't spawn second agent at {},{}".format(x,y))
  else:
    pos_list.append((x,y))
    print "A,{},{}".format(x,y)
    for gpos in circuit:
      print "G,{},{}".format(gpos[0],gpos[1])

make_agent((10,10),[(20,10),(10,10)])

def each_point_on_circuit(circuit):
  for ii in range(len(circuit)):
    make_agent(circuit[ii],circuit[ii+1:]+circuit[0:ii]+[circuit[ii]])

each_point_on_circuit([(30,30),(40,40),(40,50),(30,40)])

def each_spoke_to_hub(home,spokes):
  for sp in spokes:
    make_agent(sp,[home,sp])

each_spoke_to_hub((10,50),[(50,50),(10,70),(10,10)])

def spread_agents_on_line(pos1,pos2,circuit,num_agents):
  dx = (pos2[0]-pos1[0])/num_agents
  dy = (pos2[1]-pos1[1])/num_agents
  for ii in range(num_agents):
    make_agent((pos1[0]+ii*dx,pos1[1]+ii*dy),circuit)

spread_agents_on_line((90,90),(90,60),[(90,60),(10,60),(140,70)],12)

def two_way_trunk(pos1,pos2,num_agents):
  spread_agents_on_line(pos1,pos2,[pos2,pos1],num_agents)
  spread_agents_on_line(pos2,pos1,[pos1,pos2],num_agents)

two_way_trunk((50,5),(50,250),25)

