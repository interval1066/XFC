/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/gtk/window.hh
/// @brief A GtkWindow C++ wrapper interface.
/// 
/// Provides Window, a top-level widget used to provide a communication interface bewteen
/// your application and the window manager. 

#ifndef XFC_GTK_WINDOW_HH
#define XFC_GTK_WINDOW_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_WINDOW_H__
#include <gtk/gtkwindow.h>
#endif

namespace Xfc {

namespace G {
class Error;
}

namespace Gdk {
class Geometry;
class Pixbuf;
class Screen;
}

namespace Gtk {

class WindowGroup;

/// @class Window window.hh xfc/gtk/window.hh
/// @brief A GtkWindow C++ wrapper class.
///
/// Window is usually the first widget instantiated in an application program and for
/// regular applications (i.e. non-popup) is known a top-level widget. Its primary job
/// is to provide a communication interface bewteen your application and the window 
/// manager. When the user resizes the application's main window with the window manager,
/// that information is passed to the Window. Window is derived from Bin and thus can
/// only have one child.

class Window : public Bin
{
	friend class G::Object;

	Window(const Window&);
	Window& operator=(const Window&);

protected:
/// @name Constructors
/// @{

	explicit Window(GtkWindow *window, bool owns_reference = false);
	///< Construct a new Window from an existing GtkWindow.
	///< @param window A pointer to a GtkWindow.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>window</EM> can be a newly created GtkWindow or an existing
	///< GtkWindow (see G::Object::Object).
	
/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Widget*> SetFocusSignalType;
	typedef G::SignalProxy<TypeInstance, SetFocusSignalType> SetFocusSignalProxy;
	static const SetFocusSignalType set_focus_signal;
	///< Set focus signal (see signal_set_focus()). Calls a slot with the signature:
	///< @code
	///< void function(Widget *focus);
	///< // focus: The focus widget, or null if the focus is unset.
	///< @endcode

	typedef G::Signal<bool, const Gdk::Event&> FrameEventSignalType;
	typedef G::SignalProxy<TypeInstance, FrameEventSignalType> FrameEventSignalProxy;
	static const FrameEventSignalType frame_event_signal;
	///< Frame event signal (see signal_frame_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::Event& event);
	///< // event: The Gdk::Event.
	///< // return: false to allow the default frame event handler to be called.
	///< @endcode

	typedef G::Signal<void> KeysChangedSignalType;
	typedef G::SignalProxy<TypeInstance, KeysChangedSignalType> KeysChangedSignalProxy;
	static const KeysChangedSignalType keys_changed_signal;
	///< Keys changed signal (see signal_keys_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkWindow CObjectType;

/// @name Constructors
/// @{

	explicit Window(WindowType type = WINDOW_TOPLEVEL);
	///< Construct a new window which is a toplevel window and can contain other widgets.
	///< @param type The type of window.
	///< 	
	///<  Nearly always, the type of the window should be WINDOW_TOPLEVEL. If you're
	///< implementing something like a popup menu from scratch (which is a bad idea, 
	///< just use Menu), you might use WINDOW_POPUP. WINDOW_POPUP is not for dialogs,
	///< though in some other toolkits dialogs are called "popups". In GTK+, WINDOW_POPUP
	///< means a pop-up menu or pop-up tooltip. On X11, popup windows are not controlled
	///< by the window manager. If you simply want an undecorated window (no window borders),
	///< use set_decorated(), don't use WINDOW_POPUP.	

	virtual ~Window();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkWindow* gtk_window() const;
	///< Get a pointer to the GtkWindow structure.

	operator GtkWindow* () const;
	///< Conversion operator; safely converts a Window to a GtkWindow pointer.

	bool is_toplevel() const;
	///< Returns true if the window type is WINDOW_TOPLEVEL.

	bool is_popup() const;
	///< Returns true if the window type is WINDOW_POPUP.

	bool is_active() const;
	///< Determines whether the window is part of the current active toplevel.
	///< @return <EM>true</EM> if the window is part of the current active window.
	///<
	///< A window is part of the current active toplevel if it is receiving keystrokes.
	///< The return value is <EM>true</EM> if the window is the active toplevel itself, but
	///< also if it is, say, a Gtk::Plug embedded in the active toplevel. You might use this
	///< method if you wanted to draw a widget differently in an active window from a widget
	///< in an inactive window (see has_toplevel_focus()).

	bool has_toplevel_focus() const;
	///< Determines whether the input focus is within this window.
	///< @return <EM>true</EM> if the the input focus is within this window.
	///<
	///< For real toplevel windows, this is identical to is_active(), but for embedded
	///< windows, like Gtk::Plug, the result will differ.

	String get_title() const;
	///< Retrieves the title of the window (see set_title()).
	///< @return The title of the window, or a null String if none has been set explicitely.
	
	String get_role() const;
	///< Returns the role of the window (see set_role() for further explanation).
	///< @return The role of the window if set, or a null String.
	
	Widget* get_focus() const;
	///< Retrieves the current focused widget within the window. 
	///< @return The currently focused widget. 
	///<	
	///< Note that this is the widget that would have the focus if the toplevel
	///< window is focused; if the toplevel window is not focused then Gtk::Widget::has_focus()
	///< will not be true for the widget.
	
	Window* get_transient_for() const;
	///< Fetches the transient parent for this window (see set_transient_for()).
	///< @return The transient parent for this window, or null if no transient parent has been set.
	 
	Gdk::WindowTypeHint get_type_hint() const;
	///< Gets the type hint for this window (see set_type_hint()).
	///< @return The type hint for the window.

	bool get_skip_taskbar_hint() const;
	///< Gets the value set by set_skip_taskbar_hint().
	///< @return <EM>true</EM> if the window shouldn't be in the taskbar.

