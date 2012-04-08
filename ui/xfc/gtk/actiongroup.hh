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

/// @file xfc/gtk/actiongroup.hh
/// @brief A GtkActionGroup C++ wrapper interface.
///
/// Provides ActionGroup, an object that represents group of actions.

#ifndef XFC_GTK_ACTION_GROUP_HH
#define XFC_GTK_ACTION_GROUP_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_RADIO_ACTION_HH
#include <xfc/gtk/radioaction.hh>
#endif

#ifndef __GTK_ACTION_GROUP_H__
#include <gtk/gtkactiongroup.h>
#endif

namespace Xfc {

namespace Gtk {

class AccelKey;

/// @class ActionGroup actiongroup.hh xfc/gtk/actiongroup.hh
/// @brief A GtkActionGroup C++ wrapper class.
///
/// Actions are organised into groups. An action group is essentially a map from names to
/// Action objects. All actions that would make sense to use in a particular context should
/// be in a single group. Multiple action groups may be used for a particular user interface.
/// In fact, it is expected that most nontrivial applications will make use of multiple groups.
/// For example, in an application that can edit multiple documents, one group holding global
/// actions (e.g. quit, about, new), and one group per document holding actions that act on 
/// that document (eg. save, cut/copy/paste, etc). Each window's menus would be constructed
/// from a combination of two action groups. 
///
/// Accelerators are handled by the GTK+ accelerator map. All actions are assigned an 
/// accelerator path (which normally has the form \<Actions\>/group-name/action-name) and
/// a shortcut is associated with this accelerator path. All menuitems and toolitems take
/// on this accelerator path. The GTK+ accelerator map code makes sure that the correct 
/// shortcut is displayed next to the menu item. 
///
/// GTK+ doesn't let you override action group signals so there is no corresponding
/// ActionGroupSignals class. This means that if you want to respond to an action group
/// signal you must connect to it using the provided proxy signal function.
///
/// <B>Adding actions to an action group:</B>
///
/// When adding an action to an action group you must remember to call unref(). This is
/// because actions are G::Objects that are created with a reference count of one that
/// the caller owns. An action group increments the reference count of the actions you add.
/// So, if you don't want to hang onto to a reference, which you usually wont, you must 
/// call unref() to release the inital reference count.
///
/// There are two ways to add actions to an action group. The easiest way is to use one of
/// the overloaded add() methods. These methods create the action, add it to the action group,
/// unreference the action and return a pointer to the action that can then be connected to a
/// callback slot. For example:
///
/// @code
/// Gtk::ActionGroup *group = new Gtk::ActionGroup("TestActions");
/// Gtk::Action *action = group->add("cut", "C_ut", Gtk::StockId::CUT, Gtk::AccelKey("<control>X"), "Cut selected text to clipboard");	
/// action->signal_activate().connect(sigc::mem_fun(this, &Window::on_cut_action));
/// action = group->add("copy", "_Copy", Gtk::StockId::COPY, Gtk::AccelKey("<control>C"), "Copy selected text to clipboard");
/// action->signal_activate().connect(sigc::mem_fun(this, &Window::on_copy_action));
/// action = group->add("paste", "_Paste", Gtk::StockId::PASTE, Gtk::AccelKey("<control>V"), "Paste text from the clipboard");
/// action->signal_activate().connect(sigc::mem_fun(this, &Window::on_paste_action));
/// action = group->add("quit", Gtk::StockId::QUIT, Gtk::AccelKey("<control>Q"), "Quit the application");	
/// action->signal_activate().connect(sigc::ptr_fun(&Xfc::Main::quit));
/// @endcode
///
/// The other way to add actions to an action group is to create each action yourself and
/// call one of the add_action() methods to add it to the action group. This will require
/// a few more lines of code because you also need to set the tooltip, connect up the 
/// action's callback slot and unreference the action. For example, the above code would
/// look like this: 
///
/// @code
/// Gtk::ActionGroup *group = new Gtk::ActionGroup("TestActions");
/// Gtk::Action *action = new Gtk::Action("cut", "C_ut", StockId::CUT)
/// action->set_tooltip("Cut selected text to clipboard");	
/// group->add_action(*action, Gtk::AccelKey("<control>X"), sigc::mem_fun(this, &Window::on_cut_action));
/// action->unref();	
/// action = new Gtk::Action("copy", "_Copy", StockId::COPY)
/// action->set_tooltip("Copy selected text to clipboard");	
/// group->add_action(*action, Gtk::AccelKey("<control>C"), sigc::mem_fun(this, &Window::on_copy_action));	
/// action->unref();	
/// action = new Gtk::Action("paste", "_Paste", StockId::PASTE)
/// action->set_tooltip("Paste text from the clipboard");	
/// group->add_action(*action, Gtk::AccelKey("<control>V"), sigc::mem_fun(this, &Window::on_paste_action));	
/// action->unref();	
/// action = new Gtk::Action("quit", StockId::QUIT)
/// action->set_tooltip("Quit the application");	
/// group->add_action(*action, Gtk::AccelKey("<control>Q"), sigc::ptr_fun(&Xfc::Main::quit));	
/// @endcode
///
/// You can add a Gtk::ToggleAction and a Gtk::RadioAction to an action group using any of the
/// above methods. When adding a group radio actions you can either connect a callback slot to
/// the "activate" signal of each action, or alternatively, you can just connect one callback
/// slot to the "changed signal of one action in the group. It doesn't matter which one. Each
/// radio action in a group receives the changed signal (after the activate signal) and passes
/// as an argument a pointer to the newly activated action.
/// 
/// The easiest way the add radio actions to an action group is to use a Gtk::RadioActions
/// object. This object is for convenience only. It has several overloaded add() methods that
/// look similar to the Gtk::ActionGroup::add() methods above. You add all the radio actions
/// in one group to a RadioActions object and then you call add_actions() the add the group of
/// actions to an action group. A RadioActions object can only be  created on the stack. You
/// can reuse a RadioActions object to add a second group of radio actions by first calling 
/// Gtk::RadioActions::clear(). For example:
///
/// @code
/// Gtk::ActionGroup *group = new Gtk::ActionGroup("TestActions");
/// Gtk::RadioActions ras;
///
/// // First group
/// ras.add("justify-left", "_Left", Gtk::StockId::JUSTIFY_LEFT, JUSTIFY_LEFT, "Left justify the text"),
/// ras.add("justify-right", "_Right", Gtk::StockId::JUSTIFY_RIGHT, JUSTIFY_RIGHT, "Right justify the text");
/// ras.add("justify-center", "C_enter", Gtk::StockId::JUSTIFY_CENTER, JUSTIFY_CENTER, "Center justify the text");
/// ras.add("justify-fill", "_Fill", Gtk::StockId::JUSTIFY_FILL, JUSTIFY_FILL, "Fill justify the text");
/// group->add_actions(ras, JUSTIFY_LEFT, sigc::mem_fun(this, &Window::on_justify_action));	
/// 
/// // Second group
/// ras.clear();
/// ras.add("toolbar-icons", "Icons", TOOLBAR_ICONS);
/// ras.add("toolbar-text", "Text", TOOLBAR_TEXT);
/// ras.add("toolbar-both", "Both", TOOLBAR_BOTH);
/// ras.add("toolbar-both-horiz", "Both Horizontal", TOOLBAR_BOTH_HORIZ);
/// group->add_actions(ras, TOOLBAR_BOTH, sigc::mem_fun(this, &Window::on_toolbar_style_action));	
/// @endcode
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/uimanager.html">User Interface Manager</A> HOWTO and example.

class ActionGroup : public G::Object
{
	friend class G::Object;

