from .. import sim_builder

s = SimBuilder(128,128)

s.make_agent((10,10),[(20,10),(10,10)])

s.spread_agents_on_line((90,90),(90,60),[(90,60),(10,60),(110,70)],12)

s.two_way_trunk((50,5),(50,120),10)

s.two_way_trunk((100,100),(30,20),10)

s.two_way_trunk((100,100),(90,20),10)

s.two_way_trunk((100,100),(10,90),10)

s.two_way_trunk((100,100),(120,120),10)

s.spread_agents_on_circuit([(15,88),(67,91),(120,119),(104,4),(73,35)],10)
