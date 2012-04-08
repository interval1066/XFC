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

/// @file xfc/gtk/uimanager.hh
/// @brief A GtkUIManager C++ wrapper interface.
///
/// Provides UIManager, an object that constructs menus and toolbars from an XML description.

#ifndef XFC_GTK_UI_MANAGER_HH
#define XFC_GTK_UI_MANAGER_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_ACTION_GROUP_H
#include <xfc/gtk/actiongroup.hh>
#endif

#ifndef __GTK_UI_MANAGER_H__
#include <gtk/gtkuimanager.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Error;
}

namespace Gtk {

class AccelGroup;
class Widget;

/// @enum UIManagerItemType
/// Item type values used by Gtk::UIManager::add_ui() to determine what UI element to create. 

enum UIManagerItemType
{
	UI_MANAGER_AUTO = GTK_UI_MANAGER_AUTO, ///< Pick the type of the UI element according to context. 
	UI_MANAGER_MENUBAR = GTK_UI_MANAGER_MENUBAR, ///< Create a menubar.
	UI_MANAGER_MENU = GTK_UI_MANAGER_MENU, ///< Create a menu.
	UI_MANAGER_TOOLBAR = GTK_UI_MANAGER_TOOLBAR, ///< Create a toolbar.
	UI_MANAGER_PLACEHOLDER = GTK_UI_MANAGER_PLACEHOLDER, ///< Insert a placeholder.
	UI_MANAGER_POPUP = GTK_UI_MANAGER_POPUP, ///< Create a popup menu.
	UI_MANAGER_MENUITEM = GTK_UI_MANAGER_MENUITEM, ///< Create a menuitem.
	UI_MANAGER_TOOLITEM = GTK_UI_MANAGER_TOOLITEM, ///< Create a toolitem.
	UI_MANAGER_SEPARATOR = GTK_UI_MANAGER_SEPARATOR, ///< Create a separator.
	UI_MANAGER_ACCELERATOR = GTK_UI_MANAGER_ACCELERATOR ///< Install an accelerator.
};

/// UIManagerItemTypeField holds one or more values from the Gtk::UIManagerItemType enumeration OR'd together.

typedef unsigned int UIManagerItemTypeField;

/// @class UIManager uimanager.hh xfc/gtk/uimanager.hh
/// @brief A GtkUIManager C++ wrapper class.
///
/// A UIManager constructs a user interface (menus and toolbars) from one or more 
/// XML UI definitions, which reference actions from one or more action groups. 
///
/// <B>UI Definitions</B>
///
/// The UI definitions are specified in an XML format which can be roughly described by the following DTD.
/// 
/// @code
/// &lt;!ELEMENT ui          (menubar|toolbar|popup|accelerator)* &gt;
/// &lt;!ELEMENT menubar     (menuitem|separator|placeholder|menu)* &gt;
/// &lt;!ELEMENT menu        (menuitem|separator|placeholder|menu)* &gt;
/// &lt;!ELEMENT popup       (menuitem|separator|placeholder|menu)* &gt;
/// 
/// &lt;!ELEMENT toolbar     (toolitem|separator|placeholder)* &gt;
/// &lt;!ELEMENT placeholder (menuitem|toolitem|separator|placeholder|menu)* &gt;
/// &lt;!ELEMENT menuitem     EMPTY &gt;
/// &lt;!ELEMENT toolitem     EMPTY &gt;
/// &lt;!ELEMENT separator    EMPTY &gt;
/// &lt;!ELEMENT accelerator  EMPTY &gt;
/// &lt;!ATTLIST menubar      name               #IMPLIED &gt;
/// &lt;!ATTLIST toolbar      name               #IMPLIED &gt;
/// &lt;!ATTLIST popup        name               #IMPLIED &gt;
/// 
/// &lt;!ATTLIST placeholder  name               #IMPLIED &gt;
/// &lt;!ATTLIST separator    name               #IMPLIED &gt;
/// &lt;!ATTLIST menu         name               #IMPLIED
///                        action             #REQUIRED
///                        position (top|bot) #IMPLIED &gt;
/// &lt;!ATTLIST menuitem     name               #IMPLIED
///                        action             #REQUIRED
///                        position (top|bot) #IMPLIED &gt;
/// &lt;!ATTLIST toolitem     name               #IMPLIED
///                        action             #REQUIRED
///                        position (top|bot) #IMPLIED &gt;
/// &lt;!ATTLIST accelerator  name               #IMPLIED
///                        action             #REQUIRED &gt;
/// @endcode
///
/// There are some additional restrictions beyond those specified in the DTD, e.g. 
/// every toolitem must have a toolbar in its anchestry and every menuitem must have
/// a menubar or popup in its anchestry. Since a GMarkup parser is used to parse 
/// the UI description, it must not only be valid XML, but valid GMarkup. If a name
/// is not specified, it defaults to the action. If an action is not specified either,
/// the element name is used. 
/// 
/// <B>Example:</B>. A UI definition
///
/// @code
/// &lt;ui&gt;
///   &lt;menubar&gt;
///     &lt;menu name="FileMenu" action="FileMenuAction"&gt;
///       &lt;menuitem name="New" action="New2Action" /&gt;
///       &lt;placeholder name="FileMenuAdditions" /&gt;
///     &lt;/menu&gt;
///     &lt;menu name="JustifyMenu" action="JustifyMenuAction"&gt;
///       &lt;menuitem name="Left" action="justify-left"/&gt;
///       &lt;menuitem name="Centre" action="justify-center"/&gt;
///       &lt;menuitem name="Right" action="justify-right"/&gt;
///       &lt;menuitem name="Fill" action="justify-fill"/&gt;
///     &lt;/menu&gt;
///   &lt;/menubar&gt;
///   &lt;toolbar action="toolbar1"&gt;
///     &lt;placeholder name="JustifyToolItems"&gt;
///       &lt;separator/&gt;
///       &lt;toolitem name="Left" action="justify-left"/&gt;
///       &lt;toolitem name="Centre" action="justify-center"/&gt;
///       &lt;toolitem name="Right" action="justify-right"/&gt;
///       &lt;toolitem name="Fill" action="justify-fill"/&gt;
///       &lt;separator/&gt;
///     &lt;/placeholder&gt;
///   &lt;/toolbar&gt;
/// &lt;/ui&gt;
/// @endcode
///
/// The constructed widget hierarchy is very similar to the element tree of the
/// XML, with the exception that placeholders are merged into their parents. The 
/// correspondence of XML elements to widgets should be almost obvious: 
///
/// @code
/// menubar     - a Gtk::MenuBar
/// toolbar     - a Gtk::Toolbar
/// popup       - a toplevel Gtk::Menu
/// menu        - a Gtk::Menu attached to a menuitem
/// menuitem    - a Gtk::MenuItem subclass, the exact &type depends on the action
/// toolitem    - a Gtk::ToolItem subclass, the exact &type depends on the action
/// separator   - a Gtk::SeparatorMenuItem or Gtk::SeparatorToolItem
/// accelerator - a keyboard accelerator
/// @endcode
///
/// The "position" attribute determines where a constructed widget is positioned 
/// with respect to its siblings in the partially constructed tree. If it is "top",
/// the widget is prepended, otherwise it is appended.
///
/// <HR><B>UI Merging</B>
///
/// The most remarkable feature of UIManager is that it can overlay a set of menuitems
/// and toolitems over another one, and demerge them later. 
/// 
/// Merging is done based on the names of the XML elements. Each element is identified by a path
/// which consists of the names of its anchestors, separated by slashes. For example, the menuitem
/// named "Left" in the example above has the path /ui/menubar/JustifyMenu/Left and the toolitem
/// with the same name has path /ui/toolbar1/JustifyToolItems/Left.
///
/// <HR><B>Accelerators</B>
///
/// Every action has an accelerator path. Accelerators are installed together with menuitem proxies,
/// but they can also be explicitly added with \<accelerator\> elements in the UI definition. This 
/// makes it possible to have accelerators for actions even if they have no visible proxies. 
///
/// <HR><B>Smart Separators</B>
///
/// The separators created by UIManager are "smart", i.e. they do not show up in the UI unless they end
/// up between two visible menu or tool items. Separators which are located at the very beginning or end
/// of the menu or toolbar containing them, or multiple separators next to each other, are hidden. This
/// is a useful feature, since the merging of UI elements from multiple sources can make it hard or 
/// impossible to determine in advance whether a separator will end up in such an unfortunate position. 
///
/// <HR><B>Empty Menus</B>
///
/// Submenus pose similar problems to separators in connection with merging. It is impossible to know
/// in advance whether they will end up empty after merging. UIManager offers two ways to treat empty
/// submenus:
/// - make them disappear by hiding the menu item they're attached to 
/// - add an insensitive "Empty" item
///
/// The behaviour is chosen based on the "is_important" property of the action to which the submenu
/// is associated. 
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/uimanager.html">User Interface Manager</A> HOWTO and example.

class UIManager : public G::Object
{
	friend class G::Object;

