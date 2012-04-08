#include <xfc/cairo/surface.hh>

#include <cairo-ps.h>

namespace Xfc {
    namespace Cairo {


        class PsSurface : public Surface {
        public:
            PsSurface( const string &fname, double width_in_points, double height_in_points); 

            void set_size( double width_in_points, double height_in_points );
            void dsc_comment( const string &comment );
        };
    }
}
