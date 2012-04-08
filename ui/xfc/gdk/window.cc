/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  window.cc - GdkGeometry, GdkWindowAttr and GdkWindow C++ wrapper implementation
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
 
#include "window.hh"
#include "private/windowclass.hh"
#include "bitmap.hh"
#include "color.hh"
#include "cursor.hh"
#include "display.hh"
#include "pixmap.hh"
#include "region.hh"
#include "screen.hh"
#include "visual.hh"
#include "../gdk-pixbuf/pixbuf.hh"
#include <gdk/gdkx.h>
#include <cstring>

using namespace Xfc;

/*  Gdk::get_default_root_window
 */

Gdk::Window*
Gdk::get_default_root_window()
{
	return G::Object::wrap<Window>(gdk_get_default_root_window());
}

/*  Gdk::Geometry
 */

Gdk::Geometry::Geometry()
: mask_(0)
{
	memset(&geometry_, 0, sizeof(GdkGeometry));
}

void
Gdk::Geometry::set_min_size(int width, int height)
{
	geometry_.min_width = width;
	geometry_.min_height = height;
	mask_ |= GDK_HINT_MIN_SIZE;
}

void
Gdk::Geometry::set_max_size(int width, int height)
{
	geometry_.max_width = width;
	geometry_.max_height = height;
	mask_ |= GDK_HINT_MAX_SIZE;
}

void
Gdk::Geometry::set_base_size(int width, int height)
{
	geometry_.base_width = width;
	geometry_.base_height = height;
	mask_ |= GDK_HINT_BASE_SIZE;
}

void
Gdk::Geometry::set_resize_increments(int width_inc, int height_inc)
{
	geometry_.width_inc = width_inc;
	geometry_.height_inc = height_inc;
	mask_ |= GDK_HINT_RESIZE_INC;
}

void
Gdk::Geometry::set_aspect_range(double min_aspect_ratio, double max_aspect_ratio)
{
	geometry_.min_aspect = min_aspect_ratio;
	geometry_.max_aspect = max_aspect_ratio;
	mask_ |= GDK_HINT_ASPECT;
}

/*  Gdk::WindowAttr
 */

Gdk::WindowAttr::WindowAttr(int width, int height, WindowType type, EventMaskField event_mask)
: mask_(0)
{
	set_size(width, height);
	attr_.window_type = (GdkWindowType)type;
	attr_.wclass = GDK_INPUT_OUTPUT;
	attr_.event_mask = (int)event_mask;
}

Gdk::WindowAttr::WindowAttr(int x, int y, int width, int height, WindowType type, EventMaskField event_mask)
: mask_(0)
{
	set_allocation(x, y, width, height);
	attr_.wclass = GDK_INPUT_OUTPUT;
	attr_.window_type = (GdkWindowType)type;
	attr_.event_mask = (int)event_mask;
}

Gdk::WindowAttr::WindowAttr(const Rectangle& allocation, WindowType type, EventMaskField event_mask)
: mask_(0)
{
	set_allocation(allocation);
	attr_.wclass = GDK_INPUT_OUTPUT;
	attr_.window_type = (GdkWindowType)type;
	attr_.event_mask = (int)event_mask;
}

void
Gdk::WindowAttr::set_title(const String& title)
{
	attr_.title = const_cast<char*>(title.c_str());
	mask_ |= GDK_WA_TITLE;
}

void
Gdk::WindowAttr::set_position(int x, int y)
{
	attr_.x = x;
	attr_.y = y;
	mask_ |= (GDK_WA_X | GDK_WA_Y);
}

void
Gdk::WindowAttr::set_allocation(int x, int y, int width, int height)
{
	attr_.x = x;
	attr_.y = y;
	attr_.width = width;
	attr_.height = height;
	mask_ |= (GDK_WA_X | GDK_WA_Y);
}

void
Gdk::WindowAttr::set_allocation(const Rectangle& allocation)
{
	attr_.x = allocation.x();
	attr_.y = allocation.y();
	attr_.width = allocation.width();
	attr_.height = allocation.height();
	mask_ |= (GDK_WA_X | GDK_WA_Y);
}

void
Gdk::WindowAttr::set_cursor(const Cursor& cursor)
{
	attr_.cursor = cursor.gdk_cursor();
	mask_ |= GDK_WA_CURSOR;
}

void
Gdk::WindowAttr::set_visual(const Visual& visual)
{
	attr_.visual = visual.gdk_visual();
	mask_ |= GDK_WA_VISUAL;
}

void
Gdk::WindowAttr::set_colormap(const Colormap& colormap)
{
	attr_.colormap = colormap.gdk_colormap();
	mask_ |= GDK_WA_COLORMAP;
}

/*  Gdk::Window
 */

Gdk::Window::Window(GdkWindow *window, bool owns_reference)
: Drawable((GdkDrawable*)window, owns_reference)
{
}