	ActionGroup(const ActionGroup&);
	ActionGroup& operator=(const ActionGroup&);
	
protected:
/// @name Constructors
/// @{

	explicit ActionGroup(GtkActionGroup *action_group, bool owns_reference = true);
	///< Construct a new ActionGroup from an existing GtkActionGroup.
	///< @param action_group A pointer to a GtkActionGroup.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>action_group</EM> can be a newly created GtkActionGroup or 
	///< an existing GtkActionGroup (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{
	
	typedef G::Signal<void, Action&, Widget&> ConnectProxySignalType;
	typedef G::SignalProxy<TypeInstance, ConnectProxySignalType> ConnectProxySignalProxy;
	static const ConnectProxySignalType connect_proxy_signal;
	///< Connect proxy signal (see signal_connect_proxy()). Calls a slot with the signature:
	///< @code
	///< void function(Action& action, Widget& proxy);
	///< // action: The action proxy is being connected to.
	///< // proxy: The proxy widget being connected to action.
	///< @endcode

	typedef G::Signal<void, Action&, Widget&> DisconnectProxySignalType;
	typedef G::SignalProxy<TypeInstance, DisconnectProxySignalType> DisconnectProxySignalProxy;
	static const DisconnectProxySignalType disconnect_proxy_signal;
	///< Disconnect proxy signal (see signal_disconnect_proxy()). Calls a slot with the signature:
	///< @code
	///< void function(Action& action, Widget& proxy);
	///< // action: The action proxy is being disconnected from.
	///< // proxy: The proxy widget being disconnected from action.
	///< @endcode
	