	bool get_accept_focus() const;
	///< Gets the value set by set_accept_focus().
	///< @return <EM>true</EM> if window should receive the input focus.
	
	bool get_skip_pager_hint() const;
	///< Gets the value set by set_skip_pager_hint().
	///< @return <EM>true</EM> if the window shouldn't be in the pager.

	bool get_focus_on_map() const;
	///< Gets the value set by set_focus_on_map().
	///< @return <EM>true</EM> if the window should receive the input focus when mapped.	
	
	bool get_destroy_with_parent() const;
	///< Returns true if the window will be destroyed with its transient parent
	///< (see set_destroy_with_parent()).
	
	bool get_resizable() const;
	///< Gets the value set by set_resizable().
	///< @return <EM>true</EM> if the user can resize the window.
	 
	Gdk::Gravity get_gravity() const;
	///< Gets the value set by set_gravity().
	///< @return The window gravity.
 
	Gdk::Screen* get_screen() const;
	///< Returns the Gdk::Screen associated with the window.

	bool get_has_frame() const;
	///< Returns whether the window has a frame window exterior to gtk_window()->window
	///< (see set_has_frame()).
	///< @return <EM>true</EM> if a frame has been added to the window via set_has_frame(). 
	
	void get_frame_dimensions(int *left, int *top, int *right, int *bottom) const;
	///< Retrieves the dimensions of the frame window for this toplevel. See set_has_frame(),
	///< set_frame_dimensions().
	///< @param left The location to store the width of the frame at the left, or null. 
	///< @param top The location to store the height of the frame at the top, or null.
	///< @param right The location to store the width of the frame at the returns, or null. 
	///< @param bottom The location to store the height of the frame at the bottom, or null.
	///<	
	///< This is a special-purpose method intended for the framebuffer port; see 
	///< set_has_frame(). It will not return the size of the window border drawn by 
	///< the window manager, which is the normal case when using a windowing system. 
	///< See Gdk::Window::get_frame_extents() to get the standard window border extents.)
	 
	bool get_decorated() const;
	///< Returns true if the window has been set to have decorations such as
	///< a title bar via set_decorated().
	
	String get_icon_name() const;
	///< Returns the name of the themed icon for the window (see set_icon_name()).
	///< @return The icon name or a null string if the window has no themed icon. 
	
	bool get_icon_list(std::vector<Gdk::Pixbuf*>& icons) const;
	///< Retrieves the list of icons set by set_icon_list().
	///< @param icons A reference to a vector of Gdk::Pixbuf* to hold the list. 
	///< @return <EM>true</EM> if the vector is not empty.
	///<	
	///< The reference count on each member won't be incremented.
	 
	Gdk::Pixbuf* get_icon() const;
	///< Gets the value set by set_icon(), or if you've called set_icon_list(),
	///< gets the first icon in the icon list.
	///< @return The icon for window.
	 
	bool get_modal() const;
	///< Returns true if the window is modal and establishes a grab when shown (see set_modal()).
	
	Gdk::ModifierTypeField get_mnemonic_modifier() const;
	///< Returns the mnemonic modifier for this window (see set_mnemonic_modifier()).
	///< @return The modifier mask used to activate mnemonics on this window.
	
	void get_default_size(int *width, int *height) const;
	///< Gets the default size of the window. 
	///< @param width The location to store the default width, or null. 
	///< @param height The location to store the default height, or null.
	///<	
	///< A value of -1 for the width or height indicates that a default size has not been
	///< explicitly set for that dimension, so the "natural" size of the window will be used.
	 
	void get_size(int *width, int *height) const;
	///< Obtains the current size of the window. 
	///< @param width The return location for width, or null. 
	///< @param height The return location for height, or null.
	///<	
	///< If the window is not onscreen, it returns the size GTK+ will suggest to the 
	///< window manager for the initial window size (but this is not reliably the same as
	///< the size the window manager will actually select). The size obtained by get_size()
	///< is the last size received in a GdkEventConfigure, that is, GTK+ uses its 
	///< locally-stored size, rather than querying the X server for the size. As a result,
	///< if you call resize() then immediately call get_size(), the size won't have taken
	///< effect yet. After the window manager processes the resize request, GTK+ receives
	///< notification that the size has changed via a configure event, and the size of the
	///< window gets updated.
	///<
	///< <B>Note 1:</B> Nearly any use of this function creates a race condition, because the
	///< size of the window may change between the time that you get the size and the time
	///< that you perform some action assuming that size is the current size. To avoid race
	///< conditions, connect to "configure_event" on the window and adjust your size-dependent
	///< state to match the size delivered in the GdkEventConfigure. 
	///<
	///< <B>Note 2:</B> The returned size does not include the size of the window manager
	///< decorations (aka the window frame or border). Those are not drawn by GTK+ and GTK+
	///< has no reliable method of determining their size.
	///<
	///< <B>Note 3:</B> If you are getting a window size in order to position the window
	///< onscreen, there may be a better way. The preferred way is to simply set the window's
	///< semantic type with set_type_hint(), which allows the window manager to e.g. center
	///< dialogs. Also, if you set the transient parent of dialogs with set_transient_for()
	///< window managers will often center the dialog over its parent window. It's much 
	///< preferred to let the window manager handle these things rather than doing it yourself,
	///< because all applications will behave consistently and according to user preferences 
	///< if the window manager handles it. Also, the window manager can take the size of the
	///< window decorations/border into account, while your application cannot.
	///<
	///< In any case, if you insist on application-specified window positioning, there's
	///< still a better way than doing it yourself - set_position() will frequently handle
	///< the details for you.
	 
