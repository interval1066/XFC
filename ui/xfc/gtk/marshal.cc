/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  marshal.cc - GObject signal callback functions.
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

#include "private/marshal.hh"
#include "accelkey.hh"
#include "actiongroup.hh"
#include "adjustment.hh"
#include "celleditable.hh"
#include "menu.hh"
#include "notebook.hh"
#include "radioaction.hh"
#include "style.hh"
#include "textbuffer.hh"
#include "texttag.hh"
#include "tooltips.hh"
#include "treemodel.hh"
#include "treeviewcolumn.hh"
#include "widget.hh"
#include "../gdk/screen.hh"
#include "../gdk-pixbuf/pixbuf.hh"
#include "xfc/glib/private/connection.hh"
#include <gtk/gtktreemodelfilter.h>

using namespace Xfc;

/*  Gtk::Marshal::void_uint_gdkmodifiertype_gclosure_callback
 */

void
Gtk::Marshal::void_uint_gdkmodifiertype_gclosure_callback(void *data, guint arg1, GdkModifierType arg2, GClosure *arg3)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const Gtk::AccelKey&, GClosure*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		AccelKey accel_key(arg1, (Gdk::ModifierTypeField)arg2);
		slot(accel_key, arg3);
	}
}

/*  Gtk::Marshal::void_string_uint_gdkmodifiertype_callback
 */

void
Gtk::Marshal::void_string_uint_gdkmodifiertype_callback(void *data, const char *arg1, guint arg2, GdkModifierType arg3)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const String&, const Gtk::AccelKey&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		String s(arg1);
		AccelKey accel_key(arg2, (Gdk::ModifierTypeField)arg3);
		slot(s, accel_key);
	}
}

/*  Gtk::Marshal::void_string_string_callback
 */

void
Gtk::Marshal::void_string_string_callback(void *data, const char *arg1, const char *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const String&, const String&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		String s1(arg1);
		String s2(arg2);
		slot(s1, s2);
	}
}

/*  Gtk::Marshal::void_string_callback
 */

void
Gtk::Marshal::void_string_callback(void *data, const char *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const String&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		String s(arg);
		slot(s);
	}
}

/*  Gtk::Marshal::void_string_int_pint_callback
 */

void
Gtk::Marshal::void_string_int_pint_callback(void *data, const char *arg1, int arg2, int *arg3)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const String&, int*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		String s(arg1, arg2);
		slot(s, arg3);
	}
}

/*  Gtk::Marshal::void_widget_callback1
 */

void
Gtk::Marshal::void_widget_callback1(void *data, GtkWidget *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Widget*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(G::Object::wrap<Widget>(arg));
	}
}

/*  Gtk::Marshal::void_widget_callback2
 */

void
Gtk::Marshal::void_widget_callback2(void *data, GtkWidget *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Widget&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<Widget>(arg));
	}
}

/*  Gtk::Marshal::void_menu_callback
 */

void
Gtk::Marshal::void_menu_callback(void *data, GtkMenu *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Menu&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<Menu>(arg));
	}
}

/*  Gtk::Marshal::void_adjustment_adjustment_callback
 */

void
Gtk::Marshal::void_adjustment_adjustment_callback(void *data, GtkAdjustment *arg1, GtkAdjustment *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Adjustment*, Adjustment*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(G::Object::wrap<Adjustment>(arg1), G::Object::wrap<Adjustment>(arg2));
	}
}

/*  Gtk::Marshal::void_pint_callback
 */

void
Gtk::Marshal::void_pint_callback(void *data, int *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, int*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg);
	}
}

/*  Gtk::Marshal::void_notebookpage_uint_callback
 */

void
Gtk::Marshal::void_notebookpage_uint_callback(void *data, GtkNotebookPage *arg1, unsigned int arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Widget&, unsigned int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		GtkWidget *widget = reinterpret_cast<GtkWidget*>(arg1);
		slot(*G::Object::wrap<Widget>(widget), arg2);
	}
}

/*  Gtk::Marshal::void_double_callback
 */

void
Gtk::Marshal::void_double_callback(void *data, double arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, double> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg);
	}
}

/*  Gtk::Marshal::pchar_double_callback
 */

char*
Gtk::Marshal::pchar_double_callback(void *data, double arg)
{
	char *result = 0;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<char*, double> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		result = slot(arg);
	}
	return result;
}

/*  Gtk::Marshal::bool_callback
 */

gboolean
Gtk::Marshal::bool_callback(void *data)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		result = slot();
	}
	return result;
}

/*  Gtk::Marshal::int_callback
 */

