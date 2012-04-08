
#include "printoperationsignals.hh"
#include "private/printoperationclass.hh"

using namespace Xfc;

/*  Gtk::PrintOperationSignals
 */

Gtk::PrintOperationSignals::PrintOperationSignals(Gtk::PrintOperation *op) :
    Gtk::PrintOperationPreviewSignals(op)
{
}

Gtk::PrintOperationSignals::~PrintOperationSignals()
{
}

void Gtk::PrintOperationSignals::on_begin_print( Gtk::PrintContext &context )
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->begin_print)
        g_class->begin_print((GtkPrintOperation*)instance_, (GtkPrintContext*)context);
}

Gtk::Widget *Gtk::PrintOperationSignals::on_create_custom_widget()
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->create_custom_widget) {
        GtkWidget *wnd = g_class->create_custom_widget((GtkPrintOperation*)instance_);

        return G::Object::wrap_new<Gtk::Widget>(wnd);
    }

    return NULL;
}

void Gtk::PrintOperationSignals::on_custom_widget_apply(Gtk::Widget &widget)
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->custom_widget_apply)
        g_class->custom_widget_apply((GtkPrintOperation*)instance_, (GtkWidget*)widget);
}

void Gtk::PrintOperationSignals::on_done(Gtk::PrintOperationResult result)
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->done)
        g_class->done((GtkPrintOperation*)instance_, (GtkPrintOperationResult)result);
 }

void Gtk::PrintOperationSignals::on_draw_page(Gtk::PrintContext &context, int page_nr)
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->draw_page)
        g_class->draw_page((GtkPrintOperation*)instance_, (GtkPrintContext*)context, page_nr);
}

void Gtk::PrintOperationSignals::on_end_print(Gtk::PrintContext &context)
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->end_print)
        g_class->end_print((GtkPrintOperation*)instance_, (GtkPrintContext*)context);

}

bool Gtk::PrintOperationSignals::on_paginate(Gtk::PrintContext &context)
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->paginate)
        return g_class->paginate((GtkPrintOperation*)instance_, (GtkPrintContext*)context);

    return false;
}

bool Gtk::PrintOperationSignals::on_preview (Gtk::PrintOperationPreview &preview,
                                             Gtk::PrintContext &context, Gtk::Window &parent)
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->preview)
        return g_class->preview((GtkPrintOperation*)instance_, (GtkPrintOperationPreview*)preview,
                                (GtkPrintContext*)context, (GtkWindow*)parent);

    return false;
}

void Gtk::PrintOperationSignals::on_request_page_setup(Gtk::PrintContext &context,
                                                       int page_nr, Gtk::PageSetup &setup)
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->request_page_setup)
        g_class->request_page_setup((GtkPrintOperation*)instance_, (GtkPrintContext*)context,
                                    page_nr, (GtkPageSetup*)setup );
}

void Gtk::PrintOperationSignals::on_status_changed()
{
    GtkPrintOperationClass *g_class = PrintOperationClass::get_parent_class(instance_);
    if (g_class && g_class->status_changed)
        g_class->status_changed((GtkPrintOperation*)instance_);
}
