#include "printoperationpreviewsignals.hh"
#include "private/printoperationpreviewiface.hh"

using namespace Xfc;
using namespace Gtk;

// Make sure we only use this signal on the prober class
PrintOperationPreviewSignals::PrintOperationPreviewSignals(PrintOperationPreview *op) : G::ObjectSignals( op )
{
}

PrintOperationPreviewSignals::~PrintOperationPreviewSignals() {}

void PrintOperationPreviewSignals::on_ready(PrintContext &ctx)
{
    GtkPrintOperationPreviewIface *g_iface = PrintOperationPreviewIface::get_parent_iface(instance_);
    if (g_iface && g_iface->ready)
        g_iface->ready((GtkPrintOperationPreview*)instance_, (GtkPrintContext*)ctx);
}

void PrintOperationPreviewSignals::on_got_page_size(PrintContext &ctx, PageSetup &setup)
{
    GtkPrintOperationPreviewIface *g_iface = PrintOperationPreviewIface::get_parent_iface(instance_);
    if (g_iface && g_iface->got_page_size)
        g_iface->got_page_size((GtkPrintOperationPreview*)instance_, (GtkPrintContext*)ctx, (GtkPageSetup*)setup);
}
   
