#include "ray_caster.h"

/*
This is an inefficient placeholder until I can think of something more
efficient. 

The raycaster will:

For each ray, check every square on the map to see if the ray intersects
anything. If so what is the shortest intersection.

Lets say the map is 8 x 8

That is 64 squares.

lets say half are filled.

If the horizontal resolution is 800, Then that is 32 * 800 ray calculations
per pass through

32 * 800 = 19000 Calculations
*/
void ray_caster::get_raycast_array(wall_object raycast_array[],
                                        int raycast_array_size,
                                        float pos_x, float pos_y,
                                        generate_maze &maze, int maze_size,
                                        int FOV, int direction,
                                        int wall_size)
{
	// Temporary map until John finishes the maze generator
	int map[8][8] =	{
			{1,0,1,0,0,0,1,1},
			{1,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,1},
			{0,0,0,1,1,0,0,0},
			{0,0,0,1,0,0,0,0},
			{1,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,1},
			{1,1,0,0,0,1,0,1},
			};
	// Temporary map size
	int map_size = 8;

	// Reset all of the wall objects to have no wall
	// and reset the color to maximum brightness
	for(int i = 0; i < raycast_array_size; i++)
	{
		raycast_array[i].set_size(-1);
		raycast_array[i].set_red(0xFF);
	}


	float shortest_distance;
	float distance_calc;

	// The start angle to start casting rays
	float start_angle = direction - (FOV / 2.0f);	
	// The angle that we're currently casting rays at
	float current_angle = direction - (FOV / 2.0f);
	// The increment for every ray in the Field of View
	float angle_step = 1.0f * FOV / raycast_array_size;

	float end_x;
	float end_y;

	for(int i = 0; i < raycast_array_size; i++)
	{
		// Set the current angle for the specific ray
		current_angle = start_angle + (i * angle_step);
	
		// For every square on the map...
		for(int j = 0; j < maze_size; j++)
			for(int k = 0; k < maze_size; k++)
			{
			// Set the shortest distance to a high number
			shortest_distance = 999999999;
			// Reset the distance calculation to "No calculation"
			distance_calc = -1;

			// Get the end coordinates based of the players
			// current position, direction, and the current
			// ray we're casting
			end_x = pos_x + get_stepx(999999, current_angle);
			end_y = pos_y + get_stepy(999999, current_angle);

			// If there is something at this point in the map...
			if(maze.get_square(k, j) > 0)
			{
				// Get the closest point of the box
				distance_calc = get_box_distance(
					pos_x, pos_y,
					end_x, end_y,
					j * wall_size, k * wall_size,
					wall_size);
				// If the ray intersects the box, set the
				// Shortest distance calculated to distance
				// to the box we just found
				if((distance_calc > 0) &&
				   (distance_calc < shortest_distance))
					shortest_distance = distance_calc;
			}

			
			// Check if the ray was found. If it was, check if
			// the wall object doesn't have a set size or the
			// distance we have is shorter than the current set 
			// distance. If so set the wall object size 
			// corresponding to the distance.
			//
			// Most of these lines have to be pushed back to
			// compile and still be readable.
			if(distance_calc > 0)
			{	
			// Remove fisheye effect
			distance_calc *= cos(((-FOV / 2.0f) + 
				(angle_step * i))* M_PI / 180.0f);
				if(raycast_array[i].get_size() < 0 ||
				distance_calc < 
				raycast_array[i].get_distance())
				{
			// I have to set these lines back for 
			// g++ to accept them
				raycast_array[i].set_hex_color(
		raycast_array[i].get_base_red() / (distance_calc / 100.0f),
		raycast_array[i].get_base_green() / (distance_calc / 100.0f),
		raycast_array[i].get_base_blue() / (distance_calc / 100.0f));
			raycast_array[i].set_size(distance_calc);
				}
			}
			}
	}
}


