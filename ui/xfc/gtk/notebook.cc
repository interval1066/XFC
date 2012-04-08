/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  notebook.cc - GtkNotebook C++ wrapper implementation
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
 
#include "notebook.hh"
#include "notebooksignals.hh"
#include "label.hh"
#include "private/marshal.hh"
#include "private/notebookclass.hh"

using namespace Xfc;

/*  Gtk::Notebook
 */

Gtk::Notebook::Notebook(GtkNotebook *notebook, bool owns_reference)
: Container((GtkContainer*)notebook, owns_reference)
{
}

Gtk::Notebook::Notebook()
: Container((GtkContainer*)NotebookClass::create())
{
}

Gtk::Notebook::~Notebook() 
{
}

Gtk::Widget*
Gtk::Notebook::get_current_nth_page() const
{
	return get_nth_page(get_current_page());
}

Gtk::Widget*
Gtk::Notebook::get_nth_page(int page_num) const
{
	return G::Object::wrap<Widget>(gtk_notebook_get_nth_page(gtk_notebook(), page_num));
}

int
Gtk::Notebook::page_num(const Widget& child) const
{
	return gtk_notebook_page_num(gtk_notebook(), child.gtk_widget());
}

Gtk::Label*
Gtk::Notebook::get_tab_label(const Widget& child) const
{
	return G::Object::wrap<Label>((GtkLabel*)gtk_notebook_get_tab_label(gtk_notebook(), child.gtk_widget()));
}

Gtk::Label*
Gtk::Notebook::get_tab_label(int page_num) const
{
	GtkWidget *tab_label = 0;
	GtkWidget *child = gtk_notebook_get_nth_page(gtk_notebook(), page_num);
	if (child)
		tab_label = gtk_notebook_get_tab_label(gtk_notebook(), child);
	return tab_label ? G::Object::wrap<Label>((GtkLabel*)tab_label) : 0;
}

String
Gtk::Notebook::get_tab_label_text(const Widget& child) const
{
	return gtk_notebook_get_tab_label_text(gtk_notebook(), child.gtk_widget());
}

String
Gtk::Notebook::get_tab_label_text(int page_num) const
{
	GtkWidget *child = gtk_notebook_get_nth_page(gtk_notebook(), page_num);
	return gtk_notebook_get_tab_label_text(gtk_notebook(), child);
}

Gtk::Label*
Gtk::Notebook::get_menu_label(const Widget& child) const
{
	return G::Object::wrap<Label>((GtkLabel*)gtk_notebook_get_menu_label(gtk_notebook(), child.gtk_widget()));
}

Gtk::Label* 
Gtk::Notebook::get_menu_label(int page_num) const
{
	GtkWidget *menu_label = 0;
	GtkWidget *child = gtk_notebook_get_nth_page(gtk_notebook(), page_num);
	if (child)
		menu_label = gtk_notebook_get_menu_label(gtk_notebook(), child);
	return menu_label ? G::Object::wrap<Label>((GtkLabel*)menu_label) : 0;
}

String 
Gtk::Notebook::get_menu_label_text(const Widget& child) const
{
	return gtk_notebook_get_menu_label_text(gtk_notebook(), child.gtk_widget());
}

String 
Gtk::Notebook::get_menu_label_text(int page_num) const
{
	GtkWidget *child = gtk_notebook_get_nth_page(gtk_notebook(), page_num);
	return gtk_notebook_get_menu_label_text(gtk_notebook(), child);
}

void 
Gtk::Notebook::query_tab_label_packing(const Widget& child, bool *expand, bool *fill, PackType *pack_type) const
{
	gtk_notebook_query_tab_label_packing(gtk_notebook(), child.gtk_widget(), (gboolean*)expand, (gboolean*)fill, (GtkPackType*)pack_type);
}

int
Gtk::Notebook::append_page(Widget& child, Widget *tab_label, Widget *menu_label)
{
	return gtk_notebook_append_page_menu(gtk_notebook(), child.gtk_widget(), *tab_label, *menu_label);
}

int
Gtk::Notebook::append_page(Widget& child, const char *tab_label, const char *menu_label)
{
	int index = gtk_notebook_append_page_menu(gtk_notebook(), child.gtk_widget(), 0, 0);
	set_tab_label_text(child, tab_label);
	if (menu_label)
		set_menu_label_text(child, menu_label);
	return index;
}

int
Gtk::Notebook::append_page(Widget& child, const String& tab_label, const String& menu_label)
{
	return append_page(child, tab_label.c_str(), menu_label.c_str());
}

