#ifndef XFC_GTK_PRINT_OPERATION_HH
#define XFC_GTK_PRINT_OPERATION_HH 1

/**
   GtkPrintOperation interface
*/

#ifndef XFC_GTK_WINDOW_HH
#include <xfc/gtk/window.hh>
#endif

#ifndef XFC_GTK_PRINT_PRINTCONTEXT_HH
#include <xfc/gtk/printcontext.hh>
#endif

#ifndef XFC_GTK_PRINT_SETTING_HH
#include <xfc/gtk/printsetting.hh>
#endif

#ifndef XFC_GTK_PRINT_OPERATION_PREVIEW_HH
#include "xfc/gtk/printoperationpreview.hh"
#endif

namespace Xfc {
    namespace Gtk {
        class PrintSettings;

        enum PrintOperationResult {
            ERROR       = GTK_PRINT_OPERATION_RESULT_ERROR,
            APPLY       = GTK_PRINT_OPERATION_RESULT_APPLY,
            CANCEL      = GTK_PRINT_OPERATION_RESULT_CANCEL,
            IN_PROGRESS = GTK_PRINT_OPERATION_RESULT_IN_PROGRESS
        };
        
        enum PrintOperationAction {
            ACTION_PRINT_DIALOG = GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG,
            ACTION_PRINT        = GTK_PRINT_OPERATION_ACTION_PRINT,
            ACTION_PREVIEW      = GTK_PRINT_OPERATION_ACTION_PREVIEW,
            ACTION_EXPORT       = GTK_PRINT_OPERATION_ACTION_EXPORT
        };

        enum PrintStatus {
            INITIAL          = GTK_PRINT_STATUS_INITIAL,
            PREPARING        = GTK_PRINT_STATUS_PREPARING,
            GENERATING_DATA  = GTK_PRINT_STATUS_GENERATING_DATA,
            SENDING_DATA     = GTK_PRINT_STATUS_SENDING_DATA,
            PENDING          = GTK_PRINT_STATUS_PENDING,
            PENDING_ISSUE    = GTK_PRINT_STATUS_PENDING_ISSUE,
            PRINTING         = GTK_PRINT_STATUS_PRINTING,
            FINISHED         = GTK_PRINT_STATUS_FINISHED,
            FINISHED_ABORTED = GTK_PRINT_STATUS_FINISHED_ABORTED
        };

        /**
            Gtk::PrintOperation is the high-level, portable printing API.
            It looks a bit different than other GTK+ dialogs such as the
            GtkFileChooser, since some platforms don't expose enough infrastructure
            to implement a good print dialog. On such platforms, Gtk::PrintOperation
            uses the native print dialog. On platforms which do not
            provide a native print dialog, GTK+ uses its own
            
            @see Gtk::PrintUnixDialog.

            The typical way to use the high-level printing API is to create
            a Gtk::PrintOperation object with construcor
            when the user selects to print. Then you set some properties
            on it, e.g. the page size, any Gtk::PrintSettings from previous
            print operations, the number of pages, the current page, etc.

            Then you start the print operation by calling run(). It will
            then show a dialog, let the user select a printer and
            options. When the user finished the dialog various signals
            will be emitted on the Gtk::PrintOperation, the main one being
            draw-page, which you are supposed to catch and render the
            page on the provided Gtk::PrintContext using Cairo. 
        */
        class PrintOperation : public PrintOperationPreview {
            friend class G::Object;

            PrintOperation(const PrintOperation &);
           
            PrintOperation &operator=(const PrintOperation &);
        protected:
            /// @name Constructors
            /// @{
                
            PrintOperation();
            
            explicit PrintOperation(GtkPrintOperation *op, bool owns_reference = false);
            
            virtual ~PrintOperation();
            
            /// @}
            /// @name Signal Prototypes
            /// @{
            
            typedef G::Signal<void,PrintContext&> BeginPrintSignalType;
            typedef G::SignalProxy<G::TypeInterface, BeginPrintSignalType> BeginPrintSignalProxy;
            static const BeginPrintSignalType begin_print_signal;
            ///< Begin print signal proxy

            typedef G::Signal<void,Widget*> CreateCustomWidgetSignalType;
            typedef G::SignalProxy<G::TypeInterface, CreateCustomWidgetSignalType> CreateCustomWidgetSignalProxy;
            static const CreateCustomWidgetSignalType create_custom_widget_signal;
            ///< Create custom widget signal

