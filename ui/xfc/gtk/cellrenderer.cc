/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  cellrenderer.cc - GtkCellRenderer C++ wrapper implementation
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
 
#include "cellrenderer.hh"
#include "cellrenderersignals.hh"
#include "celleditable.hh"
#include "widget.hh"
#include "private/cellrendererclass.hh"
#include "private/marshal.hh"
#include "../gdk/color.hh"
#include "../gdk/types.hh"
#include "../gdk/window.hh"

using namespace Xfc;

/*  Gtk::CellRenderer
 */

Gtk::CellRenderer::CellRenderer(GtkCellRenderer *cell, bool owns_reference)
: Object((GtkObject*)cell, owns_reference)
{
}
	
Gtk::CellRenderer::~CellRenderer() 
{
}
	
void
Gtk::CellRenderer::get_size(const Widget& widget, const Gdk::Rectangle *cell_area,
                            int *x_offset, int *y_offset, int *width, int *height) const
{
	gtk_cell_renderer_get_size(gtk_cell_renderer(), widget.gtk_widget(), *cell_area, x_offset, y_offset, width, height);
}

void
Gtk::CellRenderer::render(Gdk::Window& window, Widget& widget, const Gdk::Rectangle *background_area,
                          const Gdk::Rectangle *cell_area, const Gdk::Rectangle *expose_area,
                          CellRendererStateField flags)
{
	gtk_cell_renderer_render(gtk_cell_renderer(), window.gdk_window(), widget.gtk_widget(), *background_area,
	                         *cell_area, *expose_area, (GtkCellRendererState)flags);
}

bool
Gtk::CellRenderer::activate(const Gdk::Event *event, Widget *widget, const String& path,
                            const Gdk::Rectangle *background_area, const Gdk::Rectangle *cell_area,
							CellRendererStateField flags)
{
	return gtk_cell_renderer_activate(gtk_cell_renderer(), *event, *widget, path.c_str(), *background_area, *cell_area,
	                                  (GtkCellRendererState)flags);
}

Gtk::CellEditable*
Gtk::CellRenderer::start_editing(const Gdk::Event *event, Widget *widget, const String& path,
                                 const Gdk::Rectangle *background_area, const Gdk::Rectangle *cell_area,
                                 CellRendererStateField flags)
{
	GtkCellEditable *editable = gtk_cell_renderer_start_editing(gtk_cell_renderer(), *event, *widget, path.c_str(),
	                                                            *background_area, *cell_area, (GtkCellRendererState)flags);
	Widget *tmp_widget = G::Object::wrap_new<Widget>((GtkWidget*)editable);
	return tmp_widget ? dynamic_cast<CellEditable*>(tmp_widget) : 0;
}

/*  Gtk::CellRendererClass
 */

void
Gtk::CellRendererClass::init(GtkCellRendererClass *g_class)
{
	ObjectClass::init((GtkObjectClass*)g_class);
	g_class->editing_canceled = &editing_canceled_proxy;
	g_class->editing_started = &editing_started_proxy;
}

GtkCellRendererClass*
Gtk::CellRendererClass::get_parent_class(void *instance)
{
	return static_cast<GtkCellRendererClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::CellRendererClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CELL_RENDERER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::CellRendererClass::create()
{
	return g_object_new(get_type(), 0);
}

void 
Gtk::CellRendererClass::editing_canceled_proxy(GtkCellRenderer *cell)
{
	CellRendererSignals *signals = dynamic_cast<CellRendererSignals*>(G::ObjectSignals::pointer((GObject*)cell));
	if (signals)
		signals->on_editing_canceled();
	else
	{
		GtkCellRendererClass *g_class = get_parent_class(cell);
		if (g_class && g_class->editing_canceled)
			g_class->editing_canceled(cell);
	}
}

void 
Gtk::CellRendererClass::editing_started_proxy(GtkCellRenderer *cell, GtkCellEditable *editable, const gchar *path)
{
	CellRendererSignals *signals = dynamic_cast<CellRendererSignals*>(G::ObjectSignals::pointer((GObject*)cell));
	if (signals)
	{
		CellEditable *tmp_editable = dynamic_cast<CellEditable*>(G::Object::wrap_new<Widget>((GtkWidget*)editable));
		String tmp_path(path);
		signals->on_editing_started(tmp_editable, tmp_path);
	}
	else
	{
		GtkCellRendererClass *g_class = get_parent_class(cell);
		if (g_class && g_class->editing_started)
			g_class->editing_started(cell, editable, path);
	}
}

/*  Gtk::CellRenderer properties
 */

const Gtk::CellRenderer::ModePropertyType Gtk::CellRenderer::mode_property("mode");

const Gtk::CellRenderer::VisiblePropertyType Gtk::CellRenderer::visible_property("visible");

const Gtk::CellRenderer::SensitivePropertyType Gtk::CellRenderer::sensitive_property("sensitive");

const Gtk::CellRenderer::XAlignPropertyType Gtk::CellRenderer::xalign_property("xalign");

const Gtk::CellRenderer::YAlignPropertyType Gtk::CellRenderer::yalign_property("yalign");

const Gtk::CellRenderer::XPadPropertyType Gtk::CellRenderer::xpad_property("xpad");

const Gtk::CellRenderer::YPadPropertyType Gtk::CellRenderer::ypad_property("ypad");

const Gtk::CellRenderer::WidthPropertyType Gtk::CellRenderer::width_property("width");

const Gtk::CellRenderer::HeightPropertyType Gtk::CellRenderer::height_property("height");

const Gtk::CellRenderer::IsExpanderPropertyType Gtk::CellRenderer::is_expander_property("is_expander");

const Gtk::CellRenderer::IsExpandedPropertyType Gtk::CellRenderer::is_expanded_property("is_expanded");

const Gtk::CellRenderer::CellBackgroundPropertyType Gtk::CellRenderer::cell_background_property("cell_background");

const Gtk::CellRenderer::CellBackgroundGdkPropertyType Gtk::CellRenderer::cell_background_gdk_property("cell_background_gdk");

const Gtk::CellRenderer::CellBackgroundSetPropertyType Gtk::CellRenderer::cell_background_set_property("cell_background_set");

/*  Gtk::CellRenderer signals
 */

const Gtk::CellRenderer::EditingCanceledSignalType Gtk::CellRenderer::editing_canceled_signal("editing-canceled", (GCallback)&G::Marshal::void_callback);

const Gtk::CellRenderer::EditingStartedSignalType Gtk::CellRenderer::editing_started_signal("editing-started", (GCallback)&Marshal::void_celleditable_string_callback);

