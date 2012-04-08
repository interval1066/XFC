#include <xfc/cairo/surface.hh>

#include <cairo-svg.h>

namespace Xfc {
    namespace Cairo {

        class SVGSurface : public Surface {
        public:
            enum Version {
                SVG_VERSION_1_1 = CAIRO_SVG_VERSION_1_1,
                SVG_VERSION_1_2 = CAIRO_SVG_VERSION_1_2
            };

            SVGSurface( const string &fname, double width_in_points, double height_in_points );

            void restrict_to_version( Version version );
        };
    }
}
