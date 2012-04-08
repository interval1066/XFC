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

/// @file xfc/gtk/fixed.hh
/// @brief A GtkFixed C++ wrapper interface.
///
/// Provides Fixed, a container which can place child widgets at fixed positions and
/// with fixed sizes, given in pixels.

#ifndef XFC_GTK_FIXED_HH
#define XFC_GTK_FIXED_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef __GTK_FIXED_H__
#include <gtk/gtkfixed.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Fixed fixed.hh xfc/gtk/fixed.hh
/// @brief A GtkFixed C++ wrapper class.
///
/// The Fixed widget is a container which can place child widgets at fixed positions and
/// with fixed sizes, given in pixels. Fixed performs no automatic layout management. For
/// most applications, you should not use this container! It keeps you from having to 
/// learn about the other containers, and it results in broken applications. With Fixed,
/// the following things will result in truncated text, overlapping widgets, and other
/// display bugs:
///
/// - Themes, which may change widget sizes.
///
/// - Fonts other than the one you used to write the app will of course change the size
///   of widgets containing text; keep in mind that users may use a larger font because
///   of difficulty reading the default, or they may be using Windows or the framebuffer
///   port of GTK+, where different fonts are available.
///
/// - Translation of text into other languages changes its size. Also, display of 
///   non-English text will use a different font in many cases.
///
/// - In addition, the fixed widget can't properly be mirrored in right-to-left languages
///   such as Hebrew and Arabic. i.e. normally GTK+ will flip the interface to put labels
///   to the right of the thing they label, but it can't do that with Fixed. So your 
///   application will not be usable in right-to-left languages.
///
/// - Finally, fixed positioning makes it kind of annoying to add/remove GUI elements, 
///   since you have to reposition all the other elements. This is a long-term maintenance
///   problem for your application.
///
/// If you know none of these things are an issue for your application, and prefer the 
/// simplicity of Fixed, by all means use the widget. But you should be aware of the
/// tradeoffs.
///
/// <B>See also:</B> the <A HREF="../../howto/html/fixed.html">Fixed Container</A> HOWTO and example.

class Fixed : public Container
{
	friend class G::Object;

	Fixed(const Fixed&);
	Fixed& operator=(const Fixed&);
	
protected:
/// @name Constructors
/// @{

	explicit Fixed(GtkFixed *fixed, bool owns_reference = false);
	///< Construct a new Fixed from an existing GtkFixed.
	///< @param fixed A pointer to a GtkFixed.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>fixed</EM> can be a newly created GtkFixed or an existing
	///< GtkFixed (see G::Object::Object).

/// @}

public:
	typedef GtkFixed CObjectType;

/// @name Constructors
/// @{

	Fixed();
	///< Construct a new fixed container.

	virtual ~Fixed();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkFixed* gtk_fixed() const;
	///< Get a pointer to the GtkFixed structure.

	operator GtkFixed* () const;
	///< Conversion operator; safely converts a Fixed to a GtkFixed pointer.

	bool get_has_window() const;
	/// Returns true if the Fixed widget has it's own Gdk::Window (see set_has_window()).

/// @}
/// @name Methods
/// @{

	void put(Widget& widget, int x, int y);
	///< Adds a widget to a Fixed container at the given position.
	///< @param widget The widget to add.
	///< @param x The horizontal position to place the widget at.
	///< @param y The vertical position to place the widget at.

	void move(Widget& widget, int x, int y);
	///< Moves a child of a Fixed container to the given position.
	///< @param widget The child widget.
	///< @param x The horizontal position to move the widget to.
	///< @param y The vertical position to move the widget to.
	
	void set_has_window(bool has_window);
	///< Sets whether a Fixed widget is created with a separate Gdk::Window or not.
	///< @param has_window <EM>true</EM> if a separate window should be created.
	///<
	///< By default, Fixed will be created with no separate Gdk::Window. This
	///< method must be called while the Fixed is not realized, for instance, 
	///< immediately after the window is created.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/fixed.inl>

#endif // XFC_GTK_FIXED_HH

