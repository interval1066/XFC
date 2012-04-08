/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  break.cc - PangoLogAttr C++ wrapper implementation
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

#define PANGO_ENABLE_ENGINE
 
#include "break.hh"
#include "item.hh"
#include <string.h>

using namespace Xfc;

Pango::LogAttr::LogAttr()
{
	memset(this, 0, sizeof(*this));
}

void
Pango::break_text(const String& text, const Analysis& analysis, std::vector<LogAttr>& attrs)
{
	g_return_if_fail(!attrs.empty());
	PangoLogAttr *tmp_attrs = reinterpret_cast<PangoLogAttr*>(&attrs[0]);
	pango_break(text.c_str(), text.size(), analysis.pango_analysis(), tmp_attrs, attrs.size());
}

void
Pango::find_paragraph_boundary(const String& text, int *paragraph_delimiter_index, int *next_paragraph_start)
{
	pango_find_paragraph_boundary(text.c_str(), text.size(), paragraph_delimiter_index, next_paragraph_start);
}

void
Pango::get_log_attrs(const String& text, PangoLanguage *language, std::vector<LogAttr>& attrs, int level)
{
	g_return_if_fail(!attrs.empty());
	PangoLogAttr *tmp_attrs = reinterpret_cast<PangoLogAttr*>(&attrs[0]);
	pango_get_log_attrs(text.c_str(), text.size(), level, language, tmp_attrs, attrs.size());
}