	UIManager(const UIManager&);
	UIManager& operator=(const UIManager&);

protected:
/// @name Constructors
/// @{

	explicit UIManager(GtkUIManager *ui_manager, bool owns_reference = true);
	///< Construct a new UIManager from an existing GtkUIManager.
	///< @param ui_manager A pointer to a GtkUIManager.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>ui_manager</EM> can be a newly created GtkUIManager or an existing
	///< GtkUIManager (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Widget&> AddWidgetSignalType;
	typedef G::SignalProxy<TypeInstance, AddWidgetSignalType> AddWidgetSignalProxy;
	static const AddWidgetSignalType add_widget_signal;
	///< Add widget signal (see signal_add_widget()). Calls a slot with the signature:
	///< @code
	///< void function(Widget& widget);
	///< // widget: The added widget.
	///< @endcode

	typedef G::Signal<void> ActionsChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ActionsChangedSignalType> ActionsChangedSignalProxy;
	static const ActionsChangedSignalType actions_changed_signal;
	///< Actions changed signal (see signal_actions_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, Action&, Widget&> ConnectProxySignalType;
	typedef G::SignalProxy<TypeInstance, ConnectProxySignalType> ConnectProxySignalProxy;
	static const ConnectProxySignalType connect_proxy_signal;
	///< Connect proxy signal (see signal_connect_proxy()). Calls a slot with the signature:
	///< @code
	///< void function(Action& action, Widget& proxy);
	///< // action: The action.
	///< // proxy: The proxy widget. 
	///< @endcode
	
