/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treeview.cc - GtkTreeView C++ wrapper implementation
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
 
#include "treeview.hh"
#include "treeviewsignals.hh"
#include "treemodel.hh"
#include "private/marshal.hh"
#include "private/treeviewclass.hh"
#include "../gdk/dnd.hh"
#include "../gdk/pixmap.hh"
#include "../gdk/window.hh"

using namespace Xfc;

/*  Gtk::TreeView
 */

Gtk::TreeView::TreeView(GtkTreeView *tree_view, bool owns_reference)
: Container((GtkContainer*)tree_view, owns_reference)
{
}

Gtk::TreeView::TreeView()
: Container((GtkContainer*)TreeViewClass::create())
{
}

Gtk::TreeView::TreeView(TreeModel& model)
: Container((GtkContainer*)TreeViewClass::create())
{
	set_model(&model);
}

Gtk::TreeView::~TreeView() 
{
}

Gtk::TreeModel*
Gtk::TreeView::get_model() const
{
	Gtk::TreeModel *tmp_model = 0;
	GtkTreeModel *model = gtk_tree_view_get_model(gtk_tree_view());
	if (model)
	{
		G::Object *object = G::Object::pointer((GObject*)model);
		tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
	}
	return tmp_model;
}

Gtk::TreeSelection*
Gtk::TreeView::get_selection() const
{
	return G::Object::wrap<TreeSelection>(gtk_tree_view_get_selection(gtk_tree_view()));
}

Gtk::Adjustment*
Gtk::TreeView::get_hadjustment() const
{
	GtkAdjustment *hadj = gtk_tree_view_get_hadjustment(gtk_tree_view());
	return hadj ? G::Object::wrap<Adjustment>(hadj) : 0;
}

Gtk::Adjustment*
Gtk::TreeView::get_vadjustment() const
{
	GtkAdjustment *vadj = gtk_tree_view_get_vadjustment(gtk_tree_view());
	return vadj ? G::Object::wrap<Adjustment>(vadj) : 0;
}

Gtk::TreeViewColumn*
Gtk::TreeView::get_column(int position) const
{
	GtkTreeViewColumn *column = gtk_tree_view_get_column(gtk_tree_view(), position);
	return column ? G::Object::wrap<TreeViewColumn>(column) : 0;
}

