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

/// @file xfc/atk/action.hh
/// @brief An AtkAction C++ wrapper interface.
///
/// Provides Action, an interface provided by UI components which the user can activate/interact with.

#ifndef XFC_ATK_ACTION_HH
#define XFC_ATK_ACTION_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __ATK_ACTION_H__
#include <atk/atkaction.h>
#endif

namespace Xfc {

namespace Atk {

/// @class Action action.hh xfc/atk/action.hh
/// @brief An AtkAction C++ wrapper class.
///
/// Action should be implemented by instances of Atk::Object classes with which
/// the user can interact directly, such as buttons, checkboxes, scrollbars, that
/// is components which are not "passive" providers of UI information. An exception
/// would be when the user interaction is already covered by another appropriate
/// interface such as EditableText (insert/delete test, etc.) or Value (set value).
/// In that case these actions should not be exposed by AtkAction as well.
///
/// Also note that the Action API is limited in that parameters may not be passed
/// to the object being activated; thus the action must be self-contained and 
/// specifiable via only a single "verb". Concrete examples include "press", 
/// "release", "click" for buttons, "drag" (meaning initiate drag) and "drop" for
/// drag sources and drop targets, etc.
///
/// Though most UI interactions on components should be invocable via keyboard
/// as well as mouse, there will generally be a close mapping between "mouse 
/// actions" that are possible on a component and the Actions. Where mouse and 
/// keyboard actions are redundant in effect, Action should expose only one 
/// action rather than exposing redundant actions if possible. By convention we
/// have been using "mouse centric" terminology for Action names.

class Action : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Action();
	///< Constructs a new Action object.	
	
	virtual ~Action() = 0;
	///< Destructor.
	
/// @}

public:
/// @name Accessors
/// @{

	AtkAction* atk_action() const;
	///< Get a pointer to the AtkAction structure.

	operator AtkAction* () const;
	///< Conversion operator; safely converts a Action to an AtkAction pointer.

	int get_n_actions()const;
	///< Gets the number of accessible actions available on the object.
	///< @return The number of actions, or 0 if action does not implement this interface.
	///<
	///< If there are more than one, the first one is considered the
	///< "default" action of the object.

	String get_description(int i) const;
	///< Returns a description of the specified action of the object.
	///< @param i The action index corresponding to the action to be performed.
	///< @return A description string, or a null String if the action object
	///< does not implement this interface.

	String get_name(int i) const;
	///< Returns the name of the specified action of the object.
	///< @param i The action index corresponding to the action to be performed.
	///< @return A name string, or a null String if the action object does not implement this interface.

	String get_keybinding(int i) const;
	///< Returns a keybinding associated with the specified action, if one exists.
	///< @param i The action index corresponding to the action to be performed.
	///< @return A string representing the keybinding, or a null String if there is no
	///< keybinding for this action.

	String get_localized_name(int i) const;
	///< Returns the localized name of the specified action of the object.
	///< @param i The action index corresponding to the action to be performed.
	///< @return A name string, or a null String if the action object does not implement this interface.

/// @}
/// @name Methods
/// @{

	bool do_action(int i);
	///< Perform the specified action on the object.
	///< @param i The action index corresponding to the action to be performed.
	///< @return <EM>true</EM> if success, <EM>false</EM> otherwise.

	bool set_description(int i, const char *desc);
	///< Sets a description of the specified action of the object.
	///< @param i The action index corresponding to the action to be performed.
	///< @param desc The description to be assigned to this action.
	///< @return <EM>true</EM> if the description was successfully set.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/action.inl>

#endif // XFC_ATK_ACTION_HH

