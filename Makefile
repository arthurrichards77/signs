all: simtest graytest evo

evo: evo.cpp map agent sign sim gray
	g++ -o evo evo.cpp sign.o gray.o map.o sim.o agent.o

simtest: simtest.cpp map agent sign sim gray
	g++ -o simtest simtest.cpp agent.o map.o sign.o gray.o sim.o

sim: sim.cpp sim.h types.h
	g++ -c sim.cpp

agent: agent.cpp agent.h types.h
	g++ -c agent.cpp

map: map.cpp map.h types.h
	g++ -c map.cpp

sign: sign.cpp sign.h types.h
	g++ -c sign.cpp

graytest: graytest.c gray
	g++ -o graytest graytest.c gray.o

gray: gray.c gray.h
	g++ -c gray.c

clean:
	rm *.o simtest graytest evo setup.txt *.csv

visualize:
	python visualize.py result.csv

result: 
	./simtest result.csv

setup: 
	python make_setup.py > setup.txt


