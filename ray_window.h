#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include "wall_object.h"

class ray_window
{
	public:
		ray_window(int v_XRES, int v_YRES);
		~ray_window();
	
		void read_events();
		
		void line_cast(wall_object line_array[]);
		void clear();
	private:

		Display *current_display;
		int screen;
		Window current_window;
		GC graphics_context;

		XEvent event;

		int XRES;
		int YRES;

		void initialize();
		void close();

};
