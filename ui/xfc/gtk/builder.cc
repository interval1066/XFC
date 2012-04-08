#include "builder.hh"

#include <xfc/glib/error.hh>

using namespace Xfc;

Gtk::Builder::Builder() : G::Object((GObject *)gtk_builder_new()) // We could make a private class .. but we dont need to ... really
{
}

Gtk::Builder::Builder( const String &filename ) : G::Object((GObject *)gtk_builder_new())
{
    add_from_file( filename );
}

Gtk::Builder::Builder(GtkBuilder *self, bool owns_reference ) :
    G::Object((GObject*)self, owns_reference)
{
}

void Gtk::Builder::add_from_file( const String &filename )
{
    G::Error error;

    if( gtk_builder_add_from_file( gtk_builder(), filename.c_str(), error ) == 0)
        throw error;
}

void Gtk::Builder::add_from_string( const String &buffer )
{
    G::Error error;
    
    if( gtk_builder_add_from_string( gtk_builder(), buffer.c_str(), buffer.size(), error ) == 0)
        throw error;
}

G::Object* Gtk::Builder::get_object( const String &name ) const
{
     return G::Object::wrap<G::Object>( gtk_builder_get_object( gtk_builder(), name.c_str() ));
}

G::SList<GObject> Gtk::Builder::get_objects() const 
{
    return G::SList<GObject>( gtk_builder_get_objects( gtk_builder()));
}

void Gtk::Builder::set_translation_domain(const String &domain)
{
    gtk_builder_set_translation_domain( gtk_builder(), domain.c_str() );
}

String Gtk::Builder::get_translation_domain() const
{
    return gtk_builder_get_translation_domain( gtk_builder());
}

GType Gtk::Builder::get_type_from_name(const String &type_name) const
{
    return gtk_builder_get_type_from_name(gtk_builder(), type_name.c_str());
}
