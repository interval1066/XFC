#include <xfc/cairo/svg_surface.hh>

using namespace Xfc;
using namespace Cairo;

SVGSurface::SVGSurface( const string &fname, double width_in_points, double height_in_points ) :
    Surface( cairo_svg_surface_create( fname.c_str(), width_in_points, height_in_points ), false )
{
}

void SVGSurface::restrict_to_version( Version version )
{
    cairo_svg_surface_restrict_to_version( m_surface, (cairo_svg_version_t)version );
}
