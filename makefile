all: montador

trimfunc.o:
	g++ -g -c -std=c++11 trimfunc.cpp

allCaps.o:
	g++ -g -c -std=c++11 allCaps.cpp

generatePre.o:
	g++ -g -c -std=c++11 generatePre.cpp

generateObj.o: 
	g++ -g -c -std=c++11 generateObj.cpp

montador: trimfunc.o allCaps.o generatePre.o generateObj.o montador.cpp
	g++ -Wall -o montador trimfunc.o allCaps.o generatePre.o generateObj.o montador.cpp
	rm trimfunc.o allCaps.o generatePre.o generateObj.o

clean: 
	rm montador