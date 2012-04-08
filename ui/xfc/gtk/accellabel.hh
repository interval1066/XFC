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
 
/// @file xfc/gtk/accellabel.hh
/// @brief A GtkAccelLabel C++ wrapper interface.
///
/// The AccelLabel widget is a subclass of Label that also displays an accelerator key
/// on the right of the label text, e.g. 'Ctl+S'. It is commonly used in menus to show
/// the keyboard short-cuts for commands.

#ifndef XFC_GTK_ACCEL_LABEL_HH
#define XFC_GTK_ACCEL_LABEL_HH

#ifndef XFC_GTK_LABEL_HH
#include <xfc/gtk/label.hh>
#endif

#ifndef __GTK_ACCEL_LABEL_H__
#include <gtk/gtkaccellabel.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class AccelLabel accellabel.hh xfc/gtk/accellabel.hh
/// @brief A GtkAccelLabel C++ wrapper class.
///
/// The AccelLabel widget is a subclass of Label that also displays an accelerator key
/// on the right of the label text, e.g. 'Ctl+S'. It is commonly used in menus to show
/// the keyboard short-cuts for commands. The accelerator key to display is not set
/// explicitly. Instead, the AccelLabel displays the accelerators which have been added
/// to a particular widget. This widget is set by calling set_accel_widget().
///
/// For example, a MenuItem widget may have an accelerator added to emit the "activate" 
/// signal when the 'Ctl+S' key combination is pressed. An AccelLabel is created and added
/// to the MenuItem, and set_accel_widget() is called with the MenuItem as its argument.
/// The AccelLabel will now display 'Ctl+S' after its label. 
/// 
/// Note that creating a MenuItem with a label (or CheckMenuItem and RadioMenuItem) 
/// automatically adds an AccelLabel to the MenuItem and calls set_accel_widget() to set
/// it up for you. An AccelLabel will only display accelerators which have Gtk::ACCEL_VISIBLE
/// set. An AccelLabel can display multiple accelerators and even signal names, though it is
/// almost always used to display just one accelerator key.
///
/// <B>Example:</B> Creating a simple menu item with an accelerator key.
/// @code
/// // Create a AccelGroup and add it to the window.
/// Pointer<Gtk::AccelGroup> accel_group;
/// window->add_accel_group(accel_group):
///
/// // Create the menu item.
/// Gtk::MenuItem *save_item = new Gtk::MenuItem("Save");
/// menu->add(*save_item);
/// save_item->show();
///
/// // Now add the accelerator to the MenuItem.
/// save_item->add_accelerator("activate", *accel_group, AccelKey(GDK_s, Gdk::CONTROL_MASK));
/// @endcode
///
/// <B>See also:</B> the <A HREF="../../howto/html/accellabel.html">AccelLabel Widget</A> HOWTO.

class AccelLabel : public Label
{
	friend class G::Object;

	AccelLabel(const AccelLabel&);
	AccelLabel& operator=(const AccelLabel&);
	
protected:
/// @name Constructors
/// @{

	explicit AccelLabel(GtkAccelLabel *accel_label, bool owns_reference = false);
	///< Construct a new AccelLabel from an existing GtkAccelLabel.
	///< @param accel_label A pointer to a GtkAccelLabel.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>accel_label</EM> can be a newly created GtkAccelLabel or an existing
	///< GtkAccelLabel. (see G::Object::Object).

/// @}

public:
	typedef GtkAccelLabel CObjectType;

/// @name Constructors
/// @{

	AccelLabel();
	///< Construct an empty accelerator label.

	explicit AccelLabel(const char *str, bool use_underline = false);
	explicit AccelLabel(const String& str, bool use_underline = false);
	///< Construct an accelerator label.
	///< @param str The label string.
	///< @param use_underline Set <EM>true</EM> if label contains a mnemonic character.

	virtual ~AccelLabel();
	///< Destructor
	
/// @}
/// @name Accessors
/// @{

	GtkAccelLabel* gtk_accel_label() const;
	///< Get a pointer to the GtkAccelLabel structure.

	operator GtkAccelLabel* () const;
	///< Conversion operator; safely converts an AccelLabel to a GtkAccelLabel pointer.

	Widget* get_accel_widget() const;
	///< Fetches the widget monitored by this accelerator label (See set_accel_widget()).
	///< @return The widget monitored by this accelerator label.

	unsigned int get_accel_width() const;
	///< Returns the width needed to display the accelerator key(s). 
	///< @return The width needed to display the accelerator key(s).
	///<
	///< This is used by menus to align all of the MenuItem widgets, and shouldn't be
	///< needed by applications.

/// @}
/// @name Methods
/// @{

	void set_accel_widget(Widget& accel_widget);
	///< Sets the widget to be monitored by this accelerator label.
	///< @param accel_widget The widget to be monitored.

	void set_accel_closure(GClosure *accel_closure);
	///< Sets the closure to be monitored by this accelerator label.
	///< @param accel_closure The closure to monitor for accelerator changes.
	///<
	///< The closure must be connected to an accelerator group; see Gtk::AccelGroup::connect().

	bool refetch();
	///< Recreates the string representing the accelerator keys.
	///< @return Always returns <EM>false</EM>.
	///<
	///< This should not be needed since the string is automatically updated whenever
	///< accelerators are added or removed from the associated widget.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/accellabel.inl>

#endif // XFC_GTK_ACCEL_LABEL_HH