bool 
Gtk::TreeView::get_columns(std::vector<TreeViewColumn*>& columns) const
{
	g_return_val_if_fail(columns.empty(), false);
	GList *first = gtk_tree_view_get_columns(gtk_tree_view());
	GList *next = first;

	while (next)
	{
		columns.push_back(G::Object::wrap<TreeViewColumn>((GtkTreeViewColumn*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !columns.empty();
}

Gtk::TreeViewColumn*
Gtk::TreeView::get_expander_column() const
{
	return G::Object::wrap<TreeViewColumn>(gtk_tree_view_get_expander_column(gtk_tree_view()));
}

bool 
Gtk::TreeView::row_expanded(const TreePath& path) const
{
	return gtk_tree_view_row_expanded(gtk_tree_view(), path.gtk_tree_path());
}

void
Gtk::TreeView::get_cursor(Pointer<TreePath> *path, TreeViewColumn **focus_column) const
{
	GtkTreePath *tmp_path = 0;
	GtkTreeViewColumn *tmp_focus_column = 0;
	gtk_tree_view_get_cursor(gtk_tree_view(), path ? &tmp_path : 0, &tmp_focus_column);

	if (path && tmp_path)
		*path = G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, tmp_path, false);

	if (focus_column && tmp_focus_column)
		*focus_column = G::Object::wrap<TreeViewColumn>(tmp_focus_column);
}

Gdk::Window*
Gtk::TreeView::get_bin_window() const
{
	return G::Object::wrap<Gdk::Window>(gtk_tree_view_get_bin_window(gtk_tree_view()));
}

bool
Gtk::TreeView::get_path_at_pos(int x, int y, Pointer<TreePath> *path, TreeViewColumn **column, int *cell_x, int *cell_y) const
{
	GtkTreePath *tmp_path = 0;
	GtkTreeViewColumn *tmp_column = 0;	
	bool result = gtk_tree_view_get_path_at_pos(gtk_tree_view(), x, y, path ? &tmp_path : 0, column ? &tmp_column : 0, cell_x, cell_y);

	if (path && tmp_path)
		*path = G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, tmp_path, false);
		
	if (column && tmp_column)
		*column = G::Object::wrap<TreeViewColumn>(tmp_column);
	return result;
}	

void
Gtk::TreeView::get_cell_area(const TreePath *path, const TreeViewColumn *column, Gdk::Rectangle& rectangle) const
{
	gtk_tree_view_get_cell_area(gtk_tree_view(), *path, *column, rectangle.gdk_rectangle());
}

Gdk::Rectangle
Gtk::TreeView::get_cell_area(const TreePath *path, const TreeViewColumn *column) const 
{
	GdkRectangle rectangle;
	gtk_tree_view_get_cell_area(gtk_tree_view(), *path, *column, &rectangle);
	return rectangle;
}

void 
Gtk::TreeView::get_background_area(const TreePath *path, const TreeViewColumn *column, Gdk::Rectangle& rectangle) const
{
	gtk_tree_view_get_background_area(gtk_tree_view(), *path, *column, rectangle.gdk_rectangle());
}

Gdk::Rectangle
Gtk::TreeView::get_background_area(const TreePath *path, const TreeViewColumn *column) const 
{
	GdkRectangle rectangle;
	gtk_tree_view_get_background_area(gtk_tree_view(), *path, *column, &rectangle);
	return rectangle;
}

void 
Gtk::TreeView::get_visible_rect(Gdk::Rectangle& visible_rect) const
{
	gtk_tree_view_get_visible_rect(gtk_tree_view(), visible_rect.gdk_rectangle());
}

Gdk::Rectangle
Gtk::TreeView::get_visible_rect() const
{
	GdkRectangle visible_rect;
	gtk_tree_view_get_visible_rect(gtk_tree_view(), &visible_rect);
	return visible_rect;
}

void
Gtk::TreeView::get_drag_dest_row(Pointer<TreePath> *path, TreeViewDropPosition *pos) const
{
	GtkTreePath *tmp_path = 0;
	gtk_tree_view_get_drag_dest_row(gtk_tree_view(), path ? &tmp_path : 0, (GtkTreeViewDropPosition*)pos);
	if (path && tmp_path)
		*path = G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, tmp_path, false);
}

bool 
Gtk::TreeView::get_dest_row_at_pos(int drag_x, int drag_y, Pointer<TreePath> *path, TreeViewDropPosition *pos) const
{
	GtkTreePath *tmp_path = 0;
	bool result = gtk_tree_view_get_dest_row_at_pos(gtk_tree_view(), drag_x, drag_y, path ? &tmp_path : 0, (GtkTreeViewDropPosition*)pos);
	if (path && tmp_path)
		*path = G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, tmp_path, false);
	return result;
}
	
void
Gtk::TreeView::set_model(TreeModel *model)
{
	gtk_tree_view_set_model(gtk_tree_view(), *model);
}

void 
Gtk::TreeView::set_hadjustment(Adjustment *adjustment)
{
	gtk_tree_view_set_hadjustment(gtk_tree_view(), *adjustment);
}

void
Gtk::TreeView::set_vadjustment(Adjustment *adjustment)
{
	gtk_tree_view_set_vadjustment(gtk_tree_view(), *adjustment);
}

int
Gtk::TreeView::append_column(TreeViewColumn& column)
{
	return gtk_tree_view_append_column(gtk_tree_view(), column.gtk_tree_view_column());
}

