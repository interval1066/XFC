#ifndef __XFC_CAIRO_XLIB_SURFACE__
#define __XFC_CAIRO_XLIB_SURFACE__ 1

#include <xfc/cairo/surface.hh>

#include <cairo-xlib.h>

namespace Xfc {
    namespace Cairo {

        class XlibSurface : public Surface {
        public:
            XlibSurface( Display *dpy, Drawable drawable,
                         Visual *visual, int width, int height);

            XlibSurface( Display *dpy, Pixmap bitmap, Screen *screen,
                         int width, int height);
            void set_size( int width, int height);
            Display* get_display();
            Screen* get_screen();
            void set_drawable( Drawable drawable, int width, int height);
            Drawable get_drawable();
            Visual* get_visual();
            int get_width();
            int get_height();
            int get_depth();
        };
    }
}

#endif