	typedef G::Signal<void, Action&> PreActivateSignalType;
	typedef G::SignalProxy<TypeInstance, PreActivateSignalType> PreActivateSignalProxy;
	static const PreActivateSignalType pre_activate_signal;
	///< Pre-activate signal (see signal_pre_activate()). Calls a slot with the signature:
	///< @code
	///< void function(Action& action);
	///< // action: The action being activated.
	///< @endcode

	typedef G::Signal<void, Action&> PostActivateSignalType;
	typedef G::SignalProxy<TypeInstance, PostActivateSignalType> PostActivateSignalProxy;
	static const PostActivateSignalType post_activate_signal;
	///< Post-activate signal (see signal_post_activate()). Calls a slot with the signature:
	///< @code
	///< void function(Action& action);
	///< // action: The action being activated.
	///< @endcode

/// @}

public:
	typedef GtkActionGroup CObjectType;
	
	typedef sigc::slot<void> ActivateSlot;
	///< Signature of the callback slot to be called when an action is activated.
	///<
	///< <B>Example:</B> Method signature for ActivateSlot.
	///< @code
	///< void method();
	///< @endcode
	
	typedef sigc::slot<void, RadioAction&> ChangedSlot;
	///< Signature of the callback slot to be called when a radio action is changed.
	///<
	///< <B>Example:</B> Method signature for ChangedSlot.
	///< @code
	///< void method(RadioAction& activated);
	///< // activated: The member of the radio action group which has just been activated.
	///< @endcode

/// @name Constructors
/// @{

	ActionGroup(const char *name);
	ActionGroup(const String& name);
	///< Constructs a new action group with a reference count of 1 that the caller owns.
	///< @param name The name of the action group.
	///<
	///< The name of the action group is used when associating keybindings with the actions.

	virtual ~ActionGroup();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkActionGroup* gtk_action_group() const;
	///< Get a pointer to the GtkActionGroup structure.

	operator GtkActionGroup* () const;
	///< Conversion operator; safely converts an ActionGroup to a GtkActionGroup pointer.

	bool get_sensitive() const;
	///< Determines whether the action group is sensitive. 
	///< @return <EM>true</EM> if the group is sensitive.
	///<	
	///< The constituent actions can only be logically sensitive (see Gtk::Action::is_sensitive())
	///< if they are sensitive (see Gtk::Action::get_sensitive()) and their group is sensitive.

	bool get_visible() const;
	///< Determines whether the group is visible. 
	///Returns :
	///< @return <EM>true</EM> if the group is visible.
	///<	
	///< The constituent actions can only be logically visible (see Gtk::Action::is_visible()) 
	///< if they are visible (see Gtk::Action::get_visible()) and their group is visible.

	String get_name() const;
	///< Gets the name of the action group.
	///< @return The name of the action group.

	Action* get_action(const char *action_name);
	Action* get_action(const String& action_name);
	///< Looks up an action in the action group by name.
	///< @param action_name The name of the action.
	///< @return The action, or null if no action by that name exists.

/// @}
/// @name Methods
/// @{

	void set_sensitive(bool sensitive);
	///< Changes the sensitivity of the action group.
	///< @param sensitive The new sensitivity.
	 
	void set_visible(bool visible);
	///< Changes the visibility of the action group.
	///< @param visible The new visibility.
	
	bool list_actions(std::vector<Action*>& actions) const;
	///< Lists the action objects in the action group.
	///< @param actions A reference to a vector of Action pointers to hold the list of actions.
	///< @return <EM>true</EM> if the vector of actions is not empty, <EM>false</EM> otherwise.

