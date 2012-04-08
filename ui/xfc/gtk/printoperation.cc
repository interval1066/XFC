#include "printoperation.hh"
#include "printoperationsignals.hh"
#include "private/printoperationpreviewiface.hh"
#include "private/printoperationclass.hh"

#include <iostream>
/*
 * Gtk::PrintOperationClass
 */
namespace Xfc {
    
    namespace Gtk {

        // PrintOperation

        PrintOperation::PrintOperation() : PrintOperationPreview((GObject*)PrintOperationClass::create()) {}

        PrintOperation::PrintOperation( GtkPrintOperation *op, bool owns_reference )
            : PrintOperationPreview( (GObject*)op, owns_reference ) {}
        
        PrintOperation::~PrintOperation() {}

        void PrintOperation::set_allow_async(bool allow_async)
        {
            gtk_print_operation_set_allow_async( gtk_print_operation(), allow_async );
        }
        
        void PrintOperation::set_default_page_setup(PageSetup *default_page_setup)
        {
            gtk_print_operation_set_default_page_setup( gtk_print_operation(), default_page_setup->gtk_page_setup() );
        }
        
        PageSetup* PrintOperation::get_default_page_setup()
        {
            GtkPageSetup *psetup = gtk_print_operation_get_default_page_setup(gtk_print_operation());
            return G::Object::wrap<PageSetup>( psetup );
        }
        
        void PrintOperation::set_print_settings( PrintSettings *print_settings )
        {
            gtk_print_operation_set_print_settings( gtk_print_operation(), print_settings->gtk_print_settings() );
        }
        
        PrintSettings* PrintOperation::get_print_settings()
        {
            GtkPrintSettings *pset = gtk_print_operation_get_print_settings( gtk_print_operation());
            return G::Object::wrap<PrintSettings>( pset );
        }
        
        void PrintOperation::set_job_name( const String &job_name )
        {
            gtk_print_operation_set_job_name( gtk_print_operation(), job_name.c_str() );
        }
        
        void PrintOperation::set_n_pages( int n_pages )
        {
            gtk_print_operation_set_n_pages( gtk_print_operation(), n_pages );
        }
        
        void PrintOperation::set_current_page( int current_page)
        {
            gtk_print_operation_set_current_page( gtk_print_operation(), current_page );
        }
        
        void PrintOperation::set_use_full_page( bool full_page)
        {
            gtk_print_operation_set_use_full_page( gtk_print_operation(), full_page );
        }
        
        void PrintOperation::set_unit(Gtk::Unit unit)
        {
            gtk_print_operation_set_unit( gtk_print_operation(), (GtkUnit)unit );
        }
        
        void PrintOperation::set_export_filename( const String &filename)
        {
            gtk_print_operation_set_export_filename( gtk_print_operation(), filename.c_str() );
        }
        
        void PrintOperation::set_show_progress( bool show_progress)
        {
            gtk_print_operation_set_show_progress( gtk_print_operation(), show_progress );
        }
        
        void PrintOperation::set_track_print_status( bool track_status)
        {
            gtk_print_operation_set_track_print_status( gtk_print_operation(), track_status );
        }
        
        void PrintOperation::set_custom_tab_label( const String &label )
        {
            gtk_print_operation_set_custom_tab_label( gtk_print_operation(), label.c_str() );
        }
        
        PrintOperationResult PrintOperation::run( PrintOperationAction action, Window *parent )
        {
            GtkWindow *pwnd = NULL;
            GError *error;

            if( parent )
                pwnd = parent->gtk_window();
            
            return (PrintOperationResult)gtk_print_operation_run( gtk_print_operation(), (GtkPrintOperationAction)action, pwnd, &error );
        }
        
        void PrintOperation::cancel()
        {
            gtk_print_operation_cancel( gtk_print_operation() );
        }
        
        // PrintOperationClass
        
        void PrintOperationClass::init(GtkPrintOperationClass *g_class)
        {
            ObjectClass::init((GtkObjectClass*)g_class);
            
            g_class->begin_print = &begin_print_proxy;
            g_class->create_custom_widget = &create_custom_widget_proxy;
            g_class->custom_widget_apply = &custom_widget_apply_proxy;
            g_class->done = &done_proxy;
            g_class->draw_page = &draw_page_proxy;
            g_class->end_print = &end_print_proxy;
            g_class->paginate = &paginate_proxy;
            g_class->preview = &preview_proxy;
            g_class->request_page_setup = &request_page_setup_proxy;
            g_class->status_changed = &status_changed_proxy;
        }

