/*  XFC: Xfce Foundation Classes (Core Library)
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

/// @file xfc/glib/boxed.hh
/// @brief Boxed type C++ interface.
///
/// Provides a base class for boxed types, such a Gdk::Color, G::Value, Gtk::TreeIter
/// and Gtk::TreePath.

#ifndef XFC_G_BOXED_HH
#define XFC_G_BOXED_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __GLIB_GOBJECT_H__
#include <glib-object.h>
#endif

#ifndef _CPP_MAP
#include <map>
#endif

namespace Xfc {

namespace G {

/// @class Boxed boxed.hh xfc/glib/boxed.hh
/// @brief A generic base class for GTK+ boxed objects.
///
/// The Boxed class handles the GTK+ memory allocation for boxed objects, saving you the trouble and
/// initializes the underlying GTK+ structure where appropriate. Boxed is derived from Object so its
/// derived classes can be managed by the XFC smart pointer, Pointer<>. Boxed is an implementation
/// class so you wont need to use it unless you are deriving a new boxed object type. Some examples
/// of boxed objects are Gdk::Color, G::Value, Gtk::TreeIter and Gtk::TreePath.
///
/// A Boxed object is a small object that is frequently copied and freed by GTK+. What it means to
/// copy a Boxed object depends on each individual object. Sometimes a copied object will be a deep
/// copy (an exact duplicate) and at other times it will be a shallow copy (merely reference counted).

class Boxed : public Xfc::Object
{
	Boxed(const Boxed&);
	Boxed& operator=(const Boxed&);

	GType boxed_type_;
	bool can_free;

protected:
/// @name Constructors
/// @{

	explicit Boxed(GType boxed_type);
	///< Construct a new boxed type.
	///< @param boxed_type The GType value for the boxed object.
	///<
	///< Creates an empty wrapper for the boxed object type <EM>boxed_type</EM>. Objects
	///< calling this constructor must call copy() to copy a boxed object to the wrapper.

	Boxed(GType boxed_type, void *boxed);
	///< Construct a new boxed type.
	///< @param boxed_type The GType value for the boxed object.
	///< @param boxed A generic pointer to a GTK+ boxed object.
	///<
	///< This constructor is used by Boxed::wrap for wrapping boxed objects that must not be freed.

	Boxed(GType boxed_type, void *boxed, bool copy);
	///< Construct a new boxed type.
	///< @param boxed_type The GType value for the boxed object.
	///< @param boxed A generic pointer to a GTK+ boxed object.
	///< @param copy Set <EM>true</EM> if a copy of <EM>boxed</EM> should be used.
	///<
	///< If <EM>copy</EM> is true <EM>boxed</EM> is copied. If false <EM>boxed</EM> is assumed to be
	///< a valid copy of a boxed object that must be freed.

/// @}

	void* boxed_;
	///< Generic GTK+ boxed object pointer.

/// @name Methods
/// @{

	void copy(const Boxed& src);
	///< Make a copy of the boxed object src.
	///< @param src The Boxed object.

	void copy(const void *boxed);
	///< Copy the GTK+ <EM>boxed</EM> object to this C++ wrapper.
	///< @param boxed A generic pointer to the GTK+ boxed object to copy.
	///<
	///< <EM>boxed</EM> must be a valid boxed objrect and have the same GType as the calling object.
	///< The previous object, if any, is freed appropriately.
	
/// @}

public:
	virtual ~Boxed();
	///< Destructor.

	void* g_boxed() const;
	///< Returns a generic pointer to the GTK+ boxed object.

/// @name Templates
/// @{

	template<typename T>
	static T* wrap(GType boxed_type, void *boxed);
	///< Generic C++ wrapper function for GTK+ boxed objects.
	///< @param boxed_type The GType value of the boxed object.
	///< @param boxed A generic pointer to a GTK+ boxed object.
	///<
	///< This version wraps GTK+ boxed objects that must not be freed. This is a temporary
	///< C++ wrapper and doesn't take over ownership of the boxed object.

	template<typename T>
	static T* wrap(GType boxed_type, void *boxed, bool copy);
	///< Generic C++ wrapper function for GTK+ boxed objects.
	///< @param boxed_type The GType value of the boxed object.
	///< @param boxed A generic pointer to a GTK+ boxed object.
	///< @param copy Set <EM>true</EM> if a copy of <EM>boxed</EM> should be used.
	///<
	///< This version wraps GTK+ boxed objects that must be freed. If <EM>copy</EM> is true
	///< a copy of the boxed object is made. If <EM>copy</EM> is false the C++ wrapper takes
	///< over ownership of the boxed object and frees it appropriately.
	
/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/boxed.inl>

#endif // XFC_G_BOXED_HH