	void get_position(int *root_x, int *root_y) const;
	///< This method returns the position you need to pass to move() to keep window in its
	///< current position; the meaning of the returned value varies with window gravity
	///< (see move() for more details). 
	///< @param root_x The return location for X coordinate of gravity-determined reference point. 
	///< @param root_y The return location for Y coordinate of gravity-determined reference point.
	///<	
	///< If you haven't changed the window gravity, its gravity will be GRAVITY_NORTH_WEST.
	///< This means that get_position() gets the position of the top-left corner of the window
	///< manager frame for the window. move() sets the position of this same top-left corner. 
	///< get_position() is not 100% reliable because the X Window System does not specify a 
	///< way to obtain the geometry of the decorations placed on a window by the window manager.
	///< Thus GTK+ is using a "best guess" that works with most window managers. Moreover, 
	///< nearly all window managers are historically broken with respect to their handling of
	///< window gravity. So moving a window to its current position as returned by get_position()
	///< tends to result in moving the window slightly. Window managers are slowly getting better
	///< over time. If a window has gravity GRAVITY_STATIC the window manager frame is not 
	///< relevant, and thus get_position() will always produce accurate results. However you 
	///< can't use static gravity to do things like place a window in a corner of the screen,
	///< because static gravity ignores the window manager decorations. If you are saving and
	///< restoring your application's window positions, you should know that it's impossible for
	///< applications to do this without getting it somewhat wrong because applications do not
	///< have sufficient knowledge of window manager state. The Correct Mechanism is to support
	///< the session management protocol (see the "GnomeClient" object in the GNOME libraries
	///< for example) and allow the window manager to save your window sizes and positions.
	 
	Gdk::Point get_position() const;	
	///< This method returns the position you need to pass to move() to keep window in its
	///< current position, as a Gdk::Point (see get_position(int *, int *) const).

/// @}
/// @name Accessors
/// @{
	
	static bool get_default_icon_list(std::vector<Gdk::Pixbuf*>& icons);
	///< Gets the icon list set by set_default_icon_list(). 
	///< @param icons A reference to a vector of Gdk::Pixbuf* to hold the list.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< The pixbufs in the list have not had their reference count incremented,
	///< so don't unreference them.

/// @}
/// @name Methods
/// @{
	
	void set_title(const char *title);
	void set_title(const String& title);
	///< Sets the title of the window.
	///< @param title The title of the window.
	///<	
	///< The title of a window will be displayed in its title bar; on the X Window System,
	///< the title bar is rendered by the window manager, so exactly how the title appears to
	///< users may vary according to a user's exact configuration. The title should help a user
	///< distinguish this window from other windows they may have open. A good title might 
	///< include the application name and current document filename, for example.
 
	void set_wmclass(const String& wmclass_name, const String& wmclass_class);
	///< Sets the X Window System "class" and "name" hints for a window.
	///< @param wmclass_name The window name hint. 
	///< @param wmclass_class The window class hint.
	///<	
	///< Don't use this method. According to the ICCCM, you should always set <EM>wmclass_name</EM>
	///< and <EM>wmclass_class</EM> to the same value for all windows in an application, and GTK+ sets
	///< them to that value by default, so calling this method is sort of pointless. However, you may
	///< want to call set_role() on each window in your application, for the benefit of the session 
	///< manager. Setting the role allows the window manager to restore window positions when loading
	///< a saved session.
	 
	void set_role(const char *role);
	void set_role(const String& role);
	///< This method is only useful on X11, not with other GTK+ targets.
	///< @param role The unique identifier for the window to be used when restoring a session.
	///<	
	///< In combination with the window title, the window role allows a window manager
	///< to identify "the same" window when an application is restarted. So for example
	///< you might set the "toolbox" role on your app's toolbox window, so that when 
	///< the user restarts their session, the window manager can put the toolbox back
	///< in the same place. If a window already has a unique title, you don't need to
	///< set the role, since the window manager can use the title to identify the 
	///< window when restoring the session.
	 
	AccelGroup* add_accel_group(AccelGroup *accel_group = 0);
	///< Associate <EM>accel_group</EM> with the window, such that calling Gtk::AccelGroup_activate()
	///< on the window will activate accelerators in <EM>accel_group</EM>.
	///< @param accel_group An AccelGroup.
	///< @return A pointer to an AccelGroup.
	///<
	///< If <EM>accel_group</EM> is null a newly created AccelGroup owned by the window 
	///< is returned, otherwise <EM>accel_group</EM> is returned.

	void remove_accel_group(AccelGroup& accel_group);
	///< Reverses the effects of add_accel_group().
	///< @param accel_group An AccelGroup.
	
	void set_position(WindowPosition position);
	///< Sets a position constraint for this window. 
	///< @param position A position constraint.
	///<	
	///< If the old or new constraint is WIN_POS_CENTER_ALWAYS, this will also cause
	///< the window to be repositioned to satisfy the new constraint.
 
	bool activate_focus();
	///< Activate the current focused widget. 
	///< @return <EM>true</EM> if the widget was activatable.
	///<	 
	///< Activation is what happens when you press Enter on a widget during key navigation;
	///< clicking a button, selecting a menu item, etc. If widget isn't activatable, this method
	///< returns false.

	void set_focus(Widget *focus);
	///< If <EM>focus</EM> is not the current focus widget, and is focusable, sets it as the
	///< focus widget for the window. 
	///< @param focus The new focus widget, or null to unset the current focus widget.
	///<	
	///< If <EM>focus</EM> is null, unsets the focus widget for this window. To set the
	///< focus to a particular widget in the toplevel, it is usually more convenient to use 
	///< Gtk::Widget::grab_focus() instead of this method.
	
	void set_default(Widget *default_widget);
	///< The default widget is the widget that's activated when the user presses Enter
	///< in a dialog, for example. 
	///< @param default_widget The widget to be the default, or null to unset the default widget.
	///<	
	///< This method sets or unsets the default widget for a Window. When setting 
	///< (rather than unsetting) the default widget it's generally easier to call 
	///< grab_focus() on the widget. Before making a widget the default widget, you must
	///< set the CAN_DEFAULT flag on the widget you'd like to make the default using
	///< Gtk::Widget::set_flags().
	 
