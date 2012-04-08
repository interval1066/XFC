#include <xfc/cairo/matrix.hh>

using namespace Xfc;
using namespace Cairo;

Matrix::Matrix()
{
}

Matrix::Matrix( const Matrix &matrix )
{
    xx = matrix.xx; 
    yx = matrix.yx;
    xy = matrix.xy; 
    yy = matrix.yy;
    x0 = matrix.x0; 
    y0 = matrix.y0;
}

Matrix::Matrix( double xx, double yx, double xy, double yy, double x0, double y0)
{
    cairo_matrix_init( this, xx, yx, xy, yy, x0, y0 );
}

void Matrix::init_identity()
{
    cairo_matrix_init_identity( this );
}

void Matrix::init_translate( double tx, double ty)
{
    cairo_matrix_init_translate( this, tx, ty );
}

void Matrix::init_scale( double sx, double sy)
{
    cairo_matrix_init_scale( this, sx, sy );
}

void Matrix::init_rotate( double radians )
{
    cairo_matrix_init_rotate( this, radians );
}

void Matrix::translate( double tx, double ty)
{
    cairo_matrix_translate( this, tx, ty );
}

void Matrix::scale( double sx, double sy)
{
    cairo_matrix_scale( this, sx, sy );
}

void Matrix::rotate( double radians )
{
    cairo_matrix_rotate( this, radians );
}

Status Matrix::invert()
{
    cairo_matrix_invert( this );
}

void Matrix::multiply( const Matrix &a, const Matrix &b ) 
{
    cairo_matrix_multiply( this, &a, &b );
}

void Matrix::transform_distance( double &dx, double &dy )
{
    cairo_matrix_transform_distance( this, &dx, &dy );
}

void Matrix::transform_point( double &x, double &y)
{
    cairo_matrix_transform_point( this, &x, &y );
}
