#include <xfc/cairo/pattern.hh>

using namespace Xfc;
using namespace Cairo;

Pattern::Pattern( cairo_pattern_t *pattern )
{
    m_pattern = pattern;

    cairo_pattern_reference( m_pattern );
}

Pattern::Pattern( const Pattern &pattern ) 
{
    m_pattern = pattern.m_pattern;

    cairo_pattern_reference( m_pattern );
}

Pattern::Pattern( double red, double green, double blue )
{
    m_pattern = cairo_pattern_create_rgb( red, green, blue );
}

Pattern::Pattern( double red, double green, double blue, double alpha)
{
    m_pattern = cairo_pattern_create_rgba( red, green, blue, alpha );
}

Pattern pattern_create_linear( double x0, double y0, double x1, double y1 )
{
    Pattern pattern( cairo_pattern_create_linear( x0, y0, x1, y1 ));

    return pattern;
}

Pattern pattern_create_radial( double cx0, double cy0, double radius0, 
                               double cx1, double cy1, double radius1 )
{
    Pattern pattern( cairo_pattern_create_radial( cx0, cy0, radius0, 
                                                  cx1, cy1, radius1 ));

    return pattern;
}

Pattern::~Pattern()
{
    cairo_pattern_destroy( m_pattern );
}


void Pattern::add_color_stop_rgb( double offset, double red,
                                  double green,  double blue)
{
    cairo_pattern_add_color_stop_rgb( m_pattern, offset, red, green, blue );
}

void Pattern::add_color_stop_rgba( double offset, double red,
                                   double green, double blue, double alpha)
{
    cairo_pattern_add_color_stop_rgba( m_pattern, offset, red, green, blue, alpha );
}

Status Pattern::status() 
{
    return (Status)cairo_pattern_status( m_pattern );
}

void Pattern::set_extend( Extend extend )
{
    cairo_pattern_set_extend( m_pattern, (cairo_extend_t)extend );
}

Extend Pattern::get_extend()
{
    return (Extend)cairo_pattern_get_extend( m_pattern );
}

void Pattern::set_filter( Filter filter )
{
    cairo_pattern_set_filter( m_pattern, (cairo_filter_t)filter );
}

Filter Pattern::get_filter()
{
    return (Filter)cairo_pattern_get_filter( m_pattern );
}

void Pattern::set_matrix( const Matrix &matrix )
{
    cairo_pattern_set_matrix( m_pattern, &matrix );
}

Matrix Pattern::get_matrix()
{
    Matrix matrix;

    cairo_pattern_get_matrix( m_pattern, &matrix );

    return matrix;
}

PatternType Pattern::get_type()
{
    return (PatternType)cairo_pattern_get_type( m_pattern );
}