	bool activate_default();
	///< Activate the default widget. 
	///< @return <EM>true</EM> if the default widget was activatable.
	///<	 
	///< Activation is what happens when you press Enter on a widget during key navigation;
	///< clicking a button, selecting a menu item, etc. If the default widget isn't activatable,
	///< then the current focused widget will be activated. If the focused widget isn't 
	///< activatable, this method returns false.

	void set_transient_for(Window *parent);
	///< Dialog windows should be set transient for the main application window
	///< they were spawned from. 
	///< @param parent The parent window.
	///<
	///< This method allows window managers to e.g. keep a dialog on top of the
	///< main window, or center the dialog over the main window. 
	 
	void set_type_hint(Gdk::WindowTypeHint hint);
	///< By setting the type hint for the window, you allow the window manager to
	///< decorate and handle the window in a way which is suitable to the function
	///< of the window in your application. 
	///< @param hint The window type.
	///<	
	///< This method should be called before the window becomes visible. Gtk::Dialog
	///< will sometimes call set_type_hint() on your behalf, so you wont need to.

	void set_skip_taskbar_hint(bool setting);
	///< Windows may set a hint asking the desktop environment not to display
	///< the window in the task bar; this method toggles this hint.
	///< @param setting Set <EM>true</EM> to keep this window from appearing in the task bar.

	void set_skip_pager_hint(bool setting);
	///< Windows may set a hint asking the desktop environment not to display
	///< the window in the pager; this function toggles this hint.
	///< @param setting Set <EM>true</EM> to keep this window from appearing in the pager.
	///<
	///< A "pager" is any desktop navigation tool such as a workspace switcher
	///< that displays a thumbnail representation of the windows on the screen.

	void set_accept_focus(bool setting);
	///< Set a hint telling the desktop environment whether or not this window 
	///< should receive the input focus.
	///< @param setting Set <EM>true</EM> to let this window receive the input focus. 
	
	void set_focus_on_map(bool setting);
	///< Set a hint telling the desktop environment whether or not this window 
	///< should receive the input focus when mapped.
	///< @param setting Set to true to let this window receive input focus on map. 
	
	void set_destroy_with_parent(bool setting);
	///< If setting is true, then destroying the transient parent of window will also
	///< destroy the window itself. 
	///< @param setting Whether to destroy window with its transient parent.
	///<	
	///< This is useful for dialogs that shouldn't persist beyond the lifetime of
	///< the main window they're associated with, for example.

	void set_resizable(bool resizable);
	///< Sets whether the user can resize a window.
	///< @param resizable <EM>true</EM> if the user can resize this window.
	///<
	///< Windows are user resizable by default.
	 
	void set_gravity(Gdk::Gravity gravity);
	///< Window gravity defines the meaning of coordinates passed to move() (see move() and
	///< Gdk::Gravity for more details).
	///< @param gravity The window gravity 
	///< 
	///< The default window gravity is GRAVITY_NORTH_WEST which will typically
	///< "do what you mean."

	void set_geometry_hints(Widget *geometry_widget, const Gdk::Geometry& geometry);
	///< This function sets up hints about how a window can be resized by the user.
	///< @param geometry_widget The widget the geometry hints will be applied to,
	///<                        or null for the toplevel widget.
	///< @param geometry A Gdk::Geometry object containing geometry information.
	///<
	///< You can set a minimum and maximum size; allowed resize increments
	///< (e.g. for xterm, you can only resize by the size of a character); 
	///< aspect ratios; and more. See the Gdk::Geometry.

	void set_screen(const Gdk::Screen& screen);
	///< Sets the Gdk::Screen where the window is displayed; if the window is already mapped,
	///< it will be unmapped, and then remapped on the new screen.
	///< @param screen A Gdk::Screen.

	void set_has_frame(bool setting);
	///< This is a special-purpose method for the framebuffer port, that causes
	///< GTK+ to draw its own window border. 
	///< @param setting Set <EM>true</EM> if the window is to have a frame.
	///<	
	///< For most applications, you want set_decorated() instead, which tells the
	///< window manager whether to draw the window border. If this method is called
	///< on a window with setting of true, before it is realized or showed, it will
	///< have a "frame" window around window->window, accessible in gtk_window()->frame.
	///< Using the signal frame_event you can recieve all events targeted at the frame.
	///< 
	///< This method is used by the linux-fb port to implement managed windows, but
	///< it could concievably be used by X-programs that want to do their own window
	///< decorations.
	
	void set_frame_dimensions(int left, int top, int right, int bottom);
	///< (Note: this is a special-purpose method intended for the framebuffer port; see set_has_frame().
	///< @param left The width of the left border. 
	///< @param top The height of the top border. 
	///< @param right The width of the right border. 
	///< @param bottom The height of the bottom border.
	///<	 
	///< This method will have no effect on the window border drawn by the window manager,
	///< which is the normal case when using the X Window system. For windows with frames 
	///< (see set_has_frame()) this method can be used to change the size of the frame border.
	 
	void set_decorated(bool setting);
	///< Ask the window manager to decorate or not decorate the window with a title bar, etc.
	///< @param setting Set <EM>true</EM> to decorate the window.
	///< 
	///< By default, windows are decorated with a title bar, resize controls, etc.
	///< Some window managers allow GTK+ to disable these decorations, creating a
	///< borderless window. If you set the decorated property to false using this
	///< function, GTK+ will do its best to convince the window manager not to 
	///< decorate the window. Depending on the system, this function may not have
	///< any effect when called on a window that is already visible, so you should
	///< call it before calling Gtk::Widget::show(). 

