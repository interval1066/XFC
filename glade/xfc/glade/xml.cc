/*  XFC: Xfce Foundation Classes (Glade Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  xml.cc - GladeXML C++ wrapper implementation
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */
 
#include "xml.hh"
#include "private/xmlclass.hh"
#include "xfc/gtk/widget.hh"

using namespace Xfc;

/*  Glade::Xml
 */

Glade::Xml::Xml(GladeXML *self, bool owns_reference)
: G::Object((GObject*)self, owns_reference)
{
}

Glade::Xml::Xml()
: G::Object((GObject*)XmlClass::create())
{
}	
	
Glade::Xml::~Xml() 
{
}

Pointer<Glade::Xml> 
Glade::Xml::create(const char *filename, const char *root, const char *domain)
{
	GladeXML *xml = glade_xml_new(filename, root, domain);
	return xml ? G::Object::wrap<Xml>(xml, true) : 0;	
}
	
Pointer<Glade::Xml> 
Glade::Xml::create(const std::string& filename, const String& root, const String& domain)
{
	return create(filename.c_str(), root.c_str(), domain.c_str());	
}

Pointer<Glade::Xml> 
Glade::Xml::create(const char *buffer, int size, const char *root, const char *domain)
{
	GladeXML *xml = glade_xml_new_from_buffer(buffer, size, root, domain);
	return xml ? G::Object::wrap<Xml>(xml, true) : 0;	
}

Pointer<Glade::Xml> 
Glade::Xml::create(const char *buffer, int size, const String& root, const String& domain)
{
	return create(buffer, size, root.c_str(), domain.c_str());	
}

bool 
Glade::Xml::construct(const char *filename, const char *root, const char *domain)
{
	return glade_xml_construct(glade_xml(), filename, root, domain);
}

bool 
Glade::Xml::construct(const std::string& filename, const String& root, const String& domain)
{
	return construct(filename.c_str(), root.c_str(), domain.c_str());
}

std::string 
Glade::Xml::get_filename() const
{
	return std::string(glade_xml()->filename ? glade_xml()->filename : "");
}	

Gtk::Widget*
Glade::Xml::get_widget(const char *name) const
{
	Gtk::Widget *widget = 0;	
	GtkWidget *tmp_widget = glade_xml_get_widget(glade_xml(), name);
	if (tmp_widget)
	{
		widget = G::Object::wrap<Gtk::Widget>(tmp_widget);	
	} 
	return widget;
}

Gtk::Widget*
Glade::Xml::get_widget(const String& name) const
{
	return get_widget(name.c_str());
}

bool
Glade::Xml::get_widget_prefix(const char *prefix, std::vector<Gtk::Widget*>& widgets) const
{
	g_return_val_if_fail(widgets.empty(), false);
	GList *first = glade_xml_get_widget_prefix(glade_xml(), prefix);
	GList *next = first;
	
	while (next)
	{
		widgets.push_back(G::Object::wrap<Gtk::Widget>((GtkWidget*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !widgets.empty();
}
bool
Glade::Xml::get_widget_prefix(const String& prefix, std::vector<Gtk::Widget*>& widgets) const
{
	return get_widget_prefix(prefix.c_str(), widgets);
}

std::string 
Glade::Xml::relative_file(const char *filename) const
{
	char *tmp_filename = glade_xml_relative_file(glade_xml(), filename);
	std::string s(tmp_filename);
	g_free(tmp_filename);
	return s;
}

std::string 
Glade::Xml::relative_file(const std::string& filename) const
{
	return relative_file(filename.c_str());
}

String 
Glade::Xml::get_widget_name(Gtk::Widget& widget)
{
	return glade_get_widget_name(widget.gtk_widget());
}

Pointer<Glade::Xml> 
Glade::Xml::get_widget_tree(Gtk::Widget& widget)
{
	GladeXML *self = glade_get_widget_tree(widget.gtk_widget());
	return self ? G::Object::wrap<Glade::Xml>(self) : 0;
}

/*  Glade::XmlClass
 */

void
Glade::XmlClass::init(GladeXMLClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Glade::XmlClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GLADE_TYPE_XML, (GClassInitFunc)&init);
	}
	return type;
}

void*
Glade::XmlClass::create()
{
	return g_object_new(get_type(), 0);
}

