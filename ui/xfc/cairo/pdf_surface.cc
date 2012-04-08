#include <xfc/cairo/pdf_surface.hh>

using namespace Xfc;
using namespace Cairo;

PDFSurface::PDFSurface( const string &fname, double width_in_points, double height_in_points ) :
    Surface( cairo_pdf_surface_create( fname.c_str(), width_in_points, height_in_points ), false )
{
}

void PDFSurface::set_size( double width_in_points, double height_in_points )
{
    cairo_pdf_surface_set_size( m_surface, width_in_points, height_in_points );
}