	void set_icon_list(std::vector<Gdk::Pixbuf*>& icons);
	///< Sets up the icon representing the window. 
	///< @param icons A reference to a vector of Gdk::Pixbuf* that holds the list.
	///<	
	///< The icon is used when the window is minimized (also known as iconified).
	///< Some window managers or desktop environments may also place it in the window
	///< frame, or display it in other contexts. set_icon_list() allows you to pass
	///< in the same icon in several hand-drawn sizes. The list should contain the
	///< natural sizes your icon is available in; that is, don't scale the image before
	///< passing it to GTK+. Scaling is postponed until the last minute, when the 
	///< desired final size is known, to allow best quality. By passing several sizes,
	///< you may improve the final image quality of the icon, by reducing or eliminating
	///< automatic image scaling. Recommended sizes to provide: 16x16, 32x32, 48x48
	///< at minimum, and larger images (64x64, 128x128) if you have them. See also 
	///< set_default_icon_list() to set the icon for all windows in your application
	///< in one go. 
	///<
	///< Note that transient windows (those who have been set transient for another
	///< window using set_transient_for()) will inherit their icon from their transient
	///< parent. So there's no need to explicitly set the icon on transient windows.
	
	void set_icon(Gdk::Pixbuf& icon);
	///< Sets up the icon representing the window. 
	///< @param icon The icon image, or null. 
	///<	
	///< This icon is used when the window is minimized (also known as iconified). 
	///< Some window managers or desktop environments may also place it in the window
	///< frame, or display it in other contexts. The icon should be provided in 
	///< whatever size it was naturally drawn; that is, don't scale the image before
	///< passing it to GTK+. Scaling is postponed until the last minute, when the 
	///< desired final size is known, to allow best quality. If you have your icon
	///< hand-drawn in multiple sizes, use set_icon_list(). Then the best size will
	///< be used. This method is equivalent to calling set_icon_list() with one
	///< element in the list. See also set_default_icon_list() to set the icon for
	///< all windows in your application in one go.

	void set_icon_name(const char *name);
	void set_icon_name(const String& name);
	///< Sets the icon for the window from a named themed icon. 
	///< @param name The name of the themed icon.
	///<	
	///< See the docs for Gtk::IconTheme for more details. Note that this method has 
	///< nothing to do with the WM_ICON_NAME property which is mentioned in the ICCCM.
	
	bool set_icon_from_file(const char *filename, G::Error *error = 0);
	bool set_icon_from_file(const String& filename, G::Error *error = 0);
	///< Sets the icon for the window.
	///< @param filename The location of the icon file.
	///< @param error The location of a G::Error object to store any error, or null.
	///< @return <EM>true</EM> if setting the icon succeeded.
	///<
	///< This method is equivalent to calling set_icon() with a pixbuf created
	///< by loading the image from <EM>filename</EM>. There are several examples
	///< of using G::Error in the source code for gfc-demo program.
	///<
	///< <B>Note:</B> Warns on failure if error is null.

	void set_modal(bool modal);
	///< Sets a window modal or non-modal.
	///< @param modal Whether the window is modal.
	///<	
	///< Modal windows prevent interaction with other windows in the same application. To 
	///< keep modal dialogs on top of the main application windows, use set_transient_for() to
	///< make the dialog transient for the parent; most window managers will then disallow 
	///< lowering the dialog below the parent.

	void add_mnemonic(unsigned int keyval, Widget& target);
	///< Adds a mnemonic to this window.
	///< @param keyval The mnemonic.
	///< @param target The widget that gets activated by the mnemonic.
	
	void remove_mnemonic(unsigned int keyval, Widget& target);
	///< Removes a mnemonic from this window.
	///< @param keyval The mnemonic. 
	///< @param target The widget that gets activated by the mnemonic.
	 
	bool mnemonic_activate(unsigned int keyval, Gdk::ModifierTypeField modifier);
	///< Activates the targets associated with the mnemonic.
	///< @param keyval The mnemonic. 
	///< @param modifier The modifiers 
	///< @return <EM>true</EM> if the activation is done.
	 
	void set_mnemonic_modifier(Gdk::ModifierTypeField modifier);
	///< Sets the mnemonic modifier for this window.
	///< @param modifier The modifier mask used to activate mnemonics on this window.
	 
	bool activate_key(const Gdk::EventKey& event);
	///< Activates mnemonics and accelerators for this window. 
	///< @param event A Gdk::EventKey event
	///< @return <EM>true</EM> if a mnemonic or accelerator was found and activated.
	///< 	
	///< This is normally called by the default <EM>key_press_event</EM> handler
	///< for toplevel windows, however in some cases it may be useful to call this
	///< directly when overriding the standard key handling for a toplevel window.

	bool propagate_key_event(const Gdk::EventKey& event);
	///< Propagate a key press or release event to the focus widget and up the focus
	///< container chain until a widget handles <EM>event</EM>.
	///< @param event A Gdk::EventKey event
	///< @return <EM>true</EM> if a widget in the focus chain handled the event.
	///<	 
	///< This is normally called by the default <EM>key_press_event</EM> and 
	///< <EM>key_release_event</EM> handlers for toplevel windows, however in some
	///< cases it may be useful to call this directly when overriding the standard
	///< key handling for a toplevel window.
		
	void present();
	///< Presents a window to the user. This may mean raising the window in the stacking order,
	///< deiconifying it, moving it to the current desktop, and/or giving it the keyboard focus,
	///< possibly dependent on the user's platform, window manager, and preferences. If the
	///< window is hidden, this method calls Gtk::Widget::show() as well. This method should be
	///< used when the user tries to open a window that's already open. Say for example the 
	///< preferences dialog is currently open, and the user chooses Preferences from the menu a
	///< second time; use present() to move the already-open dialog where the user can see it.
	
