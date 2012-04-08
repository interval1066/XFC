/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  container.cc - GtkContainer C++ wrapper implementation
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
 
#include "container.hh"
#include "containersignals.hh"
#include "private/containerclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Container
 */

Gtk::Container::Container(GtkContainer *container, bool owns_reference)
: Widget((GtkWidget*)container, owns_reference) 
{
}

Gtk::Container::~Container()
{
}

bool
Gtk::Container::is_resize_container() const 
{ 
	return is_a(GTK_TYPE_CONTAINER) && gtk_container()->resize_mode != GTK_RESIZE_PARENT; 
}

Gtk::Widget*
Gtk::Container::focus_child() const
{
	return G::Object::wrap<Widget>(gtk_container()->focus_child);
}

bool
Gtk::Container::get_children(std::vector<Widget*>& child_list) const
{
	g_return_val_if_fail(child_list.empty(), false);
	GList *first = gtk_container_get_children(gtk_container());
	GList *next = first;

	while (next)
	{
		child_list.push_back(G::Object::wrap<Widget>((GtkWidget*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !child_list.empty();
}

bool
Gtk::Container::get_focus_chain(std::vector<Widget*>& focusable_widgets) const
{
	GList *first = 0;
	bool result = gtk_container_get_focus_chain(gtk_container(), &first);
	GList *next = first;

	while (next)
	{
		focusable_widgets.push_back(G::Object::wrap<Widget>((GtkWidget*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return result;
}

Gtk::Adjustment*
Gtk::Container::get_focus_vadjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_container_get_focus_vadjustment(gtk_container()));
}

Gtk::Adjustment*
Gtk::Container::get_focus_hadjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_container_get_focus_hadjustment(gtk_container()));
}

void
Gtk::Container::add(Widget& widget)
{
	gtk_container_add(gtk_container(), widget.gtk_widget());
}

void
Gtk::Container::remove(Widget&widget)
{
	gtk_container_remove(gtk_container(), widget.gtk_widget());
}

void
Gtk::Container::set_focus_child(Widget& widget)
{
	gtk_container_set_focus_child(gtk_container(), widget.gtk_widget());
}

namespace { // foreach_slot_callback

void foreach_slot_callback(GtkWidget *widget, gpointer data)
{
	Gtk::Container::ForeachSlot& slot = *static_cast<Gtk::Container::ForeachSlot*>(data);
	slot(*G::Object::wrap<Gtk::Widget>(widget));
}

} // namespace

void 
Gtk::Container::foreach(const ForeachSlot& each)
{
	ForeachSlot tmp_each(each);
	gtk_container_foreach(gtk_container(), &foreach_slot_callback, &tmp_each);
}

void
Gtk::Container::set_focus_vadjustment(Adjustment *adjustment)
{
	gtk_container_set_focus_vadjustment(gtk_container(), *adjustment);
}

void
Gtk::Container::set_focus_hadjustment(Adjustment *adjustment)
{
	gtk_container_set_focus_hadjustment(gtk_container(), *adjustment);
}

void
Gtk::Container::propagate_expose(Widget& child, const Gdk::EventExpose& event)
{
	gtk_container_propagate_expose(gtk_container(), child.gtk_widget(), event.gdk_event_expose());
}

void
Gtk::Container::set_focus_chain(const std::vector<Widget*>& focusable_widgets)
{
	g_return_if_fail(!focusable_widgets.empty());
	GList *tmp_widgets = 0;
	int count = focusable_widgets.size();
	
	int i = 0;
	while (i < count)
	{
		tmp_widgets = g_list_append(tmp_widgets, focusable_widgets[i]->gtk_widget());
		++i;
	}

	gtk_container_set_focus_chain(gtk_container(), tmp_widgets);
	g_list_free(tmp_widgets);
}

/*  Gtk::ContainerClass
 */

void
Gtk::ContainerClass::init(GtkContainerClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
	g_class->add = &add_proxy;
	g_class->remove = &remove_proxy;
	g_class->check_resize = &check_resize_proxy;
	g_class->set_focus_child = &set_focus_child_proxy;
}

GtkContainerClass*
Gtk::ContainerClass::get_parent_class(void *instance)
{
	return static_cast<GtkContainerClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ContainerClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CONTAINER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ContainerClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ContainerClass::add_proxy(GtkContainer *container, GtkWidget *widget)
{
	ContainerSignals *signals = dynamic_cast<ContainerSignals*>(G::ObjectSignals::pointer((GObject*)container));
	if (signals)
		signals->on_add(*G::Object::wrap<Widget>(widget));
	else
	{
		GtkContainerClass *g_class = get_parent_class(container);
		if (g_class && g_class->add)
			g_class->add(container, widget);
	}
}

void
Gtk::ContainerClass::remove_proxy(GtkContainer *container, GtkWidget *widget)
{
	ContainerSignals *signals = dynamic_cast<ContainerSignals*>(G::ObjectSignals::pointer((GObject*)container));
	if (signals)
		signals->on_remove(*G::Object::wrap<Widget>(widget));
	else
	{
		GtkContainerClass *g_class = get_parent_class(container);
		if (g_class && g_class->remove)
			g_class->remove(container, widget);
	}
}

void
Gtk::ContainerClass::check_resize_proxy(GtkContainer *container)
{
	ContainerSignals *signals = dynamic_cast<ContainerSignals*>(G::ObjectSignals::pointer((GObject*)container));
	if (signals)
		signals->on_check_resize();
	else
	{
		GtkContainerClass *g_class = get_parent_class(container);
		if (g_class && g_class->check_resize)
			g_class->check_resize(container);
	}
}

void
Gtk::ContainerClass::set_focus_child_proxy(GtkContainer *container, GtkWidget *widget)
{
	ContainerSignals *signals = dynamic_cast<ContainerSignals*>(G::ObjectSignals::pointer((GObject*)container));
	if (signals)
		signals->on_set_focus_child(G::Object::wrap<Widget>(widget));
	else
	{
		GtkContainerClass *g_class = get_parent_class(container);
		if (g_class && g_class->set_focus_child)
			g_class->set_focus_child(container, widget);
	}
}

/*  Gtk::Container signals
 */

const Gtk::Container::AddSignalType Gtk::Container::add_signal("add", (GCallback)&Marshal::void_widget_callback2);

const Gtk::Container::RemoveSignalType Gtk::Container::remove_signal("remove", (GCallback)&Marshal::void_widget_callback2);

const Gtk::Container::CheckResizeSignalType Gtk::Container::check_resize_signal("check_resize", (GCallback)&G::Marshal::void_callback);

const Gtk::Container::SetFocusChildSignalType Gtk::Container::set_focus_child_signal("set_focus_child", (GCallback)&Marshal::void_widget_callback1);

