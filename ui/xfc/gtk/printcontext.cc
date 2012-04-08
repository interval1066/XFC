#include <xfc/gtk/printcontext.hh>

using namespace Xfc;
using namespace Gtk;

PrintContext::PrintContext( GtkPrintContext *ctx, bool owns_reference ) :
    G::Object( (GObject*)ctx, owns_reference )
{
}

Cairo::Context PrintContext::get_cairo_context()
{
    Cairo::Context cr( gtk_print_context_get_cairo_context( gtk_printcontext() ));

    return cr;
}

GtkPrintContext * PrintContext::gtk_printcontext() const
{
    return reinterpret_cast<GtkPrintContext*>(instance_);
}

void PrintContext::set_cairo_context ( Cairo::Context ctx, double dpi_x, double dpi_y )
{
    gtk_print_context_set_cairo_context( gtk_printcontext(), ctx, dpi_x, dpi_y );
}

PageSetup *PrintContext::get_page_setup()
{
    return G::Object::wrap<PageSetup>( gtk_print_context_get_page_setup( gtk_printcontext()));
}

gdouble PrintContext::get_width()
{
    return gtk_print_context_get_width( gtk_printcontext());
}

gdouble PrintContext::get_height()
{
    return gtk_print_context_get_height( gtk_printcontext());
}

gdouble PrintContext::get_dpi_x()
{
    return gtk_print_context_get_dpi_x( gtk_printcontext());
}

gdouble PrintContext::get_dpi_y()
{
    return gtk_print_context_get_dpi_y( gtk_printcontext());
}

Pango::FontMap* PrintContext::get_pango_fontmap()
{
    return G::Object::wrap<Pango::FontMap>( gtk_print_context_get_pango_fontmap( gtk_printcontext()));
}

Pango::Context* PrintContext::create_pango_context()
{
    return G::Object::wrap_new<Pango::Context>(gtk_print_context_create_pango_context(gtk_printcontext()), true);
}

Pango::Layout* PrintContext::create_pango_layout() 
{
    return G::Object::wrap_new<Pango::Layout>(gtk_print_context_create_pango_layout(gtk_printcontext()), true);
}