	void iconify();
	///< Asks to iconify (minimize) the specified window. Note that you shouldn't assume the
	///< window is definitely iconified afterward, because other entities (e.g. the user or
	///< window manager) could deiconify it again, or there may not be a window manager in 
	///< which case iconification isn't possible, etc. But normally the window will end up
	///< iconified. Just don't write code that crashes if not. It's permitted to call this
	///< method before showing a window, in which case the window will be iconified before
	///< it ever appears onscreen. You can track iconification via the "window_state_event" 
	///< signal on the window.
	
	void deiconify();
	///< Asks to deiconify (unminimize) the specified window. 
	///< Note that you shouldn't assume the window is definitely deiconified afterward,
	///< because other entities (e.g. the user or window manager) could iconify it again
	///< before your code which assumes deiconification gets to run. You can track 
	///< iconification via the "window_state_event" signal on the window.
 
	void stick();
	///< Asks to stick the window, which means that it will appear on all user desktops.
	///< Note that you shouldn't assume the window is definitely stuck afterward, because
	///< other entities (e.g. the user or window manager) could unstick it again, and 
	///< some window managers do not support sticking windows. But normally the window will
	///< end up stuck. Just don't write code that crashes if not. It's permitted to call 
	///< this method before showing a window. You can track stickiness via the 
	///< "window_state_event" signal on the window.
	
	void unstick();
	///< Asks to unstick the window, which means that it will appear on only one of the user's desktops. 
	///< Note that you shouldn't assume the window is definitely unstuck afterward, because
	///< other entities (e.g. the user or window manager) could stick it again. But normally
	///< the window will end up stuck. Just don't write code that crashes if not. You can 
	///< track stickiness via the "window_state_event" signal on the window.
	
	void maximize();
	///< Asks to maximize window, so that it becomes full-screen. 
	///< Note that you shouldn't assume the window is definitely maximized afterward, because
	///< other entities (e.g. the user or window manager) could unmaximize it again, and not
	///< all window managers support maximization. But normally the window will end up maximized.
	///< Just don't write code that crashes if not. It's permitted to call this method before 
	///< showing a window, in which case the window will be maximized when it appears onscreen
	///< initially. You can track maximization via the "window_state_event" signal on the window.

	void unmaximize();
	///< Asks to unmaximize window. 
	///< Note that you shouldn't assume the window is definitely unmaximized afterward, because
	///< other entities (e.g. the user or window manager) could maximize it again, and not all
	///< window managers honor requests to unmaximize. But normally the window will end up 
	///< unmaximized. Just don't write code that crashes if not. You can track maximization via
	///< the "window_state_event" signal on the window.

	void fullscreen();
	///< Asks to place the window in the fullscreen state. Note that you shouldn't assume
	///< the window is definitely full screen afterward, because other entities (e.g. the
	///< user or window manager) could unfullscreen it again, and not all window managers
	///< honor requests to fullscreen windows. But normally the window will end up
	///< fullscreen. Just don't write code that crashes if not. You can track the fullscreen
	///< state via the Gtk::Widget "window_state_event" signal.

	void unfullscreen();
	///< Asks to toggle off the fullscreen state for the window. Note that you shouldn't
	///< assume the window is definitely not full screen afterward, because other entities
	///< (e.g. the user or window manager) could fullscreen it again, and not all window
	///< managers honor requests to unfullscreen windows. But normally the window will end
	///< up restored to its normal state. Just don't write code that crashes if not. You 
	///< can track the fullscreen state via the Gtk::Widget "window_state_event" signal.

	void set_keep_above(bool setting);
	///< Asks to keep the window above, so that it stays on top.
	///< @param setting Whether to keep window above other windows.
	///<
	///< Note that you shouldn't assume the window is definitely above afterward,
	///< because other entities (e.g. the user or window manager) could not keep it
	///< above, and not all window managers support keeping windows above. But normally
	///< the window will end up kept above. Just don't write code that crashes if not.
	///<
	///< It's permitted to call this function before showing a window, in which case
	///< the window will be kept above when it appears onscreen initially. You can
	///< track the above state via the Gtk::Widget <EM>window_state_event</EM> signal.
	///<
	///< Note that, according to the Extended Window Manager Hints specification, the
	///< above state is mainly meant for user preferences and should not be used by
	///< applications e.g. for drawing attention to their dialogs.

	void set_keep_below(bool setting);
	///< Asks to keep window below, so that it stays in bottom.
	///< @param setting Whether to keep window below other windows.
	///<
	///< Note that you shouldn't assume the window is definitely below afterward,
	///< because other entities (e.g. the user or window manager) could not keep it
	///< below, and not all window managers support putting windows below. But normally
	///< the window will be kept below. Just don't write code that crashes if not.
	///<
	///< It's permitted to call this function before showing a window, in which case the
	///< window will be kept below when it appears onscreen initially. You can track the
	///< below state via the Gtk::Widget <EM>window_state_event</EM> signal.
	///<
	///< Note that, according to the Extended Window Manager Hints specification, the
	///< above state is mainly meant for user preferences and should not be used by
	///< applications e.g. for drawing attention to their dialogs.

	void begin_resize_drag(Gdk::WindowEdge edge, int button, int root_x, int root_y, unsigned int timestamp);
	///< Starts resizing a window.
	///< @param edge The position of the resize control. 
	///< @param button The mouse button that initiated the drag. 
	///< @param root_x The X position where the user clicked to initiate the drag,
	///<               in root window coordinates. 
	///< @param root_y The Y position where the user clicked to initiate the drag
	///<               in root window coordinates. 
	///< @param timestamp The timestamp from the click event that initiated the drag.
	///<	
	///< This mehod is used if an application has window resizing controls.
	///< When GDK can support it, the resize will be done using the standard mechanism
	///< for the window manager or windowing system. Otherwise, GDK will try to emulate
	///< window resizing, potentially not all that well, depending on the windowing system.
	 
