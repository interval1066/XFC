/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  selection.inl - Atk::Selection inline functions
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

inline AtkSelection*
Xfc::Atk::Selection::atk_selection() const
{
	return reinterpret_cast<AtkSelection*>(instance_);
}

inline Xfc::Atk::Selection::operator AtkSelection* () const
{
	return this ? atk_selection() : 0;
}

inline int
Xfc::Atk::Selection::get_selection_count() const
{
	return atk_selection_get_selection_count(atk_selection());
}

inline bool
Xfc::Atk::Selection::is_child_selected(int i) const
{
	return atk_selection_is_child_selected(atk_selection(), i);
}

inline bool
Xfc::Atk::Selection::add_selection(int i)
{
	return atk_selection_add_selection(atk_selection(), i);
}

inline bool
Xfc::Atk::Selection::clear_selection()
{
	return atk_selection_clear_selection(atk_selection());
}

inline bool
Xfc::Atk::Selection::remove_selection(int i)
{
	return atk_selection_remove_selection(atk_selection(), i);
}

inline bool
Xfc::Atk::Selection::select_all_selection()
{
	return atk_selection_select_all_selection(atk_selection());
}

inline const Xfc::Atk::Selection::SelectionChangedSignalProxy
Xfc::Atk::Selection::signal_selection_changed()
{
	return SelectionChangedSignalProxy(this, &selection_changed_signal);
}

