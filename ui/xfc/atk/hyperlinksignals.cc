/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  hyperlinksignals.cc - Atk::Hyperlink virtual signal handlers
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
 
#include "hyperlink.hh"
#include "hyperlinksignals.hh"
#include "private/hyperlinkclass.hh"

using namespace Xfc;

/*  Atk::HyperlinkSignals
 */

Atk::HyperlinkSignals::HyperlinkSignals(Hyperlink *hyperlink) 
: G::ObjectSignals(hyperlink)
{
}

Atk::HyperlinkSignals::~HyperlinkSignals() 
{
}
	
void
Atk::HyperlinkSignals::on_link_activated()
{
	AtkHyperlinkClass *g_class = HyperlinkClass::get_parent_class(instance_);
	if (g_class && g_class->link_activated)
		g_class->link_activated((AtkHyperlink*)instance_);
}

