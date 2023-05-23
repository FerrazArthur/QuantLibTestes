CC = g++
CFLAGS = -g -Wall
DEPS = titulos.hpp

teste: teste.cpp titulos.o
	$(CC) $(CFLAGS) -o teste teste.cpp titulos.o -lQuantLib

titulos.o: titulos.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o titulos.o titulos.cpp -lQuantLib

clear:
	@if [ -f ./titulos.o ]; then rm titulos.o; fi

purge:
	@if [ -f ./teste ]; then rm teste; fi
	@if [ -f ./titulos.o ]; then rm titulos.o; fi
