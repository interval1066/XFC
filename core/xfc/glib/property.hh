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

/// @file xfc/glib/property.hh
/// @brief GObject properties C++ interface.
///
/// The property classes declared in this file are used by XFC to wrap the GObject
/// property system. Properties are object specific. For each property, a class
/// declares a protected static property that requires an object pointer and a
/// class specific public accessor function that passes the object pointer for you.
/// Most properties are readable and writable, but some one or the other. You can
/// tell if a property is readable and/or writable by its protected declaration.
/// To set a property you use its set() method. To get a property use its get method.
/// It is unlikely you will ever need to use these property classes yourself, unless
/// your wrapping a new GTK+ C object. Usually you will use those properties already
/// implemented by XFC. Setting and getting object properties is discussed in the
/// <EM>Header Files</EM> section of the tutorial Introduction.

#ifndef XFC_G_PROPERTY_HH
#define XFC_G_PROPERTY_HH

#ifndef XFC_G_VALUE_HH
#include <xfc/glib/value.hh>
#endif

namespace Xfc {

namespace Gtk {
class Widget;
}

namespace G {

class Object;

/*  G::PropertyBase
 */

class PropertyBase
{
	const char *const name_;

protected:
	PropertyBase(const char* name);

	~PropertyBase();

	GParamSpec* find_property(const Object *object) const;

	void get_property(const Object *object, Value& value) const;

	void set_property(const Object *object, Value& value) const;
};

/*  G::Property (readable and writable)
 */

template<typename DataType, typename ValueType = DataType>
class Property : public PropertyBase
{
public:
	typedef DataType Data;

	Property(const char* name) : PropertyBase(name)
	{
	}

	void get(const Object *object, DataType& data) const
	{
		GParamSpec *pspec = find_property(object);
		ValueType tmp_data = 0;
		if (pspec)
		{
			Value value(pspec);
			get_property(object, value);
			value.get(tmp_data);
		}
		data = static_cast<DataType>(tmp_data);
	}

	void set(const Object *object, const DataType& data) const
	{
		GParamSpec *pspec = find_property(object);
		if (pspec)
		{
			Value value(pspec);
			value.set((ValueType)data);
			set_property(object, value);
		}
	}
};

/*  G::ReadableProperty (read only)
 */

template<typename DataType, typename ValueType = DataType>
class ReadableProperty : private Property<DataType, ValueType>
{
	typedef Property<DataType, ValueType> Base;

public:
	typedef DataType Data;
	
	using Base::get;

	ReadableProperty(const char *name) : Base(name)
	{
	}
};

/*  G::WritableProperty (write only)
 */

template<typename DataType, typename ValueType = DataType>
class WritableProperty : private Property<DataType, ValueType>
{
	typedef Property<DataType, ValueType> Base;

public:
	typedef DataType Data;
	
	using Base::set;

	WritableProperty(const char *name) : Base(name)
	{
	}
};

/*  G::PropertyProxyBase
 */

template<typename ObjectType, typename PropertyType>
class PropertyProxyBase
{
	ObjectType *const object_;
	const PropertyType *const property_;

protected:
	PropertyProxyBase(ObjectType *object, const PropertyType *property) : object_(object), property_(property)
	{
	}

	~PropertyProxyBase()
	{
	}

	const ObjectType* object() const
	{
		return object_;
	}

	const PropertyType* property() const
	{
		return property_;
	}
};

/*  G::PropertyProxy
 */

template<typename ObjectType, typename PropertyType>
class PropertyProxy : public PropertyProxyBase<ObjectType, PropertyType>
{
	typedef PropertyProxyBase<ObjectType, PropertyType> Base;

public:
	typedef typename PropertyType::Data DataType;

	PropertyProxy(ObjectType *object, const PropertyType *property) : Base(object, property)
	{
	}

	void get(DataType& data) const
	{
		Base::property()->get(Base::object(), data);
	}

	void set(const DataType& data) const
	{
		Base::property()->set(Base::object(), data);
	}

	operator DataType() const
	{
		DataType data;
		get(data);			
		return data;
	}
	
	void operator=(const DataType& data) const
	{
		set(data);		
	}
};

} // namespace G

} // namespace Xfc

#endif // XFC_G_PROPERTY_HH
