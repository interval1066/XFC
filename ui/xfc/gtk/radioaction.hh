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

/// @file xfc/gtk/radioaction.hh
/// @brief A GtkRadioAction C++ wrapper interface.
///
/// Provides RadioAction and RadioActions. RadioAction is an object that represents
/// an action of which only one in a group can be active. RadioActions represents a
/// group of actions. It is a convenience class that is used as a way to easily add 
/// a group of radio actions to a Gtk::ActionGroup.

#ifndef XFC_GTK_RADIO_ACTION_HH
#define XFC_GTK_RADIO_ACTION_HH

#ifndef XFC_GTK_TOGGLE_ACTION_HH
#include <xfc/gtk/toggleaction.hh>
#endif

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef __GTK_RADIO_ACTION_H__
#include <gtk/gtkradioaction.h>
#endif

namespace Xfc {

namespace Gtk {

class AccelKey;

/// @class RadioAction radioaction.hh xfc/gtk/radioaction.hh
/// @brief A GtkRadioAction C++ wrapper class.
///
/// A RadioAction is similar to RadioMenuItem. A number of radio actions
/// can be linked together so that only one may be active at any one time. 
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/uimanager.html">User Interface Manager</A> HOWTO and example.

class RadioAction : public ToggleAction
{
	friend class G::Object;

	RadioAction(const RadioAction&);
	RadioAction& operator=(const RadioAction&);

protected:
/// @name Constructors
/// @{

	explicit RadioAction(GtkRadioAction *action, bool owns_reference = true);
	///< Construct a new RadioAction from an existing GtkRadioAction.
	///< @param action A pointer to a GtkRadioAction.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>action</EM> can be a newly created GtkRadioAction or an existing
	///< GtkRadioAction (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, RadioAction&> ChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChangedSignalType> ChangedSignalProxy;
	static const ChangedSignalType changed_signal;
	///< Changed signal (see signal_changed()). Calls a slot with the signature:
	///< @code
	///< void function(RadioAction& current);
	///< // current: The member of the action group which has just been activated. 
	///< @endcode

/// @}

public:
	typedef GtkRadioAction CObjectType;
	
	typedef GSList Group;
	///< The radio action group.

/// @name Constructors
/// @{

	RadioAction(const RadioAction *group, const char *name, const char *label, int value);	
	RadioAction(const RadioAction *group, const String& name, const String& label, int value);
	///< Constructs a RadioAction object that is a member of <EM>group</EM>. 
	///< @param group An existing radio button group, or null to start a new group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param value The value which get_current_value() should return if this action is selected. 
	///<	
	///< To add the action to an ActionGroup and set the accelerator for the action, 
	///< call Gtk::ActionGroup::add_action(). The RadioAction is created with a reference
	///< count of 1 that the caller owns.
	
	RadioAction(const RadioAction *group, const char *name, const StockId& stock_id, int value);	
	RadioAction(const RadioAction *group, const String& name, const StockId& stock_id, int value);
	///< Constructs a RadioAction object that is a member of <EM>group</EM>. 
	///< @param group An existing radio button group, or null to start a new group.
	///< @param name A unique name for the action. 
	///< @param stock_id The stock icon and label to display in widgets representing the action. 
	///< @param value The value which get_current_value() should return if this action is selected. 
	///<	
	///< To add the action to an ActionGroup and set the accelerator for the action, 
	///< call Gtk::ActionGroup::add_action(). The RadioAction is created with a reference
	///< count of 1 that the caller owns.
	
	RadioAction(const RadioAction *group, const char *name, const char *label, const StockId& stock_id, int value);	
	RadioAction(const RadioAction *group, const String& name, const String& label, const StockId& stock_id, int value);
	///< Constructs a RadioAction object that is a member of <EM>group</EM>. 
	///< @param group An existing radio button group, or null to start a new group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param value The value which get_current_value() should return if this action is selected. 
	///<	
	///< To add the action to an ActionGroup and set the accelerator for the action, 
	///< call Gtk::ActionGroup::add_action(). Note that <EM>label</EM> is displayed
	///< instead of the <EM>stock_id</EM> label. The RadioAction is created with a reference
	///< count of 1 that the caller owns.
	
	virtual ~RadioAction();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkRadioAction* gtk_radio_action() const;
	///< Get a pointer to the GtkRadioAction structure.

