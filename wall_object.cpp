#include "wall_object.h"

wall_object::wall_object()
{
	// Set both sizes to zero as a default
	MAX_SIZE = 0;
	UNIT_SIZE = 0;
}

wall_object::wall_object(int p_max, int p_unit)
{
	// Set units and size to visiting variables
	MAX_SIZE = p_max;
	UNIT_SIZE = p_unit;
}


void wall_object::set_hex_color(int r, int g, int b)
{
	// Set RED, BLUE, & GREEN to the visiting values.
	// Modulo by 100 to get values between 0x00 and 0xFF
	RED = (r % 100);
	GREEN = (g % 100);
	BLUE = (b % 100);
}

int wall_object::get_hex_color()
{
	int total_val;

	// Multiply each color member to look like this:
	//	RED = 	0xFF0000
	//	GREEN =	0x00FF00
	//	BLUE =	0x0000FF
	//
	// So added together they will look like 0xFFFFFF


	total_val = RED * 0x10000;
	total_val += (GREEN * 0x100);
	total_val += BLUE;

	return total_val;
}

void wall_object::set_size(int distance)
{
	int size_calc;

	// If the wall exists	
	if(distance > 0)
		//Calculate the wall
		size_calc =  MAX_SIZE / distance;
	else // Wall doesn't exist
		size_calc = -1;

	// If the wall size exceeds the maximum size
	if(size_calc > MAX_SIZE)
		// Set the wall size equal to the max size
		SIZE = MAX_SIZE;
	else
		// Set the size equal to the calculation
		SIZE = size_calc;
}
