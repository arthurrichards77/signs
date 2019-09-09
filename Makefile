all: signworld

signworld: signworld.cpp map agent sign
	g++ -o signworld signworld.cpp agent.o map.o sign.o

agent: agent.cpp agent.h map
	g++ -c agent.cpp

map: map.cpp map.h
	g++ -c map.cpp

sign: sign.cpp sign.h agent map
	g++ -c sign.cpp

clean:
	rm *.o *.gch *.exe signworld setup.txt *.csv

run: setup result visualize

visualize:
	python visualize.py result.csv

result: signworld
	./signworld result.csv

setup: 
	python make_setup.py > setup.txt