	void add_action(Action& action);
	///< Adds an action object to the action group.
	///< @param action An action object.
	///<
	///< Note that if the action set a stock item this method sets up the stock item's
	///< accelerator path for the action. Otherwise you must set the accelerator path
	///< yourself by calling Gtk::AccelMap::add_entry() and Gtk::Action::set_accel_path().

	void add_action(Action& action, const AccelKey& accel_key);
	///< Adds an action to the action group and sets up the accelerator. 
	///< @param action The action to add. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///<
	///< Accelerator paths are set to \<Actions\>/group-name/action-name.
	
	void add_action(Action& action, const ActivateSlot& slot);
	///< Adds an action to the action group and connects <EM>slot</EM> to its "activate" signal.
	///< @param action An action object.
	///< @param slot A callback slot to connect to the action's activate signal.	
	///<
	///< Note that if the action set a stock item this method sets up the stock item's
	///< accelerator path for the action. Otherwise you must set the accelerator path
	///< yourself by calling Gtk::AccelMap::add_entry() and Gtk::Action::set_accel_path().

	void add_action(Action& action, const AccelKey& accel_key, const ActivateSlot& slot);
	///< Adds an action to the action group, sets up the accelerator and connects <EM>slot</EM>
	///< to the action's "activate" signal.  
	///< @param action The action to add. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param slot A callback slot to connect to the action's activate signal.	
	///<
	///< Accelerator paths are set to \<Actions\>/group-name/action-name. The accelerator 
	///< must be in the format understood by Gtk::accelerator_parse(), or null to use the
	///< stock accelerator.	
		
	void add_action(RadioAction& action, const AccelKey& accel_key);
	///< Adds a radio action to the action group and sets up the accelerator. 
	///< @param action The radio action to add. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///<
	///< Accelerator paths are set to \<Actions\>/group-name/action-name.
	
	void add_action(RadioAction& action, const ChangedSlot& slot);
	///< Adds a radio action to the action group and connects <EM>slot</EM> to its "changed" signal.
	///< @param action A radio action object.
	///< @param slot A callback slot to connect to the radio action's changed signal.	
	///<
	///< You only need to connect one ChangedSlot to a radio action, usually the first
	///< in a group. All other members of the same group will also receive the "changed"
	///< signal. 
	///<
	///< Note that if the action set a stock item this method sets up the stock item's
	///< accelerator path for the action. Otherwise you must set the accelerator path
	///< yourself by calling Gtk::AccelMap::add_entry() and Gtk::Action::set_accel_path().
	
	void add_action(RadioAction& action, const AccelKey& accel_key, const ChangedSlot& slot);
	///< Adds a radio action to the action group, sets up the accelerator and connects 
	///< <EM>slot</EM> to the action's "changed" signal.  
	///< @param action The action to add. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param slot A callback slot to connect to the radio action's "changed" signal.	
	///<
	///< You only need to connect one ChangedSlot to a radio action, usually the first
	///< in a group. All other members of the same group will also receive the "changed"
	///< signal. 
	///<
	///< Accelerator paths are set to \<Actions\>/group-name/action-name. The accelerator 
	///< must be in the format understood by Gtk::accelerator_parse(), or null to use the
	///< stock accelerator.	
		
	void add_actions(const RadioActions& group, int value, const ChangedSlot& slot);
	///< Adds the actions in the RadioActions group to the action group, sets the default
	///< value and connects <EM>slot</EM> to the changed signal of the first radio action.
	///< @param group A RadioActions group.
	///< @param value The value of the action to activate initially, or -1 if no action should be activated. 
	///< @param slot The slot to connect to the changed signal. 
	///<
	///< This is a convenience method that uses a Gtk::RadioActions group to set up a group
	///< Gtk::RadioAction and adds them to the action group with one function call. The advantage
	///< of using a RadioActions group is that it handles the reference counting issues for you.
		
	void remove_action(Action& action);
	///< Removes an action object from the action group.
	///< @param action An action object.

/// @}
/// @name Action create and add methods.
/// @{

	Action* add(const char *name, const char *label, const char *tooltip = 0);
	///< Creates and adds a new action to the action group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param tooltip The tooltip to display for the action.
	
