/**
   @file xfc/cairo/pattern.hh
   @brief A Cairo Pattern C++ wrapper class
   
   Patterns - Gradients and filtered sources
*/

#ifndef __XFC_CAIRO_PATTERN__
#define __XFC_CAIRO_PATTERN__ 1

#include <xfc/cairo/types.hh>
#include <xfc/cairo/matrix.hh>
// #include <xfc/cairo/surface.hh>

namespace Xfc {
    namespace Cairo {
        class Surface;

        enum Filter {
            FILTER_FAST     = CAIRO_FILTER_FAST,
            FILTER_GOOD     = CAIRO_FILTER_GOOD,
            FILTER_BEST     = CAIRO_FILTER_BEST,
            FILTER_NEAREST  = CAIRO_FILTER_NEAREST,
            FILTER_BILINEAR = CAIRO_FILTER_BILINEAR,
            FILTER_GAUSSIAN = CAIRO_FILTER_GAUSSIAN
        };

        enum PatternType {
            PATTERN_SOLID =   CAIRO_PATTERN_TYPE_SOLID,
            PATTERN_SURFACE = CAIRO_PATTERN_TYPE_SURFACE,
            PATTERN_LINEAR =  CAIRO_PATTERN_TYPE_LINEAR,
            PATTERN_RADIAL =  CAIRO_PATTERN_TYPE_RADIAL
        }; 

        enum Extend {
            EXTEND_NONE =    CAIRO_EXTEND_NONE,
            EXTEND_REPEAT =  CAIRO_EXTEND_REPEAT,
            EXTEND_REFLECT = CAIRO_EXTEND_REFLECT,
            EXTEND_PAD =     CAIRO_EXTEND_PAD
        };

        /**
           A Pattern represents a source when drawing onto a surface. There are different 
           subtypes of Pattern, for different types of sources; for example, 
           Pattern( red, green, blue) creates a pattern for a solid opaque color.

           The type of a pattern can be queried with get_type() member.
         */
        class Pattern {
            cairo_pattern_t *m_pattern;
        public:
            explicit Pattern( cairo_pattern_t *pattern );

            Pattern( double red, double green, double blue );
            Pattern( double red, double green, double blue, double alpha );
//            Pattern( double x0, double y0, double x1, double y1);
//            Pattern( double cx0, double cy0, double radius0, double cx1,
//                     double cy1, double radius1);
            Pattern( const Pattern &pattern );
            ~Pattern();

            void add_color_stop_rgb( double offset, double red,
                                     double green,  double blue);
            void add_color_stop_rgba( double offset, double red,
                                      double green, double blue, double alpha);

            Status status();
            void set_extend( Extend extend );
            Extend get_extend();
            void set_filter( Filter filter );
            Filter get_filter();
            void set_matrix( const Matrix &matrix );
            Matrix get_matrix();
            PatternType get_type();

            // Return a lowlevel handle
            operator cairo_pattern_t *() const { return m_pattern;}
        };

        Pattern pattern_create_linear( double x0, double y0, double x1, double y1 );
        Pattern pattern_create_radial( double cx0, double cy0, double radius0, double cx1,
                                       double cy1, double radius1 );
    }
}

#endif
