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
 
/// @file xfc/glib/value.hh
/// @brief A GValue wrapper class.
///
/// Provides G::Value, a wrapper class for the GValue structure.

#ifndef XFC_G_VALUE_HH
#define XFC_G_VALUE_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

namespace Xfc {

namespace G {

class Object;

/// @class Value value.hh xfc/glib/value.hh
/// @brief A GValue wrapper class.
///
/// Value wraps the GValue structure which is basically a variable container that
/// consists of a type identifier and a specific value of that type. The type
/// identifier within a GValue structure determines the type of the associated value.
///
/// Values are used throughout the XFC API to set and get property values. You
/// don't have to initialize a Value before using it. The constructor initializes
/// the Value for you. Normally you would create a Value on the stack and pass a 
/// pointer or reference to it, to a constructor or method as required.

class Value : public Boxed
{
public:
/// @name Constructors
/// @{

	Value();
	///< Construct an uninitialized Value that can be passed to a constructor or method.

	explicit Value(GType type);
	///< Construct a Value to hold a value of <EM>type</EM>.
	///< @param type The type identifier of the value.

	explicit Value(GParamSpec *pspec);
	///< Construct a Value from the value type of a GParamSpec structure.

	explicit Value(GValue *value);
	///< Construct a temporary Value to hold an existing GValue.
	///< @param value An existing GValue structure.
	///<
	///< Value does not take over ownership of the GValue, no copy is made and
	///< the GValue is not freed.

	Value(GValue *value, bool copy);
	///< Construct a Value to hold an existing GValue.
	///< @param value An existing GValue structure.
	///< @param copy Set <EM>true</EM> if the Value should make a copy of <EM>value</EM> and use
	///<             that, set <EM>false</EM> if it should take over ownership of the value.
	///<
	///< Value either makes a copy of the GValue or takes over its ownership. When the Value is
	///< destroyed the GValue freed.

	Value(const Value& src);
	///< Copy constructor.

	~Value();
	///< Destructor.

	Value& operator=(const Value& src);
	///< Assignment operator.

/// @}
/// @name Accessors
/// @{

	GValue* g_value() const;
	///< Get a pointer to the GValue structure.

	operator GValue* () const;
	///< Conversion operator; get a pointer to the GValue structure.

	bool is_valid() const;
	///< Returns true if the Value holds a valid initialized GValue.

	GType type() const;
	///< Get the type identifier of the value the Value holds.

	String type_name() const;
	///< Returns the type name of the value.

	bool holds(GType type) const;
	///< Returns true if the Value holds a value of type.

	bool equal(const Value& other) const;
	///< Returns true if the Value and other hold the same value.

	bool operator==(const Value& other) const;
	///< Returns true if the Value and other hold the same value.

	bool operator!=(const Value& other) const;
	///< Returns true if the Value and other do not hold the same value.

	void get(bool& value) const;
	///< Get a boolean value.
	///< @param value A reference to the location that will hold the boolean value.

	void get(gchar& value) const;
	///< Get a char value.
	///< @param value A reference to the location that will hold the char value.

	void get(guchar& value) const;
	///< Get an unsigned char value.
	///< @param value A reference to the location that will hold the unsigned char value.

	void get(gint& value) const;
	///< Get an integer value.
	///< @param value A reference to the location that will hold the integer value.
	///<
	///< This method gets values of type G_TYPE_INT and G_TYPE_ENUM.

	void get(guint& value) const;
	///< Get an unsigned integer value.
	///< @param value A reference to the location that will hold the unsigned integer value.
	///<
	///< This method gets values of type G_TYPE_UINT or G_TYPE_FLAGS.

	void get(gint64& value) const;
	///< Get a 64-bit integer value.
	///< @param value A reference to the location that will hold the 64-bit integer value.

	void get(guint64& value) const;
	///< Get an unsigned 64-bit integer value.
	///< @param value A reference to the location that will hold the unsigned 64-bit integer value.

