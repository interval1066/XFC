/// @file xfc/gtk/widgetsignals.hh
/// @brief Gtk::Widget virtual signal handlers.
///
/// Provides Gtk::WidgetSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Widget objects.

#ifndef XFC_GTK_PRINT_OPERATION_SIGNALS_HH
#define XFC_GTK_PRINT_OPERATION_SIGNALS_HH 1

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef XFC_GTK_OBJECT_SIGNALS_HH
#include <xfc/gtk/objectsignals.hh>
#endif

#ifndef XFC_GTK_PRINT_OPERATION_HH
#include <xfc/gtk/printoperation.hh>
#endif

#ifndef XFC_PRINT_OPERATION_PREVIEW_SIGNALS_HH
#include <xfc/gtk/printoperationpreviewsignals.hh>
#endif

namespace Xfc {

    namespace Gtk {

        /// @class PrintOperationSignals printoperationsignals.hh xfc/gtk/printoperationsignals.hh
        /// @brief Abstract base class that implements the virtual signal handlers for Gtk::PrintOperation.

        class PrintOperationSignals : public PrintOperationPreviewSignals {
        protected:
            PrintOperationSignals(PrintOperation *operation);

            virtual ~PrintOperationSignals();
        public:
        /// @name Basic print operation signal handlers
        /// {@
            virtual void on_begin_print(PrintContext &context);
            virtual Widget *on_create_custom_widget();
            virtual void on_custom_widget_apply(Widget &widget);
            virtual void on_done(PrintOperationResult result);
            virtual void on_draw_page(PrintContext &context, int page_nr);
            virtual void on_end_print(PrintContext &context);
            virtual bool on_paginate(PrintContext &context);
            virtual bool on_preview (PrintOperationPreview &preview,
                                   PrintContext &context, Window &parent);
            virtual void on_request_page_setup(PrintContext &context,
                                             int page_nr, PageSetup &setup);
            virtual void on_status_changed();
        /// @}
        };

    }  // namespace Xfc

}  // namespace Gtk

#endif // XFC_GTK_PRINT_OPERATION_SIGNALS_HH
