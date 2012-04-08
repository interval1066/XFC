#ifndef __XFC_CAIRO_FONTOPTIONS__
#define __XFC_CAIRO_FONTOPTIONS__ 1

#include <xfc/cairo/types.hh>

namespace Xfc {
    namespace Cairo {
        /// Specifies the type of antialiasing to do when rendering text or shapes.
        enum Antialias {
            ANTIALIAS_DEFAULT =  CAIRO_ANTIALIAS_DEFAULT,   /// Use the default antialiasing for the subsystem and target device
            ANTIALIAS_NONE =     CAIRO_ANTIALIAS_NONE,      /// Use a bilevel alpha mask
            ANTIALIAS_GRAY =     CAIRO_ANTIALIAS_GRAY,      /// Perform single-color antialiasing (using shades of gray for black text on a white background, for example).
            ANTIALIAS_SUBPIXEL = CAIRO_ANTIALIAS_SUBPIXEL   /// Perform antialiasing by taking advantage of the order of subpixel elements on devices such as LCD panels
        };
        
        enum SubpixelOrder {
            SUBPIXEL_ORDER_DEFAULT = CAIRO_SUBPIXEL_ORDER_DEFAULT,
            SUBPIXEL_ORDER_RGB     = CAIRO_SUBPIXEL_ORDER_RGB,
            SUBPIXEL_ORDER_BGR     = CAIRO_SUBPIXEL_ORDER_BGR,
            SUBPIXEL_ORDER_VRGB    = CAIRO_SUBPIXEL_ORDER_VRGB,
            SUBPIXEL_ORDER_VBGR    = CAIRO_SUBPIXEL_ORDER_VBGR
        };
        
        enum HintStyle {
            HINT_STYLE_DEFAULT =  CAIRO_HINT_STYLE_DEFAULT,
            HINT_STYLE_NONE    = CAIRO_HINT_STYLE_NONE,
            HINT_STYLE_SLIGHT  = CAIRO_HINT_STYLE_SLIGHT,
            HINT_STYLE_MEDIUM  = CAIRO_HINT_STYLE_MEDIUM,
            HINT_STYLE_FULL    = CAIRO_HINT_STYLE_FULL
        };

        enum HintMetrics {
            HINT_METRICS_DEFAULT = CAIRO_HINT_METRICS_DEFAULT,
            HINT_METRICS_OFF     = CAIRO_HINT_METRICS_OFF,
            HINT_METRICS_ON      = CAIRO_HINT_METRICS_ON
        };


        class FontOptions {
            cairo_font_options_t *m_font_options;
        public:
            FontOptions();
            FontOptions( const cairo_font_options_t *fo );
            FontOptions( const FontOptions &fo );

            ~FontOptions();

            Status status();
            void merge( const FontOptions &other );
            unsigned long hash();
            bool equal( const FontOptions &other );
            void set_antialias( Antialias antialias);
            Antialias get_antialias();
            void set_subpixel_order( SubpixelOrder subpixel_order);
            SubpixelOrder get_subpixel_order();
            void set_hint_style( HintStyle hint_style);
            HintStyle get_hint_style();
            void set_hint_metrics( HintMetrics hint_metrics);
            HintMetrics get_hint_metrics();

            operator cairo_font_options_t* () const;
        };
    }
}

#endif
