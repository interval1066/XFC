/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  tabs.cc - PangoTabArray C++ wrapper implementation
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
 
#include "tabs.hh"

using namespace Xfc;

Pango::TabArray::TabArray(int initial_size, bool positions_in_pixels)
: G::Boxed(PANGO_TYPE_TAB_ARRAY, pango_tab_array_new(initial_size, positions_in_pixels), false)
{
}

Pango::TabArray::TabArray(int size, bool positions_in_pixels, int first_position, ...)
: G::Boxed(PANGO_TYPE_TAB_ARRAY, pango_tab_array_new(size, positions_in_pixels), false)
{
	if (size > 0)
		pango_tab_array_set_tab(pango_tab_array(), 0, PANGO_TAB_LEFT, first_position);

	if (size > 1)
	{
		va_list args;
		va_start(args, first_position);

  		int i = 1;
  		while (i < size)
		{
			int pos = va_arg(args, int);
			pango_tab_array_set_tab(pango_tab_array(), i, PANGO_TAB_LEFT, pos);
			++i;
		}

   	 	va_end (args);
	}
}

Pango::TabArray::TabArray(int size, bool positions_in_pixels, TabAlign first_alignment, int first_position, ...)
: G::Boxed(PANGO_TYPE_TAB_ARRAY, pango_tab_array_new(size, positions_in_pixels), false)
{
	if (size > 0)
		pango_tab_array_set_tab(pango_tab_array(), 0, (PangoTabAlign)first_alignment, first_position);

	if (size > 1)
	{
		va_list args;
		va_start(args, first_position);

  		int i = 1;
  		while (i < size)
		{
			PangoTabAlign align = (PangoTabAlign)va_arg(args, int);
			int pos = va_arg(args, int);
			pango_tab_array_set_tab(pango_tab_array(), i, align, pos);
			++i;
		}

   	 	va_end (args);
	}
}

Pango::TabArray::TabArray(const std::vector<std::pair<TabAlign , int> >& tabs, bool positions_in_pixels)
: G::Boxed(PANGO_TYPE_TAB_ARRAY, pango_tab_array_new(tabs.size(), positions_in_pixels), false)
{
	int size = tabs.size();
	if (size > 0)
		pango_tab_array_set_tab(pango_tab_array(), 0, (PangoTabAlign)tabs[0].first, tabs[0].second);

	if (size > 1)
	{
 		int i = 1;
  		while (i < size)
		{
			pango_tab_array_set_tab(pango_tab_array(), i, (PangoTabAlign)tabs[i].first, tabs[i].second);
			++i;
		}
	}
}

Pango::TabArray::TabArray(PangoTabArray *tab_array)
: G::Boxed(PANGO_TYPE_TAB_ARRAY, tab_array)
{
}

Pango::TabArray::TabArray(PangoTabArray *tab_array, bool copy)
: G::Boxed(PANGO_TYPE_TAB_ARRAY, tab_array, copy)
{
}

Pango::TabArray::TabArray(const TabArray& src)
: G::Boxed(PANGO_TYPE_TAB_ARRAY, src.pango_tab_array(), true)
{
}

Pango::TabArray::~TabArray()
{
}


Pango::TabArray&
Pango::TabArray::operator=(const TabArray& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

int
Pango::TabArray::get_size() const
{
	return pango_tab_array_get_size(pango_tab_array());
}

int
Pango::TabArray::get_tab(int tab_index, TabAlign *alignment) const
{
	int location;
	pango_tab_array_get_tab(pango_tab_array(), tab_index, (PangoTabAlign*)alignment, &location);
	return location;
}

std::vector<std::pair<Pango::TabAlign, int> >
Pango::TabArray::get_tabs() const
{
	PangoTabAlign *tmp_alignments = 0;
	int *tmp_locations = 0;
	pango_tab_array_get_tabs(pango_tab_array(), &tmp_alignments, &tmp_locations);
	int size = pango_tab_array_get_size(pango_tab_array());

	typedef std::pair<TabAlign, int> Tab;
	std::vector<Tab> tabs(size);

	for (int i = 0; i < size; i++)
	{
		tabs[i] = Tab((TabAlign)tmp_alignments[i], tmp_locations[i]);
	}

	g_free(tmp_alignments);
	g_free(tmp_locations);
	return tabs;
}