	typedef G::Signal<void, Action&, Widget&> DisconnectProxySignalType;
	typedef G::SignalProxy<TypeInstance, DisconnectProxySignalType> DisconnectProxySignalProxy;
	static const DisconnectProxySignalType disconnect_proxy_signal;
	///< Disconnect proxy signal (see signal_disconnect_proxy()). Calls a slot with the signature:
	///< @code
	///< void function(Action& action, Widget& proxy);
	///< // action: The action.
	///< // proxy: The proxy widget. 
	///< @endcode

	typedef G::Signal<void, Action&> PreActivateSignalType;
	typedef G::SignalProxy<TypeInstance, PreActivateSignalType> PreActivateSignalProxy;
	static const PreActivateSignalType pre_activate_signal;
	///< Pre-activate signal (see signal_pre_activate()). Calls a slot with the signature:
	///< @code
	///< void function(Action& action);
	///< // action: The action.
	///< @endcode

	typedef G::Signal<void, Action&> PostActivateSignalType;
	typedef G::SignalProxy<TypeInstance, PostActivateSignalType> PostActivateSignalProxy;
	static const PostActivateSignalType post_activate_signal;
	///< Post-activate signal (see signal_post_activate()). Calls a slot with the signature:
	///< @code
	///< void function(Action& action);
	///< // action: The action.
	///< @endcode

/// @}

public:
	typedef GtkUIManager CObjectType;

/// @name Constructors
/// @{

	UIManager();
	///< Constructs a new UIManager object with a reference count of 1 that the caller owns.
	
	virtual ~UIManager();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkUIManager* gtk_ui_manager() const;
	///< Get a pointer to the GtkUIManager structure.

	operator GtkUIManager* () const;
	///< Conversion operator; safely converts an UIManager to a GtkUIManager pointer.

	bool get_add_tearoffs() const;
	///< Determines whether menus generated by this UIManager will have tearoff menu items.
	///< @return Whether tearoff menu items are added.