int
Gtk::Marshal::int_callback(void *data)
{
	int result = 0;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		result = slot();
	}
	return result;
}

/*  Gtk::Marshal::int_pdouble_callback
 */

int
Gtk::Marshal::int_pdouble_callback(void *data, double *arg)
{
	int result = 0;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<int, double*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		result = slot(arg);
	}
	return result;
}

/*  Gtk::Marshal::void_uint_string_callback
 */

void
Gtk::Marshal::void_uint_string_callback(void *data, unsigned int arg1, const char *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, unsigned int, const String&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		String s(arg2);
		slot(arg1, s);
	}
}

/*  Gtk::Marshal::void_textiter_callback
 */

void Gtk::Marshal::void_textiter_callback( void *data, GtkTextIter *arg1 )
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TextIter&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TextIter iter(arg1);
		slot(iter);
	}
}

/*  Gtk::Marshal::void_textiter_string_int_callback
 */

void
Gtk::Marshal::void_textiter_string_int_callback(void *data, GtkTextIter *arg1, const char *arg2, int arg3)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TextIter&, const String&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TextIter iter(arg1);
		String s(arg2, arg3);
		slot(iter, s);
	}
}

/*  Gtk::Marshal::void_textiter_gdkpixbuf_callback
 */

void
Gtk::Marshal::void_textiter_gdkpixbuf_callback(void *data, GtkTextIter *arg1, GdkPixbuf *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TextIter&, Gdk::Pixbuf&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TextIter iter(arg1);
		slot(iter, *G::Object::wrap<Gdk::Pixbuf>(arg2));
	}
}

/*  Gtk::Marshal::void_textiter_textchildanchor_callback
 */

void
Gtk::Marshal::void_textiter_textchildanchor_callback(void *data, GtkTextIter *arg1, GtkTextChildAnchor *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TextIter&, TextChildAnchor&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TextIter iter(arg1);
		slot(iter, *G::Object::wrap<TextChildAnchor>(arg2));
	}
}

/*  Gtk::Marshal::void_textiter_textiter_callback
 */

void
Gtk::Marshal::void_textiter_textiter_callback(void *data, GtkTextIter *arg1, GtkTextIter *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TextIter&, TextIter&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TextIter iter1(arg1);
		TextIter iter2(arg2);
		slot(iter1, iter2);
	}
}

/*  Gtk::Marshal::void_textiter_textmark_callback
 */

void
Gtk::Marshal::void_textiter_textmark_callback(void *data, const GtkTextIter *arg1, GtkTextMark *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const TextIter&, TextMark&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TextIter iter(const_cast<GtkTextIter*>(arg1));
		slot(iter, *G::Object::wrap<TextMark>(arg2));
	}
}

/* Gtk::Marshal::void_textiter_callback
 */

void
Gtk::Marshal::void_textmark_callback(void *data, GtkTextMark *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TextMark&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<TextMark>(arg));
	}
}

/*  Gtk::Marshal::void_textag_textiter_textiter_callback
 */

void
Gtk::Marshal::void_textag_textiter_textiter_callback(void *data, GtkTextTag *arg1, const GtkTextIter *arg2, const GtkTextIter *arg3)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TextTag&, const TextIter&, const TextIter&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TextIter iter1(const_cast<GtkTextIter*>(arg2));
		TextIter iter2(const_cast<GtkTextIter*>(arg3));
		slot(*G::Object::wrap<TextTag>(arg1), iter1, iter2);
	}
}

/*  Gtk::Marshal::bool_gobject_gdkevent_textiter_callback
 */

gboolean
Gtk::Marshal::bool_gobject_gdkevent_textiter_callback(void *data, GObject *arg1, GdkEvent *arg2, const GtkTextIter *arg3)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, G::Object&, Gdk::Event&, const TextIter&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event(arg2);
		TextIter iter(const_cast<GtkTextIter*>(arg3));
		result = slot(*G::Object::wrap<G::Object>(arg1), event, iter);
	}
	return result;
}

/*  Gtk::Marshal::void_texttag_bool_callback
 */

void
Gtk::Marshal::void_texttag_bool_callback(void *data, GtkTextTag *arg1, gboolean arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Gtk::TextTag&, bool> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<TextTag>(arg1), arg2);
	}
}

/*  Gtk::Marshal::void_texttag_callback
 */

void
Gtk::Marshal::void_texttag_callback(void *data, GtkTextTag *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TextTag&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<TextTag>(arg));
	}
}

/*  Gtk::Marshal::void_orientation_callback
 */

