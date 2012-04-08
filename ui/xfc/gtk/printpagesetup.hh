#ifndef XFC_GTK_PAGE_SETUP_HH
#define XFC_GTK_PAGE_SETUP_HH 1

#include <xfc/config.h>

#ifdef XFC_CAIRO

#ifndef __GTK_PAGE_SETUP_H__
#include <gtk/gtkpagesetup.h>
#endif

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_OBJECT_HH
#include <xfc/gtk/object.hh>
#endif

// #ifndef XFC_GTK_PAPER_SIZE_HH
// #include <xfc/printpapersize.hh>
// #endif

namespace Xfc {
    namespace Gtk {
        
        class PaperSize;
        
        enum Unit {
            UNIT_PIXEL  = GTK_UNIT_PIXEL,
            UNIT_POINTS = GTK_UNIT_POINTS,
            UNIT_INCH   = GTK_UNIT_INCH,
            UNIT_MM     = GTK_UNIT_MM
        };

        enum PageOrientation {
            PAGE_ORIENTATION_PORTRAIT          = GTK_PAGE_ORIENTATION_PORTRAIT,
            PAGE_ORIENTATION_LANDSCAPE         = GTK_PAGE_ORIENTATION_LANDSCAPE,
            PAGE_ORIENTATION_REVERSE_PORTRAIT  = GTK_PAGE_ORIENTATION_REVERSE_PORTRAIT,
            PAGE_ORIENTATION_REVERSE_LANDSCAPE = GTK_PAGE_ORIENTATION_REVERSE_LANDSCAPE
        };

        /**
            A Gtk::PageSetup object stores the page size, orientation and
            margins. The idea is that you can get one of these from the
            page setup dialog and then pass it to the Gtk::PrintOperation
            when printing. The benefit of splitting this out of the Gtk::PrintSettings
            is that these affect the actual layout of the page, and thus
            need to be set long before user prints.

            The margins specified in this object are the "print margins",
            i.e. the parts of the page that the printer cannot print on.
            These are different from the layout margins that a word processor
            uses; they are typically used to determine the minimal size for
            the layout margins.

            use gtk_print_run_page_setup_dialog() to show the page setup
            dialog and receive the resulting page setup. 
        */
        class PageSetup : public G::Object {
        public:
            PageSetup();
            PageSetup( const PageSetup *pagesetup );
            PageSetup( GtkPageSetup *ctx, bool owns_reference = true );

            GtkPageSetup *gtk_page_setup() const;

            operator GtkPageSetup* () const;

            PageOrientation get_orientation();
            void set_orientation( PageOrientation orientation );
            PaperSize get_paper_size();
            void set_paper_size( const PaperSize &size);
            double get_top_margin( Unit unit);
            void set_top_margin( double margin, Unit unit);
            double get_bottom_margin( Unit unit);
            void set_bottom_margin( double margin, Unit unit );
            double get_left_margin( Unit unit );
            void set_left_margin( double margin, Unit unit );
            double get_right_margin( Unit unit );
            void set_right_margin( double margin, Unit unit );
            void set_paper_size_and_default_margins( PaperSize *size );
            double get_paper_width( Unit unit);
            double get_paper_height( Unit unit );
            double get_page_width( Unit unit);
            double get_page_height( Unit unit );
        };
    }
}

#include <xfc/gtk/inline/printpagesetup.inl>

#endif
#endif
