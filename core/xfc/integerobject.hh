/*  XFC: Xfce Foundation Classes  (Core Library)
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

/// @file xfc/integerobject.hh
/// @brief A template base class for GTK+ integer objects.
///
/// Provides a template base class for integer objects such as Gdk::Keyval, G::Quark and G::Unichar.

#ifndef XFC_INTEGER_OBJECT_HH
#define XFC_INTEGER_OBJECT_HH

namespace Xfc {

/// @class IntegerObject integerobject.hh xfc/integerobject.hh
/// @brief A C++ template base class for integer objects.
///
/// IntegerObject is a template base class for integer objects like
/// Gdk::Keyval, G::Quark and G::Unichar.

template<typename IntegerType>
class IntegerObject
{
protected:
	IntegerType value_;

/// @name Constructors
/// @{

	IntegerObject(IntegerType value) : value_(value) {}
	///< Construct a new integer object.
	///< @param value The integer value to initialize the integer object with.
	
/// @}

public:
	typedef IntegerObject<IntegerType> Base;
	///< Convenient base class typedef for derived classes.

/// @name Accessors
/// @{

	operator IntegerType () const { return value_; }
	///< Conversion operator; converts an IntegerObject to an IntegerType.
	
	bool equal(IntegerType value) const { return value_ == value; }
	///< Determines whether this integer object is equal to <EM>value</EM>.
	///< @param value A value of type IntegerType.
	///< @return <EM>true</EM> if the value of this integer object and <EM>value</EM> are equal.

	bool operator==(const IntegerObject& other) const { return value_ == other.value_; }
	///< Equality operator.
	///< @param other Another IntegerObject.
	///< @return <EM>true</EM> if the value of this integer object and other are equal.

	bool operator!=(const IntegerObject& other) const { return value_ != other.value_; }
	///< Inequality operator.
	///< @param other Another IntegerObject.
	///< @return <EM>true</EM> if the value of this integer object and other are not equal.

/// @}
};

/// @name IntegerObject equality operators
/// @{

template<typename IntegerType>
inline bool 
operator==(const IntegerObject<IntegerType>& lhs, IntegerType rhs)
{
	return lhs.equal(rhs);
}
///< Equality operator.
///< @param lhs An IntegerObject.
///< @param rhs A value of type IntegerType.
///< @return <EM>true</EM> if the value of <EM>lhs</EM> is equal to <EM>rhs</EM>.

template<typename IntegerType>
inline bool 
operator==(IntegerType lhs, const IntegerObject<IntegerType>& rhs)
{
	return rhs.equal(lhs);
}
///< Equality operator.
///< @param lhs A value of type IntegerType.
///< @param rhs An IntegerObject.
///< @return <EM>true</EM> if the value of <EM>rhs</EM> is equal to <EM>lhs</EM>.

template<typename IntegerType>
inline bool 
operator!=(const IntegerObject<IntegerType>& lhs, IntegerType rhs)
{
	return !(lhs.equal(rhs));
}
///< Inequality operator.
///< @param lhs An IntegerObject.
///< @param rhs A value of type IntegerType.
///< @return <EM>true</EM> if the value of <EM>lhs</EM> is equal to <EM>rhs</EM>.

template<typename IntegerType>
inline bool 
operator!=(IntegerType lhs, const IntegerObject<IntegerType>& rhs)
{
	return !(rhs.equal(lhs));
}
///< Inequality operator.
///< @param lhs A value of type IntegerType.
///< @param rhs An IntegerObject.
///< @return <EM>true</EM> if the value of <EM>rhs</EM> is equal to <EM>lhs</EM>.

/// @}
	
} // namespace Xfc

#endif // XFC_INTEGER_OBJECT_HH


