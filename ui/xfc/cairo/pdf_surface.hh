#include <xfc/cairo/surface.hh>

#include <cairo-pdf.h>

namespace Xfc {
    namespace Cairo {

        class PDFSurface : public Surface {
        public:
            PDFSurface( const string &fname, double width_in_points, double height_in_points );
            void set_size( double width_in_points, double height_in_points );
        };
    }
}