int
Gtk::TreeView::append_column(const char *title, CellRenderer& cell, const CellColumnAttributes& attributes)
{
	TreeViewColumn *column = new TreeViewColumn(title, cell, attributes);
	return gtk_tree_view_append_column(gtk_tree_view(), *column);
}

int
Gtk::TreeView::append_column(const String& title, CellRenderer& cell, const CellColumnAttributes& attributes)
{
	return append_column(title.c_str(), cell, attributes);
}

int
Gtk::TreeView::append_column(const char *title, CellRenderer& cell, const CellDataSlot& data)
{
	return insert_column(-1, title, cell, data);
}

int
Gtk::TreeView::append_column(const String& title, CellRenderer& cell, const CellDataSlot& data)
{
	return insert_column(-1, title.c_str(), cell, data);
}

int
Gtk::TreeView::remove_column(TreeViewColumn& column)
{
	return gtk_tree_view_remove_column(gtk_tree_view(), column.gtk_tree_view_column());
}

int
Gtk::TreeView::insert_column(TreeViewColumn& column, int position)
{
	return gtk_tree_view_insert_column(gtk_tree_view(), column.gtk_tree_view_column(), position);
}

int
Gtk::TreeView::insert_column(int position, const char *title, CellRenderer& cell, const CellColumnAttributes& attributes)
{
	TreeViewColumn *column = new TreeViewColumn(title, cell, attributes);
	return gtk_tree_view_insert_column(gtk_tree_view(), *column, position);
}

int
Gtk::TreeView::insert_column(int position, const String& title, CellRenderer& cell, const CellColumnAttributes& attributes)
{
	return insert_column(position, title.c_str(), cell, attributes);
}

namespace { // CellDataCallback

struct CellDataCallback
{
	typedef Gtk::TreeViewColumn::CellDataSlot CellDataSlot;
	CellDataSlot slot_;

	CellDataCallback(const CellDataSlot& slot)
	: slot_(slot)
	{
	}

	static void notify(GtkTreeViewColumn*, GtkCellRenderer *cell, GtkTreeModel *model, GtkTreeIter *iter, void *data)
	{
		CellDataCallback *cb = static_cast<CellDataCallback*>(data);
		G::Object *object = G::Object::pointer((GObject*)model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreeIter tmp_iter(iter);
		cb->slot_(*G::Object::wrap<Gtk::CellRenderer>(cell), *tmp_model, tmp_iter);
	}

	static void destroy(void *data)
	{
		CellDataCallback *cb = static_cast<CellDataCallback*>(data);
		delete cb;
	}
};

} // namespace

int
Gtk::TreeView::insert_column(int position, const char *title, CellRenderer& cell, const CellDataSlot& data)
{
	CellDataCallback *cb = new CellDataCallback(data);
	return gtk_tree_view_insert_column_with_data_func(gtk_tree_view(), position, title, cell.gtk_cell_renderer(),
							  &CellDataCallback::notify, cb, &CellDataCallback::destroy);
}

int
Gtk::TreeView::insert_column(int position, const String& title, CellRenderer& cell, const CellDataSlot& data)
{
	return insert_column(position, title.c_str(), cell, data);
}

void
Gtk::TreeView::move_column_after(TreeViewColumn& column, TreeViewColumn *base_column)
{
	gtk_tree_view_move_column_after(gtk_tree_view(), column.gtk_tree_view_column(), *base_column);
}

void
Gtk::TreeView::set_expander_column(TreeViewColumn *column)
{
	gtk_tree_view_set_expander_column(gtk_tree_view(), *column);
}

namespace { // ColumnDropCallback

struct ColumnDropCallback
{
	typedef Gtk::TreeView::ColumnDropSlot ColumnDropSlot;
	ColumnDropSlot slot_;

