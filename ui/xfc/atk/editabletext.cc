/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  editabletext.cc - AtkEditableText C++ wrapper implementation
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

#include "editabletext.hh"
#include <cstring>

using namespace Xfc;

/*  Atk::EditableText
 */

Atk::EditableText::EditableText()
{
}
	
Atk::EditableText::~EditableText()
{
}
	
bool
Atk::EditableText::set_run_attributes(const std::vector<Attribute>& attribs, int start_offset, int end_offset)
{
	g_return_val_if_fail(!attribs.empty(), false);

	GSList *tmp_attribs = 0;
	int count = attribs.size();

	int i = 0;
	while (i < count)
	{
		tmp_attribs = g_slist_append(tmp_attribs, attribs[i].atk_attribute());
		++i;
	}
	bool result = atk_editable_text_set_run_attributes(atk_editable_text(), tmp_attribs, start_offset, end_offset);
	g_slist_free(tmp_attribs);
	return result;
}

void
Atk::EditableText::set_text_contents(const String& str)
{
	atk_editable_text_set_text_contents(atk_editable_text(), str.c_str());
}

void
Atk::EditableText::insert_text(const char *str, int *position)
{
	atk_editable_text_insert_text(atk_editable_text(), str, strlen(str), position);
}

void
Atk::EditableText::insert_text(const String& str, int *position)
{
	atk_editable_text_insert_text(atk_editable_text(), str.c_str(), str.size(), position);
}

