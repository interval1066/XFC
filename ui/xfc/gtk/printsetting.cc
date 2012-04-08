#include <xfc/gtk/printsetting.hh>
#include <stdexcept>
#include <cstring>

using namespace Xfc;

///////////////////
// PageRanges

Gtk::PageRanges::PageRanges( GtkPageRange *pr, int cnt, bool no_free )
{
    _no_free = no_free;
    _cnt = cnt;
    _pr = pr;
}

Gtk::PageRanges::PageRanges( const PageRanges &pr )
{
    if( pr._no_free ) {
        _no_free = false;
        _cnt = pr._cnt;
        _pr = pr._pr;
    } else {
        _cnt = pr._cnt;
        _pr = (GtkPageRange*)g_malloc( sizeof( GtkPageRange ) * _cnt );
        memcpy(_pr, pr, sizeof( GtkPageRange ) * _cnt );
        _no_free = false;
    }
}

Gtk::PageRanges::~PageRanges()
{
    if( !_no_free && _pr )
        g_free( _pr );
}

GtkPageRange& Gtk::PageRanges::operator[] (int n)
{
    if( n > _cnt )
        throw std::invalid_argument( "index of PageRanges out of range" );
        
    return _pr[ n ];
}
///////////////////////
// PaperSize


Gtk::PaperSize::PaperSize( const String &name )
{
    _papersize = gtk_paper_size_new( name.c_str());
}

Gtk::PaperSize::PaperSize( GtkPaperSize *papersize )
{
    _papersize = papersize;
}

Gtk::PaperSize::PaperSize( const String &name, const String &display_name, double width, double height, Unit unit )
{
    _papersize = gtk_paper_size_new_custom(name.c_str(), display_name.c_str(), width, height, (GtkUnit)unit);
}

Gtk::PaperSize::PaperSize( const Gtk::PaperSize &ps )
{
    _papersize = gtk_paper_size_copy( ps._papersize );
}

Gtk::PaperSize::~PaperSize()
{
    if( _papersize )
        gtk_paper_size_free( _papersize );
}
    
bool Gtk::PaperSize::is_equal( const Gtk::PaperSize &size2) const 
{
    return gtk_paper_size_is_equal( _papersize, size2 );
}

const String Gtk::PaperSize::get_name() const
{
    return gtk_paper_size_get_name( _papersize );
}

const String Gtk::PaperSize::get_display_name() const
{
    return gtk_paper_size_get_display_name( _papersize );
}

const String Gtk::PaperSize::get_ppd_name() const 
{
    return gtk_paper_size_get_ppd_name( _papersize );
}

double Gtk::PaperSize::get_width(Unit unit) const 
{
    return gtk_paper_size_get_width( _papersize, (GtkUnit)unit );
}

double Gtk::PaperSize::get_height(Unit unit) const 
{
    return gtk_paper_size_get_height( _papersize, (GtkUnit)unit );
}

bool Gtk::PaperSize::is_custom() const
{
    return gtk_paper_size_is_custom( _papersize );
}

void Gtk::PaperSize::set_size( double width, double height, Unit unit)
{
    gtk_paper_size_set_size( _papersize, width, height, (GtkUnit)unit );
}

double Gtk::PaperSize::get_default_top_margin(Unit unit) const
{
    return gtk_paper_size_get_default_top_margin( _papersize, (GtkUnit)unit );
}

double Gtk::PaperSize::get_default_bottom_margin(Unit unit) const
{
    return gtk_paper_size_get_default_bottom_margin( _papersize, (GtkUnit)unit );
}

double Gtk::PaperSize::get_default_left_margin(Unit unit) const
{
    return gtk_paper_size_get_default_left_margin( _papersize, (GtkUnit)unit );
}

double Gtk::PaperSize::get_default_right_margin(Unit unit) const
{
    return gtk_paper_size_get_default_right_margin( _papersize, (GtkUnit)unit );
}

const String Gtk::PaperSize::get_default(void)
{
    return gtk_paper_size_get_default();
}

///////////////////////
// PrintSettings

// We need no private class when no signals are emitted
Gtk::PrintSettings::PrintSettings() : G::Object((GObject*)gtk_print_settings_new() ) {}

Gtk::PrintSettings::PrintSettings(GtkPrintSettings *op, bool owns_reference)
    : G::Object( (GObject*)op, owns_reference ) {}

Gtk::PrintSettings::~PrintSettings() {}

bool Gtk::PrintSettings::has_key( const String &key )
{
    return gtk_print_settings_has_key( gtk_print_settings(), key.c_str());
}

String Gtk::PrintSettings::get( const String &key )
{
    return gtk_print_settings_get( gtk_print_settings(), key.c_str());
}