	void get(gfloat& value) const;
	///< Get a float value.
	///< @param value A reference to the location that will hold the float value.

	void get(gdouble& value) const;
	///< Get an double value.
	///< @param value A reference to the location that will hold the double value.

	bool get(gpointer& value, bool wrap = false) const;
	///< Get a pointer value.
	///< @param value A reference to the location that will hold the pointer value.
	///< @param wrap Set <EM>true</EM> if the pointer is a G::Boxed or G::Object type
	///<             and should be wrapped.
	///< @return <EM>false</EM> if a null pointer is returned.
	///<
	///< This method gets values of type G_TYPE_BOXED, G_TYPE_OBJECT and G_TYPE_POINTER.

	bool get(String& value) const;
	///< Get a String value.
	///< @param value A reference to the location that will hold the String value.
	///< @return <EM>false</EM> if a null String is returned.

	bool get(Boxed *&value) const;
	///< Get a Boxed value.
	///< @param value A reference to the location that will hold the G::Boxed value.
	///< @return <EM>false</EM> if a null pointer is returned.
	///<
	///< You will need to call unref() on the boxed object when finished.

	bool get(G::Object *&value) const;
	///< Get an Object value.
	///< @param value A reference to the location that will hold the G::Object value.
	///< @return <EM>false</EM> if a null pointer is returned.

	template<typename ObjectType>
	bool get(Pointer<ObjectType>& value) const
	{
		gpointer tmp_value = 0;
		bool result = get(tmp_value, true);
		value = static_cast<ObjectType*>(tmp_value);
		return result;
	}
	///< Get a G::Boxed or G::Object smart pointer value.
	///< @param value A reference to the location that will hold the smart pointer value.
	///< @return <EM>false</EM> if a null pointer is returned.

/// @}
/// @name Methods
/// @{

	void set(bool value);
	///< Set a boolean value.
	///< @param value The boolean value to set.

	void set(gchar value);
	///< Set a char value.
	///< @param value The char value to set.

	void set(guchar value);
	///< Set an unsigned char value.
	///< @param value The unsigned char value to set.

	void set(gint value);
	///< Set an integer value.
	///< @param value The integer value to set.
	///<
	///< This method sets values of type G_TYPE_INT and G_TYPE_ENUM.

	void set(guint value);
	///< Set an unsigned integer value.
	///< @param value The unsigned integer value to set.
	///<
	///< This method sets values of type G_TYPE_UINT and G_TYPE_FLAGS.

	void set(gint64 value);
	///< Set a 64-bit integer value.
	///< @param value The 64-bit integer value to set.

	void set(guint64 value);
	///< Set an unsigned 64-bit integer value.
	///< @param value The unsigned 64-bit integer value to set.

	void set(gfloat value);
	///< Set a float value.
	///< @param value The float value to set.

	void set(gdouble value);
	///< Set a double value.
	///< @param value The double value to set.

	void set(const gpointer value, bool wrapped = false);
	///< Set a pointer value.
	///< @param value The pointer value to set.
	///< @param wrapped Set <EM>true</EM> if the pointer is a G::Boxed or G::Object type.
	///<
	///< This method sets values of type G_TYPE_BOXED, G_TYPE_OBJECT and G_TYPE_POINTER.

	void set(const String& value);
	///< Set a String value.
	///< @param value The String value to set.

	void set(const Boxed *value);
	///< Set a boxed value.
	///< @param value The G::Boxed value to set.

	void set(const G::Object *value);
	///< Set an object value.
	///< @param value The G::Object value to set.

	template<typename ObjectType>
	void set(const Pointer<ObjectType>& value)
	{
		set(value, true);
	}
	///< Set a G::Boxed or G::Object smart pointer value.
	///< @param value The smart pointer value to set.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/value.inl>

#endif // XFC_G_VALUE_HH


