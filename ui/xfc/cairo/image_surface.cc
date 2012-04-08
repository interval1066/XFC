#include <xfc/cairo/image_surface.hh>

using namespace Xfc;
using namespace Cairo;

ImageSurface::ImageSurface( Format f, int width, int height ) :
    Surface( cairo_image_surface_create( (cairo_format_t)f, width, height ), false )
{
    if( STATUS_SUCCESS != status())
        throw Exception( status());
}

ImageSurface::ImageSurface( const string &png_fname ) :
    Surface( cairo_image_surface_create_from_png( png_fname.c_str() ), false )
{
    if( STATUS_SUCCESS != status())
        throw Exception( status());
}

void ImageSurface::write_png( const string &fname ) 
{
    cairo_surface_write_to_png( m_surface, fname.c_str() );
}

Format ImageSurface::get_format() const
{
    return (Format) cairo_image_surface_get_format(m_surface);
}

int ImageSurface::get_width() const
{
    return cairo_image_surface_get_width(m_surface);
}

int ImageSurface::get_height() const
{
    return cairo_image_surface_get_height(m_surface);
}

int ImageSurface::get_stride() const
{
    return cairo_image_surface_get_stride(m_surface);
}







