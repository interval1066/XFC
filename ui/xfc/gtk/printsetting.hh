/**
   GtkPrintSetting - Stores print settings
*/
#ifndef XFC_GTK_PRINT_SETTING_HH
#define XFC_GTK_PRINT_SETTING_HH 1

#include <gtk/gtkprintoperation.h>

#include <xfc/gtk/printoperation.hh>

namespace Xfc {
    namespace Gtk { 

        // Holder class for page ranges array, in XFC
        class PageRanges { 
            GtkPageRange *_pr;
            int _cnt;
            bool _no_free;
        public:
            // Take over the pointer an free it on destruction (no refcnt)
            PageRanges( GtkPageRange *pr, int num, bool no_free = false );
            PageRanges( const PageRanges &pr );
            ~PageRanges();

            operator GtkPageRange *() const { return _pr; }
            
            GtkPageRange& operator[] (int n);
            int size() const {return _cnt;}
        };

        enum PageSet {
            ALL  = GTK_PAGE_SET_ALL,
            EVEN = GTK_PAGE_SET_EVEN,
            ODD  = GTK_PAGE_SET_ODD
        };

        enum PrintDuplex {
            SIMPLEX    = GTK_PRINT_DUPLEX_SIMPLEX,
            HORIZONTAL = GTK_PRINT_DUPLEX_HORIZONTAL,
            VERTICA    = GTK_PRINT_DUPLEX_VERTICAL
        };

        enum PrintQuality {
            LOW    = GTK_PRINT_QUALITY_LOW,
            NORMAL = GTK_PRINT_QUALITY_NORMAL,
            HIGH   = GTK_PRINT_QUALITY_HIGH,
            DRAFT  = GTK_PRINT_QUALITY_DRAFT
        };

        enum PrintPages {
            PAGES_ALL     = GTK_PRINT_PAGES_ALL,
            PAGES_CURRENT = GTK_PRINT_PAGES_CURRENT,
            PAGES_RANGES  = GTK_PRINT_PAGES_RANGES
        };
        
        /**
           A PageSetup object stores the page size, orientation and margins. 
           The idea is that you can get one of these from the page setup 
           dialog and then pass it to the PrintOperation when printing. 
           The benefit of splitting this out of the PrintSettings is that 
           these affect the actual layout of the page, and thus need to 
           be set long before user prints.

           The margins specified in this object are the "print margins", 
           i.e. the parts of the page that the printer cannot print on. 
           These are different from the layout margins that a word processor 
           uses; they are typically used to determine the minimal size 
           for the layout margins.

           To obtain a PageSetup use gtk_page_setup_new() to get the defaults, 
           or use run_page_setup_dialog() to show the page setup 
           dialog and receive the resulting page setup. 
        */
        class PaperSize {
            GtkPaperSize *_papersize;
        public:
            PaperSize( const String &name );
            PaperSize( const String &name, const String &display_name, double width, double height, Unit unit );
            
            /// The pointer will be freed when this class are destroyed !
            PaperSize( GtkPaperSize * );
            PaperSize( const PaperSize & );
            
            ~PaperSize();

            operator GtkPaperSize *() const {return _papersize;}

            bool is_equal( const PaperSize &size2) const;
            const String get_name() const;
            const String get_display_name() const;
            const String get_ppd_name() const;
            double get_width(Unit unit) const;
            double get_height(Unit unit) const;
            bool is_custom() const;
            double get_default_top_margin(Unit unit) const;
            double get_default_bottom_margin(Unit unit) const;
            double get_default_left_margin(Unit unit) const;
            double get_default_right_margin(Unit unit) const;

            void set_size( double width, double height, Unit unit);

            static const String get_default(void);
        };

        /**
           A GtkPrintSettings object represents the settings of a print dialog 
           in a system-independent way. The main use for this object is that once 
           you've printed you can get a settings object that represents the 
           settings the user chose, and the next time you print you can pass 
           that object in so that the user doesn't have to re-set all his settings.

           Its also possible to enumerate the settings so that you can easily 
           save the settings for the next time your app runs, or even store 
           them in a document. The predefined keys try to use shared values 
           as much as possible so that moving such a document between systems still works. 
         */
        class PrintSettings : public G::Object {
        public:
            PrintSettings();

            explicit PrintSettings(GtkPrintSettings *op, bool owns_reference = false);
            
            virtual ~PrintSettings();

            GtkPrintSettings *gtk_print_settings() const;

            operator GtkPrintSettings *() const;

            bool has_key( const String &key );
            String get( const String &key);
            void set( const String &key, const String &value );
            void unset( const String &key);
            // void foreach( PrintSettingsFunc func, gpointer user_data);
            bool get_bool( const String &key);
            void set_bool( const String &key, bool value);
            double get_double( const String &key);
            double get_double( const String &key, double def);
            void set_double( const String &key, double value);
            double get_length( const String &key, Unit unit);
            void set_length( const String &key, double value, Unit unit);
            int get_int( const String &key);
            int get_int( const String &key, int def);
            void set_int( const String &key, int value);
            String get_printer();
            void set_printer( const String &printer);
            PageOrientation get_orientation();
            void set_orientation( PageOrientation orientation);

            PaperSize get_paper_size();
            void set_paper_size( PaperSize *paper_size );
            double get_paper_width( Unit unit );
            void set_paper_width( double width, Unit unit );
            double get_paper_height( Unit unit );
            void set_paper_height( double height, Unit unit );
            bool get_use_color();
            void set_use_color( bool use_color );
            bool get_collate();
            void set_collate( bool collate );
            bool get_reverse();
            void set_reverse( bool reverse);
            PrintDuplex get_duplex();
            void set_duplex( PrintDuplex duplex);
            PrintQuality get_quality();
            void set_quality( PrintQuality quality );
            int get_n_copies();
            void set_n_copies( int num_copies);
            int get_number_up();
            void set_number_up( int number_up);
            int get_resolution();
            void set_resolution( int resolution );
            double get_scale();
            void set_scale( double scale);
            PrintPages get_print_pages();
            void set_print_pages( PrintPages pages);
            PageRanges get_page_ranges();
            void set_page_ranges( PageRanges &ranges );
            PageSet get_page_set();
            void set_page_set( PageSet page_set);
            String get_default_source();
            void set_default_source( const String &default_source );
            String get_media_type();
            void set_media_type( const String &media_type);
            String get_dither();
            void set_dither( const String &dither);
            String get_finishings();
            void set_finishings( const String &finishings );
            String get_output_bin();
            void set_output_bin( const String &output_bin);
        };

        inline GtkPrintSettings* PrintSettings::gtk_print_settings() const
        {
            return reinterpret_cast<GtkPrintSettings*>(instance_);
        }

        inline PrintSettings::operator GtkPrintSettings* () const
        {
            return this ? gtk_print_settings() : NULL;
        }

    }
}

#endif
