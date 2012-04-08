/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  clipboard.inl - Gtk::Clipboard inline functions
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

inline GtkClipboard*
Xfc::Gtk::Clipboard::gtk_clipboard() const
{
	return reinterpret_cast<GtkClipboard*>(instance_);
}

inline Xfc::Gtk::Clipboard::operator GtkClipboard* () const
{
	return this ? gtk_clipboard() : 0;
}

inline bool
Xfc::Gtk::Clipboard::wait_is_text_available() const
{
	return gtk_clipboard_wait_is_text_available(gtk_clipboard());
}

inline bool 
Xfc::Gtk::Clipboard::is_image_available() const
{
	return gtk_clipboard_wait_is_image_available(gtk_clipboard());
}
	
inline bool 
Xfc::Gtk::Clipboard::is_target_available(Gdk::Atom target) const
{
	return gtk_clipboard_wait_is_target_available(gtk_clipboard(), target);
}

inline void
Xfc::Gtk::Clipboard::clear()
{
	gtk_clipboard_clear(gtk_clipboard());
}

inline void 
Xfc::Gtk::Clipboard::store()
{
	gtk_clipboard_store(gtk_clipboard());
}

