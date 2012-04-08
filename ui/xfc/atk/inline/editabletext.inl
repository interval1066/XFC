/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  editabletext.inl - Atk::EditableText inline functions
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

inline AtkEditableText*
Xfc::Atk::EditableText::atk_editable_text() const
{
	return reinterpret_cast<AtkEditableText*>(instance_);
}

inline Xfc::Atk::EditableText::operator AtkEditableText* () const
{
	return this ? atk_editable_text() : 0;
}

inline void
Xfc::Atk::EditableText::set_text_contents(const char *str)
{
	atk_editable_text_set_text_contents(atk_editable_text(), str);
}

inline void
Xfc::Atk::EditableText::copy_text(int start_pos, int end_pos)
{
	atk_editable_text_copy_text(atk_editable_text(), start_pos, end_pos);
}

inline void
Xfc::Atk::EditableText::cut_text(int start_pos, int end_pos)
{
	atk_editable_text_cut_text(atk_editable_text(), start_pos, end_pos);
}

inline void
Xfc::Atk::EditableText::delete_text(int start_pos, int end_pos)
{
	atk_editable_text_delete_text(atk_editable_text(), start_pos, end_pos);
}

inline void
Xfc::Atk::EditableText::paste_text(int position)
{
	atk_editable_text_paste_text(atk_editable_text(), position);
}

