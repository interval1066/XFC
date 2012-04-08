/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
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

/// @file xfc/atk/objectsignals.hh
/// @brief Atk::Object virtual signal handlers.
///
/// Provides Atk::Object, an abstract base class that implements
/// the overridable virtual signal handlers for Atk::Object objects.

#ifndef XFC_ATK_OBJECT_SIGNALS_HH
#define XFC_ATK_OBJECT_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Atk {

/// @class ObjectSignals objectsignals.hh xfc/atk/objectsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Atk::Object.

class ObjectSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	ObjectSignals(Object *object);
	///< Constructs a new ObjectSignals object.
	///< @param object An Atk::Object inheriting the Atk::ObjectSignals implementation.

	virtual ~ObjectSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_children_changed(unsigned int change_index, void *changed_child);
	///< Called when the number of children of the object changes.
	///< @param change_index The index of the added or removed child.
	///< @param changed_child The child which was added or removed.
	///
	///< The <EM>children_changed</EM> signal supports two details, "add" and "remove"
	///< which indicate whether a child was added or removed.

	virtual void on_focus_event(bool focus_in);
	///< Called when there is a focus event for an object.
	///< @param focus_in Indicates whether or not the focus event is is or out.

	virtual void on_property_change(AtkPropertyValues *values);
	///< Called when the value of an object property changes.
	///< @param values The new value of the property which changed.

	virtual void on_state_change(const String& name, bool state_set);
	///< Called when the state of an object changes.
	///< @param name The name of the state which has changed.
	///< @param state_set Indicates whether the state has been set or unset.
	///<
	///< This signal supports any of the accessible state types.

	virtual void on_visible_data_changed();
	///< Called when there is a change in the visible data for an object.

	virtual void on_active_descendant_changed(void **child);
	///< Called when there is a change in the 'active' child or children of the object,
	///< for instance when interior focus changes in a table or list.
	///< @param child The newly focused object.

/// @}
};

} // namespace Atk

} // namespace Xfc

#endif // XFC_ATK_OBJECT_SIGNALS_HH

