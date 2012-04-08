/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  scrolledwindow.inl - Gtk::ScrolledWindow inline functions
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

inline GtkScrolledWindow*
Xfc::Gtk::ScrolledWindow::gtk_scrolled_window() const
{
	return reinterpret_cast<GtkScrolledWindow*>(instance_);
}

inline Xfc::Gtk::ScrolledWindow::operator GtkScrolledWindow* () const
{
	return this ? gtk_scrolled_window() : 0;
}

inline void
Xfc::Gtk::ScrolledWindow::get_policy(PolicyType *hscrollbar_policy, PolicyType *vscrollbar_policy) const
{
	gtk_scrolled_window_get_policy(gtk_scrolled_window(), (GtkPolicyType*)hscrollbar_policy, (GtkPolicyType*)vscrollbar_policy);
}

inline Xfc::Gtk::CornerType
Xfc::Gtk::ScrolledWindow::get_placement() const
{
	return (CornerType)gtk_scrolled_window_get_placement(gtk_scrolled_window());
}

inline Xfc::Gtk::ShadowType
Xfc::Gtk::ScrolledWindow::get_shadow_type() const
{
	return (ShadowType)gtk_scrolled_window_get_shadow_type(gtk_scrolled_window());
}

inline void
Xfc::Gtk::ScrolledWindow::set_policy(PolicyType hscrollbar_policy, PolicyType vscrollbar_policy)
{
	gtk_scrolled_window_set_policy(gtk_scrolled_window(), (GtkPolicyType)hscrollbar_policy, (GtkPolicyType)vscrollbar_policy);
}

inline void
Xfc::Gtk::ScrolledWindow::set_policy_automatic()
{
	gtk_scrolled_window_set_policy(gtk_scrolled_window(), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
}

inline void
Xfc::Gtk::ScrolledWindow::set_placement(CornerType window_placement)
{
	gtk_scrolled_window_set_placement(gtk_scrolled_window(), (GtkCornerType)window_placement);
}

inline void
Xfc::Gtk::ScrolledWindow::set_shadow_type(ShadowType type)
{
	gtk_scrolled_window_set_shadow_type(gtk_scrolled_window(), (GtkShadowType)type);
}