int
Gtk::Notebook::prepend_page(Widget& child, Widget *tab_label, Widget *menu_label)
{
	return gtk_notebook_prepend_page_menu(gtk_notebook(), child.gtk_widget(), *tab_label, *menu_label);
}

int
Gtk::Notebook::prepend_page(Widget& child, const char *tab_label, const char *menu_label)
{
	int index = gtk_notebook_prepend_page_menu(gtk_notebook(), child.gtk_widget(), 0, 0);
	set_tab_label_text(child, tab_label);
	if (menu_label)
		set_menu_label_text(child, menu_label);
	return index;
}

int
Gtk::Notebook::prepend_page(Widget& child, const String& tab_label, const String& menu_label)
{
	return prepend_page(child, tab_label.c_str(), menu_label.c_str());
}

int
Gtk::Notebook::insert_page(Widget& child, int position, Widget *tab_label, Widget *menu_label)
{
	return gtk_notebook_insert_page_menu(gtk_notebook(), child.gtk_widget(), *tab_label, *menu_label, position);
}

int
Gtk::Notebook::insert_page(Widget& child, int position, const char *tab_label, const char *menu_label)
{
	int index = gtk_notebook_insert_page_menu(gtk_notebook(), child.gtk_widget(), 0, 0, position);
	set_tab_label_text(child, tab_label);
	if (menu_label)
		set_menu_label_text(child, menu_label);
	return index;
}

int
Gtk::Notebook::insert_page(Widget& child, int position, const String& tab_label, const String& menu_label)
{
	return insert_page(child, position, tab_label.c_str(), menu_label.c_str());
}

void
Gtk::Notebook::set_tab_label(Widget& child, Widget *tab_label)
{
	gtk_notebook_set_tab_label(gtk_notebook(), child.gtk_widget(), *tab_label);
}

void
Gtk::Notebook::set_tab_label_text(Widget& child, const char *tab_text)
{
	gtk_notebook_set_tab_label_text(gtk_notebook(), child.gtk_widget(), tab_text);
}

void
Gtk::Notebook::set_tab_label_text(Widget& child, const String& tab_text)
{
	gtk_notebook_set_tab_label_text(gtk_notebook(), child.gtk_widget(), tab_text.c_str());
}

void
Gtk::Notebook::set_menu_label(Widget& child, Widget *menu_label)
{
	gtk_notebook_set_menu_label(gtk_notebook(), child.gtk_widget(), *menu_label);
}

void
Gtk::Notebook::set_menu_label_text(Widget& child, const char *menu_text)
{
	gtk_notebook_set_menu_label_text(gtk_notebook(), child.gtk_widget(), menu_text);
}

void
Gtk::Notebook::set_menu_label_text(Widget& child, const String& menu_text)
{
	gtk_notebook_set_menu_label_text(gtk_notebook(), child.gtk_widget(), menu_text.c_str());
}

void
Gtk::Notebook::set_tab_label_packing(Widget& child, bool expand, bool fill, PackType pack_type)
{
	gtk_notebook_set_tab_label_packing(gtk_notebook(), child.gtk_widget(), expand, fill, (GtkPackType)pack_type);
}

void 
Gtk::Notebook::reorder_child(Widget& child, int position)
{
	gtk_notebook_reorder_child(gtk_notebook(), child.gtk_widget(), position);
}

/*  Gtk::NotebookClass
 */

void
Gtk::NotebookClass::init(GtkNotebookClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
	g_class->switch_page = &switch_page_proxy;
}

GtkNotebookClass*
Gtk::NotebookClass::get_parent_class(void *instance)
{
	return static_cast<GtkNotebookClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::NotebookClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_NOTEBOOK, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::NotebookClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::NotebookClass::switch_page_proxy(GtkNotebook *notebook, GtkNotebookPage *page, guint page_num)
{
	NotebookSignals *signals = dynamic_cast<NotebookSignals*>(G::ObjectSignals::pointer((GObject*)notebook));
	if (signals)
	{
		GtkWidget *widget = reinterpret_cast<GtkWidget*>(page);
		signals->on_switch_page(*G::Object::wrap<Widget>(widget), page_num);
	}
	else
	{
		GtkNotebookClass *g_class = get_parent_class(notebook);
		if (g_class && g_class->switch_page)
			g_class->switch_page(notebook, page, page_num);
	}
}

/*  Gtk::Notebook signals
 */

const Gtk::Notebook::SwitchPageSignalType Gtk::Notebook::switch_page_signal("switch_page", (GCallback)&Marshal::void_notebookpage_uint_callback);

