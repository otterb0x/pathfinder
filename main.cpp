#include "ray_window.h"
#include "wall_object.h"
#include "ray_caster.h"

#define RESOLUTION_X 800
#define RESOLUTION_Y 600

#define CUBE_SIDE_LENGTH 100

/*
Unfinished raycast engine.

Check events stops the engine until a key is pressed.

Press any key to spin around and look at the map defined in the
ray_caster class

Chris: 	Look in the ray_window.cpp file for the check_events function.
	Thats where you'll want to read events from.

John:	Look in the ray_caster.cpp file. See what the best way to implement
	your maze class is in the get_raycast_array function.
*/

int main()
{
	ray_window cast_display(RESOLUTION_X, RESOLUTION_Y);

	wall_object rays[RESOLUTION_X];

	// Set default values for all the wall_objects in the rays array
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
	

	ray_caster caster;

	int angle = 0;

	// Game loop
	while(1)
	{
		caster.get_raycast_array(rays, RESOLUTION_X,
                                 400, 400,
                                 90, angle,
                                 100);

		// Read any keyboard events (Not finished)
		cast_display.read_events();
		// Display the wall_objects
		cast_display.line_cast(rays);
		
		angle++;
	}
}