        GtkPrintOperationClass* PrintOperationClass::get_parent_class(void *instance)
        {
            return static_cast<GtkPrintOperationClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
        }

        GType PrintOperationClass::get_type()
        {
            static GType type = 0;
            if (!type) {
                type = G::TypeInstance::register_type(GTK_TYPE_PRINT_OPERATION, (GClassInitFunc)&init);
                G::TypeInstance::add_interface(type, GTK_TYPE_PRINT_OPERATION_PREVIEW, 
                                               (GInterfaceInitFunc)&PrintOperationPreviewIface::init);
            }
            return type;
        }

        void* PrintOperationClass::create()
        {
            return g_object_new(get_type(), 0);
        }

        void PrintOperationClass::begin_print_proxy( GtkPrintOperation *operation, GtkPrintContext *context )
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {
                PrintContext *ctx = G::Object::wrap<PrintContext>(context);
        
                signals->on_begin_print(*ctx);
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->begin_print)
                    g_class->begin_print( operation, context );
            }
        }

        GtkWidget* PrintOperationClass::create_custom_widget_proxy( GtkPrintOperation *operation)
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {
                Widget *w = signals->on_create_custom_widget();
                
                return (GtkWidget *)w;
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->create_custom_widget)
                    return g_class->create_custom_widget( operation );
            }
            return NULL;
        }
        
        void PrintOperationClass::custom_widget_apply_proxy(GtkPrintOperation *operation, GtkWidget *widget )
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {         
                signals->on_custom_widget_apply(*G::Object::wrap<Widget>( widget ));
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->custom_widget_apply)
                    g_class->custom_widget_apply( operation, widget );
            }
        }
        
        void PrintOperationClass::done_proxy(GtkPrintOperation *operation, GtkPrintOperationResult result )
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {         
                signals->on_done((PrintOperationResult)result );
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->done )
                    g_class->done( operation, result );
            }
        }
            
        void PrintOperationClass::draw_page_proxy(GtkPrintOperation *operation, GtkPrintContext *context, gint page_nr )
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {         
                signals->on_draw_page(*G::Object::wrap<PrintContext>( context ), page_nr );
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->draw_page)
                    g_class->draw_page( operation, context, page_nr );
            }
        }
        
        void PrintOperationClass::end_print_proxy(GtkPrintOperation *operation, GtkPrintContext *context )
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {         
                signals->on_end_print(*G::Object::wrap<PrintContext>( context ));
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->end_print)
                    g_class->end_print( operation, context );
            }
        }

        gboolean PrintOperationClass::paginate_proxy(GtkPrintOperation *operation, GtkPrintContext *context )
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {         
                return signals->on_paginate(*G::Object::wrap<PrintContext>( context ));
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->paginate)
                    return g_class->paginate( operation, context );
            }
            return false;
        }
        
        gboolean PrintOperationClass::preview_proxy(GtkPrintOperation *operation, GtkPrintOperationPreview *preview,
                                                    GtkPrintContext *context, GtkWindow *parent )
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {
                PrintOperation *op = G::Object::wrap<PrintOperation>(operation);
                PrintOperationPreview *pop = (PrintOperationPreview *)(op);
                PrintContext *ctx = G::Object::wrap<PrintContext>(context);
                Window *w = G::Object::wrap<Window>(parent);
                
                return signals->on_preview(*pop, *ctx, *w);
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->preview)
                    return g_class->preview( operation, preview, context, parent );
            }
            return false; // XXX, it this the propper default ?
        }
        
        void PrintOperationClass::request_page_setup_proxy(GtkPrintOperation *operation, GtkPrintContext *context,
                                                           gint page_nr, GtkPageSetup *setup )
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {
                PrintContext *ctx = G::Object::wrap<PrintContext>(context);
                PageSetup *ps = G::Object::wrap<PageSetup>(setup);
                
                signals->on_request_page_setup(*ctx, page_nr, *ps);
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->request_page_setup)
                    g_class->request_page_setup(operation, context, page_nr, setup);
            }
        }
        
        void PrintOperationClass::status_changed_proxy(GtkPrintOperation *operation )
        {
            PrintOperationSignals *signals = dynamic_cast<PrintOperationSignals*>(G::ObjectSignals::pointer((GObject*)operation));
            if (signals) {         
                signals->on_status_changed();
            } else {
                GtkPrintOperationClass *g_class = get_parent_class(operation);
                
                if (g_class && g_class->status_changed)
                    g_class->status_changed( operation );
            }
        }

    } // Gtk namespace
    
} // Xfc namespace
