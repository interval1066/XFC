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
 
/// @file xfc/glib/type.hh
/// @brief Abstract base classes for GTK+ interfaces and objects.

#ifndef XFC_G_TYPE_HH
#define XFC_G_TYPE_HH

#ifndef XFC_TRACKABLE_HH
#include <xfc/trackable.hh>
#endif

#ifndef XFC_G_SIGNALS_HH
#include <xfc/glib/signals.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

namespace Xfc {

namespace G {

/// @class TypeInstance type.hh xfc/glib/type.hh
/// @brief Abstract base class for GTK+ interfaces and objects.
///
/// TypeInstance encapsulates GTypeInstance, the base structure for GObjects.
/// It exists only to serve as a common base class for concrete objects and
/// the abstract interfaces they inherit. Gtk::Entry is a good example. It
/// inherits from Gtk::Widget, Gtk::Editable and Gtk::CellEditable. Gtk::Widget
/// is the concrete object and Gtk::Editable and Gtk::CellEditable are its
/// abstract interfaces.

class TypeInstance : public virtual Trackable
{
	TypeInstance(const TypeInstance&);
	TypeInstance& operator=(const TypeInstance&);

protected:
 	GTypeInstance *instance_;
	///< A Pointer to the wrapped GTypeInstance structure.

	TypeInstance();
	///< Constructor.

	virtual ~TypeInstance() = 0;
	///< Destructor.

public:
/// @name Accessors
/// @{

	GTypeInstance* g_type_instance() const;
	///< Get a pointer to the GTypeInstance structure.

	bool is_a(GType is_a_type) const;
	///< If <EM>is_a_type</EM> is a derivable type, check whether the instance type
	///< is a descendant of <EM>is_a_type</EM>, or if <EM>is_a_type</EM> is an interface,
	///< check whether the instance type conforms to it.
	///< @param is_a_type Possible ancestor of type or interface type the instance type could conform to.
	///< @return <EM>true</EM> if the instance type is_a is_a_type holds true.

	GType type() const;
	///< Get the type ID for the instance.

	String type_name() const;
	///< Get the type name for the instance.

	GType parent_type() const;
	// Get the GType of the immediate parent for the instance, or 0 if it has no parent.

/// @}
/// @name Methods
/// @{

	void add_interface(GType interface_type, GInterfaceInitFunc interface_init);
	///< Adds the static <EM>interface_type</EM> to this TypeInstance.
	///< @param interface_type GType value of the interface type to add.
	///< @param interface_init The location of the function that initializes <EM>interface_type</EM>.

/// @}
/// @name Methods
/// @{
	
	static void add_interface(GType instance_type, GType interface_type, GInterfaceInitFunc interface_init);
	///< Adds the static <EM>interface_type</EM> to the instantiable <EM>instance_type</EM>.
	///< @param instance_type GType value of an instantiable type.
	///< @param interface_type GType value of the interface type to add.
	///< @param interface_init The location of the function that initializes <EM>interface_type</EM>.

	static GType register_type(GType parent_type, GClassInitFunc class_init);
	///< Registers a new static XFC type derived from parent_type.
	///< @param parent_type The type which this type will be derived from.
	///< @param class_init The location of the class initialization function.
	///< @return The new type identifier.

/// @}
};

/// @class TypeInterface type.hh xfc/glib/type.hh
/// @brief Abstract base class for GTK+ interfaces.

class TypeInterface : public virtual TypeInstance
{
protected:
/// @name Constructors
/// @{

	TypeInterface();
	///< Constructor.
	
	virtual ~TypeInterface() = 0;
	///< Destructor.

/// @}
/// @name Accessors
/// @{
	static bool is_interface(GType type);
	///< Determines whether <EM>type</EM> is an interface type.
	///< @param type A GType value.
	///<
	///< Interface types are types that provide pure APIs, the implementation of which is provided
	///< by another type (which is then said to conform to the interface). GLib interfaces are somewhat
	///< analogous to Java interfaces and C++ classes containing only pure virtual functions, with the
	///< difference that GType interfaces are not derivable.

/// @}

public:
/// @name Accessors
/// @{

	GTypeInterface* g_type_interface(GType type) const;
	///< Get a pointer to the GTypeInterface structure for <EM>type</EM>.
	///< @param type The interface type to get.
	///< @return A GTypeInterface pointer.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/type.inl>

#endif // XFC_G_TYPE_HH

