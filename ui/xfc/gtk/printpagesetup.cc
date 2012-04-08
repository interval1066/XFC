#include "printpagesetup.hh"
//#include "private/printpagesetupclass.hh"
#include "xfc/atk/object.hh"

#include <xfc/gtk/printsetting.hh>

namespace Xfc {

namespace Gtk {
    
//PageSetup::PageSetup( const PageSetup *pagesetup ) : Object( PageSetupClass::create())
//{
//}

PageSetup::PageSetup( GtkPageSetup *ctx, bool owns_reference ) : G::Object((GObject *)ctx, owns_reference ) 
{
}

PageOrientation PageSetup::get_orientation()
{
    return (PageOrientation)gtk_page_setup_get_orientation( gtk_page_setup());
}

void PageSetup::set_orientation( PageOrientation orientation )
{
    gtk_page_setup_set_orientation( gtk_page_setup(), (GtkPageOrientation)orientation );
}

PaperSize PageSetup::get_paper_size()
{
    return PaperSize( gtk_page_setup_get_paper_size( gtk_page_setup()));
}

void PageSetup::set_paper_size( const PaperSize &size )
{
    gtk_page_setup_set_paper_size( gtk_page_setup(), (GtkPaperSize*)size );
}

double PageSetup::get_top_margin( Unit unit )
{
    return gtk_page_setup_get_top_margin( gtk_page_setup(), (GtkUnit)unit );
}

void PageSetup::set_top_margin( double margin, Unit unit)
{
    gtk_page_setup_set_top_margin( gtk_page_setup(), margin, (GtkUnit)unit );
}

double PageSetup::get_bottom_margin( Unit unit)
{
    return gtk_page_setup_get_bottom_margin( gtk_page_setup(), (GtkUnit)unit );
}

void PageSetup::set_bottom_margin( double margin, Unit unit )
{
    gtk_page_setup_set_bottom_margin( gtk_page_setup(), margin, (GtkUnit)unit );
}

double PageSetup::get_left_margin( Unit unit )
{
    return gtk_page_setup_get_left_margin( gtk_page_setup(), (GtkUnit)unit );
}

void PageSetup::set_left_margin( double margin, Unit unit )
{
    gtk_page_setup_set_left_margin( gtk_page_setup(), margin, (GtkUnit)unit );
}

double PageSetup::get_right_margin( Unit unit )
{
    return gtk_page_setup_get_right_margin( gtk_page_setup(), (GtkUnit)unit );
}

void PageSetup::set_right_margin( double margin, Unit unit )
{
    gtk_page_setup_set_right_margin( gtk_page_setup(), margin, (GtkUnit)unit );
}

#if 0
void PageSetup::set_paper_size_and_default_margins( PaperSize *size )
{
    
}
#endif

double PageSetup::get_paper_width( Unit unit)
{
    return gtk_page_setup_get_paper_width( gtk_page_setup(), (GtkUnit)unit );
}

double PageSetup::get_paper_height( Unit unit )
{
    return gtk_page_setup_get_paper_height( gtk_page_setup(), (GtkUnit)unit );
}

double PageSetup::get_page_width( Unit unit)
{
    return gtk_page_setup_get_page_width( gtk_page_setup(), (GtkUnit)unit );
}

double PageSetup::get_page_height( Unit unit )
{
    return gtk_page_setup_get_page_height( gtk_page_setup(), (GtkUnit)unit );
}

}

}
