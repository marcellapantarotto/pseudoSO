#.PHONY: all clean
#all: run clean

simulation: main.o process.o memory.o resource.o scheduler.o
	@echo " Creating link to objects in 'run' file."
	@g++ main.o process.o memory.o resource.o scheduler.o -g -std=c++11 -pthread -o run
	@echo " Ready to run!"
	@echo " Command to Execute:    ./run processes.txt"

main.o: main.cpp
	@echo " Creating main.o"
	@g++ main.cpp -g -std=c++11 -c

processo.o: process.cpp process.hpp
	@echo " Creating process.o"
	@g++ process.cpp -g -std=c++11 -c

memoria.o: memory.cpp memory.hpp
	@echo " Creating memory.o"
	@g++ memory.cpp -g -std=c++11 -c

recurso.o: resource.cpp resource.hpp
	@echo " Creating resource.o"
	@g++ resource.cpp -g -std=c++11 -c

scheduler.o: scheduler.cpp scheduler.hpp
	@echo " Creating scheduler.o"
	@g++ scheduler.cpp -g -std=c++11 -c
