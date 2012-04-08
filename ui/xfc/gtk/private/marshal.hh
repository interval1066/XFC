/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  marshal.hh - Private interface
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

// Provides the signal callback functions used by GTK Objects to translate
// GObject signal notifications into sigc::slot calls.

#ifndef XFC_GTK_MARSHALL_HH
#define XFC_GTK_MARSHALL_HH

#ifndef XFC_G_MARSHALL_HH
#include <xfc/glib/private/marshal.hh>
#endif

#ifndef __GTK_H__
#include <gtk/gtkadjustment.h>
#include <gtk/gtkmenu.h>
#include <gtk/gtknotebook.h>
#include <gtk/gtkradioaction.h>
#include <gtk/gtktextiter.h>
#include <gtk/gtktextchild.h>
#include <gtk/gtktextmark.h>
#include <gtk/gtktexttag.h>
#include <gtk/gtktooltips.h>
#include <gtk/gtktreemodel.h>
#include <gtk/gtktreeviewcolumn.h>
#include <gtk/gtkwidget.h>
#endif

#ifndef GDK_PIXBUF_H
#include <gdk-pixbuf/gdkpibuf.h>
#endif

namespace Xfc {

namespace Gtk {

class Marshal
{
public:
	static void void_uint_gdkmodifiertype_gclosure_callback(void*, guint, GdkModifierType, GClosure*);

	static void void_string_uint_gdkmodifiertype_callback(void *data, const char*, guint, GdkModifierType);
	
	static void void_string_string_callback(void*, const char*, const char*);

	static void void_string_callback(void*, const char*);

	static void void_string_int_pint_callback(void*, const char*, int, int*);

	static void void_widget_callback1(void*, GtkWidget*);

	static void void_widget_callback2(void*, GtkWidget*);

	static void void_menu_callback(void*, GtkMenu*);

	static void void_adjustment_adjustment_callback(void*, GtkAdjustment*, GtkAdjustment*);

	static void void_pint_callback(void*, int*);

	static void void_notebookpage_uint_callback(void*, GtkNotebookPage*, unsigned int);

	static void void_double_callback(void*, double);

	static char* pchar_double_callback(void*, double);

	static gboolean bool_callback(void*);

	static int int_callback(void*);

	static int int_pdouble_callback(void*, double*);

	static void void_uint_string_callback(void*, unsigned int, const char*);

    static void void_textiter_callback(void*, GtkTextIter*);

	static void void_textiter_string_int_callback(void*, GtkTextIter*, const char*, int);

	static void void_textiter_gdkpixbuf_callback(void*, GtkTextIter*, GdkPixbuf*);

	static void void_textiter_textchildanchor_callback(void*, GtkTextIter*, GtkTextChildAnchor*);

	static void void_textiter_textiter_callback(void*, GtkTextIter*, GtkTextIter*);

	static void void_textiter_textmark_callback(void*, const GtkTextIter*, GtkTextMark*);

	static void void_textmark_callback(void*, GtkTextMark*);

	static void void_textag_textiter_textiter_callback(void*, GtkTextTag*, const GtkTextIter*, const GtkTextIter*);

	static gboolean bool_gobject_gdkevent_textiter_callback(void*, GObject*, GdkEvent*, const GtkTextIter*);

	static void void_texttag_bool_callback(void*, GtkTextTag*, gboolean);

	static void void_texttag_callback(void*, GtkTextTag*);

	static void void_orientation_callback(void*, GtkOrientation);

	static void void_toolbarstyle_callback(void*, GtkToolbarStyle);

	static gboolean bool_int_int_int_callback(void*, int, int, int);

	static void void_treepath_callback(void*, GtkTreePath*);

	static void void_treepath_treeiter_callback(void*, GtkTreePath*, GtkTreeIter*);

	static void void_treepath_treeiter_pint_callback(void*, GtkTreePath*, GtkTreeIter*, int*);

	static void void_treepath_treeviewcolumn_callback(void*, GtkTreePath*, GtkTreeViewColumn*);

	static gboolean bool_treeiter_treepath_callback(void*, GtkTreeIter*, GtkTreePath*);

	static void void_treeiter_treepath_callback(void*, GtkTreeIter*, GtkTreePath*);

	static void void_requistion_callback(void*, GtkRequisition*);

	static void void_allocation_callback(void*, GtkAllocation*);

	static void void_statetype_callback(void*, GtkStateType);

	static void void_style_callback(void*, GtkStyle*);

	static void void_textdirection_callback(void*, GtkTextDirection);

	static void void_gparamspec_callback(void*, GParamSpec*);

	static gboolean bool_bool_callback(void*, bool);

	static gboolean bool_directiontype_callback(void*, GtkDirectionType);

	static void void_gdkscreen_callback(void*, GdkScreen*);

	static gboolean bool_uint_callback(void*, unsigned int);

	static void void_selectiondata_uint_uint_callback(void*, GtkSelectionData*, unsigned int, unsigned int);

	static void void_selectiondata_uint_callback(void*, GtkSelectionData*, unsigned int);

	static void void_dragcontext_callback(void*, GdkDragContext*);

	static void void_dragcontext_selectiondata_uint_uint_callback(void*, GdkDragContext*, GtkSelectionData*, unsigned int, unsigned int);

	static void void_dragcontext_uint_callback(void*, GdkDragContext*, unsigned int);

	static gboolean bool_dragcontext_int_int_uint_callback(void*, GdkDragContext*, int, int, unsigned int);

	static void void_dragcontext_int_int_selectiondata_uint_uint_callback(void*, GdkDragContext*, int, int, GtkSelectionData*, unsigned int, unsigned int);

	static gboolean bool_event_callback(void*, GdkEvent*);

	static void void_event_callback(void*, GdkEvent*);
	
	static gboolean bool_eventany_callback(void*, GdkEventAny*);

	static gboolean bool_eventbutton_callback(void*, GdkEventButton*);

	static gboolean bool_eventscroll_callback(void*, GdkEventScroll*);

	static gboolean bool_eventmotion_callback(void*, GdkEventMotion*);

	static gboolean bool_eventexpose_callback(void*, GdkEventExpose*);

	static gboolean bool_eventkey_callback(void*, GdkEventKey*);

	static gboolean bool_eventcrossing_callback(void*, GdkEventCrossing*);

	static gboolean bool_eventconfigure_callback(void*, GdkEventConfigure*);

	static gboolean bool_eventfocus_callback(void*, GdkEventFocus*);

	static gboolean bool_eventproperty_callback(void*, GdkEventProperty*);

	static gboolean bool_eventselection_callback(void*, GdkEventSelection*);

	static gboolean bool_eventproximity_callback(void*, GdkEventProximity*);

	static gboolean bool_eventvisibility_callback(void*, GdkEventVisibility*);

	static gboolean bool_eventclient_callback(void*, GdkEventClient*);

	static gboolean bool_eventwindowstate_callback(void*, GdkEventWindowState*);
	
	static void void_radioaction_callback(void*, GtkRadioAction*);

	static void void_action_callback(void*, GtkAction*);

	static void void_action_widget_callback(void*, GtkAction*, GtkWidget*);

	static gboolean bool_tooltips_string_string_callback(void*, GtkTooltips*, const char*, const char*);
	
	static gboolean bool_treemodel_treeiter_callback(void*, GtkTreeModel*, GtkTreeIter*);
	
	static void void_int_callback(void*, int);
	
	static void void_celleditable_string_callback(void*, GtkCellEditable*, const char*);

	static gboolean bool_string_callback(void*, const char*);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_MARSHALL_HH

