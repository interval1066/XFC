// Simple test application that opens a test print page in preview mode
// To demo the usage of printing in XFC
#include "printing.hh"

#include <xfc/main.hh>
#include <xfc/gtk/printoperation.hh>
#include <xfc/gtk/printoperationsignals.hh>
#include <xfc/gtk/window.hh>
#include <iostream>

using namespace Xfc;
using namespace std;

class PagePrinting : public Gtk::PrintOperation, public Gtk::PrintOperationSignals
{
public:    
    PagePrinting();

    void on_begin_print(Gtk::PrintContext &ctx);
    bool on_paginate(Gtk::PrintContext &ctx);
    void on_draw_page(Gtk::PrintContext &ctx, int page_nr);
    void on_done(Gtk::PrintOperationResult result);
    bool on_preview (Gtk::PrintOperationPreview &preview, Gtk::PrintContext &context, Gtk::Window &parent);
    
    // From the preview class
    void on_ready( Gtk::PrintContext &ctx );
    void on_got_page_size( Gtk::PrintContext &ctx, Gtk::PageSetup &setup );
};

PagePrinting::PagePrinting() : Gtk::PrintOperationSignals( this )
{
}

void PagePrinting::on_begin_print(Gtk::PrintContext &ctx)
{
    clog << "begin print" << endl;
    
    set_unit( Gtk::UNIT_MM );
    set_n_pages( 1 );  // only one page to print
    set_job_name( "XFC test print" );
}

bool PagePrinting::on_paginate(Gtk::PrintContext &ctx)
{
    clog << "paginate" << endl;
    return true;
}

// Messure the page and paint a cross in the middle of the page
void PagePrinting::on_draw_page(Gtk::PrintContext &context, int page_nr )
{
    clog << "draw page " << page_nr << endl;
    
    Cairo::Context ctx = context.get_cairo_context();

    int width = context.get_width(); // see "set_unit"
    int height = context.get_height();

    clog << "page size is " << width << " x " << height << " mm" << endl;

    ctx.set_source_rgb(0, 0, 0);
    ctx.set_line_width(0.5);

    ctx.move_to((width / 2) - 20, height / 2);
    ctx.line_to((width / 2) + 20, height / 2);

    ctx.move_to(width / 2, (height / 2) - 20);
    ctx.line_to(width / 2, (height / 2) + 20);

    ctx.stroke();

    clog << "drawn the page" << endl;
}

void PagePrinting::on_done(Gtk::PrintOperationResult result)
{
    clog << "done (" << result << ")" << endl;
}

void PagePrinting::on_ready( Gtk::PrintContext &context )
{
    clog << "ready" << endl;
}

void PagePrinting::on_got_page_size( Gtk::PrintContext &ctx, Gtk::PageSetup &setup )
{
    clog << "got_page_size" << endl;
}

bool PagePrinting::on_preview (Gtk::PrintOperationPreview &preview, Gtk::PrintContext &context, Gtk::Window &parent)
{
    clog << "on_preview" << endl;

    return Gtk::PrintOperationSignals::on_preview(preview, context, parent );
} 

int main( int argc, char *argv[] )
{
    using namespace Main;

    init(&argc, &argv);
    
    // We just pop up an preview window
    PagePrinting prn;

    clog << "Make test page ..." << endl;

    Gtk::PrintOperationResult res = prn.run( Gtk::ACTION_PRINT_DIALOG );

    if( res == Gtk::ERROR )
        cerr << "Error while printing" << endl;
}
