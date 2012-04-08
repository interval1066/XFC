/**
   @file xfc/cairo/surface.hh
   @brief A Cairo Surface C++ wrapper interface.

   Base class for surfaces
*/

#ifndef __XFC_CAIRO_SURFACE__
#define __XFC_CAIRO_SURFACE__ 1

#include <xfc/cairo/types.hh>
#include <xfc/cairo/fontoptions.hh>
#include <xfc/cairo/context.hh>

#include <string>

namespace Xfc {
    namespace Cairo {
        
        using namespace std;

        class Context;

        enum SurfaceType {
            SURFACE_TYPE_IMAGE =    CAIRO_SURFACE_TYPE_IMAGE,
            SURFACE_TYPE_PDF =      CAIRO_SURFACE_TYPE_PDF,
            SURFACE_TYPE_PS =       CAIRO_SURFACE_TYPE_PS,
            SURFACE_TYPE_XLIB =     CAIRO_SURFACE_TYPE_XLIB,
            SURFACE_TYPE_XCB =      CAIRO_SURFACE_TYPE_XCB,
            SURFACE_TYPE_GLITZ =    CAIRO_SURFACE_TYPE_GLITZ,
            SURFACE_TYPE_QUARTZ =   CAIRO_SURFACE_TYPE_QUARTZ,
            SURFACE_TYPE_WIN32 =    CAIRO_SURFACE_TYPE_WIN32,
            SURFACE_TYPE_BEOS =     CAIRO_SURFACE_TYPE_BEOS,
            SURFACE_TYPE_DIRECTFB = CAIRO_SURFACE_TYPE_DIRECTFB,
            SURFACE_TYPE_SVG =      CAIRO_SURFACE_TYPE_SVG
        };
        
        class Surface {
        protected:
            cairo_surface_t *m_surface;
        public:
            explicit Surface( cairo_surface_t *surface, bool owns_reference = true );

            Surface( const Surface &surface );

            /**
               Create a new surface that is as compatible as possible with an existing 
               surface. For example the new surface will have the same fallback 
               resolution and font options as other. Generally, the new surface will 
               also use the same backend as other, unless that is not possible for 
               some reason. The type of the returned surface may be examined with 
               the get_type() member.

               Initially the surface contents are all 0 (transparent if contents have 
               transparency, black otherwise.)

               @param other an existing surface used to select the backend of the new surface
               @param content the content for the new surface
               @param width width of the new surface, (in device-space units)
               @param height height of the new surface (in device-space units)
            */
            Surface( const Surface &other, Content content, int width, int height );

            virtual ~Surface();

            Context get_context();
            void finish();
            void flush();
            void get_font_options( FontOptions &fo );
            Content get_content();
            Pattern get_pattern();
            void mark_dirty();
            void mark_dirty_rectangle( int x, int y, int width,int height);
            void set_device_offset( double x_offset, double y_offset);
            void get_device_offset( double &x_offset, double &y_offset);
            void set_fallback_resolution(double x_pixels_per_inch, double y_pixels_per_inch);
            Status status();
            SurfaceType get_type() const;

            operator cairo_surface_t* () const { return m_surface; }
        };

    }
}

#endif