void
Gtk::Marshal::void_orientation_callback(void *data, GtkOrientation arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Gtk::Orientation> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot((Orientation)arg);
	}
}

/*  Gtk::Marshal::void_toolbarstyle_callback
 */

void
Gtk::Marshal::void_toolbarstyle_callback(void *data, GtkToolbarStyle arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, ToolbarStyle> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot((ToolbarStyle)arg);
	}
}

/*  Gtk::Marshal::bool_int_int_int_callback
 */

gboolean
Gtk::Marshal::bool_int_int_int_callback(void *data, int arg1, int arg2, int arg3)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, int, int, int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		result = slot(arg1, arg2, arg3);
	}
	return result;
}

/*  Gtk::Marshal::void_treepath_callback
 */

void
Gtk::Marshal::void_treepath_callback(void *data, GtkTreePath *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TreePath&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TreePath path(arg);
		slot(path);
	}
}

/*  Gtk::Marshal::void_treepath_treeiter_callback
 */

void
Gtk::Marshal::void_treepath_treeiter_callback(void *data, GtkTreePath *arg1, GtkTreeIter *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TreePath&, TreeIter&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TreePath path(arg1);
		TreeIter iter(arg2);
		slot(path, iter);
	}
}

/*  Gtk::Marshal::void_treepath_treeiter_pint_callback
 */

void
Gtk::Marshal::void_treepath_treeiter_pint_callback(void *data, GtkTreePath *arg1, GtkTreeIter *arg2, int *arg3)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TreePath&, TreeIter&, int*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TreePath path(arg1);
		TreeIter iter(arg2);
		slot(path, iter, arg3);
	}
}

/*  Gtk::Marshal::void_treepath_treeviewcolumn_callback
 */

void
Gtk::Marshal::void_treepath_treeviewcolumn_callback(void *data, GtkTreePath *arg1, GtkTreeViewColumn *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const TreePath&, TreeViewColumn&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TreePath path(arg1);
		slot(path, *G::Object::wrap<TreeViewColumn>(arg2));
	}
}

/*  Gtk::Marshal::bool_treeiter_treepath_callback
 */

gboolean
Gtk::Marshal::bool_treeiter_treepath_callback(void *data, GtkTreeIter *arg1, GtkTreePath *arg2)
{
	gboolean result = false;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const TreeIter&, const TreePath&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TreeIter iter(arg1);
		TreePath path(arg2);
		result = slot(iter, path);
	}
	return result;
}

/*  Gtk::Marshal::void_treeiter_treepath_callback
 */

void
Gtk::Marshal::void_treeiter_treepath_callback(void *data, GtkTreeIter *arg1, GtkTreePath *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const TreeIter&, const TreePath&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		TreeIter iter(arg1);
		TreePath path(arg2);
		slot(iter, path);
	}
}

/*  Gtk::Marshal::void_requistion_callback
 */

void
Gtk::Marshal::void_requistion_callback(void *data, GtkRequisition *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Requisition*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(reinterpret_cast<Requisition*>(arg));
	}
}

/*  Gtk::Marshal::void_allocation_callback
 */

void
Gtk::Marshal::void_allocation_callback(void *data, GtkAllocation *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const Allocation&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(reinterpret_cast<Allocation&>(*arg));
	}
}

/*  Gtk::Marshal::void_statetype_callback
 */

void
Gtk::Marshal::void_statetype_callback(void *data, GtkStateType arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, StateType> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot((StateType)arg);
	}
}

/*  Gtk::Marshal::void_style_callback
 */

void
Gtk::Marshal::void_style_callback(void *data, GtkStyle *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Style*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(G::Object::wrap<Style>(arg));
	}
}

/*  Gtk::Marshal::void_textdirection_callback
 */

void
Gtk::Marshal::void_textdirection_callback(void *data, GtkTextDirection arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, TextDirection> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot((TextDirection)arg);
	}
}

/*  Gtk::Marshal::void_gparamspec_callback
 */

void
Gtk::Marshal::void_gparamspec_callback(void *data, GParamSpec *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, GParamSpec*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg);
	}
}

/*  Gtk::Marshal::bool_bool_callback
 */

gboolean
Gtk::Marshal::bool_bool_callback(void *data, bool arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, bool> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		result = slot(arg);
	}
	return result;
}

/*  Gtk::Marshal::void_directiontype_callback
 */

gboolean
Gtk::Marshal::bool_directiontype_callback(void *data, GtkDirectionType arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, DirectionType> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		result = slot((DirectionType)arg);
	}
	return result;
}

