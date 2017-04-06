#include "wall_object.h"

/*
A default constructor that sets a couple variables
*/
wall_object::wall_object()
{
	// Set both sizes to zero as a default
	MAX_SIZE = 0;
	UNIT_SIZE = 0;
}

/*
A constructor that lets you set the size as the object is created
*/
wall_object::wall_object(int p_max, int p_unit)
{
	// Set units and size to visiting variables
	MAX_SIZE = p_max;
	UNIT_SIZE = p_unit;
}

/*
Takes three hexadecimal numbers and set the corresponding members
equal to them moduloed by 100 to make sure the range for each
color is between 0x00 and 0xFF
*/
void wall_object::set_hex_color(int r, int g, int b)
{
	// Set RED, BLUE, & GREEN to the visiting values.
	// Modulo by 100 to get values between 0x00 and 0xFF
	RED = (r % 100);
	GREEN = (g % 100);
	BLUE = (b % 100);
}


/*
Multiply each color member to look like this:
	RED = 	0xFF0000
	GREEN =	0x00FF00
	BLUE =	0x0000FF

So added together they will look like 0xFFFFFF
*/
int wall_object::get_hex_color()
{
	int total_val;

	total_val = RED * 0x10000;
	total_val += (GREEN * 0x100);
	total_val += BLUE;

	return total_val;
}

void wall_object::set_base_hex_color(int r, int g, int b)
{
	BASE_RED = (r % 100);
        BASE_GREEN = (g % 100);
        BASE_BLUE = (b % 100);
}


int wall_object::get_base_hex_color()
{
	int total_val;

        total_val = BASE_RED * 0x10000;
        total_val += BASE_GREEN * 0x100;
        total_val += BASE_BLUE;

        return total_val;
}


/*
Sets the member named SIZE to the size of the wall divided by the distance
to make seem like the wall is farther when the distance is higher. 
Also sets the member DISTANCE to the visiting variable distance. 
If size calculated appears to be bigger than the max size then the member
SIZE will be set to the max size
*/
void wall_object::set_size(float distance)
{
	float size_calc;
	DISTANCE = distance;

	// If the wall exists	
	if(distance > 0)
	{
		//Calculate the wall
		size_calc = 500.0f * UNIT_SIZE / distance;
	}
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
