#ifndef XFC_PRINT_OPERATION_PREVIEW_SIGNALS_HH
#define XFC_PRINT_OPERATION_PREVIEW_SIGNALS_HH 1

// printoperationpreviewsignals

#ifndef XFC_PRINT_CONTEXT_HH
#include <xfc/gtk/printcontext.hh>
#endif

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

#ifndef XFC_GTK_PRINT_OPERATION_PREVIEW_HH
#include <xfc/gtk/printoperationpreview.hh>
#endif
 
namespace Xfc {
    
    namespace Gtk {
    
        class PrintOperationPreviewSignals : public G::ObjectSignals
        {
        protected:
            PrintOperationPreviewSignals( PrintOperationPreview *op );
            
            virtual ~PrintOperationPreviewSignals() = 0;
        public:
            virtual void on_ready( PrintContext &ctx );
            
            virtual void on_got_page_size( PrintContext &ctx, PageSetup &setup );
        }; 
        
    }
}

#endif
