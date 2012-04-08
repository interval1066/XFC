#ifndef XFC_GTK_PRINT_DIALOGS_HH 
#define XFC_GTK_PRINT_DIALOGS_HH 1

#include <gtk/gtkprintunixdialog.h>

#include <xfc/gtk/dialog.hh>

#include <xfc/gtk/printpagesetup.hh>

#include <xfc/gtk/printsetting.hh>

#include <xfc/gtk/printer.hh>

namespace Xfc {
    namespace Gtk {
   
        enum PrintCapabilities {
            PAGE_SET     = GTK_PRINT_CAPABILITY_PAGE_SET,
            COPIES       = GTK_PRINT_CAPABILITY_COPIES,
            COLLATE      = GTK_PRINT_CAPABILITY_COLLATE,
            REVERSE      = GTK_PRINT_CAPABILITY_REVERSE,
            SCALE        = GTK_PRINT_CAPABILITY_SCALE,
            GENERATE_PDF = GTK_PRINT_CAPABILITY_GENERATE_PDF,
            GENERATE_PS  = GTK_PRINT_CAPABILITY_GENERATE_PS,
            PREVIEW      = GTK_PRINT_CAPABILITY_PREVIEW
        };

        /**
           PrintUnixDialog implements a print dialog for platforms which 
           don't provide a native print dialog, like Unix. It can be 
           used very much like any other GTK+ dialog, at the cost of 
           the portability offered by the high-level printing API

           In order to print something with PrintUnixDialog, you need 
           to use unix_dialog_get_selected_printer() to obtain a GtkPrinter 
           object and use it to construct a PrintJob using job_new().

           GtkPrintUnixDialog uses the following response values:

           GTK_RESPONSE_OK 	    for the "Print" button
           GTK_RESPONSE_APPLY 	for the "Preview" button
           GTK_RESPONSE_CANCEL 	for the "Cancel" button
         */
        class PrintUnixDialog : public Dialog {
        public:
            void set_page_setup( GtkPageSetup *page_setup );
            PageSetup* get_page_setup();
            void set_current_page( gint current_page );
            gint get_current_page();
            void set_settings( PrintSettings *settings);
            PrintSettings* get_settings();
            Printer* get_selected_printer();
            void add_custom_tab( Widget *child, Widget *tab_label);
            void set_manual_capabilities( PrintCapabilities capabilities);
        };

        /**
           PageSetupUnixDialog implements a page setup dialog for platforms 
           which don't provide a native page setup dialog, like Unix. It can 
           be used very much like any other GTK+ dialog, at the cost of the 
           portability offered by the high-level printing API
         */
        class PrintPageSetupUnixDialog : public Dialog {
        public:
            void set_page_setup( PageSetup *page_setup );
            PageSetup* get_page_setup();
            void set_print_settings( PrintSettings *print_settings);
            PrintSettings* get_print_settings();
        };
    }
}

#endif
