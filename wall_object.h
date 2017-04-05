#ifndef Included_wall_object_H
#define Included_wall_object_H


class wall_object
{
	public:
		wall_object();
		wall_object(int p_max, int p_unit);

		int get_hex_value();
		
		int get_red() {return RED;}
		int get_green() {return GREEN;}
		int get_blue() {return BLUE;}
		
		int get_base_red() {return BASE_RED;}
		int get_base_green() {return BASE_GREEN;}
		int get_base_blue() {return BASE_BLUE;}
		
		void set_hex_color(int r, int g, int b);
		int get_hex_color();

		void set_base_hex_color(int r, int g, int b);
		int get_base_hex_color();

		void set_base_red(int val) {BASE_RED = (val % 100);}
		void set_base_green(int val) {BASE_GREEN = (val % 100);}
		void set_base_blue(int val) {BASE_BLUE = (val % 100);}

		void set_red(int val) {RED = (val % 100);}
		void set_green(int val) {GREEN = (val % 100);}
		void set_blue(int val) {BLUE = (val % 100);}

		void set_size(float distance);
		float get_size() {return SIZE;}

		void set_unit(int size) {UNIT_SIZE = size;}
		void set_max(int size) {MAX_SIZE = size;}

		void set_distance(float distance) {DISTANCE = distance;}
		float get_distance() {return DISTANCE;}

	private:
		int BASE_RED;
		int BASE_GREEN;
		int BASE_BLUE;

		int RED;
		int GREEN;
		int BLUE;

		int MAX_SIZE;
		int UNIT_SIZE;
		float SIZE;
		float DISTANCE;
};

#endif
