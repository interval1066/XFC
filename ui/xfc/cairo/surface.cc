#include <xfc/cairo/surface.hh>

using namespace Xfc;
using namespace Cairo;

Surface::Surface( cairo_surface_t *surface, bool owns_reference )
{
    m_surface = surface;

    if( owns_reference )
        cairo_surface_reference( m_surface );
}

Surface::Surface( const Surface &other, Content content, int width, int height)
{
    m_surface = cairo_surface_create_similar( other.m_surface, 
                                              (cairo_content_t)content, width, height );

    if( STATUS_SUCCESS != status())
        throw Exception( status());
}

Surface::Surface( const Surface &surface )
{
    m_surface = surface.m_surface;

    cairo_surface_reference( m_surface );
}

Surface::~Surface() 
{
    cairo_surface_destroy( m_surface );
}

Context Surface::get_context()
{
    return Context( cairo_create( m_surface ));
}

Pattern Surface::get_pattern()
{
    return Pattern( cairo_pattern_create_for_surface( m_surface ));
}

void Surface::finish()
{
    cairo_surface_finish( m_surface );
}

void Surface::flush()
{
    cairo_surface_flush( m_surface );
}

void Surface::get_font_options( FontOptions &fo )
{
    cairo_surface_get_font_options( m_surface, fo );
}

Content Surface::get_content()
{
    return (Content)cairo_surface_get_content( m_surface );
}

void Surface::mark_dirty()
{
    cairo_surface_mark_dirty( m_surface );
}

void Surface::mark_dirty_rectangle( int x, int y, int width, int height)
{
    cairo_surface_mark_dirty_rectangle( m_surface, x, y , width, height);
}

void Surface::set_device_offset( double x_offset, double y_offset)
{
    cairo_surface_set_device_offset( m_surface, x_offset, y_offset );
}

void Surface::get_device_offset( double &x_offset, double &y_offset )
{
    cairo_surface_get_device_offset( m_surface,  &x_offset, &y_offset );
}

void Surface::set_fallback_resolution(double x_pixels_per_inch, double y_pixels_per_inch)
{
    cairo_surface_set_fallback_resolution( m_surface, x_pixels_per_inch, y_pixels_per_inch );
}

Status Surface::status()
{
    return (Status)cairo_surface_status( m_surface );
}

SurfaceType Surface::get_type() const
{
    return (SurfaceType)cairo_surface_get_type( m_surface );
}

