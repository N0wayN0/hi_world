#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Display* d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }
    int s = DefaultScreen(d);
    Window w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 200, 1,
                                    BlackPixel(d, s), WhitePixel(d, s));
    XSetStandardProperties(d, w, "My Window", "My Icon", None, NULL, 0, NULL);
    Atom wmDeleteMessage = XInternAtom(d, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(d, w, &wmDeleteMessage, 1);
    XSelectInput(d, w, ExposureMask|ButtonPressMask);
    GC gc = XCreateGC(d, w, 0, NULL);
    XSetForeground(d, gc, BlackPixel(d, s));
    XSetBackground(d, gc, WhitePixel(d, s));
    XFontStruct* font = XLoadQueryFont(d, "9x15");
    XSetFont(d, gc, font->fid);
    XMapWindow(d, w);
    while (1) {
        XEvent e;
        XNextEvent(d, &e);
        if (e.type == Expose) {
            XDrawString(d, w, gc, 50, 50, "Hello, world!", 13);
        }
        if (e.type == ButtonPress) {
            if (e.xbutton.button == Button1) {
                XDestroyWindow(d, w);
                break;
            }
        }
        if (e.type == ClientMessage) {
            if (e.xclient.message_type == XInternAtom(d, "WM_PROTOCOLS", True) &&
                e.xclient.format == 32 && e.xclient.data.l[0] == wmDeleteMessage) {
                XDestroyWindow(d, w);
                break;
            }
        }
    }
    XFreeGC(d, gc);
    XUnloadFont(d, font->fid);
    XCloseDisplay(d);
    return 0;
}

