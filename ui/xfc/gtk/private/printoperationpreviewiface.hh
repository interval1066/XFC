#ifndef XFC_GTK_PRINT_OPERATION_PREVIEW_CLASS_HH
#define XFC_GTK_PRINT_OPERATION_PREVIEW_CLASS_HH

#ifndef __GTK_PRINT_OPERATION_PREVIEW_H__
#include "gtk/gtkprintoperationpreview.h"
#endif

namespace Xfc {
    
    namespace Gtk {
        
        class PrintOperationPreviewIface
        {
        public:
            static void init(GtkPrintOperationPreviewIface *g_iface);
            
            static GtkPrintOperationPreviewIface* get_parent_iface(void *instance);
            
            static void ready_proxy(GtkPrintOperationPreview *, GtkPrintContext *);
            
            static void got_page_size_proxy(GtkPrintOperationPreview *, 
                                            GtkPrintContext *,
                                            GtkPageSetup *);
        };
        
    }
}

#endif
