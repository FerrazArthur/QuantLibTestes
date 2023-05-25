CC = g++
CFLAGS = -g -Wall
DEPS = titulos.hpp

avaliar: avaliar.cpp titulos.o
	$(CC) $(CFLAGS) -o avaliar avaliar.cpp titulos.o -lQuantLib

gerarcsv: gerarcsv.cpp titulos.o
	$(CC) $(CFLAGS) -o gerarcsv gerarcsv.cpp titulos.o -lQuantLib
	@./gerarcsv && python3 plotar.py

titulos.o: titulos.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o titulos.o titulos.cpp -lQuantLib

clear:
	@if [ -f ./titulos.o ]; then rm titulos.o; fi

purge:
	@if [ -f ./avaliar ]; then rm avaliar; fi
	@if [ -f ./gerarcsv ]; then rm gerarcsv; fi
	@if [ -f ./titulos.o ]; then rm titulos.o; fi
