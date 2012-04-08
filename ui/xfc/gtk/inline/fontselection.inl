/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  fontselection.inl - Gtk::FontSelection and Gtk::FontSelectionDialog inline functions
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

/*  Gtk::FontSelection
 */

inline GtkFontSelection*
Xfc::Gtk::FontSelection::gtk_font_selection() const
{
	return reinterpret_cast<GtkFontSelection*>(instance_);
}

inline Xfc::Gtk::FontSelection::operator GtkFontSelection* () const
{
	return this ? gtk_font_selection() : 0;
}

inline bool
Xfc::Gtk::FontSelection::set_font_name(const char *fontname)
{
	return gtk_font_selection_set_font_name(gtk_font_selection(), fontname);
}

inline void
Xfc::Gtk::FontSelection::set_preview_text(const char *text)
{
	gtk_font_selection_set_preview_text(gtk_font_selection(), text);
}

/*  Gtk::FontSelectionDialog
 */

inline GtkFontSelectionDialog*
Xfc::Gtk::FontSelectionDialog::gtk_font_selection_dialog() const
{
	return reinterpret_cast<GtkFontSelectionDialog*>(instance_);
}

inline Xfc::Gtk::FontSelectionDialog::operator GtkFontSelectionDialog* () const
{
	return this ? gtk_font_selection_dialog() : 0;
}

inline bool
Xfc::Gtk::FontSelectionDialog::set_font_name(const char *fontname)
{
	return gtk_font_selection_dialog_set_font_name(gtk_font_selection_dialog(), fontname);
}

inline void
Xfc::Gtk::FontSelectionDialog::set_preview_text(const char *text)
{
	gtk_font_selection_dialog_set_preview_text(gtk_font_selection_dialog(), text);
}

