#ifndef __XFC_CAIRO_MATRIX__
#define __XFC_CAIRO_MATRIX__ 1

#include <xfc/cairo/types.hh>

namespace Xfc {
    namespace Cairo {

        class Matrix : public cairo_matrix_t {
        public:
            Matrix();
            Matrix( const Matrix &matrix );
            Matrix( double xx, double yx, double xy, double yy, double x0, double y0);

            void init_identity();
            void init_translate( double tx, double ty);
            void init_scale( double sx, double sy);
            void init_rotate( double radians );
            void translate( double tx, double ty);
            void scale( double sx, double sy);
            void rotate( double radians );
            Status invert();
            void multiply( const Matrix &a, const Matrix &b);
            void transform_distance ( double &dx, double &dy);
            void transform_point( double &x, double &y);
        };
    }
}

#endif
