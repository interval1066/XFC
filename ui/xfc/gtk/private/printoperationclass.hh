#ifndef XFC_GTK_PRINT_OPERATION_CLASS_HH
#define XFC_GTK_PRINT_OPERATION_CLASS_HH

#include <xfc/gtk/private/objectclass.hh>

namespace Xfc {
namespace Gtk {
    
class PrintOperationClass {
public:
    static void init(GtkPrintOperationClass *g_class);

    static GtkPrintOperationClass* get_parent_class(void *instance);

    static GType get_type();

    static void* create();

    static void begin_print_proxy( GtkPrintOperation *operation, GtkPrintContext *context );
    
    static GtkWidget* create_custom_widget_proxy(GtkPrintOperation *operation);
    
    static void custom_widget_apply_proxy(GtkPrintOperation *operation, GtkWidget *widget );
    
    static void done_proxy(GtkPrintOperation *operation, GtkPrintOperationResult result );
    
    static void draw_page_proxy(GtkPrintOperation *operation, GtkPrintContext *context, gint page_nr );
    
    static void end_print_proxy(GtkPrintOperation *operation, GtkPrintContext *context );
    
    static gboolean paginate_proxy(GtkPrintOperation *operation, GtkPrintContext *context );
    
    static gboolean preview_proxy(GtkPrintOperation *operation, GtkPrintOperationPreview *preview,
        GtkPrintContext *context, GtkWindow *parent );
        
    static void request_page_setup_proxy(GtkPrintOperation *operation, GtkPrintContext *context,
        gint page_nr, GtkPageSetup *setup );
        
    static void status_changed_proxy(GtkPrintOperation *operation );
};

} // namespace Gtk
} // namespace Xfc

#endif
