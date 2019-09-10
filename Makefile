all: signworld graytest

signworld: signworld.cpp map agent sign
	g++ -o signworld signworld.cpp agent.o map.o sign.o gray.o

agent: agent.cpp agent.h map
	g++ -c agent.cpp

map: map.cpp map.h
	g++ -c map.cpp

sign: sign.cpp sign.h gray agent map
	g++ -c sign.cpp

graytest: graytest.c gray
	g++ -o graytest graytest.c gray.o

gray: gray.c gray.h
	g++ -c gray.c

clean:
	rm *.o *.gch *.exe signworld setup.txt *.csv

visualize:
	python visualize.py result.csv

sim: signworld
	./signworld result.csv

setup: 
	python make_setup.py > setup.txt