	void begin_move_drag(int button, int root_x, int root_y, unsigned int timestamp);
	///< Starts moving a window.
	///< @param button The mouse button that initiated the drag.
	///< @param root_x The X position where the user clicked to initiate the drag,
	///<               in root window coordinates. 
	///< @param root_y The Y position where the user clicked to initiate the drag
	///<               in root window coordinates. 
	///< @param timestamp The timestamp from the click event that initiated the drag.
	///<	
	///< This method is used if an application has window movement grips. When GDK 
	///< can support it, the window movement will be done using the standard mechanism
	///< for the window manager or windowing system. Otherwise, GDK will try to emulate
	///< window movement, potentially not all that well, depending on the windowing system.
 
	void set_default_size(int width, int height);
	///< Sets the default size of a window. 
	///< @param width The width in pixels, or -1 to unset the default width. 
	///< @param height The height in pixels, or -1 to unset the default height.
	///<	
	///< If the window's "natural" size (its size request) is larger than the default, the
	///< default will be ignored. More generally, if the default size does not obey the geometry
	///< hints for the window (set_geometry_hints() can be used to set these explicitly), the
	///< default size will be clamped to the nearest permitted size. 
	///<
	///< Unlike set_size_request(), which sets a size request for a widget and thus would keep
	///< users from shrinking the window, this method only sets the initial size, just as if
	///< the user had resized the window themselves. Users can still shrink the window again
	///< as they normally would. Setting a default size of -1 means to use the "natural" 
	///< default size (the size request of the window). 
	///<
	///< For more control over a window's initial size and how resizing works, investigate 
	///< set_geometry_hints(). For some uses, resize() is a more appropriate method. resize()
	///< changes the current size of the window, rather than the size to be used on initial
	///< display. resize() always affects the window itself, not the geometry widget. The
	///< default size of a window only affects the first time a window is shown; if a window
	///< is hidden and re-shown, it will remember the size it had prior to hiding, rather 
	///< than using the default size. Windows can't actually be 0x0 in size, they must be at
	///< least 1x1, but passing 0 for width and height is OK, resulting in a 1x1 default size.

 	void resize(int width, int height);
	///< Resizes the window as if the user had done so, obeying geometry constraints.
	///< @param width The width in pixels to resize the window to.
	///< @param height The height in pixels to resize the window to.
	///<
	///< The default geometry constraint is that windows may not be smaller than their
	///< size request; to override this constraint, call Gtk::Widget::set_size_request() 
	///< to set the window's request to a smaller value. If resize() is called before 
	///< showing a window for the first time, it overrides any default size set with
	///< set_default_size(). Windows may not be resized smaller than 1 by 1 pixels.

	void move(int x, int y);
	///< Asks the window manager to move window to the given position. 
	///< @param x The X coordinate to move window to. 
	///< @param y The Y coordinate to move window to.
	///< 	
	///< Window managers are free to ignore this; most window managers ignore requests
	///< for initial window positions (instead using a user-defined placement algorithm) 
	///< and honor requests after the window has already been shown.
	///<
	///< Note: the position is the position of the gravity-determined reference point for
	///< the window. The gravity determines two things: first, the location of the reference
	///< point in root window coordinates; and second, which point on the window is 
	///< positioned at the reference point. By default the gravity is GRAVITY_NORTH_WEST,
	///< so the reference point is simply the x, y supplied to move(). The top-left corner
	///< of the window decorations (aka window frame or border) will be placed at x, y.
	///< Therefore, to position a window at the top left of the screen, you want to use
	///< the default gravity (which is GRAVITY_NORTH_WEST) and move the window to 0,0.
	///< To position a window at the bottom right corner of the screen, you would set
	///< GRAVITY_SOUTH_EAST, which means that the reference point is at x + the window
	///< width and y + the window height, and the bottom-right corner of the window border
	///< will be placed at that reference point. So, to place a window in the bottom right
	///< corner you would first set gravity to south east, then write:
	///< @code 
	///< move(gdk_screen_width() - window_width, gdk_screen_height() - window_height). 
	///< @endcode
	
	void move(const Gdk::Point& point);
	///< Asks the window manager to move window to the given point (see move(int, int)). 
	///< @param point The X,Y coordinates to move window to, as a Gdk::Point.

	bool parse_geometry(const char *geometry);
	bool parse_geometry(const String& geometry);
	///< Parses a standard X Window System geometry string - see the manual page for X
	///< (type 'man X') for details on this. 
	///< @param geometry The geometry string. 
	///< @return <EM>true</EM> if string was parsed successfully.
	///<	
	///< This method does work on all GTK+ ports including Win32 but is primarily 
	///< intended for an X environment. If either a size or a position can be extracted
	///< from the geometry string, parse_geometry() returns true and calls set_default_size()
	///< and/or move() to resize/move the window. If parse_geometry() returns true, it will
	///< also set the Gdk::HINT_USER_POS and/or Gdk::HINT_USER_SIZE hints indicating to
	///< the window manager that the size/position of the window was user-specified. This
	///< causes most window managers to honor the geometry.
	
	void reshow_with_initial_size();
	///< Hides window, then reshows it, resetting the default size and position
	///< of the window (used by GUI builders only).
 