	bool get_action_groups(std::vector<ActionGroup*>& action_groups) const;
	///< Gets the list of action groups associated with the UIManager.
	///< @param action_groups A vector of ActionGroup* to hold the action groups.
	///< @returns <EM>true</EM> if any action groups were returned, <EM>false</EM> if there were none.

	AccelGroup* get_accel_group() const;
	///< Gets the AccelGroup associated with the UIManager.
	///< @return The AccelGroup. 
	
	Widget* get_widget(const char *path) const;
	Widget* get_widget(const String& path) const;
	///< Looks up a widget by following a path. 
	///< @param path A path. 
	///< @return The widget found by following the path, or null if no widget was found.
	///<	
	///< The path consists of the names specified in the XML description of the UI
	///< separated by '/'. Elements which don't have a name or action attribute in the
	///< XML (e.g. \<popup\>) can be addressed by their XML element name (e.g. "popup").
	///< The root element ("/ui") can be omitted in the path.
	///<
	///< Note that the widget found by following a path that ends in a \<menu\> element
	///< is the menuitem to which the menu is attached, not the menu itself.

	bool get_toplevels(std::vector<Widget*>& toplevels, UIManagerItemTypeField types) const;
	///< Obtains a list of all toplevel widgets of the requested types.
	///< @param toplevels A vector of widget* to hold the list of all toplevel widgets of the requested types. 
	///< @param types Specifies the Gtk::UIManagerItemType of toplevel widgets to include. 
	///<	
	///< The allowed types are Gtk::UI_MANAGER_MENUBAR, Gtk::UI_MANAGER_TOOLBAR and Gtk::UI_MANAGER_POPUP. 
	///< @return <EM>true</EM> if any widgets of the requested types were were returned, <EM>false</EM> otherwise. 

	Action* get_action(const char *path) const;
	///< Looks up an action by following a path (see get_widget() for more information about paths).
	///< @param path A path. 
	///< @return The action whose proxy widget is found by following the path, or null if no widget was found.
	
	String get_ui() const;
	///< Creates a UI definition of the merged UI.
	///< @return A String containing an XML representation of the merged UI. 
	
/// @}
/// @name Methods
/// @{
	
	void set_add_tearoffs(bool add_tearoffs);
	///< Sets whether menus generated by this UIManager will have tearoff menu items.
	///< @param add_tearoffs Whether tearoff menu items are added.
	///<
	///< Note that this only affects regular menus. Generated popup menus 
	///< never have tearoff menu items.
	
	void insert_action_group(ActionGroup& action_group, int pos = 0);
	///< Inserts an action group into the list of action groups associated with this UIManager. 
	///< @param action_group The action group to be inserted. 
	///< @param pos The position at which the group will be inserted.
	///<	
	///< Note actions in earlier groups hide actions with the same name in later groups.
	
	void remove_action_group(ActionGroup& action_group);
	///< Removes an action group from the list of action groups associated with self.
	///< @param action_group The action group to be removed. 

	unsigned int add_ui_from_string(const char *buffer, int length = -1, G::Error *error = 0);
	///< Parses a string containing a UI definition and merges it with the current contents of the UIManager.
	///< @param buffer The string to parse. 
	///< @param length The length of buffer, or -1 if buffer is null-terminated. 
	///< @param error The return location for an error. 
	///< @return The merge id for the merged UI. 
	///<	 
	///< An enclosing \<ui\> element is added if it is missing. The merge id can be used
	///< to unmerge the UI with remove_ui(). If an error occurred, the return value is 0.
	
	unsigned int add_ui_from_string(const String& buffer, G::Error *error = 0);
	///< Parses a string containing a UI definition and merges it with the current contents of the UIManager.
	///< @param buffer The string to parse. 
	///< @param error The return location for an error. 
	///< @return The merge id for the merged UI. 
	///<	 
	///< An enclosing \<ui\> element is added if it is missing. The merge id can be used
	///< to unmerge the UI with remove_ui(). If an error occurred, the return value is 0.

