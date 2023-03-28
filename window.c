#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

static const char * const MARK_COLOR   = "#FF0000";

int main() {
	/* get the colors black and white (see section for details) */
	unsigned long black,white;

	/* use the information from the environment variable DISPLAY 
	   to create the X connection:
	*/	
	Display *dis = XOpenDisplay(NULL);
	if (!dis) {
		return 1;
	}
   	int screen = DefaultScreen(dis);
	black=BlackPixel(dis,screen),	/* get color black */
	white=WhitePixel(dis, screen);  /* get color white */

	/* once the display is initialized, create the window.
	   This window will be have be 200 pixels across and 300 down.
	   It will have the foreground white and background black
	*/
  /* 	Window win = XCreateSimpleWindow(dis,DefaultRootWindow(dis), 0, 0, 200, 300, 5, white, black);




  XMapWindow(dis, win);
  XFlush(dis);

  while (1) {
    XEvent e;
    XNextEvent(dis, &e);
  }
*/
  return 0;
}

