#include <xfc/cairo/xlib_surface.hh>

using namespace Xfc;
using namespace Cairo;

XlibSurface::XlibSurface( Display *dpy, Drawable drawable,
                          Visual *visual, int width, int height) :
    Surface( cairo_xlib_surface_create( dpy, drawable, visual, width, height ), false )
{}

XlibSurface::XlibSurface( Display *dpy, Pixmap bitmap, Screen *screen,
                          int width, int height) : 
    Surface( cairo_xlib_surface_create_for_bitmap( dpy, bitmap, screen, width, height ), false ) 
{}

void XlibSurface::set_size( int width, int height)
{
    cairo_xlib_surface_set_size( m_surface, width, height );
}

Display* XlibSurface::get_display()
{
    return cairo_xlib_surface_get_display( m_surface );
}

Screen* XlibSurface::get_screen()
{
    return cairo_xlib_surface_get_screen( m_surface );
}

void XlibSurface::set_drawable( Drawable drawable, int width, int height)
{
    cairo_xlib_surface_set_drawable( m_surface, drawable, width, height );
}

Drawable XlibSurface::get_drawable()
{
    return cairo_xlib_surface_get_drawable( m_surface );
}

Visual* XlibSurface::get_visual()
{
    return cairo_xlib_surface_get_visual( m_surface );
}

int XlibSurface::get_width()
{
    return cairo_xlib_surface_get_width( m_surface );
}

int XlibSurface::get_height()
{
    return cairo_xlib_surface_get_height( m_surface );
}

int XlibSurface::get_depth()
{
    return cairo_xlib_surface_get_depth( m_surface );
}
