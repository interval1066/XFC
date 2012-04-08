/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  script.cc - PangoScriptIter C++ wrapper implementation
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

#include "script.hh"

using namespace Xfc;

/*  Pango::ScriptIter
 */

Pango::ScriptIter::ScriptIter(const char *text, int length)
: iter_(pango_script_iter_new(text, length))
{
}

Pango::ScriptIter::ScriptIter(const String& text)
: iter_(pango_script_iter_new(text.c_str(), text.size()))
{
}

Pango::ScriptIter::~ScriptIter()
{
	pango_script_iter_free(iter_);
}

Pango::Script
Pango::ScriptIter::get_range(const char **start, const char **end)
{
	PangoScript script;
	pango_script_iter_get_range(pango_script_iter(), start, end, &script);
	return (Script)script;
}

Pango::Script
Pango::ScriptIter::get_range(String *range)
{
	const char *start = 0;
	const char *end = 0;
	PangoScript script;

	pango_script_iter_get_range(pango_script_iter(), &start, &end, &script);

	if (range)
		range->assign(Forward_StringIterator(start), Forward_StringIterator(end));

	return (Script)script;
}

