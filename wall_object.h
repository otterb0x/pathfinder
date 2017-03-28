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
		
		void set_hex_color(int r, int g, int b);
		int get_hex_color();

		void set_red(int val) {RED = (val % 100);}
		void set_green(int val) {GREEN = (val % 100);}
		void set_blue(int val) {BLUE = (val % 100);}

		void set_size(int distance);
		int get_size() {return SIZE;}

		void set_unit(int size) {UNIT_SIZE = size;}
		void set_max(int size) {MAX_SIZE = size;}

	private:
		int RED;
		int GREEN;
		int BLUE;

		int MAX_SIZE;
		int UNIT_SIZE;
		int SIZE;
};

#endif
