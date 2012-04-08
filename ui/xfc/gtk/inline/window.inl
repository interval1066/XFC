/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  window.inl - Gtk::Window and Gtk::WindowGroup inline functions
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

/*  Gtk::Window
 */

inline GtkWindow*
Xfc::Gtk::Window::gtk_window() const
{
	return reinterpret_cast<GtkWindow*>(instance_);
}

inline Xfc::Gtk::Window::operator GtkWindow* () const
{
	return this ? gtk_window() : 0;
}

inline bool
Xfc::Gtk::Window::is_toplevel() const
{
	return gtk_window()->type == GTK_WINDOW_TOPLEVEL;
}

inline bool
Xfc::Gtk::Window::is_popup() const
{
	return gtk_window()->type == GTK_WINDOW_POPUP;
}

inline bool
Xfc::Gtk::Window::is_active() const
{
	return gtk_window_is_active(gtk_window());
}

inline bool
Xfc::Gtk::Window::has_toplevel_focus() const
{
	return gtk_window_has_toplevel_focus(gtk_window());
}

inline bool
Xfc::Gtk::Window::get_skip_taskbar_hint() const
{
	return gtk_window_get_skip_taskbar_hint(gtk_window());
}

inline bool
Xfc::Gtk::Window::get_skip_pager_hint() const
{
	return gtk_window_get_skip_pager_hint(gtk_window());
}

inline bool 
Xfc::Gtk::Window::get_accept_focus() const
{
	return gtk_window_get_accept_focus(gtk_window());
}

inline bool 
Xfc::Gtk::Window::get_focus_on_map() const
{
	return gtk_window_get_focus_on_map(gtk_window());
}

inline bool
Xfc::Gtk::Window::get_destroy_with_parent() const
{
	return gtk_window_get_destroy_with_parent(gtk_window());
}

inline bool
Xfc::Gtk::Window::get_resizable() const
{
	return gtk_window_get_resizable(gtk_window());
}

inline Xfc::Gdk::Gravity
Xfc::Gtk::Window::get_gravity() const
{
	return (Gdk::Gravity)gtk_window_get_gravity(gtk_window());
}

inline bool
Xfc::Gtk::Window::get_has_frame() const
{
	return gtk_window_get_has_frame(gtk_window());
}

inline void
Xfc::Gtk::Window::get_frame_dimensions(int *left, int *top, int *right, int *bottom) const
{
	gtk_window_get_frame_dimensions(gtk_window(), left, top, right, bottom);
}

inline bool
Xfc::Gtk::Window::get_decorated() const
{
	return gtk_window_get_decorated(gtk_window());
}

inline bool
Xfc::Gtk::Window::get_modal() const
{
	return gtk_window_get_modal(gtk_window());
}

inline Xfc::Gdk::ModifierTypeField
Xfc::Gtk::Window::get_mnemonic_modifier() const
{
	return (Gdk::ModifierTypeField)gtk_window_get_mnemonic_modifier(gtk_window());
}

inline void
Xfc::Gtk::Window::get_default_size(int *width, int *height) const
{
	gtk_window_get_default_size(gtk_window(), width, height);
}

inline void
Xfc::Gtk::Window::get_size(int *width, int *height) const
{
	gtk_window_get_size(gtk_window(), width, height);
}

inline void
Xfc::Gtk::Window::get_position(int *root_x, int *root_y) const
{
	gtk_window_get_position(gtk_window(), root_x, root_y);
}

inline void
Xfc::Gtk::Window::set_title(const char *title)
{
	gtk_window_set_title(gtk_window(), title);
}

inline void
Xfc::Gtk::Window::set_role(const char *role)
{
	gtk_window_set_role(gtk_window(), role);
}

inline void
Xfc::Gtk::Window::set_position(WindowPosition position)
{
	gtk_window_set_position(gtk_window(), (GtkWindowPosition)position);
}

inline bool
Xfc::Gtk::Window::activate_focus()
{
	return gtk_window_activate_focus(gtk_window());
}

inline bool
Xfc::Gtk::Window::activate_default()
{
	return gtk_window_activate_default(gtk_window());
}

inline void
Xfc::Gtk::Window::set_type_hint(Gdk::WindowTypeHint hint)
{
	gtk_window_set_type_hint(gtk_window(), (GdkWindowTypeHint)hint);
}


inline void
Xfc::Gtk::Window::set_skip_taskbar_hint(bool setting)
{
	gtk_window_set_skip_taskbar_hint(gtk_window(), setting);
}

inline void
Xfc::Gtk::Window::set_skip_pager_hint(bool setting)
{
	gtk_window_set_skip_pager_hint(gtk_window(), setting);
}

inline void 
Xfc::Gtk::Window::set_accept_focus(bool setting)
{
	gtk_window_set_accept_focus(gtk_window(), setting);
}

inline void 
Xfc::Gtk::Window::set_focus_on_map(bool setting)
{
	gtk_window_set_focus_on_map(gtk_window(), setting);
}

inline void
Xfc::Gtk::Window::set_destroy_with_parent(bool setting)
{
	gtk_window_set_destroy_with_parent(gtk_window(), setting);
}

inline void
Xfc::Gtk::Window::set_resizable(bool resizable)
{
	gtk_window_set_resizable(gtk_window(), resizable);
}