	ColumnDropCallback(const ColumnDropSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(GtkTreeView *tree_view, GtkTreeViewColumn *column, GtkTreeViewColumn *prev_column,
	                       GtkTreeViewColumn *next_column, void *data)
	{
		ColumnDropCallback *cb = static_cast<ColumnDropCallback*>(data);
		return cb->slot_(*G::Object::wrap<Gtk::TreeView>(tree_view),
				 *G::Object::wrap<Gtk::TreeViewColumn>(column),
		                 G::Object::wrap<Gtk::TreeViewColumn>(prev_column),
		                 G::Object::wrap<Gtk::TreeViewColumn>(next_column));
	}

	static void destroy(void *data)
	{
		ColumnDropCallback *cb = static_cast<ColumnDropCallback*>(data);
		delete cb;
	}
};

} // namespace

void
Gtk::TreeView::set_column_drag_function(const ColumnDropSlot& drop)
{
	ColumnDropCallback *cb = new ColumnDropCallback(drop);
	gtk_tree_view_set_column_drag_function(gtk_tree_view(), &ColumnDropCallback::notify, cb, &ColumnDropCallback::destroy);
}

void
Gtk::TreeView::scroll_to_cell(const TreePath *path, const TreeViewColumn *column)
{
	gtk_tree_view_scroll_to_cell(gtk_tree_view(), *path, *column, false, 0.0, 0.0);
}

void
Gtk::TreeView::scroll_to_cell(const TreePath *path, const TreeViewColumn *column, float row_align, float col_align)
{
	gtk_tree_view_scroll_to_cell(gtk_tree_view(), *path, *column, true, row_align, col_align);
}

void
Gtk::TreeView::row_activated(TreePath& path, TreeViewColumn& column)
{
	gtk_tree_view_row_activated(gtk_tree_view(), path.gtk_tree_path(), column.gtk_tree_view_column());
}

void
Gtk::TreeView::expand_to_path(const TreePath& path)
{
	gtk_tree_view_expand_to_path(gtk_tree_view(), path.gtk_tree_path());
}

bool
Gtk::TreeView::expand_row(const TreePath& path, bool open_all)
{
	return gtk_tree_view_expand_row(gtk_tree_view(), path.gtk_tree_path(), open_all);
}

bool
Gtk::TreeView::collapse_row(const TreePath& path)
{
	return gtk_tree_view_collapse_row(gtk_tree_view(), path.gtk_tree_path());
}

namespace { // mapping_slot_callback

void mapping_slot_callback(GtkTreeView *tree_view, GtkTreePath *path, gpointer data)
{
	Gtk::TreeView::MappingSlot& slot = *static_cast<Gtk::TreeView::MappingSlot*>(data);
	Gtk::TreePath tmp_path(path);
	slot(*G::Object::wrap<Gtk::TreeView>(tree_view), tmp_path);
}

} // namespace

void
Gtk::TreeView::map_expanded_rows(const MappingSlot& map)
{
	MappingSlot tmp_map(map);
	gtk_tree_view_map_expanded_rows(gtk_tree_view(), &mapping_slot_callback, &tmp_map);
}

void
Gtk::TreeView::set_cursor(const TreePath& path, TreeViewColumn *focus_column, bool start_editing)
{
	gtk_tree_view_set_cursor(gtk_tree_view(), path.gtk_tree_path(), *focus_column, start_editing);
}

void
Gtk::TreeView::set_cursor_on_cell(const TreePath& path, TreeViewColumn *focus_column, CellRenderer *focus_cell, bool start_editing)
{
	gtk_tree_view_set_cursor_on_cell(gtk_tree_view(), path.gtk_tree_path(), *focus_column, *focus_cell, start_editing);
}

void
Gtk::TreeView::enable_model_drag_source(Gdk::ModifierTypeField start_button_mask, const std::vector<TargetEntry>& targets, Gdk::DragActionField actions)
{
	g_return_if_fail(!targets.empty());
	int count = targets.size();
	GtkTargetEntry *tmp_targets = new GtkTargetEntry[count];

	int i = 0;
	while (i < count)
	{
		tmp_targets[i] = *(targets[i].gtk_target_entry());
		++i;
	}

	gtk_tree_view_enable_model_drag_source(gtk_tree_view(), (GdkModifierType)start_button_mask, tmp_targets, count, (GdkDragAction)actions);
	delete [] tmp_targets;
}

void
Gtk::TreeView::enable_model_drag_dest(const std::vector<TargetEntry>& targets, Gdk::DragActionField actions)
{
	g_return_if_fail(!targets.empty());
	int count = targets.size();
	GtkTargetEntry *tmp_targets = new GtkTargetEntry[count];

	int i = 0;
	while (i < count)
	{
		tmp_targets[i] = *(targets[i].gtk_target_entry());
		++i;
	}

	gtk_tree_view_enable_model_drag_dest(gtk_tree_view(), tmp_targets, count, (GdkDragAction)actions);
	delete [] tmp_targets;
}

void
Gtk::TreeView::set_drag_dest_row(const TreePath& path, TreeViewDropPosition pos)
{
	gtk_tree_view_set_drag_dest_row(gtk_tree_view(), path.gtk_tree_path(), (GtkTreeViewDropPosition)pos);
}

Pointer<Gdk::Pixmap>
Gtk::TreeView::create_row_drag_icon(const TreePath& path)
{
	return G::Object::wrap_new<Gdk::Pixmap>(gtk_tree_view_create_row_drag_icon(gtk_tree_view(), path.gtk_tree_path()), true);
}

namespace { // SearchEqualCallback

struct SearchEqualCallback
{
	typedef Gtk::TreeView::SearchEqualSlot SearchEqualSlot;
	SearchEqualSlot slot_;

