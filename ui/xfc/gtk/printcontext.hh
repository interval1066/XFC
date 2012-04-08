/**
   GtkPrintContext
*/

#ifndef XFC_PRINT_CONTEXT_HH
#define XFC_PRINT_CONTEXT_HH 1

#include <xfc/gtk/printpagesetup.hh>
#include <xfc/cairo/context.hh>
#include <xfc/pango/context.hh>
#include <xfc/pango/layout.hh>
#include <xfc/pango/fontmap.hh>

#include <gtk/gtkprintcontext.h>

namespace Xfc {
    namespace Gtk {
        /**
           A PrintContext encapsulates context information that 
           is required when drawing pages for printing, such as the 
           cairo context and important parameters like page size 
           and resolution. It also lets you easily create PangoLayout 
           and PangoContext objects that match the font metrics of the 
           cairo surface.

           PrintContext objects gets passed to the ::begin-print, 
           ::end-print, ::request-page-setup and ::draw-page signals 
           on the PrintOperation. 
         */
        class PrintContext : public G::Object {

        public:
            PrintContext( GtkPrintContext *ctx, bool owns_reference = true );
            
            GtkPrintContext *gtk_printcontext() const;

            operator GtkPrintContext* () const {return gtk_printcontext();}
            
            Cairo::Context get_cairo_context();
            void set_cairo_context( Cairo::Context cr, double dpi_x, double dpi_y );
            PageSetup *get_page_setup();
            double get_width();
            double get_height();
            double get_dpi_x();
            double get_dpi_y();
            Pango::FontMap* get_pango_fontmap();
            Pango::Context* create_pango_context();
            Pango::Layout* create_pango_layout();
        };
    }
}

#endif
