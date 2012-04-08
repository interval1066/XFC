/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  notebook.inl - Gtk::Notebook inline functions
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

inline GtkNotebook*
Xfc::Gtk::Notebook::gtk_notebook() const
{
	return reinterpret_cast<GtkNotebook*>(instance_);
}

inline Xfc::Gtk::Notebook::operator GtkNotebook* () const
{
	return this ? gtk_notebook() : 0;
}

inline int
Xfc::Gtk::Notebook::get_current_page() const
{
	return gtk_notebook_get_current_page(gtk_notebook());
}

inline int
Xfc::Gtk::Notebook::get_n_pages() const
{
	return gtk_notebook_get_n_pages(gtk_notebook());
}

inline bool
Xfc::Gtk::Notebook::get_show_border() const
{
	return gtk_notebook_get_show_border(gtk_notebook());
}

inline bool
Xfc::Gtk::Notebook::get_show_tabs() const
{
	return gtk_notebook_get_show_tabs(gtk_notebook());
}

inline Xfc::Gtk::PositionType
Xfc::Gtk::Notebook::get_tab_pos() const
{
	return (PositionType)gtk_notebook_get_tab_pos(gtk_notebook());
}

inline bool
Xfc::Gtk::Notebook::get_scrollable() const
{
	return gtk_notebook_get_scrollable(gtk_notebook());
}

inline void
Xfc::Gtk::Notebook::remove_page(int page_num)
{
	gtk_notebook_remove_page(gtk_notebook(), page_num);
}

inline void
Xfc::Gtk::Notebook::set_current_page(int page_num)
{
	gtk_notebook_set_current_page(gtk_notebook(), page_num);
}

inline void
Xfc::Gtk::Notebook::next_page()
{
	gtk_notebook_next_page(gtk_notebook());
}

inline void
Xfc::Gtk::Notebook::prev_page()
{
	gtk_notebook_prev_page(gtk_notebook());
}

inline void
Xfc::Gtk::Notebook::set_show_border(bool show_border)
{
	gtk_notebook_set_show_border(gtk_notebook(), show_border);
}

inline void
Xfc::Gtk::Notebook::set_show_tabs(bool show_tabs)
{
	gtk_notebook_set_show_tabs(gtk_notebook(), show_tabs);
}

inline void
Xfc::Gtk::Notebook::set_tab_pos(PositionType pos)
{
	gtk_notebook_set_tab_pos(gtk_notebook(), (GtkPositionType)pos);
}

inline void
Xfc::Gtk::Notebook::set_scrollable(bool scrollable)
{
	gtk_notebook_set_scrollable(gtk_notebook(), scrollable);
}

inline void
Xfc::Gtk::Notebook::popup_enable()
{
	gtk_notebook_popup_enable(gtk_notebook());
}

inline void
Xfc::Gtk::Notebook::popup_disable()
{
	gtk_notebook_popup_disable(gtk_notebook());
}

inline const Xfc::Gtk::Notebook::SwitchPageSignalProxy
Xfc::Gtk::Notebook::signal_switch_page()
{
	return SwitchPageSignalProxy(this, &switch_page_signal);
}

