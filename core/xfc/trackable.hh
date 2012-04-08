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

/// @file xfc/trackable.hh
/// @brief Primary base class for the XFC object hierarchy.
///
/// Provides Trackable, the primary base class for Xfc::Object,
/// Xfc::G::Boxed, and Xfc::G::TypeInstance base classes. Trackable
/// manages object memory allocation and reference counting.

#ifndef XFC_TRACKABLE_HH
#define XFC_TRACKABLE_HH

#ifndef SIGCXX_SIGCXX_H
#include <sigc++/sigc++.h>
#endif

#ifndef XFC_POINTER_HH
#include <xfc/pointer.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

namespace Xfc {

/// @class Trackable trackable.hh xfc/trackable.hh
/// @brief The primary base class for the XFC object hierarchy.
///
/// Trackable is a reference counting base class. It implements the reference
/// counting features required by the XFC smart pointer, Xfc::Pointer<>. Trackable
/// is also a memory manager. It allows XFC objects to be created either on the heap
/// or on the stack, and it prevents memory leaks by catching any stray objects.
/// Trackable is based on "Item 27" from Scott Meyers book: More Effective C++.
/// It is a memory tracking class that keeps track of objects allocated on the
/// heap. Trackable provides it's own version of operator new and delete. All
/// new allocations are added to an internal allocation list. When an object's
/// reference count reaches zero the object is removed from this list and delete
/// is called.
///
/// When a program ends, Trackable walks through the object allocation list and calls
/// operator delete to free any pointers it finds. This frees the raw memory a pointer
/// points to but note - it doesn't call the object destructor. Ideally, if a program
/// manages heap memory correctly the list should be empty, but it wont be. The list
/// will contain a C++ pointers to any wrapped global GTK+ objects used in your program,
/// such as Gdk::Display, Gdk::Keymap, Gdk::Screen, Gtk::Clipboard, the default
/// Gdk::Colormap and the default Gtk::Style.
///
/// Why? If you remember, XFC adds a hook to GTK+ that calls a global "destroy_notify"
/// function when each GTK+ object is destroyed. This function checks to see if the C++
/// wrapper for the GTK+ object being destroyed was dynamically allocated, and if it was
/// calls delete (otherwise the object was allocated on the stack and nothing happens).
/// This is how XFC manages memory. It lets the GTK+ object decide when it's time to
/// destroy the C++ wrapper, which only happens when an object's reference count drops
/// to zero. This causes a problem for those few default and global objects owned by GTK+.
/// They don't get destroyed until GTK+ is removed from memory, which is never if you use
/// the GNOME desktop. When a program ends the C++ wrappers for these objects will not
/// be deleted and over time could cause a significant memory leak. Since these objects
/// are few, the easiest solution was to have Trackable clean up after itself and free
/// their allocated raw memory.
///
/// <B>Note:</B> Do not use Trackable as a garbage collector. It only cleans up after
/// a program ends and not while it's running. The programmer is still responsible for
/// allocating and freeing heap objects correctly. Trackable is just a safe guard to
/// prevent inadvertent memory leaks.

class Trackable : public sigc::trackable
{
	template<typename T> friend class Pointer;

	Trackable(const Trackable&);
	Trackable& operator=(const Trackable&);

	class AllocationList : public std::list<void*>
	{
	public:
		AllocationList();
		~AllocationList();
	};
	
	static AllocationList allocation_list_;
	static std::new_handler current_handler_;

	bool owns_reference_;

protected:
/// @name Constructors
/// @{

	Trackable();
	///< Constructor.

	virtual ~Trackable() = 0;
	///< Pure virtual Destructor.

/// @}
/// @name Methods
/// @{

	void set_owns_reference(bool setting) { owns_reference_ = setting; }
	///< Set the internal <EM>owns_reference</EM> flag.
	///< @param setting Set <EM>true</EM> if the initial reference count must be removed by owner.
	///<
	///< Called by derived classes to set the owns_reference_ flag. A G::Object sets this flag
	///< to true , indicating that it owns the initial reference count and unref() must be called.
	///< As a general rule a Gtk::Object sets this flag to false, indicating that the initial
	///< reference count is floating and unref() only needs to be called if you take ownership.
	///< If you pass a Gtk::Object to an owner or add a Gtk::Widget to a container you only
	///< need to call unref() if you called ref().

/// @}

public:
/// @name Accessors
/// @{

	bool is_dynamic() const;
	///< Determines whether the object was allocated from the heap.
	///< @returns <EM>true</EM> if the object was created by new and can safely be deleted.

	bool owns_reference() const { return owns_reference_; }
	///< The owns_reference flag setting.
	///< @return <EM>true</EM> if unref() must be explicitly called on this object.
	///<
	///< This is mainly used by the XFC smart pointer to deteremine if the initial
	///< reference count is owned by the object and must be explicitly cleared.

/// @}
/// @name Methods
/// @{

	virtual void ref();
	///< Increases the object's reference count by one.

	virtual void unref();
	///< Decreases the object's reference count by one.
	///< After this call, if the object reference is zero and the object was allocated on the
	///< heap, delete is automatically called. <B>You don't need to call delete on objects
	///< derived from Trackable</B>. Trackable has no refernece counter itself. It just sets
	///< up the reference counting API for the derived classes classes Xfc::Object and
	///< Xfc::G::TypeInstance, which do have reference counters. Therefore Trackable::unref()
	///< must only be called by a dervied class when its reference count reaches zero.

/// @}
/// @name Methods
/// @{

	static std::new_handler set_new_handler(std::new_handler handler);
	///< Specify a class-specific out-of-memory handler.
	///< @param handler A user defined out-of-memory handler to install.

	static void* operator new(size_t size);
	///< Class-specific operator new; inherited by derived classes.
	///< Stores a pointer to each <EM>new</EM> allocation in the allocation_list.
	///< If the allocation fails the out-of-memory handler is called.

#if (__GNUC__ < 4 && __GNUC_MINOR__ < 4)

	static void* operator new(size_t size, void *ptr);
	///< Class-specific placement operator new. This operator new is defined for
	///< GCC versions prior to 3.4.0. The standard C++ library included with these
	///< versions has a bug in <stl_construct.h> at line 78. Operator new in this
	///< line is missing the scope resolution operator, so instead of calling global
	///< placement new it calls the class placement new operator. This version of
	///< placement new simply calls the global placement new operator .

#endif

	static void operator delete(void *ptr);
	///< Class-specific operator delete; inherited by derived classes.
	///< Only deletes <EM>ptr</EM> if it's in the Trackable allocation list. You should
	///< not call delete yourself! Object deletion is handled internally by XFC.

/// @}
};

} // namespace Xfc

#endif // XFC_TRACKABLE_HH

