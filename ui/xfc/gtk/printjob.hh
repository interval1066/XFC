#ifndef XFC_GTK_PRINTJOB_HH 
#define XFC_GTK_PRINTJOB_HH 1

#include <gtk/gtkprintjob.h>

#include <xfc/glib/object.hh>

#include <xfc/gtk/printsetting.hh>

#include <xfc/gtk/printer.hh>

namespace Xfc {
    namespace Gtk {

        class PrintJobSignals {
        public:
            virtual void status_changed() = 0;
        };

        /**
           A PrintJob object represents a job that is sent to a 
           printer. You only need to deal directly with print jobs 
           if you use the non-portable PrintUnixDialog API.

           Use get_surface() to obtain the cairo surface onto which 
           the pages must be drawn. Use job_send() 
           to send the finished job to the printer. If you don't use 
           cairo PrintJob also supports printing of manually generated 
           postscript, via set_source_file().
         */
        class PrintJob : public G::Object {
        public:
            PrintJob( GtkPrintJob *p, bool owned_reference = true );

            PrintSettings* get_settings();
            Printer* get_printer();
            String get_title();
            PrintStatus get_status();
            bool set_source_file( const string &filename, GError **error );
            cairo_surface_t* get_surface( GError **error );
            void set_track_print_status( bool track_status);
            bool get_track_print_status();

            // Signals
            
        };
    }
}

#endif
