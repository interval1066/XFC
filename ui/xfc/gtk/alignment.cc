/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  alignment.cc - GtkAlignment C++ wrapper implementation
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
 
#include "alignment.hh"
#include "private/alignmentclass.hh"

using namespace Xfc;

/*  Gtk::Alignment
 */

Gtk::Alignment::Alignment(GtkAlignment *alignment, bool owns_reference)
: Bin((GtkBin*)alignment, owns_reference)
{
}

Gtk::Alignment::Alignment()
: Bin((GtkBin*)AlignmentClass::create())
{
}

Gtk::Alignment::Alignment(float xalign, float yalign, float xscale, float yscale)
: Bin((GtkBin*)AlignmentClass::create())
{
	set(xalign, yalign, xscale, yscale);
}

Gtk::Alignment::~Alignment()
{
}

/*  Gtk::AlignmentClass
 */

void
Gtk::AlignmentClass::init(GtkAlignmentClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
}

GType
Gtk::AlignmentClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ALIGNMENT, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::AlignmentClass::create()
{
	return g_object_new(get_type(), 0);
}