inline void
Xfc::Gtk::Window::set_gravity(Gdk::Gravity gravity)
{
	gtk_window_set_gravity(gtk_window(), (GdkGravity)gravity);
}

inline void
Xfc::Gtk::Window::set_has_frame(bool setting)
{
	gtk_window_set_has_frame(gtk_window(), setting);
}

inline void
Xfc::Gtk::Window::set_frame_dimensions(int left, int top, int right, int bottom)
{
	gtk_window_set_frame_dimensions(gtk_window(), left, top, right, bottom);
}

inline void
Xfc::Gtk::Window::set_decorated(bool setting)
{
	gtk_window_set_decorated(gtk_window(), setting);
}

inline void 
Xfc::Gtk::Window::set_icon_name(const char *name)
{
	gtk_window_set_icon_name(gtk_window(), name);
}

inline void
Xfc::Gtk::Window::set_auto_startup_notification(bool setting)
{
	gtk_window_set_auto_startup_notification(setting);
}

inline void
Xfc::Gtk::Window::set_modal(bool modal)
{
	gtk_window_set_modal(gtk_window(), modal);
}

inline bool
Xfc::Gtk::Window::mnemonic_activate(unsigned int keyval, Gdk::ModifierTypeField modifier)
{
	return gtk_window_mnemonic_activate(gtk_window(), keyval, (GdkModifierType)modifier);
}

inline void
Xfc::Gtk::Window::set_mnemonic_modifier(Gdk::ModifierTypeField modifier)
{
	gtk_window_set_mnemonic_modifier(gtk_window(), (GdkModifierType)modifier);
}

inline void
Xfc::Gtk::Window::present()
{
	gtk_window_present(gtk_window());
}

inline void
Xfc::Gtk::Window::iconify()
{
	gtk_window_iconify(gtk_window());
}

inline void
Xfc::Gtk::Window::deiconify()
{
	gtk_window_deiconify(gtk_window());
}

inline void
Xfc::Gtk::Window::stick()
{
	gtk_window_stick(gtk_window());
}

inline void
Xfc::Gtk::Window::unstick()
{
	gtk_window_unstick(gtk_window());
}

inline void
Xfc::Gtk::Window::maximize()
{
	gtk_window_maximize(gtk_window());
}

inline void
Xfc::Gtk::Window::unmaximize()
{
	gtk_window_unmaximize(gtk_window());
}

inline void
Xfc::Gtk::Window::fullscreen()
{
	gtk_window_fullscreen(gtk_window());
}

inline void
Xfc::Gtk::Window::unfullscreen()
{
	gtk_window_unfullscreen(gtk_window());
}

inline void
Xfc::Gtk::Window::set_keep_above(bool setting)
{
	gtk_window_set_keep_above(gtk_window(), setting);
}

inline void
Xfc::Gtk::Window::set_keep_below(bool setting)
{
	gtk_window_set_keep_below(gtk_window(), setting);
}

inline void
Xfc::Gtk::Window::begin_resize_drag(Gdk::WindowEdge edge, int button, int root_x, int root_y, unsigned int timestamp)
{
	gtk_window_begin_resize_drag(gtk_window(), (GdkWindowEdge)edge, button, root_x, root_y, timestamp);
}

inline void
Xfc::Gtk::Window::begin_move_drag(int button, int root_x, int root_y, unsigned int timestamp)
{
	gtk_window_begin_move_drag(gtk_window(), button, root_x, root_y, timestamp);
}

inline void
Xfc::Gtk::Window::set_default_size(int width, int height)
{
	gtk_window_set_default_size(gtk_window(), width, height);
}

inline void
Xfc::Gtk::Window::resize(int width, int height)
{
	gtk_window_resize(gtk_window(), width, height);
}

inline void
Xfc::Gtk::Window::move(int x, int y)
{
	gtk_window_move(gtk_window(), x, y);
}

inline bool
Xfc::Gtk::Window::parse_geometry(const char *geometry)
{
	return gtk_window_parse_geometry(gtk_window(), geometry);
}

inline void
Xfc::Gtk::Window::reshow_with_initial_size()
{
	gtk_window_reshow_with_initial_size(gtk_window());
}

inline void 
Xfc::Gtk::Window::set_default_icon_name(const char *name)
{
	gtk_window_set_default_icon_name(name);
}

inline const Xfc::Gtk::Window::SetFocusSignalProxy
Xfc::Gtk::Window::signal_set_focus()
{
	return SetFocusSignalProxy(this, &set_focus_signal);
}

inline const Xfc::Gtk::Window::FrameEventSignalProxy
Xfc::Gtk::Window::signal_frame_event()
{
	return FrameEventSignalProxy(this, &frame_event_signal);
}

inline const Xfc::Gtk::Window::KeysChangedSignalProxy
Xfc::Gtk::Window::signal_keys_changed()
{
	return KeysChangedSignalProxy(this, &keys_changed_signal);
}

/*  Gtk::WindowGroup
 */

inline GtkWindowGroup*
Xfc::Gtk::WindowGroup::gtk_window_group() const
{
	return reinterpret_cast<GtkWindowGroup*>(instance_);
}

inline Xfc::Gtk::WindowGroup::operator GtkWindowGroup* () const
{
	return this ? gtk_window_group() : 0;
}

