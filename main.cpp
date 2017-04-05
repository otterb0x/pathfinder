#include <cmath>
#include <iostream>

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
		rays[i].set_base_hex_color(0xFF,0x00,0x00);
	}


	ray_caster caster;

	int angle = 0;
	float time = 0;
	int pos_x = 200;
	int pos_y = 400;

	// Game loop
	while(1)
	{
		// Get the sizes of the walls to be drawn
		caster.get_raycast_array(rays, RESOLUTION_X,
                                 pos_x, pos_y,
                                 90, angle,
                                 100);
	
		// Draw the ceiling
		cast_display.draw_rectangle_to_buffer(0,0, RESOLUTION_X - 1,
				RESOLUTION_Y / 2, 0xFFFFFF);

		// Draw the floor
		cast_display.draw_rectangle_to_buffer(0, RESOLUTION_Y / 2, 
				RESOLUTION_X - 1, RESOLUTION_Y - 1, 0xBA924E);
		// Draw the wall
		cast_display.line_cast_to_buffer(rays);
		
		// Draw the buffer to the screen
		cast_display.draw_buffer();
		
		// Update camera position
		pos_x = 400.0f + (sin(time) * 200.0f);
		pos_y = 400.0f + (cos(time) * 200.0f);

		// Time & angle tracking for example
		time += 0.01f;
		angle++;
	}
}
