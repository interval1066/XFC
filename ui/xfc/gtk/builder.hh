/**
   Interface builder in GTK that have about the same function as 
   libglade. Loads a xml description from a file (or memory) and 
   convert this to an interface, that the application can hook into
   and use.

   This came in GTK version 2.12
*/
#ifndef XFC_BUILDER_HH
#define XFC_BUILDER_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef XFC_GTK_WINDOW_HH
#include <xfc/gtk/window.hh>
#endif

#ifndef __GTK_BUILDER_H__
#include <gtk/gtkbuilder.h>
#endif

#ifndef XFC_SLIST_HH
#include <xfc/glib/slist.hh>
#endif

namespace Xfc {
namespace Gtk {

/**
    A GtkBuilder is an auxiliary object that reads textual descriptions
    of a user interface and instantiates the described objects.

    A GtkBuilder holds a reference to all objects that it has constructed
    and drops these references when it is finalized. This finalization
    can cause the destruction of non-widget objects or widgets which
    are not contained in a toplevel window. For toplevel windows
    constructed by a builder, it is the responsibility of the user to
    call Gtk::Widget::destroy() to get rid of them and all the widgets
    they contain.
*/
class Builder : public G::Object {
public:
    /**
        Construct an empty builder object without any content.
    */
    Builder();

    /**
        Construct a new builder object and load the definition from
        given filename.
    */
    Builder( const String &filename );

    /**
        Constuct a new builder from a lowlevel C GtkBuilder object.
    */
    explicit Builder(GtkBuilder *self, bool owns_reference = true);

    GtkBuilder* gtk_builder() const;
	
	operator GtkBuilder* () const;

    /**
        Parses a file containing a GtkBuilder UI definition and merges
        it with the current contents of builder.

        @param filename name of the file to parse
        @exception G::Error on some kind of error
    */
    void add_from_file( const String &filename );

    /**
        Parses a string containing a GtkBuilder UI definition and merges
        it with the current contents of builder.

        @param the string to parse
        @exception G::Error on some kind of error
    */
    void add_from_string( const String &buffer );

    /**
        Gets the object named name. Note that this function does not
        increment the reference count of the returned object.

        @param name of the object to get (dismiss when done)
        @return the object named name or NULL if it could not be found
        in the object tree. 
    */
    G::Object* get_object( const String &name ) const;

	/**
        Gets a pointer to the Gtk::Widget corresponding to <EM>name</EM> in the interface description. 
        @param name The name of the widget in the XML description. 
        @return A pointer to the widget matching <EM>name</EM>, or null if none exists.
    */
    Gtk::Widget *get_widget( const String &name ) const;

	/**
        Gets a pointer to the Gtk::Widget corresponding to <EM>name</EM> in the interface description. 
        @param name The name of the widget in the XML description. 
        @param widget A reference to a pointer to hold the widget matching <EM>name</EM>, or null if none exists.
        @return <EM>true</EM> if successful, <EM>false</EM> if no widget exists.
	 
        To use this method <EM>WidgetType</EM> must be one of the standard XFC widgets. 
	
        <B>Example:</B> Connecting a "clicked" signal handler to a Gtk::Button.
        @code
        Gtk::Button *button;
        if (xml->get_widget("my_button", button))
        {
            button->signal_clicked().connect(sigc::mem_fun(this, &MyWindow::on_my_button_clicked));
        }
        @endcode    
    */
    template<typename WidgetType>
        bool get_widget(const String& name, WidgetType *&widget) const;

	/**
        Gets a pointer to the Gtk::Widget corresponding to <EM>name</EM> in the interface description.
        @param parrent Parent window.
        @param name The name of the widget in the XML description.
        @param widget A reference to a pointer to hold the widget matching <EM>name</EM>, or null if none exists.
        @return <EM>true</EM> if successful, <EM>false</EM> if no widget exists.

        To use this method <EM>WidgetType</EM> must be one of the standard XFC widgets.

        <B>Example:</B> Connecting a "clicked" signal handler to a Gtk::Button.
        @code
        Gtk::Button *button;
        if (xml->get_widget(parentWindow, "my_button", button))
        {
            button->signal_clicked().connect(sigc::mem_fun(this, &MyWindow::on_my_button_clicked));
        }
        @endcode
    */
    template<typename WidgetType>
        bool get_widget(Xfc::Gtk::Window *parent, const String& name, WidgetType *&widget) const;

    /**
        Gets a pointer to the Gtk::Widget corresponding to <EM>name</EM> in the interface description. 
        @param name The name of the widget in the XML description. 
        @param widget A reference to a pointer to hold the widget matching <EM>name</EM>, or null if none exists.
        @return <EM>true</EM> if successful, <EM>false</EM> if no widget exists.
        
        To use this method <EM>DerivedType</EM> must be a user-defined widget class
        that derives from one of the standard XFC widgets. The derived widget class
        must declare it's constructor with the following signature:
	        
        <B>Example:</B> Instantiating a main application window from an XML description.
        @code
        MyWindow *window;
        if (xml->get_widget_derived("MyWindow", window))
        {
            window->signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
            window->show();
            run();
        }
        @endcode
    */
    template<typename DerivedType>
        bool get_widget_derived(const String& name, DerivedType *&widget) const;

    /**
        Gets a pointer to the Gtk::Widget corresponding to <EM>name</EM> in the interface description.
        @param parrent Parent window.
        @param name The name of the widget in the XML description.
        @param widget A reference to a pointer to hold the widget matching <EM>name</EM>, or null if none exists.
        @return <EM>true</EM> if successful, <EM>false</EM> if no widget exists.

        To use this method <EM>DerivedType</EM> must be a user-defined widget class
        that derives from one of the standard XFC widgets. The derived widget class
        must declare it's constructor with the following signature:

        <B>Example:</B> Instantiating a main application window from an XML description.
        @code
        MyWindow *window;
        if (xml->get_widget_derived(parentWindow, "MyWindow", window))
        {
            window->signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
            window->show();
            run();
        }
        @endcode
    */
    template<typename DerivedType>
        bool get_widget_derived(Xfc::Gtk::Window *parent, const String& name, DerivedType *&widget) const;

    /**
        Gets all objects that have been constructed by builder.

        @note that this function does not increment the reference
        counts of the returned objects.

        @return a newly-allocated GSList containing all the objects constructed by the GtkBuilder instance. It should be freed by g_slist_free()
    */
    G::SList<GObject> get_objects() const;

    /**
        Sets the translation domain of builder.

        @param domain the translation domain
    */
    void set_translation_domain(const String &domain);

    /**
        Gets the translation domain of builder
        
        @return the translation domain.
    */
    String get_translation_domain() const;

    /**
        Looks up a type by name, using the virtual function that GtkBuilder
        has for that purpose. This is mainly used when implementing the
        GtkBuildable interface on a type.
    */
    GType get_type_from_name(const String &type_name) const;
};

} // Gtk
} // Xfc

#include <xfc/gtk/inline/builder.inl>

#endif
