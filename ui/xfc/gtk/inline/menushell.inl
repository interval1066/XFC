/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  menushell.inl - Gtk::MenuShell inline functions
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

inline GtkMenuShell*
Xfc::Gtk::MenuShell::gtk_menu_shell() const
{
	return reinterpret_cast<GtkMenuShell*>(instance_);
}

inline Xfc::Gtk::MenuShell::operator GtkMenuShell* () const
{
	return this ? gtk_menu_shell() : 0;
}

inline void
Xfc::Gtk::MenuShell::deselect()
{
	gtk_menu_shell_deselect(gtk_menu_shell());
}

inline void
Xfc::Gtk::MenuShell::deactivate()
{
	gtk_menu_shell_deactivate(gtk_menu_shell());
}

inline void
Xfc::Gtk::MenuShell::select_first(bool search_sensitive)
{
	gtk_menu_shell_select_first(gtk_menu_shell(), search_sensitive);
}

inline const Xfc::Gtk::MenuShell::DeactivateSignalProxy
Xfc::Gtk::MenuShell::signal_deactivate()
{
	return DeactivateSignalProxy(this, &deactivate_signal);
}

inline const Xfc::Gtk::MenuShell::SelectionDoneSignalProxy
Xfc::Gtk::MenuShell::signal_selection_done()
{
	return SelectionDoneSignalProxy(this, &selection_done_signal);
}

