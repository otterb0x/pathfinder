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
                                        int FOV, float direction,
                                        int wall_size)
{
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

	int map_x = pos_x / 100;
	int map_y = pos_y / 100;

	float dir_x;
	float temp_x;
	float dir_y;
	float temp_y;

	float step_x_calc;
	float step_y_calc;

	float end_x;
	float end_y;

	float side_x;
	float side_y;

	float side_px;
	float side_py;

	float step_x;
	float step_y;

	int map_step_x;
	int map_step_y;

	float current_box_dist;

	bool hit;
	int count = 0;

	for(int i = 0; i < raycast_array_size; i++)
	{
		hit = false;
		count = 0;

		current_angle = start_angle + (i * angle_step);

		end_x = get_stepx(9999999, current_angle);
		end_y = get_stepy(9999999, current_angle);

		current_box_dist = get_box_distance(pos_x, pos_y,
						end_x, end_y,
						map_x, map_y,
						wall_size);
		
		side_x = current_box_dist * cos(current_angle * M_PI / 180.0f);
		side_y = current_box_dist * sin(current_angle * M_PI / 180.0f);

		while(dir_x == -1)
		{
			get_intersect_points(pos_x, pos_y,
						end_x, end_y,
						ceil(pos_x/100)*100, 999999,
						ceil(pos_y/100)*100, -999999,
						dir_x, temp_y);
		}
		while(dir_y == -1)
		{
			get_intersect_points(pos_x, pos_y,
						end_x, end_y,
						ceil(pos_x/100)*100, 999999,
						ceil(pos_y/100)*100, -999999,
						temp_x, dir_y);
		}

		step_x = get_distance(pos_x + dir_x, pos_y + temp_y,
					end_x, end_y,
					ceil((pos_x/100)+1)*100, -9999999,
					ceil((pos_x/100)+1)*100, 9999999);

		step_y = get_distance(pos_x + temp_x, pos_y + dir_y,
					end_x, end_y,
					9999999, ceil((pos_y/100)+1)*100,
					-9999999, ceil((pos_y/100)+1)*100);

		if(dir_x < pos_x)
		{
			map_step_x = -1;
		}
		else
		{
			map_step_x = 1;
		}
		if(dir_y > pos_y)
		{
			map_step_y = 1;
		}
		else
		{
			map_step_y = -1;
		}

		while(!hit && count < 1000)
		{
			if(side_x < side_y)
			{
				map_x += map_step_x;
				side_x += step_x;
			}
			else
			{
				map_y += map_step_y;
				side_y += step_y;
			}

			if(maze.get_square(map_step_x, map_step_y) > 0)
			{
				hit = true;
			}
			count++;
		}
/*
		distance_calc = sqrt(pow(side_x - pos_x, 2) + 
					pow(side_y - pos_y, 2));
*/

		distance_calc = get_box_distance(pos_x, pos_y, end_x, end_y,
						map_step_x * wall_size,
						map_step_y * wall_size,
						wall_size);

		raycast_array[i].set_hex_color(
		raycast_array[i].get_base_red() / (distance_calc / 100.0f),
		raycast_array[i].get_base_green() / (distance_calc / 100.0f),
		raycast_array[i].get_base_blue() / (distance_calc / 100.0f));
			raycast_array[i].set_size(distance_calc);
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


void ray_caster::get_intersect_points(float line1_x1, float line1_y1,
                                        float line1_x2, float line1_y2,
                                        float line2_x1, float line2_y1,
                                        float line2_x2, float line2_y2,
                                        float x, float y)
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
        return;
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
	x = intersectX;
	y = intersectY; 
    }
    else
    {
        x = -1;
	y = -1;
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

















