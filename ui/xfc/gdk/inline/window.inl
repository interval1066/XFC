/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  window.inl - Gdk::Geometry, Gdk::WindowAttr and Gdk::Window inline functions
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

/*  Gdk::Geometry
 */

inline GdkGeometry*
Xfc::Gdk::Geometry::gdk_geometry() const
{
	return const_cast<GdkGeometry*>(&geometry_);
}

inline GdkWindowHints
Xfc::Gdk::Geometry::gdk_window_hints () const
{
	return (GdkWindowHints)mask_;
}

inline int
Xfc::Gdk::Geometry::min_width() const
{
	return geometry_.min_width;
}

inline int
Xfc::Gdk::Geometry::min_height() const
{
	return geometry_.min_height;
}

inline int
Xfc::Gdk::Geometry::max_width() const
{
	return geometry_.max_width;
}

inline int
Xfc::Gdk::Geometry::max_height() const
{
	return geometry_.max_height;
}

inline int
Xfc::Gdk::Geometry::base_width() const
{
	return geometry_.base_width;
}

inline int
Xfc::Gdk::Geometry::base_height() const
{
	return geometry_.base_height;
}

inline int
Xfc::Gdk::Geometry::width_increment() const
{
	return geometry_.width_inc;
}

inline int
Xfc::Gdk::Geometry::height_increment() const
{
	return geometry_.height_inc;
}

inline double
Xfc::Gdk::Geometry::min_aspect_ratio() const
{
	return geometry_.min_aspect;
}

inline double
Xfc::Gdk::Geometry::max_aspect_ratio() const
{
	return geometry_.max_aspect;
}

inline bool
Xfc::Gdk::Geometry::min_size_set() const
{
	return (mask_ & GDK_HINT_MIN_SIZE) != 0;
}

inline bool
Xfc::Gdk::Geometry::max_size_set() const
{
	return (mask_ & GDK_HINT_MAX_SIZE) != 0;
}

inline bool
Xfc::Gdk::Geometry::base_size_set() const
{
	return (mask_ & GDK_HINT_BASE_SIZE) != 0;
}

inline bool
Xfc::Gdk::Geometry::aspect_range_set() const
{
        return (mask_ & GDK_HINT_ASPECT) != 0;
}

inline bool
Xfc::Gdk::Geometry::resize_increments_set() const
{
        return (mask_ & GDK_HINT_RESIZE_INC) != 0;
}

inline void
Xfc::Gdk::Geometry::unset_min_size()
{
	mask_ &= ~GDK_HINT_MIN_SIZE;
}

inline void
Xfc::Gdk::Geometry::unset_max_size()
{
	mask_ &= ~GDK_HINT_MAX_SIZE;
}

inline void
Xfc::Gdk::Geometry::unset_base_size()
{
	mask_ &= ~GDK_HINT_BASE_SIZE;
}

inline void
Xfc::Gdk::Geometry::unset_resize_increments()
{
	mask_ &= ~GDK_HINT_RESIZE_INC;
}

inline void
Xfc::Gdk::Geometry::unset_aspect_range()
{
	mask_ &= ~GDK_HINT_ASPECT;
}

inline void
Xfc::Gdk::Geometry::constrain_size(unsigned int flags, int width, int height, int *new_width, int *new_height)
{
	gdk_window_constrain_size(&geometry_, mask_, width, height, new_width, new_height);
}

/*  Gdk::WindowAttr
 */

inline GdkWindowAttr*
Xfc::Gdk::WindowAttr::gdk_window_attr() const
{
	return const_cast<GdkWindowAttr*>(&attr_);
}

inline void
Xfc::Gdk::WindowAttr::set_type(WindowType type)
{
	attr_.window_type = (GdkWindowType)type;
}

inline void
Xfc::Gdk::WindowAttr::set_events(EventMaskField event_mask)
{
	attr_.event_mask = (int)event_mask;
}

inline void
Xfc::Gdk::WindowAttr::set_size(int width, int height)
{
	attr_.width = width;
	attr_.height = height;
}

inline void
Xfc::Gdk::WindowAttr::set_input_only()
{
	attr_.wclass = GDK_INPUT_ONLY;
}

inline void
Xfc::Gdk::WindowAttr::set_override_redirect()
{
	attr_.override_redirect = TRUE;
	mask_ |= GDK_WA_NOREDIR;
}

/*  Gdk::Window
 */

inline GdkWindow*
Xfc::Gdk::Window::gdk_window() const
{
	return reinterpret_cast<GdkWindow*>(instance_);
}

inline GdkWindowObject*
Xfc::Gdk::Window::gdk_window_object() const
{
	return GDK_WINDOW_OBJECT(instance_);
}

inline
Xfc::Gdk::Window::operator GdkWindow* () const
{
	return this ? gdk_window() : 0;
}