            typedef G::Signal<void,Widget*> CustomWidgetApplySignalType; 
            typedef G::SignalProxy<G::TypeInterface, CustomWidgetApplySignalType> CustomWidgetApplySignalProxy;
            static const CustomWidgetApplySignalType custom_widget_apply_signal;
            ///< 

            typedef G::Signal<void,PrintOperationResult&> DoneSignalType;
            typedef G::SignalProxy<G::TypeInterface,DoneSignalType> DoneSignalProxy;
            static const DoneSignalType done_signal;

            typedef G::Signal<void,PrintContext&,int> DrawPageSignalType;
            typedef G::SignalProxy<G::TypeInterface,DrawPageSignalType> DrawPageSignalProxy;
            static const DrawPageSignalType draw_page_signal;

            typedef G::Signal<void,PrintContext&> EndPrintSignalType;
            typedef G::SignalProxy<G::TypeInterface,EndPrintSignalType> EndPrintSignalProxy;
            static const EndPrintSignalType end_print_signal;
            
            typedef G::Signal<bool,PrintContext&> PaginateSignalType;
            typedef G::SignalProxy<G::TypeInterface,PaginateSignalType> PaginateSignalProxy;
            static const PaginateSignalType paginate_signal;

            typedef G::Signal<bool,PrintOperationPreview&,PrintContext&,Window&> PreviewSignalType;
            typedef G::SignalProxy<G::TypeInterface,PreviewSignalType> PreviewSignalProxy;
            static const PreviewSignalType preview_signal;

            typedef G::Signal<void,PrintContext&,int,PageSetup&> RequestPageSetupSignalType;
            typedef G::SignalProxy<G::TypeInterface,RequestPageSetupSignalType> RequestPageSetupSignalProxy;
            static const RequestPageSetupSignalType request_page_setup;

            typedef G::Signal<void> StatusChangedSignalType;
            typedef G::SignalProxy<G::TypeInterface,StatusChangedSignalType> StatusChangedSignalProxy;
            static const StatusChangedSignalType status_changed_signal;
            
        public:
            /// @}
            /// @name Accessors
            /// @{
            
            operator GtkPrintOperation* () const;

            GtkPrintOperation* gtk_print_operation() const;
            ///< Get a pointer to the GtkPrintOperation structure.
            
            PrintStatus get_status();
            String get_status_string();
            bool is_finished();
            
            /// @}
            /// @name Methods
            /// @{

            /**
                Sets whether the run() may return before the print
                operation is completed.
                
                @note that some platforms may not allow asynchronous operation.

                @param allow_async true to allow asynchronous operation 
            */
            void set_allow_async(bool allow_async);

            /**
                Makes default_page_setup the default page setup for op.

                This page setup will be used by run(), but it can be
                overridden on a per-page basis by connecting to the
                "request-page-setup" signal.

                @param default_page_setup a GtkPageSetup, or NULL. allow-none. 
            */
            void set_default_page_setup( PageSetup *default_page_setup);

            /**
                Returns the default page setup.
                
                @see set_default_page_setup()
                @return the default page setup
            */
            PageSetup* get_default_page_setup();

            /**
                Sets the print settings for op. This is typically used to
                re-establish print settings from a previous print operation.

                @see gtk_print_operation_run().

                @param print_settings Gtk::PrintSettings. allow-none.
            */
            void set_print_settings( PrintSettings *print_settings );

            /**
                Returns the current print settings.

                @note that the return value is NULL until either set_print_settings() or run() have been called.
                @return the current print settings of op. 
            */
            PrintSettings* get_print_settings();

            /**
                Sets the name of the print job. The name is used to
                identify the job (e.g. in monitoring applications like eggcups).

                If you don't set a job name, GTK+ picks a default one by
                numbering successive print jobs.

                @param job_name a string that identifies the print job
            */
            void set_job_name( const String &job_name );

            /**
                Sets the number of pages in the document.

                This must be set to a positive number before the rendering
                starts. It may be set in a "begin-print" signal hander.

                Note that the page numbers passed to the "request-page-setup"
                and "draw-page" signals are 0-based, i.e. if the user
                chooses to print all pages, the last ::draw-page signal
                will be for page n_pages - 1.

                @param n_pages the number of pages 
            */
            void set_n_pages( int n_pages );