void Gtk::PrintSettings::set( const String &key, const String &value )
{
    gtk_print_settings_set( gtk_print_settings(), key.c_str(), value.c_str());
}

void Gtk::PrintSettings::unset( const String &key )
{
    gtk_print_settings_unset( gtk_print_settings(), key.c_str());
}

bool Gtk::PrintSettings::get_bool( const String &key )
{
    return gtk_print_settings_get_bool( gtk_print_settings(), key.c_str());
}

void Gtk::PrintSettings::set_bool( const String &key, bool value)
{
    gtk_print_settings_set_bool( gtk_print_settings(), key.c_str(), value );
}

double Gtk::PrintSettings::get_double( const String &key )
{
    return gtk_print_settings_get_double( gtk_print_settings(), key.c_str());
}

double Gtk::PrintSettings::get_double( const String &key, double def )
{
    return gtk_print_settings_get_double_with_default( gtk_print_settings(), key.c_str(), def );
}

void Gtk::PrintSettings::set_double( const String &key, double value)
{
    gtk_print_settings_set_double( gtk_print_settings(), key.c_str(), value );
}

double Gtk::PrintSettings::get_length( const String &key, Unit unit)
{
    return gtk_print_settings_get_length( gtk_print_settings(), key.c_str(), (GtkUnit)unit );
}

void Gtk::PrintSettings::set_length( const String &key, double value, Unit unit)
{
    gtk_print_settings_set_length( gtk_print_settings(), key.c_str(), value, (GtkUnit)unit );
}

int Gtk::PrintSettings::get_int( const String &key)
{
    return gtk_print_settings_get_int( gtk_print_settings(), key.c_str());
}

int Gtk::PrintSettings::get_int( const String &key, int def)
{
    return gtk_print_settings_get_int_with_default( gtk_print_settings(), key.c_str(), def );
}

void Gtk::PrintSettings::set_int( const String &key, int value)
{
    gtk_print_settings_set_int( gtk_print_settings(), key.c_str(), value );
}

String Gtk::PrintSettings::get_printer()
{
    return gtk_print_settings_get_printer( gtk_print_settings() );
}

void Gtk::PrintSettings::set_printer( const String &printer )
{
    gtk_print_settings_set_printer( gtk_print_settings(), printer.c_str());
}

Gtk::PageOrientation Gtk::PrintSettings::get_orientation()
{
    return (PageOrientation)gtk_print_settings_get_orientation( gtk_print_settings());
}

void Gtk::PrintSettings::set_orientation( PageOrientation orientation)
{
    gtk_print_settings_set_orientation( gtk_print_settings(), (GtkPageOrientation)orientation );
}

Gtk::PaperSize Gtk::PrintSettings::get_paper_size()
{
    return (Gtk::PaperSize)gtk_print_settings_get_paper_size( gtk_print_settings());
}

void Gtk::PrintSettings::set_paper_size( Gtk::PaperSize *paper_size )
{
    GtkPaperSize *ps = *paper_size;

    gtk_print_settings_set_paper_size( gtk_print_settings(), ps );
}

double Gtk::PrintSettings::get_paper_width( Unit unit )
{
    return gtk_print_settings_get_paper_width( gtk_print_settings(), (GtkUnit)unit );
}

void Gtk::PrintSettings::set_paper_width( double width, Unit unit )
{
    gtk_print_settings_set_paper_width( gtk_print_settings(), width, (GtkUnit)unit );
}

double Gtk::PrintSettings::get_paper_height( Unit unit )
{
    return gtk_print_settings_get_paper_height( gtk_print_settings(), (GtkUnit)unit );
}

void Gtk::PrintSettings::set_paper_height( double height, Unit unit )
{
    gtk_print_settings_set_paper_height( gtk_print_settings(), height, (GtkUnit)unit );
}

bool Gtk::PrintSettings::get_use_color()
{
    return gtk_print_settings_get_use_color( gtk_print_settings());
}

void Gtk::PrintSettings::set_use_color( bool use_color )
{
    gtk_print_settings_set_use_color( gtk_print_settings(), use_color );
}

bool Gtk::PrintSettings::get_collate()
{
    return gtk_print_settings_get_collate( gtk_print_settings());
}

void Gtk::PrintSettings::set_collate( bool collate )
{
    gtk_print_settings_set_collate( gtk_print_settings(), collate );
}

bool Gtk::PrintSettings::get_reverse()
{
    return gtk_print_settings_get_reverse( gtk_print_settings());
}

void Gtk::PrintSettings::set_reverse( bool reverse)
{
    gtk_print_settings_set_reverse( gtk_print_settings(), reverse );
}