inline Xfc::Gdk::WindowType
Xfc::Gdk::Window::get_window_type() const
{
	return (WindowType)gdk_window_get_window_type(gdk_window());
}

inline bool
Xfc::Gdk::Window::is_visible() const
{
	return gdk_window_is_visible((GdkWindow*)instance_);
}

inline bool
Xfc::Gdk::Window::is_viewable() const
{
	return gdk_window_is_viewable(gdk_window());
}

inline Xfc::Gdk::WindowState
Xfc::Gdk::Window::get_state() const
{
	return (WindowState)gdk_window_get_state(gdk_window());
}

inline void
Xfc::Gdk::Window::get_user_data(void *&data) const
{
	gdk_window_get_user_data(gdk_window(), &data);
}

inline void
Xfc::Gdk::Window::get_geometry(int *x, int *y, int *width, int *height, int *depth) const
{
	gdk_window_get_geometry(gdk_window(), x, y, width, height, depth);
}

inline void
Xfc::Gdk::Window::get_position(int *x, int *y) const
{
	gdk_window_get_position(gdk_window(), x, y);
}

inline bool
Xfc::Gdk::Window::get_origin(int *x, int *y) const
{
	return gdk_window_get_origin(gdk_window(), x, y);
}

inline void
Xfc::Gdk::Window::get_root_origin(int *x, int *y) const
{
	gdk_window_get_root_origin(gdk_window(), x, y);
}

inline Xfc::Gdk::EventMaskField
Xfc::Gdk::Window::get_events() const
{
	return (EventMaskField)gdk_window_get_events(gdk_window());
}

inline bool
Xfc::Gdk::Window::get_decorations(WMDecorationField *decorations) const
{
	return gdk_window_get_decorations(gdk_window(), (GdkWMDecoration*)decorations);
}

inline void
Xfc::Gdk::Window::dispose()
{
	gdk_window_destroy(gdk_window());
}

inline void
Xfc::Gdk::Window::show()
{
	gdk_window_show(gdk_window());
}

inline void
Xfc::Gdk::Window::hide()
{
	gdk_window_hide(gdk_window());
}

inline void
Xfc::Gdk::Window::withdraw()
{
	gdk_window_withdraw(gdk_window());
}

inline void
Xfc::Gdk::Window::show_unraised()
{
	gdk_window_show_unraised(gdk_window());
}

inline void
Xfc::Gdk::Window::move(int x, int y)
{
	gdk_window_move(gdk_window(), x, y);
}

inline void
Xfc::Gdk::Window::resize(int width, int height)
{
	gdk_window_resize(gdk_window(), width, height);
}

inline void
Xfc::Gdk::Window::move_resize(int x, int y, int width, int height)
{
	gdk_window_move_resize(gdk_window(), x, y, width, height);
}

inline void
Xfc::Gdk::Window::clear()
{
	gdk_window_clear(gdk_window());
}

inline void
Xfc::Gdk::Window::raise()
{
	gdk_window_raise(gdk_window());
}

inline void
Xfc::Gdk::Window::lower()
{
	gdk_window_lower(gdk_window());
}

inline void
Xfc::Gdk::Window::focus(unsigned int timestamp)
{
	gdk_window_focus(gdk_window(), timestamp);
}

inline void
Xfc::Gdk::Window::set_user_data(void *user_data)
{
	gdk_window_set_user_data(gdk_window(), user_data);
}

inline void
Xfc::Gdk::Window::set_override_redirect(bool override_redirect)
{
	gdk_window_set_override_redirect(gdk_window(), override_redirect);
}

inline void 
Xfc::Gdk::Window::set_accept_focus(bool accept_focus)
{
	gdk_window_set_accept_focus(gdk_window(), accept_focus);
}

inline void 
Xfc::Gdk::Window::set_focus_on_map(bool focus_on_map)
{	
	gdk_window_set_focus_on_map(gdk_window(), focus_on_map);
}

inline void
Xfc::Gdk::Window::scroll(int dx, int dy)
{
	gdk_window_scroll(gdk_window(), dx, dy);
}

inline void
Xfc::Gdk::Window::set_child_shapes()
{
	gdk_window_set_child_shapes(gdk_window());
}

inline void
Xfc::Gdk::Window::merge_child_shapes()
{
	gdk_window_merge_child_shapes(gdk_window());
}

inline bool
Xfc::Gdk::Window::set_static_gravities(bool use_static)
{
	return gdk_window_set_static_gravities(gdk_window(), use_static);
}

inline void
Xfc::Gdk::Window::set_type_hint(WindowTypeHint hint)
{
	gdk_window_set_type_hint(gdk_window(), (GdkWindowTypeHint)hint);
}

