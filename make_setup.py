def make_agent(pos,circuit):
  print "A,{},{}".format(pos[0],pos[1])
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
