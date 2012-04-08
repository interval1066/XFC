#ifndef XFC_GTK_PRINTER_HH 
#define XFC_GTK_PRINTER_HH 1

#include <gtk/gtkprinter.h>

#include <xfc/glib/object.hh>

#include <string>

namespace Xfc {
    namespace Gtk {
        using namespace std;

        class Printer : public G::Object {
        public:
            Printer( const string &name, GtkPrintBackend *backend,  bool virtual_);

            GtkPrintBackend* get_backend();
            string get_name();
            string get_state_message();
            string get_description();
            string get_location();
            string get_icon_name();
            gint get_job_count();
            bool is_active();
            bool is_virtual();
            bool is_default();
            bool accepts_ps();
            bool accepts_pdf();
            gint compare( Printer &a, Printer &b );
            typedef gboolean  (*GtkPrinterFunc) (GtkPrinter *printer, gpointer data);
            void printers(GtkPrinterFunc func, gpointer data, 
                          GDestroyNotify destroy, gboolean wait);
        };
    }
}

#endif
