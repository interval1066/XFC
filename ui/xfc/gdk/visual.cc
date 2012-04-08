/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  visual.cc - GdkVisual C++ wrapper implementation
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
 
#include "visual.hh"
#include "screen.hh"

using namespace Xfc;

/*  Gdk::Visual
 */

Gdk::Visual::Visual(GdkVisual *visual, bool owns_reference)
: G::Object((GObject*)visual, owns_reference)
{
}
	
Gdk::Visual::~Visual()
{
}

const Gdk::Visual* 
Gdk::Visual::get_best()
{
	return G::Object::wrap<Visual>(gdk_visual_get_best());
}

const Gdk::Visual* 
Gdk::Visual::get_best(int depth)
{
	return G::Object::wrap<Visual>(gdk_visual_get_best_with_depth(depth));
}

const Gdk::Visual* 
Gdk::Visual::get_best(VisualType visual_type)
{
	return G::Object::wrap<Visual>(gdk_visual_get_best_with_type((GdkVisualType)visual_type));
}

const Gdk::Visual* 
Gdk::Visual::get_best(int depth, VisualType visual_type)
{
	return G::Object::wrap<Visual>(gdk_visual_get_best_with_both(depth, (GdkVisualType)visual_type));
}

const Gdk::Visual*
Gdk::Visual::get_system()
{
	return G::Object::wrap<Visual>(gdk_visual_get_system());
}

std::vector<int>
Gdk::Visual::query_depths()
{
	int *tmp_depths = 0;
	int count = 0;
	gdk_query_depths(&tmp_depths, &count);

	std::vector<int> depths;
	int i = 0;
	while (i < count)
	{
		depths.push_back(tmp_depths[i]);
		++i;
	}
	return depths;
}

bool
Gdk::Visual::query_visual_types(std::vector<VisualType>& visual_types)
{
	g_return_val_if_fail(visual_types.empty(), false);
	GdkVisualType *types = 0;
	int count = 0;
	gdk_query_visual_types(&types, &count);

	int i = 0;
	while (i < count)
	{
		visual_types.push_back((VisualType)types[i]);
		++i;
	}
	return !visual_types.empty();
}

bool
Gdk::Visual::list_visuals(std::vector<const Visual*>& visuals)
{
	Screen *screen = Screen::get_default();
	return screen->list_visuals(visuals);
}

