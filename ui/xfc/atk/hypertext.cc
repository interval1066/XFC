/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  hypertext.cc - AtkHypertext C++ wrapper implementation
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
 
#include "hypertext.hh"
#include "hypertextsignals.hh"
#include "hyperlink.hh"
#include "private/hypertextiface.hh"
#include "private/marshal.hh"
#include "xfc/glib/object.hh"
#include "xfc/glib/objectsignals.hh"

using namespace Xfc;

/*  Atk::Hypertext
 */

Atk::Hypertext::Hypertext()
{
}
	
Atk::Hypertext::~Hypertext()
{
}
	
Atk::Hyperlink*
Atk::Hypertext::get_link(int link_index) const
{
	AtkHyperlink *hyperlink = atk_hypertext_get_link(atk_hypertext(), link_index);
	return hyperlink ? G::Object::wrap<Hyperlink>(hyperlink) : 0;
}

/*  Atk::HypertextIface
 */

void
Atk::HypertextIface::init(AtkHypertextIface *g_iface)
{
	g_iface->link_selected = &link_selected_proxy;
}

AtkHypertextIface*
Atk::HypertextIface::get_parent_iface(void *instance)
{
	return static_cast<AtkHypertextIface*>(g_type_interface_peek_parent(ATK_HYPERTEXT_GET_IFACE(instance)));
}

void
Atk::HypertextIface::link_selected_proxy(AtkHypertext *hypertext, gint link_index)
{
	HypertextSignals *signals = dynamic_cast<HypertextSignals*>(G::ObjectSignals::pointer((GObject*)hypertext));
	if (signals)
		signals->on_link_selected(link_index);
	else
	{
		AtkHypertextIface *g_iface = get_parent_iface(hypertext);
		if (g_iface && g_iface->link_selected)
			g_iface->link_selected(hypertext, link_index);
	}
}

/*  Atk::Hypertext signals
 */

const Atk::Hypertext::LinkSelectedSignalType Atk::Hypertext::link_selected_signal("link_selected", (GCallback)&G::Marshal::void_int_callback);