	Action* add(const char *name, const char *label, const AccelKey& accel_key, const char *tooltip = 0);
	///< Creates and adds a new action to the action group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param tooltip The tooltip to display for the action.
	
	Action* add(const char *name, const StockId& stock_id, const char *tooltip = 0);
	///< Creates and adds a new action to the action group.
	///< @param name A unique name for the action. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param tooltip The tooltip to display for the action.
	
	Action* add(const char *name, const StockId& stock_id, const AccelKey& accel_key, const char *tooltip = 0);
	///< Creates and adds a new action to the action group.
	///< @param name A unique name for the action. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param tooltip The tooltip to display for the action.
	
	Action* add(const char *name, const char *label, const StockId& stock_id, const char *tooltip = 0);
	///< Creates and adds a new action to the action group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param tooltip The tooltip to display for the action.
	
	Action* add(const char *name, const char *label, const StockId& stock_id, const AccelKey& accel_key, const char *tooltip = 0);
	///< Creates and adds a new action to the action group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param tooltip The tooltip to display for the action.
	
/// @}
/// @name ToggleAction create and add methods.
/// @{
 	
	ToggleAction* add(const char *name, const StockId& stock_id, bool is_active, const char *tooltip = 0);
	///< Creates and adds a new toggle action to the action group.
	///< @param name A unique name for the action. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param is_active The initial state of the toggle action.
	///< @param tooltip The tooltip to display for the action.
	
	ToggleAction* add(const char *name, const StockId& stock_id, const AccelKey& accel_key, bool is_active, const char *tooltip = 0);
	///< Creates and adds a new toggle action to the action group.
	///< @param name A unique name for the action. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param is_active The initial state of the toggle action.
	///< @param tooltip The tooltip to display for the action.
	
	ToggleAction* add(const char *name, const char *label, bool is_active, const char *tooltip = 0);
	///< Creates and adds a new toggle action to the action group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param is_active The initial state of the toggle action.
	///< @param tooltip The tooltip to display for the action.
	
	ToggleAction* add(const char *name, const char *label, const AccelKey& accel_key, bool is_active, const char *tooltip = 0);
	///< Creates and adds a new toggle action to the action group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param is_active The initial state of the toggle action.
	///< @param tooltip The tooltip to display for the action.
	
	ToggleAction* add(const char *name, const char *label, const StockId& stock_id, bool is_active, const char *tooltip = 0);
	///< Creates and adds a new toggle action to the action group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param is_active The initial state of the toggle action.
	///< @param tooltip The tooltip to display for the action.
	
	ToggleAction* add(const char *name, const char *label, const StockId& stock_id, const AccelKey& accel_key, bool is_active, const char *tooltip = 0);
	///< Creates and adds a new toggle action to the action group.
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///< @param accel_key An AccelKey object specifying the accelerator for the action.
	///< @param is_active The initial state of the toggle action.
	///< @param tooltip The tooltip to display for the action.

/// @}
/// @name Signal Proxies
/// @{

	const ConnectProxySignalProxy signal_connect_proxy();
	///< Connect to the connect_proxy_signal; emitted after connecting a proxy widget to an action in
	///< the group. Note that the proxy may have been connected to a different action before. This is
	///< intended for simple customizations for which a custom action class would be too clumsy, e.g.
	///< showing tooltips for menuitems in the statusbar. Gtk::UIManager proxies the signal and 
	///< provides global notification just before any action is connected to a proxy, which is 
	///< probably more convenient to use.	
	
	const DisconnectProxySignalProxy signal_disconnect_proxy();
	///< Connect to the disconnect_proxy_signal; emitted after disconnecting a proxy widget from an
	///< action in the group. Gtk::UIManager proxies the signal and provides global notification just
	///< before any action is connected to a proxy widget, which is probably more convenient to use.

	const PreActivateSignalProxy signal_pre_activate();
	///< Connect to the pre_activate_signal; emitted just before the action in the action_group is activated.
	///< This is intended for Gtk::UIManager to proxy the signal and provide global notification just before
	///< any action is activated.

	const PostActivateSignalProxy signal_post_activate();
	///< Connect to the post_activate_signal; emitted just after the action in the action_group is activated.
	///< This is intended for Gtk::UIManager to proxy the signal and provide global notification just after
	///< any action is activated.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/actiongroup.inl>

#endif // XFC_GTK_ACTION_GROUP_HH