/*  Gtk::Marshal::void_gdkscreen_callback
 */

void
Gtk::Marshal::void_gdkscreen_callback(void *data, GdkScreen *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Gdk::Screen*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(G::Object::wrap<Gdk::Screen>(arg));
	}
}

/*  Gtk::Marshal::bool_uint_callback
 */

gboolean
Gtk::Marshal::bool_uint_callback(void *data, unsigned int arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, unsigned int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		result = slot(arg);
	}
	return result;
}

/*  Gtk::Marshal::void_selectiondata_uint_uint_callback
 */

void
Gtk::Marshal::void_selectiondata_uint_uint_callback(void *data, GtkSelectionData *arg1, unsigned int arg2, unsigned int arg3)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, SelectionData&, unsigned int, unsigned int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		SelectionData selection_data(arg1);
		slot(selection_data, arg2, arg3);
	}
}

/*  Gtk::Marshal::void_selectiondata_uint_callback
 */

void
Gtk::Marshal::void_selectiondata_uint_callback(void *data, GtkSelectionData *arg1, unsigned int arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const SelectionData&, unsigned int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		SelectionData selection_data(arg1);
		slot(selection_data, arg2);
	}
}

/*  Gtk::Marshal::void_dragcontext_callback
 */

void
Gtk::Marshal::void_dragcontext_callback(void *data, GdkDragContext *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, DragContext&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<DragContext>(arg));
	}
}

/*  Gtk::Marshal::void_dragcontext_selectiondata_uint_uint_callback
 */

void
Gtk::Marshal::void_dragcontext_selectiondata_uint_uint_callback(void *data, GdkDragContext *arg1, GtkSelectionData *arg2, unsigned int arg3, unsigned int arg4)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, DragContext&, SelectionData&, unsigned int, unsigned int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		SelectionData selection_data(arg2);
		slot(*G::Object::wrap<DragContext>(arg1), selection_data, arg3, arg4);
	}
}

/*  Gtk::Marshal::void_dragcontext_uint_callback
 */

void
Gtk::Marshal::void_dragcontext_uint_callback(void *data, GdkDragContext *arg1, unsigned int arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, DragContext&, unsigned int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<DragContext>(arg1), arg2);
	}
}

/*  Gtk::Marshal::void_dragcontext_int_int_uint_callback
 */

gboolean
Gtk::Marshal::bool_dragcontext_int_int_uint_callback(void *data, GdkDragContext *arg1, int arg2, int arg3, unsigned int arg4)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, DragContext&, int, int, unsigned int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		result = slot(*G::Object::wrap<DragContext>(arg1), arg2, arg3, arg4);
	}
	return result;
}

/*  Gtk::Marshal::void_dragcontext_int_int_selectiondata_uint_uint_callback
 */

void
Gtk::Marshal::void_dragcontext_int_int_selectiondata_uint_uint_callback(void *data, GdkDragContext *arg1, int arg2, int arg3, GtkSelectionData *arg4, unsigned int arg5, unsigned int arg6)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, DragContext&, int, int, const SelectionData&, unsigned int, unsigned int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		SelectionData selection_data(arg4);
		slot(*G::Object::wrap<DragContext>(arg1), arg2, arg3, selection_data, arg5, arg6);
	}
}

/*  Gtk::Marshal::bool_event_callback
 */

gboolean
Gtk::Marshal::bool_event_callback(void *data, GdkEvent *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::Event&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(event);
	}
	return result;
}

/*  Gtk::Marshal::void_event_callback
 */

void
Gtk::Marshal::void_event_callback(void *data, GdkEvent *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const Gdk::Event&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		slot(event);
	}
}

/*  Gtk::Marshal::bool_eventany_callback
 */

gboolean
Gtk::Marshal::bool_eventany_callback(void *data, GdkEventAny *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventAny&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.any());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventbutton_callback
 */

gboolean
Gtk::Marshal::bool_eventbutton_callback(void *data, GdkEventButton *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventButton&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.button());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventscroll_callback
 */

gboolean
Gtk::Marshal::bool_eventscroll_callback(void *data, GdkEventScroll *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventScroll&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.scroll());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventmotion_callback
 */

gboolean
Gtk::Marshal::bool_eventmotion_callback(void *data, GdkEventMotion *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventMotion&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.motion());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventexpose_callback
 */

gboolean
Gtk::Marshal::bool_eventexpose_callback(void *data, GdkEventExpose *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventExpose&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.expose());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventkey_callback
 */

gboolean
Gtk::Marshal::bool_eventkey_callback(void *data, GdkEventKey *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventKey&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.key());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventcrossing_callback
 */