Gdk::Window::Window(const WindowAttr& attributes)
: Drawable((GdkDrawable*)gdk_window_new(0, attributes.gdk_window_attr(), attributes.mask()))
{
}

Gdk::Window::Window(const Window& parent, const WindowAttr& attributes)
: Drawable((GdkDrawable*)gdk_window_new(parent.gdk_window(), attributes.gdk_window_attr(), attributes.mask()))
{
}
	
Gdk::Window::~Window() 
{
}
	
Pointer<Gdk::Window>
Gdk::Window::create(GdkNativeWindow anid, const Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	return new Window(gdk_window_foreign_new_for_display(tmp_display, anid));
}

Gdk::Window*
Gdk::Window::lookup(GdkNativeWindow anid, const Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	return G::Object::wrap<Window>((GdkWindow*)gdk_xid_table_lookup_for_display(tmp_display, anid));
}

Gdk::Window*
Gdk::Window::at_pointer(int *win_x, int *win_y, const Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	return G::Object::wrap<Window>(gdk_display_get_window_at_pointer(tmp_display, win_x, win_y));
}

Gdk::Window*
Gdk::Window::at_pointer(Point& point, const Display *display)
{
	int x, y;
	Gdk::Window *window = at_pointer(&x, &y, display);
	point.set(x, y);
	return window;
}

void
Gdk::Window::get_geometry(Rectangle& rectangle, int *depth) const
{
	GdkRectangle tmp;
	gdk_window_get_geometry(gdk_window(), &tmp.x, &tmp.y, &tmp.width, &tmp.height, depth);
	rectangle.set(tmp.x, tmp.y, tmp.width, tmp.height);
}

Gdk::Point
Gdk::Window::get_position() const
{
	GdkPoint point;
	gdk_window_get_position(gdk_window(), &point.x, &point.y);
	return point;
}

Gdk::Point
Gdk::Window::get_origin() const
{
	GdkPoint point;
	gdk_window_get_origin(gdk_window(), &point.x, &point.y);
	return point;
}

Gdk::Point
Gdk::Window::get_root_origin() const
{
	GdkPoint point;
	gdk_window_get_root_origin(gdk_window(), &point.x, &point.y);
	return point;
}

Gdk::Window*
Gdk::Window::get_pointer(int *x, int *y, ModifierTypeField *mask) const
{
	GdkWindow *window = gdk_window_get_pointer(gdk_window(), x, y, (GdkModifierType*)mask);
	return window ? G::Object::wrap<Window>(window) : 0;
}

Gdk::Window*
Gdk::Window::get_parent() const
{
	GdkWindow *window = gdk_window_get_parent(gdk_window());
	return window ? G::Object::wrap<Window>(window) : 0;
}

Gdk::Window*
Gdk::Window::get_toplevel() const
{
	return G::Object::wrap<Window>(gdk_window_get_toplevel(gdk_window()));
}