Gtk::PrintDuplex Gtk::PrintSettings::get_duplex()
{
    return (Gtk::PrintDuplex)gtk_print_settings_get_duplex( gtk_print_settings());
}

void Gtk::PrintSettings::set_duplex( Gtk::PrintDuplex duplex)
{
    gtk_print_settings_set_duplex( gtk_print_settings(), (GtkPrintDuplex)duplex );
}

Gtk::PrintQuality Gtk::PrintSettings::get_quality()
{
    return (Gtk::PrintQuality)gtk_print_settings_get_quality( gtk_print_settings());
}

void Gtk::PrintSettings::set_quality( Gtk::PrintQuality quality )
{
    gtk_print_settings_set_quality( gtk_print_settings(), (GtkPrintQuality)quality );
}

int Gtk::PrintSettings::get_n_copies()
{
    return gtk_print_settings_get_n_copies( gtk_print_settings() );
}
    
void Gtk::PrintSettings::set_n_copies( int num_copies )
{
    gtk_print_settings_set_n_copies( gtk_print_settings(), num_copies );
}

int Gtk::PrintSettings::get_number_up()
{
    return gtk_print_settings_get_number_up(gtk_print_settings());
}

void Gtk::PrintSettings::set_number_up( int number_up)
{
    gtk_print_settings_set_number_up( gtk_print_settings(), number_up );
}

int Gtk::PrintSettings::get_resolution()
{
    return gtk_print_settings_get_resolution( gtk_print_settings() );
}

void Gtk::PrintSettings::set_resolution( int resolution )
{
    gtk_print_settings_set_resolution( gtk_print_settings(), resolution );
}

double Gtk::PrintSettings::get_scale()
{
    return gtk_print_settings_get_scale( gtk_print_settings());
}

void Gtk::PrintSettings::set_scale( double scale)
{
    gtk_print_settings_set_scale( gtk_print_settings(), scale );
}

Gtk::PrintPages Gtk::PrintSettings::get_print_pages()
{
    return (Gtk::PrintPages)gtk_print_settings_get_print_pages( gtk_print_settings());
}

void Gtk::PrintSettings::set_print_pages( Gtk::PrintPages pages)
{
    gtk_print_settings_set_print_pages( gtk_print_settings(), (GtkPrintPages)pages );
}

Gtk::PageRanges Gtk::PrintSettings::get_page_ranges()
{
    int num;
    
    GtkPageRange *ranges = gtk_print_settings_get_page_ranges( gtk_print_settings(), &num );

    if( ranges )
        return Gtk::PageRanges( ranges, num );
    else
        throw std::out_of_range( "No page ranges found" );
}

void Gtk::PrintSettings::set_page_ranges( Gtk::PageRanges &ranges )
{
    gtk_print_settings_set_page_ranges( gtk_print_settings(), ranges, ranges.size() );
}

Gtk::PageSet Gtk::PrintSettings::get_page_set()
{
    return (Gtk::PageSet)gtk_print_settings_get_page_set( gtk_print_settings());
}

void Gtk::PrintSettings::set_page_set( Gtk::PageSet page_set )
{
    gtk_print_settings_set_page_set( gtk_print_settings(), (GtkPageSet)page_set );
}

String Gtk::PrintSettings::get_default_source()
{
    return gtk_print_settings_get_default_source( gtk_print_settings());
}

void Gtk::PrintSettings::set_default_source( const String &default_source )
{
    gtk_print_settings_set_default_source( gtk_print_settings(), default_source.c_str());
}

String Gtk::PrintSettings::get_media_type()
{
    return gtk_print_settings_get_media_type( gtk_print_settings());
}

void Gtk::PrintSettings::set_media_type( const String &media_type)
{
    gtk_print_settings_set_media_type( gtk_print_settings(), media_type.c_str() );
}

String Gtk::PrintSettings::get_dither()
{
    return gtk_print_settings_get_dither( gtk_print_settings());
}

void Gtk::PrintSettings::set_dither( const String &dither)
{
    gtk_print_settings_set_dither( gtk_print_settings(), dither.c_str());
}

String Gtk::PrintSettings::get_finishings()
{
    return gtk_print_settings_get_finishings( gtk_print_settings());
}

void Gtk::PrintSettings::set_finishings( const String &finishings )
{
    gtk_print_settings_set_finishings( gtk_print_settings(), finishings.c_str());
}

String Gtk::PrintSettings::get_output_bin()
{
    return gtk_print_settings_get_output_bin( gtk_print_settings());
}

void Gtk::PrintSettings::set_output_bin( const String &output_bin)
{
    gtk_print_settings_set_output_bin( gtk_print_settings(), output_bin.c_str());
}
