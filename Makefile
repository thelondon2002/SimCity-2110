proj2.exe: main.o Cell.o People.o Residential.o Commercial.o Industrial.o Adoption.o SimSystem.o Pollution.o Stress.o
	g++ main.o Cell.o People.o Residential.o Commercial.o Industrial.o Adoption.o SimSystem.o Pollution.o Stress.o -o proj2.exe

main.o: main.cpp
	g++ -Wall -c main.cpp

Cell.o: Cell.h Cell.cpp
	g++ -Wall -c Cell.cpp

People.o: People.h People.cpp
	g++ -Wall -c People.cpp

Residential.o: Residential.h Residential.cpp
	g++ -Wall -c Residential.cpp

Commercial.o: Commercial.h Commercial.cpp
	g++ -Wall -c Commercial.cpp

Industrial.o: Industrial.h Industrial.cpp
	g++ -Wall -c Industrial.cpp

Adoption.o: Adoption.h Adoption.cpp
	g++ -Wall -c Adoption.cpp

SimSystem.o: SimSystem.h SimSystem.cpp
	g++ -Wall -c SimSystem.cpp

Pollution.o: Pollution.h Pollution.cpp
	g++ -Wall -c Pollution.cpp

Stress.o: Stress.h Stress.cpp
	g++ -Wall -c Stress.cpp

clean:
	rm *.o proj2.exe