	void show_about_dialog
	(
		Gdk::Pixbuf *logo,
		const String& name, 
		const String& version, 
		const String& comments,
		const String& copyright, 
		const String& website = 0,
		const std::vector<String> *authors = 0,
		const std::vector<String> *documenters = 0,
		const String& license = 0
	);	
	///< A convenience function for showing an application's about dialog box. 
	///< @param logo The pixbuf to display as the logo in the about dialog, or null for none.	
	///< @param name The name of the program.	
	///< @param version The version of the program.	
	///< @param comments A short explanation of the main purpose of the program, not a detailed list of features.	
	///< @param copyright The copyright information for the program.	
	///< @param website The URL for the link to the website of the program starting with "http://", or null for none.
	///< @param authors The authors of the program as a vector of String, or null for none.	
	///< @param documenters	The people documenting the program as a vector of String, or null for none.
	///< @param license The	license of the program, or null for none.
	///<	
	///< The constructed dialog is associated with this parent window and reused for
	///< future invocations of this method. If you require any more functionality
	///< than this you will need to create and manage your own Gtk::AboutDialog.
	///< 
	///< Each string in the authors and documenters vectors may contain email addresses
	///< and URLs, which will be displayed as links. Email addresses are recognized by 
	///< looking for <user\@host>, URLs are recognized by looking for http://url, with url
	///< extending to the next space, tab or line break. The license string is displayed 
	///< in a text view in a secondary dialog, therefore it is fine to use a long text
	///< with multiple paragraphs. Note that the text is not wrapped in the text view, 
	///< thus it must contain the intended linebreaks.
	
/// @}
/// @name Methods
/// @{

	static bool list_toplevels(std::vector<Widget*>& toplevels);
	///< Retrieves a list of all existing toplevel windows. 
	///< @param toplevels A reference to a vector of Widget* to hold the list.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< The widgets in the list are not individually referenced. If you want to iterate
	///< through the list and perform actions involving callbacks that might destroy the widgets,
	///< you must call ref() on all the widgets first, and then unref() all the widgets afterwards.

	static void set_default_icon_list(std::vector<Gdk::Pixbuf*>& icons);
	///< Sets an icon list to be used as fallback for windows that haven't had
	///< set_icon_list() called on them to set up a window-specific icon list. 
	///< @param icons A reference to a vector of Gdk::Pixbuf* that holds the list.
	///<  	
	///< This method allows you to set up the icon for all windows in your application at once.
	///< See set_icon_list() for more details.

	static void set_default_icon(Gdk::Pixbuf& icon);
	///< Sets an icon to be used as fallback for windows that haven't had set_icon()
	///< called on them from a pixbuf.
	///< @param icon The icon.

	static void set_default_icon_name(const char *name);
	static void set_default_icon_name(const String& name);
	///< Sets an icon to be used as a fallback for windows that haven't had set_icon_list()
	///< called on them for a named themed icon (see set_icon_name()).
	///< @param name The name of the themed icon.
	
	static bool set_default_icon_from_file(const String& filename, G::Error *error = 0);
	///< Sets an icon to be used as a fallback for windows that haven't had
	///< set_icon_list() called on them from a file on disk.
	///< @param filename The location of the icon file
	///< @param error The location of a G::Error object to store any error, or null.
	///< @return <EM>true</EM> if setting the icon succeeded.
	///<
	///< <B>Note:</B> Warns on failure if error is null.

	static void set_auto_startup_notification(bool setting);
	///< Whether to do automatic startup notification.
	///< @param setting Set <EM>true</EM> to automatically do startup notification.
	///<
	///< By default, after showing the first Gtk::Window for each Gdk::Screen, GTK+ calls
	///< gdk_screen_notify_startup_complete(). Call this function to disable the automatic
	///< startup notification. You might do this if your first window is a splash screen,
	///< and you want to delay notification until after your real main window has been shown,
	///< for example. In that example, you would disable startup notification temporarily,
	///< show your splash screen, then re-enable it so that showing the main window would
	///< automatically result in notification.

/// @}
/// @name Signal Proxies
/// @{
	
	const SetFocusSignalProxy signal_set_focus();
	///< Connect to the set_focus_signal; emitted when the focus widget for the window changes.

	const FrameEventSignalProxy signal_frame_event();
	///< Connect to the frame_event_signal; emitted whenever the window receives
	///< an event targeted at the frame.

	const KeysChangedSignalProxy signal_keys_changed();
	///< Connect to the keys_changed_signal; emitted when the windows menmonic and/or
	///< accelerator keys have changed.

/// @}
};

/// @class WindowGroup window.hh xfc/gtk/window.hh
/// @brief A GtkWindowGroup C++ wrapper class.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class WindowGroup : public G::Object
{
	friend class G::Object;

	WindowGroup(const WindowGroup&);
	WindowGroup& operator=(const WindowGroup&);

protected:
/// @name Constructors
/// @{

	explicit WindowGroup(GtkWindowGroup *group, bool owns_reference = false);
	///< Construct a new WindowGroup from an existing GtkWindowGroup.
	///< @param group A pointer to a GtkWindowGroup.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>group</EM> can be a newly created GtkWindowGroup or an existing
	///< GtkWindowGroup (see G::Object::Object).
	
/// @}
	
public:
	typedef GtkWindowGroup CObjectType;

/// @name Constructors
/// @{

	WindowGroup();
	///< Constructs a new window group object with a reference count of 1 that the caller owns.
	///< Grabs added with add() only affect windows within the same window group.	
	
	virtual ~WindowGroup();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkWindowGroup* gtk_window_group() const;
	///< Get a pointer to the GtkWindowGroup structure.
	
	operator GtkWindowGroup* () const;
	///< Conversion operator; safely converts a WindowGroup to a GtkWindowGroup pointer.
	
/// @}
/// @name Methods
/// @{

	void add_window(Window& window);
	///< Adds a window to the window group.
	///< @param window The Window to add.
	 	
	void remove_window(Window& window);
	///< Removes a window from the window group.
	///< @param window The Window to remove.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/window.inl>

#endif // XFC_GTK_CONTAINER_HH

