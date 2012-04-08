/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  selection.cc - AtkSelection C++ wrapper implementation
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
 
#include "selection.hh"
#include "selectionsignals.hh"
#include "object.hh"
#include "private/marshal.hh"
#include "private/selectioniface.hh"
#include "xfc/glib/object.hh"
#include "xfc/glib/objectsignals.hh"

using namespace Xfc;

/*  Atk::Selection
 */

Atk::Selection::Selection()
{
}
	
Atk::Selection::~Selection()
{
}
	
Atk::Object*
Atk::Selection::ref_selection(int i)
{
	AtkObject *object = atk_selection_ref_selection(atk_selection(), i);
	return object ? G::Object::wrap<Atk::Object>(object) : 0;
}

/*  Atk::SelectionIface
 */

void
Atk::SelectionIface::init(AtkSelectionIface *g_iface)
{
	g_iface->selection_changed = &selection_changed_proxy;
}

AtkSelectionIface*
Atk::SelectionIface::get_parent_iface(void *instance)
{
	return static_cast<AtkSelectionIface*>(g_type_interface_peek_parent(ATK_SELECTION_GET_IFACE(instance)));
}

void
Atk::SelectionIface::selection_changed_proxy(AtkSelection *selection)
{
	SelectionSignals *signals = dynamic_cast<SelectionSignals*>(G::ObjectSignals::pointer((GObject*)selection));
	if (signals)
		signals->on_selection_changed();
	else
	{
		AtkSelectionIface *g_iface = get_parent_iface(selection);
		if (g_iface && g_iface->selection_changed)
			g_iface->selection_changed(selection);
	}
}

/*  Atk::Selection signals
 */

const Atk::Selection::SelectionChangedSignalType Atk::Selection::selection_changed_signal("selection_changed", (GCallback)&G::Marshal::void_callback);

