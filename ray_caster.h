#include <cmath>
#include <climits>

#include "wall_object.h"

class ray_caster
{
	public:
		void get_raycast_array(wall_object raycast_array[],
					int raycast_array_size,
				  /*	int map[][], int map_size,*/
					float pos_x, float pos_y,
				  	int FOV, int direction,
					int wall_size);
	private:
		float get_box_distance(float X1, float Y1, float X2, float Y2,
					int box_x, int box_y, int wall_size);

		float get_distance(float line1_x1, float line1_y1,
                                        float line1_x2, float line1_y2,
                                        float line2_x1, float line2_y1,
                                        float line2_x2, float line2_y2);

		float get_stepx(float rate, int degrees);
		float get_stepy(float rate, int degrees);
};
