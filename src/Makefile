CC = g++ -Wall

all: simtest graytest evo

evo: evo.cpp map agent sign sim gray
	$(CC) -o evo evo.cpp sign.o gray.o map.o sim.o agent.o

simtest: simtest.cpp map agent sign sim gray
	$(CC) -o simtest simtest.cpp agent.o map.o sign.o gray.o sim.o

sim: sim.cpp sim.h types.h
	$(CC) -c sim.cpp

agent: agent.cpp agent.h types.h
	$(CC) -c agent.cpp

map: map.cpp map.h types.h
	$(CC) -c map.cpp

sign: sign.cpp sign.h types.h
	$(CC) -c sign.cpp

graytest: graytest.c gray
	$(CC) -o graytest graytest.c gray.o

gray: gray.c gray.h
	$(CC) -c gray.c

clean:
	rm *.o simtest graytest evo

install:
	cp simtest evo ../bin
