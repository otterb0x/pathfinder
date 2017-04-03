#include "ray_window.h"

ray_window::ray_window(int v_XRES, int v_YRES)
{
	// Set the XRES & YRES to the visiting variables
	XRES = v_XRES;
	YRES = v_YRES;

	window_buffer = new int*[XRES];

	for(int i = 0; i < XRES; i++)
		window_buffer[i] = new int[YRES];		

	// Initialize the display
	initialize();
}

ray_window::~ray_window()
{
	// Free up resources
	close();
}

void ray_window::initialize()
{
	unsigned long black,white;

	// Create the X connection to open the current_displayplay
        current_display = XOpenDisplay((char *)0);
        screen = DefaultScreen(current_display);
        black = BlackPixel(current_display,screen),
        white = WhitePixel(current_display, screen);
        
	// Create the window after the current_displayplay is initialized
	current_window=XCreateSimpleWindow(current_display,
					   DefaultRootWindow(current_display),
					   0,0,
                			   XRES, YRES, 5,
					   black, white);
        
	// Set the properties of the window
	XSetStandardProperties(current_display,
				current_window,
				"Ray Window",
				"Ray Window",
				None,NULL,0,NULL);
        
	// Set the type of inputs that are allowed
	XSelectInput(current_display, current_window, 
		     ExposureMask|ButtonPressMask|KeyPressMask);
        
	// Create graphics content
	graphics_context=XCreateGC(current_display, current_window, 0,0);
        
	// Set the background and foreground colors
	XSetBackground(current_display,graphics_context,white);
        XSetForeground(current_display,graphics_context,black);
        
	// Clear the window and bring it to the top of the other windows
	XClearWindow(current_display, current_window);
        XMapRaised(current_display, current_window);
}

void ray_window::close()
{
	// Free up system resources
	XFreeGC(current_display, graphics_context);
        XDestroyWindow(current_display,current_window);
        XCloseDisplay(current_display);
}


// Chris if you're reading this this is problem a function to work on.
void ray_window::read_events()
{
	// Read next event.
	XNextEvent(current_display, &event);
}


void ray_window::line_cast_to_buffer(wall_object line_array[])
{
	int current_point;
	int draw_size;

	for(int i = 0; i < XRES; i++)
	{
		current_point = (YRES / 2) - (line_array[i].get_size() / 2);
		draw_size = line_array[i].get_size(); 

		while(current_point < draw_size)
		{
			if((current_point > 0) && (current_point < YRES))
			{
				window_buffer[i][current_point] = 
						line_array[i].get_hex_color();
			}
		}
	}
}

void ray_window::draw_rectangle_to_buffer(int X1, int Y1,
				int X2, int Y2,
				int color)
{
	for(int i = X1; i < X2; i++)
	{
		if((i > 0) && (i < XRES))
		{
			for(int j = Y1; j < Y2; j++)
			{
				if((j > 0) && (j < YRES))
				{
				 window_buffer[i][j] = color;	
				}
			}
		}
	}
}


void ray_window::draw_buffer()
{
	for(int i = 0; i < XRES; i++)
		for(int j = 0; j < YRES; j++)
		{
			XSetForeground(current_display, 
					graphics_context,
					window_buffer[i][j]);

			XDrawPoint(current_display, current_window, 
				graphics_context, i, j);
		}
}

void ray_window::line_cast(wall_object line_array[])
{
	XClearWindow(current_display, current_window);

	// Set the draw color to white and draw the ceiling
	XSetForeground(current_display,graphics_context,
					0xFFFFFF
					);

	XFillRectangle(current_display,
			current_window,
			graphics_context,
			0, 0,
			XRES, (YRES / 2));

	// Set the draw color to tan and draw the floor
	XSetForeground(current_display,graphics_context,
					0xBA924E
					);
	XFillRectangle(current_display,
			current_window,
			graphics_context,
			0, (YRES / 2),
			XRES, YRES);

	for(int i = 0; i < XRES; i++)
	{
		// Set the draw color to the shade of the current
		// wall_object
		XSetForeground(current_display,graphics_context,
                                        line_array[i].get_hex_color()
                                        );
		
		// If the size of the wall is greater than zero, as in it
		// exists, then draw the wall
		if(line_array[i].get_size() > 0)
			XDrawLine(current_display, 
				current_window, 
				graphics_context,
			  i, ((YRES / 2) - (line_array[i].get_size() / 2)),
			  i, ((YRES / 2) + (line_array[i].get_size() / 2)));
	}
}

void ray_window::clear()
{
	// Set the window to white
	XClearWindow(current_display, current_window);
}















