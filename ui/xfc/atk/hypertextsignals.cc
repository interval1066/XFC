/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  hypertextsignals.cc - Atk::Hypertext virtual signal handlers
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
 
#include <atk/atkhypertext.h>
#include "hypertextsignals.hh"
#include "private/hypertextiface.hh"

using namespace Xfc;

/*  Atk::HypertextSignals
 */

Atk::HypertextSignals::~HypertextSignals()
{
}
	
void
Atk::HypertextSignals::on_link_selected(int link_index)
{
	AtkHypertextIface *g_iface = HypertextIface::get_parent_iface(instance_);
	if (g_iface && g_iface->link_selected)
		g_iface->link_selected((AtkHypertext*)instance_, link_index);
}

