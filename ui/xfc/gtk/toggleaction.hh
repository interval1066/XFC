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

/// @file xfc/gtk/toggleaction.hh
/// @brief A GtkToggleAction C++ wrapper interface.
///
/// Provides ToggleAction, an object that represents an action which can be toggled between two states.

#ifndef XFC_GTK_TOGGLE_ACTION_HH
#define XFC_GTK_TOGGLE_ACTION_HH

#ifndef XFC_GTK_ACTION_HH
#include <xfc/gtk/action.hh>
#endif

#ifndef __GTK_TOGGLE_ACTION_H__
#include <gtk/gtktoggleaction.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class ToggleAction toggleaction.hh xfc/gtk/toggleaction.hh
/// @brief A GtkToggleAction C++ wrapper class.
///
/// A ToggleAction corresponds roughly to a CheckMenuItem. It has an "active" state
/// specifying whether the action has been checked or not. 
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/uimanager.html">User Interface Manager</A> HOWTO and example.

class ToggleAction : public Action
{
	friend class G::Object;

	ToggleAction(const ToggleAction&);
	ToggleAction& operator=(const ToggleAction&);

protected:
/// @name Constructors
/// @{

	explicit ToggleAction(GtkToggleAction *action, bool owns_reference = true);
	///< Construct a new ToggleAction from an existing GtkToggleAction.
	///< @param action A pointer to a GtkToggleAction.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>action</EM> can be a newly created GtkToggleAction or an existing
	///< GtkToggleAction (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ToggledSignalType;
	typedef G::SignalProxy<TypeInstance, ToggledSignalType> ToggledSignalProxy;
	static const ToggledSignalType toggled_signal;
	///< Toggled signal (see signal_toggled()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkToggleAction CObjectType;

/// @name Constructors
/// @{

	ToggleAction(const char *name, const char *label, bool is_active);	
	ToggleAction(const String& name, const String& label, bool is_active);
	///< Constructs a new ToggleAction object with a reference count of 1 that the caller owns. 
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param is_active Whether the initial state of the toggle action is <EM>active</EM>.  
	///<	
	///< To add the action to a ActionGroup and set the accelerator for the action, 
	///< call Gtk::ActionGroup::add_action().
	
	ToggleAction(const char *name, const StockId& stock_id, bool is_active);	
	ToggleAction(const String& name, const StockId& stock_id, bool is_active);
	///< Constructs a new ToggleAction object. 
	///< @param name A unique name for the action. 
	///< @param is_active Whether the initial state of the toggle action is <EM>active</EM>.  
	///< @param stock_id The stock icon and label to display in widgets representing the action. 
	///<	
	///< To add the action to a ActionGroup and set the accelerator for the action, 
	///< call Gtk::ActionGroup::add_action(). The ToggleAction is created with a reference count
	///< of 1 that the caller owns.
		
	ToggleAction(const char *name, const char *label, const StockId& stock_id, bool is_active);	
	ToggleAction(const String& name, const String& label, const StockId& stock_id, bool is_active);
	///< Constructs a new ToggleAction object. 
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param is_active Whether the initial state of the toggle action is <EM>active</EM>.  
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///<	
	///< To add the action to a ActionGroup and set the accelerator for the action, 
	///< call Gtk::ActionGroup::add_action(). Note that <EM>label</EM> is displayed
	///< instead of the <EM>stock_id</EM> label. The ToggleAction is created with a 
	///< reference count of 1 that the caller owns.

	virtual ~ToggleAction();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkToggleAction* gtk_toggle_action() const;
	///< Get a pointer to the GtkToggleAction structure.

	operator GtkToggleAction* () const;
	///< Conversion operator; safely converts an ToggleAction to a GtkToggleAction pointer.

	bool get_active() const;
	///< Determines the checked state of the toggle action.
	///< @return <EM>true</EM> if the toggle action is checked. 

	bool get_draw_as_radio() const;
	///< Determines whether the action should have proxies like a radio action.
	///< @return Whether the action should have proxies like a radio action.
	
/// @}
/// @name Methods
/// @{

	void toggled();
	///< Emits the "toggled" signal on the toggle action.
	
	void set_active(bool is_active);
	///< Sets the checked state of the toggle action.
	///< @param is_active Whether the action should be checked or not.
	 
	void set_draw_as_radio(bool draw_as_radio);
	///< Sets whether the action should have proxies like a radio action.
	///< @param draw_as_radio Whether the action should have proxies like a radio action.

/// @}
/// @name Signal Proxies
/// @{

	const ToggledSignalProxy signal_toggled();
	///< Connect to the toggled_signal; emitted when the action is toggled between its two states.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/toggleaction.inl>

#endif // XFC_GTK_TOGGLE_ACTION_HH

