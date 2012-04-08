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

/// @file xfc/pointer.hh
/// @brief Smart pointer class interface.
///
/// Provides a reference-counted-object aware smart pointer class.

#ifndef XFC_POINTER_HH
#define XFC_POINTER_HH

namespace Xfc {

/// @class Pointer pointer.hh xfc/pointer.hh
/// @brief Smart pointer template class.
///
/// Pointer is a standard auto_ptr-like smart pointer for managing heap 
/// allocated reference counted objects. T must be a class derived from
/// Xfc::G::Object or Xfc::Object.

template <typename T>
class Pointer
{
	T *t;

	void set(T *object)
	{
		if (object)
		{
			if (!object->owns_reference())
				object->ref();
			object->set_owns_reference(false);
		}
		if (t)
			t->unref();
		t = object;
	}

public:
/// @name Constructors
/// @{

	Pointer(T *object = 0) : t(0)
	{
		set(object);
	}
	///< Construct a new smart pointer.
	///< @param object A pointer to an object allocated on the heap.
	///<
	///< Initialize a new Pointer with any dumb pointer.

	Pointer(const Pointer& src) : t(0)
	{
		set(src.get());
	}
	///< Copy constructor.
	///< @param src A reference to a smart pointer.
	///<
	///< Initialize a new Pointer with any compatible Pointer.

	template <typename T1>
	Pointer(const Pointer<T1>& src)	: t(0)
	{
		set(src.get());
	}
	///< Copy constructor.
	///< @param src A Pointer to type T1 where T1 is derived from T.
	///<
	///< Initialize a new Pointer of type T from a Pointer of type T1,
	///< only if T1 is derived from T.

	~Pointer()
	{
		set(0);
	}
	///< Destructor.
	///< Decreases the object reference count.

	Pointer& operator=(const Pointer& src)
	{
		set(src.get());
		return *this;
	}
	///< Assignment operator.
	///< @param src A reference to a smart pointer.
	///<
	///< Releases the current dumb pointer, if any and assigns the dumb pointer
	///< managed by <EM>src</EM> to this Pointer, incrementing its reference count.

	template <typename T1>
	Pointer& operator=(const Pointer<T1>& src)
	{
		set(src.get());
		return *this;
	}
	///< Assignment operator.
	///< @param src A Pointer to type T1 where T1 is derived from T.
	///<
	///< Releases the current dumb pointer, if any and assigns the dumb pointer 
	///< of type T1 managed by <EM>src</EM> to this Pointer as a dumb pointer of type T,
	///< only if T1 is derived from T. The reference count is incremented.

/// @}
/// @name Accessors
/// @{

	T& operator*() const
	{
		return *get();
	}
	///< Dereference operator.
	///< @return A reference to the object pointed to by the dumb pointer.

	T* operator->() const
	{
		return get();
	}
	///< Member selection operator.
	///< @return The dumb pointer.

	operator T*() const
	{
		return get();
	}
	///< Conversion operator.
	///< Converts a Pointer into its dumb pointer: the C pointer it manages.
	///< Normally it is considered pretty evil to mix smart and regular pointers.
	///< In XFC you can safely if you just follow the reference counting rules
	///< for each of them. You can never call delete on Pointer either because
	///< you don't call delete on XFC objects; you call unref().

	T* get() const
	{
		return t;
	}
	///< Returns the dumb pointer; the regular C pointer managed by the Pointer.
	///< @return The dumb pointer.

	bool null() const
	{
		return t == 0;
	}
	///< Returns true if the Pointer has no dumb pointer.

	template<typename T1>
	bool operator==(const Pointer<T1>& other)
	{
		return t == other.get();
	}
	///< Compares the dumb pointer with other's dumb pointer, for equality.
	///< @param other Another smart pointer.
	///< @return <EM>true</EM> if both Pointers manage to same dumb pointer.

	template<typename T1>
	bool operator!=(const Pointer<T1>& other)
	{
		return t != other.get();
	}
	///< Compares the dumb pointer with other's dumb pointer, for inequality.
	///< @param other Another smart pointer.
	///< @return <EM>true</EM> if both Pointers manage a different dumb pointer.

/// @}
/// @name Methods
/// @{

	T* release()
	{
		T *tmp = t;
		if (tmp)
			tmp->ref();
		set(0);
		return tmp;
	}
	///< Releases the dumb pointer.
	///< @return The regular C pointer previously managed by the Pointer.
	///<
	///< Before releasing the dumb pointer its reference count is incremented
	///< to prevent it being destroyed. You must call unref() on the pointer to
	///< prevent a memory leak.

	void reset(T *object = 0)
	{
		set(object);
	}
	///< Sets a new dumb pointer for the Pointer to manage.
	///< @param object The new dumb pointer.
	///<
	///< Releases the current dumb pointer, if any, and assigns <EM>object</EM>
	///< to the Pointer, incrementing its reference count.
	
	void swap(Pointer& other)
	{
 		const T* tmp = t;
		t = other.t;
		other.t = tmp;     
 	}
	///< Swaps the dumb pointer with other's dumb pointer
	///< @param other Another smart pointer.
	
/// @}
};

/// @name Smart pointer C++-style casting functions
/// @{

template <typename To, typename From>
inline Pointer<To>
cast_const(const Pointer<From>& from)
{
	return Pointer<To>(from ? const_cast<To*>(from.get()) : 0);
}
///< Removes the <EM>const</EM> qualifier from a managed const dumb pointer.
///< @param from A Pointer that manages a const dumb pointer.
///< @return A new Pointer that manages the non-const dumb pointer.
///<
///< Calls <EM>const_cast</EM> on the dumb pointer and returns the non-const
///< pointer as a new Pointer.

template <typename To, typename From>
inline Pointer<To>
cast_dynamic(const Pointer<From>& from)
{
	return Pointer<To>(dynamic_cast<To*>(from.get()));
}
///< Casts a managed polymophic dumb pointer down or across its inheritance heirarchy.
///< @param from A Pointer managing a polymophic dumb pointer of type From.
///< @return A new Pointer managing the dumb pointer as a base or sibling pointer of type <EM>To</EM>.
///<
///< Calls <EM>dynmaic_cast</EM> to safely cast a managed polymophic dumb pointer
///< of type <EM>From</EM> to a base, derived or sibling class pointer of type <EM>To</EM>.

template <typename To, typename From>
inline Pointer<To>
cast_static(const Pointer<From>& from)
{
	return Pointer<To>(from ? static_cast<To*>(from.get()) : 0);
}
///< Casts a managed dumb pointer to a pointer to a related type.
///< @param from A Pointer managing a dumb pointer of type From.
///< @return A new Pointer managing the dumb pointer as a pointer of type <EM>To</EM>.
///<
///< Calls <EM>static_cast</EM> to cast a dumb pointer of type <EM>From</EM> to a 
///< pointer of type <EM>To</EM>.

/// @}

} // namespace Xfc

#endif // XFC_POINTER_HH