	unsigned int add_ui_from_file(const char *filename, G::Error *error = 0);
	unsigned int add_ui_from_file(const String& filename, G::Error *error = 0);
	///< Parses a file containing a UI definition and merges it with the current contents of the UIManager.
	///< @param filename The name of the file to parse.
	///< @param error The return location for an error. 
	///< @return The merge id for the merged UI. 
	///<	 
	///< An enclosing \<ui\> element is added if it is missing. The merge id can be used
	///< to unmerge the UI with remove_ui(). If an error occurred, the return value is 0.
	 
	void add_ui(unsigned int merge_id, const char *path, const char *name, const char *action,
	            UIManagerItemType type = UI_MANAGER_AUTO, bool top = false);
	void add_ui(unsigned int merge_id, const String& path, const String& name, const String& action,
	            UIManagerItemType type = UI_MANAGER_AUTO, bool top = false);
	///< Adds a UI element to the current contents of the UIManager. 
	///< @param merge_id The merge id for the merged UI (see new_merge_id()).
	///< @param path A path. 
	///< @param name The name for the added UI element. 
	///< @param action The name of the action to be proxied, or null to add a separator. 
	///< @param type The type of UI element to add. 
	///< @param top If <EM>true</EM> the UI element is added before its siblings, otherwise it's added after.
	///<
	///< If type is Gtk::UI_MANAGER_AUTO, GTK+ inserts a menuitem, toolitem or separator if
	///< such an element can be inserted at the place determined by path. Otherwise type must
	///< indicate an element that can be inserted at the place determined by path. When adding
	///< several UI elements you will want to use the same <EM>merge_id</EM> for each element.
	///< This will avoid unecessary multiple calls to new_merge_id() and will make it easier
	///< to unmerge several elements with one call to remove_ui();

	void add_ui_separator(unsigned int merge_id, const char *path, const char *name, bool top = false);
	void add_ui_separator(unsigned int merge_id, const String& path, const String& name, bool top = false);
	///< Adds a separator UI element to the current contents of the UIManager. 
	///< @param merge_id The merge id for the merged UI (see new_merge_id()).
	///< @param path A path. 
	///< @param name The name for the added separator UI element. 
	///< @param top If <EM>true</EM> the separator is added before its siblings, otherwise it's added after.

	void remove_ui(unsigned int merge_id);
	///< Unmerges the part of the UIManager content identified by merge_id.
	///< @param merge_id A merge id as returned by add_ui_from_string().
	
	void ensure_update();
	///< Makes sure that all pending updates to the UI have been completed. This may
	///< occasionally be necessary, since UIManager updates the UI in an idle function.
	///< A typical example where this function is useful is to enforce that the menubar
	///< and toolbar have been added to the main window before showing it:
	///< @code
	///< window->add(*vbox); 
	///< ui_manager->signal_add_widget().connect(sigc::mem_fun(vbox, &MyVBox::on_add_widget)); 
	///< ui_manager->add_ui_from_file("my-menus");
	///< ui_manager->add_ui_from_file("my-toolbars");
	///< ui_manager->ensure_update();  
	///< window->show();
	///< @endcode

	unsigned int new_merge_id();
	///< Obtains an unused merge id, suitable for use with add_ui().
	///< @return An unused merge id. 
	
/// @}
/// @name Signal Proxies
/// @{

	const AddWidgetSignalProxy signal_add_widget();
	///< Connect to the add_widget_signal; emitted for each generated menubar and toolbar.
	
	const ActionsChangedSignalProxy signal_actions_changed();
	///< Connect to the actions_changed_signal; emitted whenever the set of actions changes.

	const ConnectProxySignalProxy signal_connect_proxy();
	///< Connect to the connect_proxy_signal; emitted after connecting a proxy widget to an action in the group.

	const DisconnectProxySignalProxy signal_disconnect_proxy();
	///< Connect to the disconnect_proxy_signal; emitted after disconnecting a proxy widget from an action in the group.

	const PreActivateSignalProxy signal_pre_activate();
	///< Connect to the pre_activate_signal; emitted just before an action is activated.

	const PostActivateSignalProxy signal_post_activate();
	///< Connect to the post_activate_signal; emitted just after an action is activated.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/uimanager.inl>

#endif // XFC_GTK_UI_MANAGER_HH