            /**
                Returns the number of pages that will be printed.

                Note that this value is set during print preparation phase
                (GTK_PRINT_STATUS_PREPARING), so this function should
                never be called before the data generation phase
                (GTK_PRINT_STATUS_GENERATING_DATA). You can connect to
                the "status-changed" signal and call get_n_pages_to_print()
                when print status is GTK_PRINT_STATUS_GENERATING_DATA.
                This is typically used to track the progress of print operation.
    
                @eturn the number of pages that will be printed 
            */
            int get_n_pages_to_print();
            
            /**
                Sets the current page.

                If this is called before run(), the user will be able to
                select to print only the current page.

                @note that this only makes sense for pre-paginated documents.

                @param current_page the current page, 0-based 
            */   
            void set_current_page( int current_page);

            /**
                If full_page is true, the transformation for the cairo context
                obtained from GtkPrintContext puts the origin at the top
                left corner of the page (which may not be the top left
                corner of the sheet, depending on page orientation and the
                number of pages per sheet). Otherwise, the origin is at
                the top left corner of the imageable area (i.e. inside
                the margins).

                @params full_page true to set up the Gtk::PrintContext for the full page 
            */
            void set_use_full_page( bool full_page );

            /**
                Sets up the transformation for the cairo context obtained
                from Gtk::PrintContext in such a way that distances are
                measured in units of unit.

                @param unit the unit to use 
            */
            void set_unit(Gtk::Unit unit);

            /**
                Sets up the Gtk::PrintOperation to generate a file
                instead of showing the print dialog. The indended use of
                this function is for implementing "Export to PDF" actions.
                Currently, PDF is the only supported format.

                "Print to PDF" support is independent of this and is
                done by letting the user pick the "Print to PDF" item
                from the list of printers in the print dialog.

                @param filename the filename for the exported file 
            */
            void set_export_filename( const String &filename);

            /**
                If show_progress is true, the print operation will show a
                progress dialog during the print operation.

                @param show_progress true to show a progress dialog 
            */
            void set_show_progress( bool show_progress);

            /**
                If track_status is true , the print operation will try to
                continue report on the status of the print job in the printer
                queues and printer. This can allow your application to show
                things like "out of paper" issues, and when the print
                job actually reaches the printer.

                This function is often implemented using some form of polling,
                so it should not be enabled unless needed.

                @param track_status true to track status after printing
            */
            void set_track_print_status( bool track_status);

            /**
                Sets the label for the tab holding custom widgets.

                @param label the label to use, or NULL to use the default label. allow-none. 
            */
            void set_custom_tab_label( const String &label);

            /**
                Runs the print operation, by first letting the user modify
                print settings in the print dialog, and then print the document.

                Normally that this function does not return until the rendering
                of all pages is complete. You can connect to the "status-changed"
                signal on op to obtain some information about the progress
                of the print operation. Furthermore, it may use a recursive
                mainloop to show the print dialog.

                If you call set_allow_async() or set the "allow-async" property
                the operation will run asynchronously if this is supported
                on the platform. The "done" signal will be emitted with the
                result of the operation when the it is done (i.e. when the
                dialog is canceled, or when the print succeeds or fails).

                @note that run() can only be called once on a given GtkPrintOperation.

                @param action the action to start
                @param parent Transient parent of the dialog. allow-none.
                @param error Return location for errors, or NULL. allow-none.
                @return the result of the print operation. A return value of
                GTK_PRINT_OPERATION_RESULT_APPLY indicates that the printing
                was completed successfully. In this case, it is a good idea
                to obtain the used print settings with get_print_settings()
                and store them for reuse with the next print operation.
                A value of GTK_PRINT_OPERATION_RESULT_IN_PROGRESS means the
                operation is running asynchronously, and will emit the "done"
                signal when done. 
            */
            PrintOperationResult run( PrintOperationAction action, Window *parent = NULL);

            /**
                Cancels a running print operation. This function may be called
                from a "begin-print", "paginate" or "draw-page" signal handler
                to stop the currently running print operation.
            */
            void cancel();

            /// @}
            /// @name Signal Proxies
            /// @{

