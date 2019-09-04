all: signworld

signworld: signworld.cpp world agent
	g++ -o signworld signworld.cpp agent.h world.h agent.o world.o

agent: agent.cpp agent.h world
	g++ -c agent.cpp agent.h world.h

world: world.cpp world.h
	g++ -c world.cpp world.h

clean:
	rm *.o *.gch *.exe signworld
