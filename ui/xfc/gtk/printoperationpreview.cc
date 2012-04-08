#include "printoperationpreview.hh"
#include "printoperationpreviewsignals.hh"	
#include "private/printoperationpreviewiface.hh"

#include "xfc/glib/object.hh"
#include "xfc/glib/objectsignals.hh"

namespace Xfc {
    
    namespace Gtk {

        // PrintOperationPreview

        PrintOperationPreview::PrintOperationPreview( GObject *inst, bool has_reference ) : G::Object( inst, has_reference ) {}

        PrintOperationPreview::~PrintOperationPreview() {}
    
        void PrintOperationPreview::end_preview()
        {
            gtk_print_operation_preview_end_preview( gtk_printoperationpreview() );
        }

        bool PrintOperationPreview::is_selected( int page_nr )
        {
            return gtk_print_operation_preview_is_selected( gtk_printoperationpreview(), page_nr );
        }

        void PrintOperationPreview::render_page( int page_nr )
        {
            gtk_print_operation_preview_render_page( gtk_printoperationpreview(), page_nr );
        }
        
        // PrintOperationPreviewIface

        void PrintOperationPreviewIface::init(GtkPrintOperationPreviewIface *g_iface)
        {
            g_iface->ready = &PrintOperationPreviewIface::ready_proxy;
            g_iface->got_page_size = &PrintOperationPreviewIface::got_page_size_proxy;
        }

        GtkPrintOperationPreviewIface *PrintOperationPreviewIface::get_parent_iface(void *instance)
        {
            return static_cast<GtkPrintOperationPreviewIface*>(g_type_interface_peek_parent(GTK_PRINT_OPERATION_PREVIEW_GET_IFACE(instance)));
        }

        void PrintOperationPreviewIface::ready_proxy(GtkPrintOperationPreview *preview, GtkPrintContext *ctx)
        {
            PrintOperationPreviewSignals *signals = dynamic_cast<PrintOperationPreviewSignals*>
                (G::ObjectSignals::pointer((GObject*)preview));
            
            if (signals) {
                signals->on_ready(*G::Object::wrap<PrintContext>(ctx));
            } else {
                GtkPrintOperationPreviewIface *g_iface = get_parent_iface(preview);
                if (g_iface && g_iface->ready)
                    g_iface->ready(preview, ctx);
            }
        }
        
        void PrintOperationPreviewIface::got_page_size_proxy( GtkPrintOperationPreview *preview, 
                                                              GtkPrintContext *ctx, GtkPageSetup *setup )
        {
            PrintOperationPreviewSignals *signals = dynamic_cast<PrintOperationPreviewSignals*>
                (G::ObjectSignals::pointer((GObject*)preview));
            
            if(signals) {
                signals->on_got_page_size( *G::Object::wrap<PrintContext>(ctx), 
                                        *G::Object::wrap<PageSetup>(setup) );
            } else {
                GtkPrintOperationPreviewIface *g_iface = get_parent_iface(preview);
                if (g_iface && g_iface->got_page_size)
                    g_iface->got_page_size(preview, ctx, setup);
            }
        }
        
    } // namespace Gtk
} // namespace Xfc
