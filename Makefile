COMPILE = g++

main: main.cpp instance.o problem.o
	$(COMPILE) main.cpp instance.o problem.o

problem.o: problem.cpp problem.h
	$(COMPILE) -c problem.cpp
	
instance.o: instance.cpp instance.h
	$(COMPILE) -c instance.cpp