	SearchEqualCallback(const SearchEqualSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(GtkTreeModel *model, int column, const char *key, GtkTreeIter *iter, void *data)
	{
		SearchEqualCallback *cb = static_cast<SearchEqualCallback*>(data);
		G::Object *object = G::Object::pointer((GObject*)model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreeIter tmp_iter(iter);
		return cb->slot_(*tmp_model, column, key, tmp_iter);
	}

	static void destroy(void *data)
	{
		SearchEqualCallback *cb = static_cast<SearchEqualCallback*>(data);
		delete cb;
	}
};

} // namespace

void 
Gtk::TreeView::set_fixed_height_mode(bool enable)
{
	gtk_tree_view_set_fixed_height_mode(gtk_tree_view(), enable);
}

void 
Gtk::TreeView::set_hover_selection(bool hover)
{
	gtk_tree_view_set_hover_selection(gtk_tree_view(), hover);
}
		
void 
Gtk::TreeView::set_hover_expand(bool expand)
{
	gtk_tree_view_set_hover_expand(gtk_tree_view(), expand);
}

namespace { // RowSeparatorCallback

struct RowSeparatorCallback
{
	typedef Gtk::TreeView::RowSeparatorSlot RowSeparatorSlot;
	RowSeparatorSlot slot_;

	RowSeparatorCallback(const RowSeparatorSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(GtkTreeModel *model, GtkTreeIter *iter, void *data)
	{
		RowSeparatorCallback *cb = static_cast<RowSeparatorCallback*>(data);
		G::Object *object = G::Object::pointer((GObject*)model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreeIter tmp_iter(iter);
		return cb->slot_(*tmp_model, tmp_iter);
	}

	static void destroy(void *data)
	{
		RowSeparatorCallback *cb = static_cast<RowSeparatorCallback*>(data);
		delete cb;
	}
};

} // namespace

void 
Gtk::TreeView::set_row_separator_func(const RowSeparatorSlot& slot)
{
	RowSeparatorCallback *cb = new RowSeparatorCallback(slot);
	gtk_tree_view_set_row_separator_func(gtk_tree_view(), &RowSeparatorCallback::notify, cb, &RowSeparatorCallback::destroy);
}

void  
Gtk::TreeView::unset_row_separator_func()
{
	gtk_tree_view_set_row_separator_func(gtk_tree_view(), 0, 0, 0);
}

void
Gtk::TreeView::set_search_equal_func(const SearchEqualSlot& search_equal)
{
	SearchEqualCallback *cb = new SearchEqualCallback(search_equal);
	gtk_tree_view_set_search_equal_func(gtk_tree_view(), &SearchEqualCallback::notify, cb, &SearchEqualCallback::destroy);
}

/*  Gtk::TreeViewClass
 */

void
Gtk::TreeViewClass::init(GtkTreeViewClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
	g_class->set_scroll_adjustments = &set_scroll_adjustments_proxy;
	g_class->row_activated = &row_activated_proxy;
	g_class->test_expand_row = &test_expand_row_proxy;
	g_class->test_collapse_row = &test_collapse_row_proxy;
	g_class->row_expanded = &row_expanded_proxy;
	g_class->row_collapsed = &row_collapsed_proxy;
	g_class->columns_changed = &columns_changed_proxy;
	g_class->cursor_changed = &cursor_changed_proxy;
}

GtkTreeViewClass*
Gtk::TreeViewClass::get_parent_class(void *instance)
{
	return static_cast<GtkTreeViewClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::TreeViewClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TREE_VIEW, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TreeViewClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::TreeViewClass::set_scroll_adjustments_proxy(GtkTreeView *tree_view, GtkAdjustment *hadjustment, GtkAdjustment *vadjustment)
{
	TreeViewSignals *signals = dynamic_cast<TreeViewSignals*>(G::ObjectSignals::pointer((GObject*)tree_view));
	if (signals)
		signals->on_set_scroll_adjustments(G::Object::wrap<Adjustment>(hadjustment),
		                                   G::Object::wrap<Adjustment>(vadjustment));
	else
	{
		GtkTreeViewClass *g_class = get_parent_class(tree_view);
		if (g_class && g_class->set_scroll_adjustments)
			g_class->set_scroll_adjustments(tree_view, hadjustment, vadjustment);
	}
}

void
Gtk::TreeViewClass::row_activated_proxy(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column)
{
	TreeViewSignals *signals = dynamic_cast<TreeViewSignals*>(G::ObjectSignals::pointer((GObject*)tree_view));
	if (signals)
	{
		TreePath tmp_path(path);
		signals->on_row_activated(tmp_path, *G::Object::wrap<TreeViewColumn>(column));
	}
	else
	{
		GtkTreeViewClass *g_class = get_parent_class(tree_view);
		if (g_class && g_class->row_activated)
			g_class->row_activated(tree_view, path, column);
	}
}

gboolean
Gtk::TreeViewClass::test_expand_row_proxy(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path)
{
	gboolean result = FALSE;
	TreeViewSignals *signals = dynamic_cast<TreeViewSignals*>(G::ObjectSignals::pointer((GObject*)tree_view));
	if (signals)
	{
		TreeIter tmp_iter(iter);
		TreePath tmp_path(path);
		result = signals->on_test_expand_row(tmp_iter, tmp_path);
	}
	else
	{
		GtkTreeViewClass *g_class = get_parent_class(tree_view);
		if (g_class && g_class->test_expand_row)
			result = g_class->test_expand_row(tree_view, iter, path);
	}
	return result;
}

gboolean
Gtk::TreeViewClass::test_collapse_row_proxy(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path)
{
	gboolean result = FALSE;
	TreeViewSignals *signals = dynamic_cast<TreeViewSignals*>(G::ObjectSignals::pointer((GObject*)tree_view));
	if (signals)
	{
		TreeIter tmp_iter(iter);
		TreePath tmp_path(path);
		result = signals->on_test_collapse_row(tmp_iter, tmp_path);
	}
	else
	{
		GtkTreeViewClass *g_class = get_parent_class(tree_view);
		if (g_class && g_class->test_collapse_row)
			result = g_class->test_collapse_row(tree_view, iter, path);
	}
	return result;
}

void
Gtk::TreeViewClass::row_expanded_proxy(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path)
{
	TreeViewSignals *signals = dynamic_cast<TreeViewSignals*>(G::ObjectSignals::pointer((GObject*)tree_view));
	if (signals)
	{
		TreeIter tmp_iter(iter);
		TreePath tmp_path(path);
		signals->on_row_expanded(tmp_iter, tmp_path);
	}
	else
	{
		GtkTreeViewClass *g_class = get_parent_class(tree_view);
		if (g_class && g_class->row_expanded)
			g_class->row_expanded(tree_view, iter, path);
	}
}

void
Gtk::TreeViewClass::row_collapsed_proxy(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path)
{
	TreeViewSignals *signals = dynamic_cast<TreeViewSignals*>(G::ObjectSignals::pointer((GObject*)tree_view));
	if (signals)
	{
		TreeIter tmp_iter(iter);
		TreePath tmp_path(path);
		signals->on_row_collapsed(tmp_iter, tmp_path);
	}
	else
	{
		GtkTreeViewClass *g_class = get_parent_class(tree_view);
		if (g_class && g_class->row_collapsed)
			g_class->row_collapsed(tree_view, iter, path);
	}
}

void
Gtk::TreeViewClass::columns_changed_proxy(GtkTreeView *tree_view)
{
	TreeViewSignals *signals = dynamic_cast<TreeViewSignals*>(G::ObjectSignals::pointer((GObject*)tree_view));
	if (signals)
		signals->on_columns_changed();
	else
	{
		GtkTreeViewClass *g_class = get_parent_class(tree_view);
		if (g_class && g_class->columns_changed)
			g_class->columns_changed(tree_view);
	}
}

void
Gtk::TreeViewClass::cursor_changed_proxy(GtkTreeView *tree_view)
{
	TreeViewSignals *signals = dynamic_cast<TreeViewSignals*>(G::ObjectSignals::pointer((GObject*)tree_view));
	if (signals)
		signals->on_cursor_changed();
	else
	{
		GtkTreeViewClass *g_class = get_parent_class(tree_view);
		if (g_class && g_class->cursor_changed)
			g_class->cursor_changed(tree_view);
	}
}

/*  Gtk::TreeView signals
 */

const Gtk::TreeView::SetScrollAdjustmentsSignalType Gtk::TreeView::set_scroll_adjustments_signal("set_scroll_adjustments", (GCallback)&Marshal::void_adjustment_adjustment_callback);

const Gtk::TreeView::RowActivatedSignalType Gtk::TreeView::row_activated_signal("row_activated", (GCallback)&Marshal::void_treepath_treeviewcolumn_callback);

const Gtk::TreeView::TestExpandRowSignalType Gtk::TreeView::test_expand_row_signal("test_expand_row", (GCallback)&Marshal::bool_treeiter_treepath_callback);

const Gtk::TreeView::TestCollapseRowSignalType Gtk::TreeView::test_collapse_row_signal("test_collapse_row", (GCallback)&Marshal::bool_treeiter_treepath_callback);

const Gtk::TreeView::RowExpandedSignalType Gtk::TreeView::row_expanded_signal("row_expanded", (GCallback)&Marshal::void_treeiter_treepath_callback);

const Gtk::TreeView::RowCollapsedSignalType Gtk::TreeView::row_collapsed_signal("row_collapsed", (GCallback)&Marshal::void_treeiter_treepath_callback);

const Gtk::TreeView::ColumnsChangedSignalType Gtk::TreeView::columns_changed_signal("columns_changed", (GCallback)&G::Marshal::void_callback);

const Gtk::TreeView::CursorChangedSignalType Gtk::TreeView::cursor_changed_signal("cursor_changed", (GCallback)&G::Marshal::void_callback);