gboolean
Gtk::Marshal::bool_eventcrossing_callback(void *data, GdkEventCrossing *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventCrossing&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.crossing());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventconfigure_callback
 */

gboolean
Gtk::Marshal::bool_eventconfigure_callback(void *data, GdkEventConfigure *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventConfigure&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.configure());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventfocus_callback
 */

gboolean
Gtk::Marshal::bool_eventfocus_callback(void *data, GdkEventFocus *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventFocus&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.focus_change());
	}
	return result;
}
/*  Gtk::Marshal::bool_eventproperty_callback
 */

gboolean
Gtk::Marshal::bool_eventproperty_callback(void *data, GdkEventProperty *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventProperty&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.property());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventselection_callback
 */

gboolean
Gtk::Marshal::bool_eventselection_callback(void *data, GdkEventSelection *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventSelection&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.selection());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventproximity_callback
 */

gboolean
Gtk::Marshal::bool_eventproximity_callback(void *data, GdkEventProximity *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventProximity&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.proximity());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventvisibility_callback
 */

gboolean
Gtk::Marshal::bool_eventvisibility_callback(void *data, GdkEventVisibility *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventVisibility&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.visibility());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventclient_callback
 */

gboolean
Gtk::Marshal::bool_eventclient_callback(void *data, GdkEventClient *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventClient&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.client());
	}
	return result;
}

/*  Gtk::Marshal::bool_eventwindowstate_callback
 */

gboolean
Gtk::Marshal::bool_eventwindowstate_callback(void *data, GdkEventWindowState *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const Gdk::EventWindowState&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		Gdk::Event event((GdkEvent*)arg);
		result = slot(*event.window_state());
	}
	return result;
}

/*  Gtk::Marshal::void_radioaction_callback
 */

void 
Gtk::Marshal::void_radioaction_callback(void *data, GtkRadioAction *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, RadioAction&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<RadioAction>(arg));
	}
}

/*  Gtk::Marshal::void_radioaction_callback
 */

void 
Gtk::Marshal::void_action_callback(void *data, GtkAction *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Action&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<Action>(arg));
	}
}

/*  Gtk::Marshal::void_action_callback
 */

void 
Gtk::Marshal::void_action_widget_callback(void *data, GtkAction *arg1, GtkWidget *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Action&, Widget> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<Action>(arg1), *G::Object::wrap<Widget>(arg2));
	}
}

/*  Gtk::Marshal::bool_tooltips_string_string_callback
 */

gboolean 
Gtk::Marshal::bool_tooltips_string_string_callback(void *data, GtkTooltips *arg1, const char *arg2, const char *arg3)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, Tooltips&, const String&, const String&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		String s1(arg2);
		String s2(arg3);
		result = slot(*G::Object::wrap<Tooltips>(arg1), s1, s2);
	}
	return result;
}

/*  Gtk::Marshal::bool_treemodel_treeiter_callback
 */

gboolean 
Gtk::Marshal::bool_treemodel_treeiter_callback(void *data, GtkTreeModel *arg1, GtkTreeIter *arg2)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		GtkTreeIter real_iter;
		gtk_tree_model_filter_convert_iter_to_child_iter((GtkTreeModelFilter*)arg1, &real_iter, arg2);
		GtkTreeModel *real_model = gtk_tree_model_filter_get_model((GtkTreeModelFilter*)arg1);		
		typedef	sigc::slot<bool, const TreeModel&, const TreeIter&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		G::Object *object = G::Object::pointer((GObject*)real_model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreeIter tmp_iter(&real_iter);
		result = slot(*tmp_model, tmp_iter);
	}
	return result;
}
	
/*  Gtk::Marshal::void_int_callback
 */

void 
Gtk::Marshal::void_int_callback(void *data, int arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg);
	}
}

/*  Gtk::Marshal::void_celleditable_string_callback
 */

void
Gtk::Marshal::void_celleditable_string_callback(void *data, GtkCellEditable *arg1, const char *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, CellEditable*, const String&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		CellEditable *editable = dynamic_cast<CellEditable*>(G::Object::wrap_new<Widget>((GtkWidget*)arg1));
		String s(arg2);
		slot(editable, s);
	}
}

/*  Gtk::Marshal::void_string_callback
 */

gboolean
Gtk::Marshal::bool_string_callback(void *data, const char *arg)
{
	gboolean result = FALSE;
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<bool, const String&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		String s(arg);
		result = slot(s);
	}
	return result;
}

