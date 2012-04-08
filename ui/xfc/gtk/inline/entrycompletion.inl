/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  entrycompletion.inl - Gtk::EntryCompletion inline functions
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

inline GtkEntryCompletion*
Xfc::Gtk::EntryCompletion::gtk_entry_completion() const
{
	return reinterpret_cast<GtkEntryCompletion*>(instance_);
}

inline Xfc::Gtk::EntryCompletion::operator GtkEntryCompletion* () const
{
	return this ? gtk_entry_completion() : 0;
}

inline int 
Xfc::Gtk::EntryCompletion::get_minimum_key_length() const 
{
	return gtk_entry_completion_get_minimum_key_length(gtk_entry_completion());
}

inline bool 
Xfc::Gtk::EntryCompletion::get_inline_completion() const
{
	return gtk_entry_completion_get_inline_completion(gtk_entry_completion());
}
	
inline bool 
Xfc::Gtk::EntryCompletion::get_popup_completion() const
{
	return gtk_entry_completion_get_popup_completion(gtk_entry_completion());
}
inline int 
Xfc::Gtk::EntryCompletion::get_text_column() const
{
	return gtk_entry_completion_get_text_column(gtk_entry_completion());
}

inline void 
Xfc::Gtk::EntryCompletion::set_minimum_key_length(int length)
{
	gtk_entry_completion_set_minimum_key_length(gtk_entry_completion(), length);
}

inline void 
Xfc::Gtk::EntryCompletion::complete()
{
	gtk_entry_completion_complete(gtk_entry_completion());
}

inline void 
Xfc::Gtk::EntryCompletion::insert_prefix()
{
	gtk_entry_completion_insert_prefix(gtk_entry_completion());
}

inline void 
Xfc::Gtk::EntryCompletion::insert_action_text(int index, const char *text)
{
	gtk_entry_completion_insert_action_text(gtk_entry_completion(), index, text);
}

inline void 
Xfc::Gtk::EntryCompletion::insert_action_markup(int index, const char *markup)
{
	gtk_entry_completion_insert_action_markup(gtk_entry_completion(), index, markup);
}

inline void 
Xfc::Gtk::EntryCompletion::delete_action(int index)
{
	gtk_entry_completion_delete_action(gtk_entry_completion(), index);
}
	
inline void 
Xfc::Gtk::EntryCompletion::set_inline_completion(bool inline_completion)
{
	gtk_entry_completion_set_inline_completion(gtk_entry_completion(), inline_completion);
}
	
inline void 
Xfc::Gtk::EntryCompletion::set_popup_completion(bool popup_completion)
{
	gtk_entry_completion_set_popup_completion(gtk_entry_completion(), popup_completion);
}
	
inline void 
Xfc::Gtk::EntryCompletion::set_text_column(int column)
{
	gtk_entry_completion_set_text_column(gtk_entry_completion(), column);
}

inline const Xfc::Gtk::EntryCompletion::MatchSelectedSignalProxy
Xfc::Gtk::EntryCompletion::signal_match_selected()
{
	return MatchSelectedSignalProxy(this, &match_selected_signal);
}

inline const Xfc::Gtk::EntryCompletion::ActionActivatedSignalProxy
Xfc::Gtk::EntryCompletion::signal_action_activated()
{
	return ActionActivatedSignalProxy(this, &action_activated_signal);
}

inline const Xfc::Gtk::EntryCompletion::InsertPrefixSignalProxy
Xfc::Gtk::EntryCompletion::signal_insert_prefix()
{
	return InsertPrefixSignalProxy(this, &insert_prefix_signal);
}

