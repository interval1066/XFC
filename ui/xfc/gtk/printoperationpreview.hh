#ifndef XFC_GTK_PRINT_OPERATION_PREVIEW_HH
#define XFC_GTK_PRINT_OPERATION_PREVIEW_HH

// This also include the TypeInterface
#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __GTK_EDITABLE_H__
#include <gtk/gtkprintoperationpreview.h>
#endif

namespace Xfc {
    
    namespace Gtk {
    
        /**
            The print operation preview interface, that really just is an interface
            but in C++ is mostly looks like a base class, and in XFC it will init at
            an object and not an interface.
        */
        class PrintOperationPreview : public G::Object {
        protected:
            /// @name Constructors
            /// @{

            PrintOperationPreview( GObject *obj, bool owns_reference = false );
            
            virtual ~PrintOperationPreview();
            
            /// @}
            /// @name Signal Prototypes
            /// @{
            
            typedef G::Signal<void, void> ReadySignalType;
            typedef G::SignalProxy<G::TypeInterface, ReadySignalType> ReadySignalProxy;
            static const ReadySignalType ready_signal;
            ///< Report when ready
            
            typedef G::Signal<void, void> GotPageSizeSignalType;
            typedef G::SignalProxy<G::TypeInterface, GotPageSizeSignalType> GotPageSizeSignalProxy;
            static const GotPageSizeSignalType got_page_size_signal;
            ///< report when it got the page size
            
        public:            
            GtkPrintOperationPreview *gtk_printoperationpreview() const;
            
            operator GtkPrintOperationPreview* () const;

            /// @}
            /// @name Accessors
            /// @{

            bool is_selected( int page_nr );
            
            /// @}
            /// @name Methods
            /// @{

            void end_preview();
            
            void render_page( int page_nr );
            
            /// @}
            /// @name Signal Proxies
            /// @{
        	const ReadySignalProxy signal_ready();
            
            const GotPageSizeSignalProxy signal_got_page_size();
            /// @}
        };
    }
}

#include "xfc/gtk/inline/printoperationpreview.inl"

#endif
