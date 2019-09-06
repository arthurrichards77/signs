all: signworld

signworld: signworld.cpp map agent
	g++ -o signworld signworld.cpp agent.h map.h agent.o map.o

agent: agent.cpp agent.h map
	g++ -c agent.cpp agent.h map.h

map: map.cpp map.h
	g++ -c map.cpp map.h

clean:
	rm *.o *.gch *.exe signworld setup.txt *.csv

setup:
	python make_setup.py > setup.txt

visualize:
	python visualize.py result.csv
