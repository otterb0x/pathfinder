# Begin Makefile
raycast: main.o ray_window.o wall_object.o
	g++ -o raycast main.o ray_window.o wall_object.o -std=c++14 -lX11
main.o:	wall_object.o
	g++ -c main.cpp
ray_window.o: wall_object.o
	g++ -c ray_window.cpp -lX11
wall_object.o:
	g++ -c wall_object.cpp