	operator GtkRadioAction* () const;
	///< Conversion operator; safely converts an RadioAction to a GtkRadioAction pointer.

	Group* get_group() const;
	///< Returns the list representing the radio group for this object.
	///< @return The list representing the radio group for this object.
	
	int get_value() const;
	///< Obtains the value for this radio action.
	///< @return The value that identifies this radio action.

	int get_current_value() const;
	///< Obtains the value of the currently active member of the group to which action belongs.
	///< @return The value of the currently active group member.
	
/// @}
/// @name Methods
/// @{

	void set_group(Group *group);
	///< Sets the radio group for the radio action object.
	///< @param group A list representing a radio group.

/// @}
/// @name Signal Proxies
/// @{

	const ChangedSignalProxy signal_changed();
	///< Connect to the changed_signal; emitted on every member of a radio group when
	///< the active member is changed. The signal gets emitted after the "activate" 
	///< signals for the previous and current active members. When creating a group
	///< radio actions manually with Gtk::ActionGroup::add_action() you only need to
	///< connect the changed_signal to the first radio action in the group.

/// @}
};

/// @class RadioActions radioaction.hh xfc/gtk/radioaction.hh
/// @brief A C++ wrapper class for a group of radio actions.
///
/// RadioActions is a convenience class that makes it easy to add a group of radio actions to
/// a Gtk::ActionGroup. RadioActions handles setting the group, tooltip and accelerator. It
/// calls unref() on each action after adding it to a Gtk::ActionGroup and it connects the
/// first radio action in the group to the GtkRadioAction "changed" signal. If you add radio
/// actions to an action group independantly by calling Gtk::ActionGroup::add_actions() you
/// would need to do all these things yourself. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/uimanager.html">User Interface Manager</A> HOWTO and example.

class RadioActions : public StackObject
{
	friend class ActionGroup;	
	
	RadioActions(const RadioActions&);
	RadioActions& operator=(const RadioActions&);
	
	std::vector<RadioAction*> actions_;
	RadioAction *group_;
	
public:
/// @name Constructors
/// @{
	
	RadioActions();
	///< Constructs a new RadioActions group. RadioActions can only be constructed
	///< on the stack. They can't be constructed dynamically.
	
	~RadioActions();
	///< Destructor.

/// @}
/// @name Methods
/// @{

	RadioAction* add(const char *name, const char *label, int value, const char *tooltip = 0);
	///< Creates and adds a new radio action to the group of radio actions.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param value The value which get_current_value() should return if this action is selected. 
	///< @param tooltip The tooltip to display for the action.
	
	RadioAction* add(const char *name, const char *label, const AccelKey& accel_key, int value, const char *tooltip = 0);
	///< Creates and adds a new radio action to the group of radio actions.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param value The value which get_current_value() should return if this action is selected. 
	///< @param tooltip The tooltip to display for the action.
	
	RadioAction* add(const char *name, const StockId& stock_id, int value, const char *tooltip = 0);
	///< Creates and adds a new radio action to the group of radio actions.
	///< @param name A unique name for the action. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param value The value which get_current_value() should return if this action is selected. 
	///< @param tooltip The tooltip to display for the action.
	
	RadioAction* add(const char *name, const StockId& stock_id, const AccelKey& accel_key, int value, const char *tooltip = 0);
	///< Creates and adds a new radio action to the group of radio actions.
	///< @param name A unique name for the action. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param value The value which get_current_value() should return if this action is selected. 
	///< @param tooltip The tooltip to display for the action.
	
	RadioAction* add(const char *name, const char *label, const StockId& stock_id, int value, const char *tooltip = 0);
	///< Creates and adds a new radio action to the group of radio actions.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param value The value which get_current_value() should return if this action is selected. 
	///< @param tooltip The tooltip to display for the action.
	
	RadioAction* add(const char *name, const char *label, const StockId& stock_id, const AccelKey& accel_key, int value, const char *tooltip = 0);
	///< Creates and adds a new radio action to the group of radio actions.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param value The value which get_current_value() should return if this action is selected. 
	///< @param tooltip The tooltip to display for the action.

	void clear();
	///< Removes all the actions from this radio actions group.
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/radioaction.inl>

#endif // XFC_GTK_RADIO_ACTION_HH