        	const BeginPrintSignalProxy signal_begin_print();
            ///< Emitted after the user has finished changing print settings in the dialog, 
            ///< before the actual rendering starts.
            ///< A typical use for ::begin-print is to use the parameters 
            ///< from the GtkPrintContext and paginate the document accordingly, and then 
            ///< set the number of pages with gtk_print_operation_set_n_pages().

            const CreateCustomWidgetSignalProxy signal_create_custom_widget();
            ///< Emitted when displaying the print dialog. If you return a widget in a handler 
            ///< for this signal it will be added to a custom tab in the print dialog. You 
            ///< typically return a container widget with multiple widgets in it.
            ///< The print dialog owns the returned widget, and its lifetime isn't controlled 
            ///< by the app. However, the widget is guaranteed to stay around until the 
            ///< "custom-widget-apply" signal is emitted on the operation. Then you can read 
            ///< out any information you need from the widgets.

            const CustomWidgetApplySignalProxy signal_custom_widget_apply();
            ///< Emitted right before "begin-print" if you added a custom widget in the 
            ///< create-custom-widget handler. When you get this signal you should read 
            ///< the information from the custom widgets, as the widgets are not 
            ///< guaraneed to be around at a later time.

            const DoneSignalProxy signal_done();
            ///< Emitted when the print operation run has finished doing everything 
            ///< required for printing. result gives you information about what 
            ///< happened during the run. If result is PRINT_OPERATION_RESULT_ERROR 
            ///< then you can call get_error() for more information.
            ///< If you enabled print status tracking then is_finished() may still 
            ///< return false after "done" was emitted.
            
            const DrawPageSignalProxy signal_draw_page();
            ///< Emitted for every page that is printed. The signal handler must render 
            ///< the page_nr's page onto the cairo context obtained from context 
            ///< using PrintContext::get_cairo_context().
            ///< Use set_use_full_page() and set_unit() before starting the print 
            ///< operation to set up the transformation of the cairo context according to your needs.

            const EndPrintSignalProxy signal_end_print();
            ///< Emitted after all pages have been rendered. A handler for this signal 
            ///< can clean up any resources that have been allocated in the "begin-print" handler.

            const PaginateSignalProxy signal_paginate();
            ///< Emitted after the "begin-print" signal, but before the actual rendering starts. 
            ///< It keeps getting emitted until it returns false.
            ///<
            ///< The paginate signal is intended to be used for paginating the document in small 
            ///< chunks, to avoid blocking the user interface for a long time. The signal handler 
            ///< should update the number of pages using set_n_pages(), and return tru if the 
            ///< document has been completely paginated.
            ///< 
            ///< If you don't need to do pagination in chunks, you can simply do it all in the 
            ///< begin-print handler, and set the number of pages from there.

            const PreviewSignalProxy signal_preview();
            ///< Gets emitted when a preview is requested from the native dialog.
            ///< The default handler for this signal uses an external viewer application to preview.
            ///< To implement a custom print preview, an application must return true from its 
            ///< handler for this signal. In order to use the provided context for the preview 
            ///< implementation, it must be given a suitable cairo context with 
            ///< PrintContext::set_cairo_context().

            ///< The custom preview implementation can use PrintOperationPreview::is_selected() 
            ///< and PrintOperationPreview::render_page() to find pages which are selected for 
            ///< print and render them. The preview must be finished by calling PrintOperationPreview::end_preview() 
            ///< (typically in response to the user clicking a close button).
    
            const RequestPageSetupSignalProxy signal_request_page();
            ///< Emitted once for every page that is printed, to give the application a 
            ///< chance to modify the page setup. Any changes done to setup will be in force 
            ///< only for printing this page.

            const StatusChangedSignalProxy signal_status_changed();
            ///< Emitted at between the various phases of the print operation. See PrintStatus 
            ///< for the phases that are being discriminated. Use get_status() to find out the
            ///< current status.

            /// @}
        };

        inline GtkPrintOperation* PrintOperation::gtk_print_operation() const
        {
            return reinterpret_cast<GtkPrintOperation*>(instance_);
        }

        inline PrintOperation::operator GtkPrintOperation* () const
        {
            return this ? gtk_print_operation() : NULL;
        }
        
    }
}

#endif
