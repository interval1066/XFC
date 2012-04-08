#ifndef __XFC_CAIRO_IMAGE_SURFACE__
#define __XFC_CAIRO_IMAGE_SURFACE__ 1

#include <xfc/cairo/surface.hh>

namespace Xfc {
    namespace Cairo {

        enum Format {
            FORMAT_ARGB32 = CAIRO_FORMAT_ARGB32,
            FORMAT_RGB24  = CAIRO_FORMAT_RGB24,
            FORMAT_A8     = CAIRO_FORMAT_A8,
            FORMAT_A1     = CAIRO_FORMAT_A1
        };

        class ImageSurface : public Surface {
        public:
            /**
               Creates an image surface of the specified format and dimensions. 
               Initially the surface contents are all 0. (Specifically, within 
               each pixel, each color or alpha channel belonging to format will 
               be 0. The contents of bits within a pixel, but not belonging to 
               the given format are undefined).

               @param format format of pixels in the surface to create
               @param width width of the surface, in pixels
               @param height height of the surface, in pixels
             */
            ImageSurface( Format f, int width, int height );

            /**
               Creates a new image surface and initializes the contents to 
               the given PNG file.

               @param png_fname the filename of the png file.
             */
            ImageSurface( const string &png_fname );
                
            /**
               Writes the contents of surface to a new file filename as a PNG image. 

               @param fname the png file name to write to
            */
            void write_png( const string &fname );

            /**
               Get the format of the surface.
               
               @returns the format of the surface
             */
            Format get_format() const;

            /**
               Get the width of the image surface in pixels.

               @return the width of the surface in pixels.
             */
            int get_width() const;

            /**
               Get the height of the image surface in pixels.

               @return the height of the surface in pixels.
             */
            int get_height() const;

            /**
               Get the stride of the image surface in bytes

               @return the stride of the image surface in bytes (or 0 if surface 
               is not an image surface). The stride is the distance in bytes from 
               the beginning of one row of the image data to the beginning of 
               the next row. 
             */
            int get_stride() const;
        };
    }
}

#endif