/*
This is how I imagined the sides of the boxes

	----1----
	|	|
	2	3
	|	|
	----4----

get_box_distance checks each side of the box against a line for an
intersection and returns the shortest distance from the origin of the
line or returns -1 if no intersection was found
*/
float ray_caster::get_box_distance(float X1, float Y1, float X2, float Y2,
                                        int box_x, int box_y, int wall_size)
{
	bool hit_wall = false;
	float shortest_distance = 99999999999;
	float current_distance;


	// Check side 1
	current_distance = get_distance(X1, Y1, X2, Y2,
                        		box_x, box_y,
                        		box_x + wall_size, box_y);
	
	// Check if the box side distance is shorter than the current distance
	// and the distance exists (greater than 0!). If so set the shortest
	// distance to the calculated distance and set the hit_wall flag
	// to true 
	if(current_distance < shortest_distance && current_distance > 0)
		{
			shortest_distance = current_distance;
			hit_wall = true;
		}
	// Check side 2		
	current_distance = get_distance(X1, Y1, X2, Y2,
                        		box_x, box_y,
                        		box_x, box_y + wall_size);

	// Check if the box side distance is shorter than the current distance
	// and the distance exists (greater than 0!). If so set the shortest
	// distance to the calculated distance and set the hit_wall flag
	// to true 
	if(current_distance < shortest_distance && current_distance > 0)
		{
			shortest_distance = current_distance;
			hit_wall = true;
		}

	// Check side 3
	current_distance = get_distance(X1, Y1, X2, Y2,
                        		box_x, box_y + wall_size,
                        		box_x + wall_size, box_y + wall_size);

	// Check if the box side distance is shorter than the current distance
	// and the distance exists (greater than 0!). If so set the shortest
	// distance to the calculated distance and set the hit_wall flag
	// to true 
	if(current_distance < shortest_distance && current_distance > 0)
		{
			shortest_distance = current_distance;
			hit_wall = true;
		}

	// Check side 4
	current_distance = get_distance(X1, Y1, X2, Y2,
                        		box_x + wall_size, box_y,
                        		box_x + wall_size, box_y + wall_size);
	
	// Check if the box side distance is shorter than the current distance
	// and the distance exists (greater than 0!). If so set the shortest
	// distance to the calculated distance and set the hit_wall flag
	// to true 
	if(current_distance < shortest_distance && current_distance > 0)
		{
			shortest_distance = current_distance;
			hit_wall = true;
		}

	// If a wall was hit
	if(hit_wall)
		// Return the shortest distance
		return shortest_distance;
	else // Wall was not hit
		// return an impossible distance
		return -1;
}


float ray_caster::get_distance(float line1_x1, float line1_y1,
                                        float line1_x2, float line1_y2,
                                        float line2_x1, float line2_y1,
                                        float line2_x2, float line2_y2)
{
	float distance;

	float A1 = line1_y2 - line1_y1;
	float B1 = line1_x1 - line1_x2;
	float C1 = (A1 * line1_x1) + (B1 * line1_y1);

	float A2 = line2_y2 - line2_y1;
	float B2 = line2_x1 - line2_x2;
	float C2 = (A2 * line2_x1) + (B2 * line2_y1);

	

    float denominator = (A1 * B2) - (A2 * B1);

    if(denominator == 0)
    {
        return -1;
    }

    // These following intersection values are assuming the line is
    // infinitly extendeding.

    float intersectX = ((B2 * C1) - (B1 * C2)) / denominator;
    float intersectY = ((A1 * C2) - (A2 * C1)) / denominator;

    // These following values are used for checking if the intersection
    // point is within the bounds of the lines.

    float rx0 = (intersectX - line1_x1) / (line1_x2 - line1_x1);
    float ry0 = (intersectY - line1_y1) / (line1_y2 - line1_y1);
    float rx1 = (intersectX - line2_x1) / (line2_x2 - line2_x1);
    float ry1 = (intersectY - line2_y1) / (line2_y2 - line2_y1);


    if(((rx0 >= 0.0f && rx0 <= 1) || 
	(ry0 >= 0.0f && ry0 <= 1)) && 
	((rx1 >= 0.0f && rx1 <= 1) || 
	(ry1 >= 0.0f && ry1 <= 1)))
    {
        return sqrt(pow((intersectX - line1_x1), 2) + 
		    pow((intersectY - line1_y1), 2));
    }
    else
    {
        return -1;
    }
}


/*
Takes in a direction and a rate and returns the rate of
travel on the X-Axis
*/
float ray_caster::get_stepx(float rate, int degrees)
{
    return (((cos(degrees * M_PI / 180.0f))*rate));
}

/*
Takes in a direction and a rate and returns the rate of
travel on the Y-Axis
*/
float ray_caster::get_stepy(float rate, int degrees)
{
    return (((sin(degrees * M_PI / 180.0f))*rate));
}

















