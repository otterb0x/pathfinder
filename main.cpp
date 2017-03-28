#include <iostream>
#include <cmath>

#include "ray_window.h"
#include "wall_object.h"


#define RESOLUTION_X 800
#define RESOLUTION_Y 600

#define CUBE_SIDE_LENGTH 100

int main()
{
	ray_window cast_display(RESOLUTION_X, RESOLUTION_Y);

	wall_object rays[RESOLUTION_X];


	// A test for the wall objects
	for(int i = 0; i < RESOLUTION_X; i++)
	{
		// Set the max height of a ray
		rays[i].set_max(RESOLUTION_Y);
		// Define wall units
		rays[i].set_unit(CUBE_SIDE_LENGTH);
		// Set the actual size of the way, using distance.
		// Will have to change later
		rays[i].set_size(i);
		// Set the color of the wall
		rays[i].set_hex_color(0xFF,0x00,0x00);
	}


	// Game loop
	while(1)
	{
		// Read any keyboard events (Not finished)
		cast_display.read_events();
		// Display the wall_objects
		cast_display.line_cast(rays);
	}
}