bool
Gdk::Window::get_children(std::vector<Window*>& child_list) const
{
	g_return_val_if_fail(child_list.empty(), false);
	GList *first = gdk_window_get_children(gdk_window());
	GList *next = first;
	
	while (next)
	{
		child_list.push_back(G::Object::wrap<Gdk::Window>((GdkWindow*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !child_list.empty();
}

bool
Gdk::Window::get_toplevels(std::vector<Window*>& toplevels)
{
	Screen *screen = Screen::get_default();
	return screen->get_toplevels(toplevels);
}

Gdk::Window* 
Gdk::Window::get_group() const
{
	GdkWindow *window = gdk_window_get_group(gdk_window());
	return window ? G::Object::wrap<Window>(window) : 0;
}

Pointer<Gdk::Region>
Gdk::Window::get_update_area() const
{
	return new Region(gdk_window_get_update_area(gdk_window()), false);
}

Gdk::Rectangle
Gdk::Window::get_frame_extents() const
{
	GdkRectangle rectangle;
	gdk_window_get_frame_extents(gdk_window(), &rectangle);
	return rectangle;
}

void 
Gdk::Window::get_frame_extents(Rectangle& rectangle) const
{
	gdk_window_get_frame_extents(gdk_window(), rectangle.gdk_rectangle());
}

void
Gdk::Window::move(const Point& point)
{
	gdk_window_move(gdk_window(), point.x(), point.y());
}

void
Gdk::Window::move_resize(const Rectangle& rectangle)
{
	gdk_window_move_resize(gdk_window(), rectangle.x(), rectangle.y(), rectangle.width(), rectangle.height());
}

void 
Gdk::Window::reparent(Window& new_parent, int x, int y)
{
	gdk_window_reparent(gdk_window(), new_parent.gdk_window(), x, y);
}
	
void
Gdk::Window::clear_area(int x, int y, int width, int height, bool generate_expose)
{
	if (!generate_expose)
		gdk_window_clear_area(gdk_window(), x, y, width, height);
	else
		gdk_window_clear_area_e(gdk_window(), x, y, width, height);
}

void 
Gdk::Window::clear_area(const Rectangle& rectangle, bool generate_expose)
{
	if (!generate_expose)
		gdk_window_clear_area(gdk_window(), rectangle.x(), rectangle.y(), rectangle.width(), rectangle.height());
	else
		gdk_window_clear_area_e(gdk_window(), rectangle.x(), rectangle.y(), rectangle.width(), rectangle.height());
}

void
Gdk::Window::add_filter(Window *window, GdkFilterFunc function, void *data)
{
	gdk_window_add_filter(*window, function, data);
}

void
Gdk::Window::remove_filter(Window *window, GdkFilterFunc function, void *data)
{
	gdk_window_remove_filter(*window, function, data);
}

void
Gdk::Window::shape_combine_mask(Bitmap *shape_mask, int x, int y)
{
	gdk_window_shape_combine_mask(gdk_window(), shape_mask->gdk_bitmap(), x, y);
}

void
Gdk::Window::shape_combine_region(Region *shape_region, int offset_x, int offset_y)
{
	gdk_window_shape_combine_region(gdk_window(), *shape_region, offset_x, offset_y);
}

void
Gdk::Window::set_geometry_hints(const Geometry *geometry)
{
	GdkGeometry *tmp_geometry = geometry ? geometry->gdk_geometry() : 0;
	unsigned int hints_mask = geometry ? geometry->gdk_window_hints() :0;
	gdk_window_set_geometry_hints(gdk_window(), tmp_geometry, (GdkWindowHints)hints_mask);
}

void
Gdk::Window::begin_paint(const Rectangle& rectangle)
{
	gdk_window_begin_paint_rect(gdk_window(), rectangle.gdk_rectangle());
}

void
Gdk::Window::begin_paint(const Region& region)
{
	gdk_window_begin_paint_region(gdk_window(), region.gdk_region());
}

void
Gdk::Window::set_title(const String& title)
{
	gdk_window_set_title(gdk_window(), title.c_str());
}

void
Gdk::Window::set_role(const String& role)
{
	gdk_window_set_role(gdk_window(), role.c_str());
}

void
Gdk::Window::set_transient_for(Window& parent)
{
	gdk_window_set_transient_for(gdk_window(), parent);
}

void
Gdk::Window::set_background(const Color& color)
{
	gdk_window_set_background(gdk_window(), color.gdk_color());
}

void
Gdk::Window::set_back_pixmap(Pixmap *pixmap, bool parent_relative)
{
	gdk_window_set_back_pixmap(gdk_window(), *pixmap, parent_relative);
}

void
Gdk::Window::set_cursor(const Cursor& cursor)
{
	gdk_window_set_cursor(gdk_window(), cursor.gdk_cursor());
}

void
Gdk::Window::set_icon_list(const std::vector<Pixbuf*>& pixbufs)
{
	g_return_if_fail(!pixbufs.empty());
	GList *tmp_pixbufs = 0;
	int count = pixbufs.size();

	int i = 0;
	while (i < count)
	{
		tmp_pixbufs = g_list_append(tmp_pixbufs, pixbufs[i]->gdk_pixbuf());
		++i;
	}

	gdk_window_set_icon_list(gdk_window(), tmp_pixbufs);
	g_list_free(tmp_pixbufs);
}

void
Gdk::Window::set_icon(Pixmap *pixmap, Bitmap *mask, Window *icon_window)
{
	gdk_window_set_icon(gdk_window(), icon_window ? icon_window->gdk_window() : 0, pixmap->gdk_pixmap(), mask->gdk_bitmap());
}

void
Gdk::Window::set_icon_name(const String& name)
{
	gdk_window_set_icon_name(gdk_window(), name.c_str());
}

void
Gdk::Window::set_group(Window& leader)
{
	gdk_window_set_group(gdk_window(), leader.gdk_window());
}

void
Gdk::Window::invalidate(const Rectangle& rectangle, bool invalidate_children)
{
	gdk_window_invalidate_rect(gdk_window(), rectangle.gdk_rectangle(), invalidate_children);
}

void
Gdk::Window::invalidate(const Region& region, bool invalidate_children)
{
	gdk_window_invalidate_region(gdk_window(), region.gdk_region(), invalidate_children);
}

Gdk::GrabStatus
Gdk::Window::pointer_grab(EventMaskField event_mask, Window *confine_to, Cursor *cursor,
                          bool owner_events, unsigned int time)
{
	return (GrabStatus)gdk_pointer_grab(gdk_window(), owner_events, (GdkEventMask)event_mask,
	                                         *confine_to, *cursor, time);
}

/*  Gdk::WindowClass
 */

void
Gdk::WindowClass::init(GdkWindowClass *g_class)
{
	DrawableClass::init((GdkDrawableClass*)g_class);
}

GType
Gdk::WindowClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_WINDOW, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::WindowClass::create()
{
	return g_object_new(get_type(), 0);
}

