#include <xfc/cairo/ps_surface.hh>

using namespace Xfc;
using namespace Cairo;

PsSurface::PsSurface( const string &fname, double width_in_points, double height_in_points) :
    Surface( cairo_ps_surface_create( fname.c_str(), width_in_points, height_in_points ), false )
{}

void PsSurface::set_size( double width_in_points, double height_in_points )
{
    cairo_ps_surface_set_size( m_surface, width_in_points, height_in_points );
}

void PsSurface::dsc_comment( const string &comment )
{
    cairo_ps_surface_dsc_comment( m_surface, comment.c_str() );
}