inline void
Xfc::Gdk::Window::set_modal_hint(bool modal)
{
	gdk_window_set_modal_hint(gdk_window(), modal);
}

inline void
Xfc::Gdk::Window::set_skip_taskbar_hint(bool skips_taskbar)
{
	gdk_window_set_skip_taskbar_hint(gdk_window(), skips_taskbar);
}

inline void
Xfc::Gdk::Window::set_skip_pager_hint(bool skips_pager)
{
	gdk_window_set_skip_pager_hint(gdk_window(), skips_pager);
}

inline void
Xfc::Gdk::Window::end_paint()
{
	gdk_window_end_paint(gdk_window());
}

inline void
Xfc::Gdk::Window::set_title(const char *title)
{
	gdk_window_set_title(gdk_window(), title);
}

inline void
Xfc::Gdk::Window::set_role(const char *role)
{
	gdk_window_set_role(gdk_window(), role);
}

inline void
Xfc::Gdk::Window::set_events(EventMaskField event_mask)
{
	gdk_window_set_events(gdk_window(), (GdkEventMask)event_mask);
}

inline void
Xfc::Gdk::Window::set_icon_name(const char *name)
{
	gdk_window_set_icon_name(gdk_window(), name);
}

inline void
Xfc::Gdk::Window::set_decorations(WMDecorationField decorations)
{
	gdk_window_set_decorations(gdk_window(), (GdkWMDecoration)decorations);
}

inline void
Xfc::Gdk::Window::set_functions(WMFunctionField functions)
{
	gdk_window_set_functions(gdk_window(), (GdkWMFunction)functions);
}

inline void
Xfc::Gdk::Window::iconify()
{
	gdk_window_iconify(gdk_window());
}

inline void
Xfc::Gdk::Window::deiconify()
{
	gdk_window_deiconify(gdk_window());
}

inline void
Xfc::Gdk::Window::stick()
{
	gdk_window_stick(gdk_window());
}

inline void
Xfc::Gdk::Window::unstick()
{
	gdk_window_unstick(gdk_window());
}

inline void
Xfc::Gdk::Window::maximize()
{
	gdk_window_maximize(gdk_window());
}

inline void
Xfc::Gdk::Window::unmaximize()
{
	gdk_window_unmaximize(gdk_window());
}

inline void
Xfc::Gdk::Window::fullscreen()
{
	gdk_window_fullscreen(gdk_window());
}

inline void
Xfc::Gdk::Window::unfullscreen()
{
	gdk_window_unfullscreen(gdk_window());
}

inline void
Xfc::Gdk::Window::set_keep_above(bool setting)
{
	gdk_window_set_keep_above(gdk_window(), setting);
}

inline void
Xfc::Gdk::Window::set_keep_below(bool setting)
{
	gdk_window_set_keep_below(gdk_window(), setting);
}

inline void
Xfc::Gdk::Window::register_dnd()
{
	gdk_window_register_dnd(gdk_window());
}

inline void
Xfc::Gdk::Window::begin_resize_drag(WindowEdge edge, int button, int root_x, int root_y, unsigned int timestamp)
{
	gdk_window_begin_resize_drag(gdk_window(), (GdkWindowEdge)edge, button, root_x, root_y, timestamp);
}

inline void
Xfc::Gdk::Window::begin_move_drag(int button, int root_x, int root_y, unsigned int timestamp)
{
	gdk_window_begin_move_drag(gdk_window(), button, root_x, root_y, timestamp);
}

inline void
Xfc::Gdk::Window::freeze_updates()
{
	gdk_window_freeze_updates(gdk_window());
}

inline void
Xfc::Gdk::Window::thaw_updates()
{
	gdk_window_thaw_updates(gdk_window());
}

inline void
Xfc::Gdk::Window::process_all_updates()
{
	gdk_window_process_all_updates();
}

inline void
Xfc::Gdk::Window::process_updates(bool update_children)
{
	gdk_window_process_updates(gdk_window(), update_children);
}

inline void
Xfc::Gdk::Window::set_debug_updates(bool setting)
{
	gdk_window_set_debug_updates(setting);
}

inline void 
Xfc::Gdk::Window::enable_synchronized_configure()
{
	gdk_window_enable_synchronized_configure(gdk_window());
}

inline void 
Xfc::Gdk::Window::configure_finished()
{
	gdk_window_configure_finished(gdk_window());
}

inline Xfc::Gdk::GrabStatus
Xfc::Gdk::Window::keyboard_grab(bool owner_events, unsigned int time)
{
	return (GrabStatus)gdk_keyboard_grab(gdk_window(), owner_events, time);
}

inline void
Xfc::Gdk::Window::set_extension_events(int mask, ExtensionMode mode)
{
	gdk_input_set_extension_events(gdk_window(), mask, (GdkExtensionMode)mode);
}

