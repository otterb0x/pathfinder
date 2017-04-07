# Begin Makefile
raycast: main.o ray_window.o wall_object.o ray_caster.o
	g++ -o pathfinder main.o ray_window.o wall_object.o ray_caster.o -std=c++14 -lX11
main.o:	wall_object.o
	g++ -c main.cpp -std=c++14
ray_window.o: wall_object.o
	g++ -c ray_window.cpp -lX11
ray_caster.o: wall_object.o
	g++ -c ray_caster.cpp
wall_object.o:
	g++ -c wall_object.cpp
