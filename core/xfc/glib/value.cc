/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  value.cc - GValue C++ wrapper implementation
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
 
#include "value.hh"
#include "object.hh"

using namespace Xfc;

/*  G::Value
 */

G::Value::Value()
: Boxed(G_TYPE_VALUE)
{
	boxed_ = g_new0(GValue, 1);
}

G::Value::Value(GType type)
: Boxed(G_TYPE_VALUE)
{
	GValue *value = g_new0(GValue, 1);
	boxed_ = g_value_init(value, type);
}

G::Value::Value(GParamSpec *pspec)
: Boxed(G_TYPE_VALUE)
{
	GValue *value = g_new0(GValue, 1);
	boxed_ = g_value_init(value, G_PARAM_SPEC_VALUE_TYPE(pspec));
}

G::Value::Value(GValue *value)
: Boxed(G_TYPE_VALUE, value)
{
}

G::Value::Value(GValue *value, bool copy)
: Boxed(G_TYPE_VALUE, value, copy)
{
}

G::Value::Value(const Value& src)
: Boxed(G_TYPE_VALUE, src.g_boxed(), true)
{
}

G::Value::~Value()
{
}

G::Value&
G::Value::operator=(const Value& src)
{
	if (!equal(src))
		copy(src);
	return *this;
}

String
G::Value::type_name() const
{
	return G_VALUE_TYPE_NAME(boxed_);
}

bool
G::Value::equal(const Value& other) const
{
	g_return_val_if_fail(other.g_value()->g_type == g_value()->g_type, false);
	bool result;

	switch (G_TYPE_FUNDAMENTAL(g_value()->g_type))
	{
	case G_TYPE_BOOLEAN:
	case G_TYPE_CHAR:
	case G_TYPE_INT:
		result = other.g_value()->data[0].v_int == g_value()->data[0].v_int;
		break;

	case G_TYPE_UCHAR:
	case G_TYPE_UINT:
		result = other.g_value()->data[0].v_uint == g_value()->data[0].v_uint;
		break;

	case G_TYPE_LONG:
	case G_TYPE_ENUM:
		result = other.g_value()->data[0].v_long == g_value()->data[0].v_long;
		break;

	case G_TYPE_ULONG:
	case G_TYPE_FLAGS:
		result = other.g_value()->data[0].v_ulong == g_value()->data[0].v_ulong;
		break;

	case G_TYPE_INT64:
		result = other.g_value()->data[0].v_int64 == g_value()->data[0].v_int64;
		break;

	case G_TYPE_UINT64:
		result = other.g_value()->data[0].v_uint64 == g_value()->data[0].v_uint64;
		break;

	case G_TYPE_FLOAT:
		result = other.g_value()->data[0].v_float == g_value()->data[0].v_float;
		break;

	case G_TYPE_DOUBLE:
		result = other.g_value()->data[0].v_double == g_value()->data[0].v_double;
		break;

	case G_TYPE_STRING:
		result = g_utf8_collate((gchar*)other.g_value()->data[0].v_pointer, (gchar*)g_value()->data[0].v_pointer) == 0;
		break;

	case G_TYPE_BOXED:
	case G_TYPE_OBJECT:
	case G_TYPE_POINTER:
		result = other.g_value()->data[0].v_pointer == g_value()->data[0].v_pointer;
		break;

	default:
		result = false;
	}
	return result;
}

bool
G::Value::operator==(const Value& other) const
{
	return equal(other);
}

bool
G::Value::operator!=(const Value& other) const
{
	return !equal(other);
}

void
G::Value::get(gint& value) const
{
	if (G_TYPE_FUNDAMENTAL(g_value()->g_type) == G_TYPE_ENUM)
		value = g_value_get_enum(g_value());
	else
		value = g_value_get_int(g_value());
}

void
G::Value::get(guint& value) const
{
	if (G_TYPE_FUNDAMENTAL(g_value()->g_type) == G_TYPE_FLAGS)
		value = g_value_get_flags(g_value());
	else
		value = g_value_get_uint(g_value());
}

bool
G::Value::get(String& value) const
{
	const char * tmp_value = g_value_get_string(g_value());
	value = tmp_value;
	return tmp_value != 0;
}

bool
G::Value::get(Boxed *&value) const
{
	void *tmp_value = g_value_get_boxed(g_value());
	value = G::Boxed::wrap<G::Boxed>(type(), tmp_value);
	return tmp_value != 0;
}

bool
G::Value::get(G::Object *&value) const
{
	void *tmp_value = g_value_get_object(g_value());
	value = G::Object::wrap<G::Object>((GObject*)tmp_value);
	return tmp_value != 0;
}

bool
G::Value::get(gpointer& value, bool wrap) const
{
	void *tmp_value = 0;

	switch (G_TYPE_FUNDAMENTAL(g_value()->g_type))
	{
	case G_TYPE_BOXED:
		tmp_value = g_value_get_boxed(g_value());
		value = wrap ? G::Boxed::wrap<G::Boxed>(type(), tmp_value) : tmp_value;
		break;

	case G_TYPE_OBJECT:
		tmp_value = g_value_get_object(g_value());
		value = wrap ? G::Object::wrap<G::Object>((GObject*)tmp_value) : tmp_value;
		break;

	default:
		tmp_value = g_value_get_pointer(g_value());
		value = tmp_value;
	}
	return tmp_value != 0;
}

void
G::Value::set(gint value)
{
	if (G_TYPE_FUNDAMENTAL(g_value()->g_type) == G_TYPE_ENUM)
		g_value_set_enum(g_value(), value);
	else
		g_value_set_int(g_value(), value);
}

void
G::Value::set(guint value)
{
	if (G_TYPE_FUNDAMENTAL(g_value()->g_type) == G_TYPE_FLAGS)
		g_value_set_flags(g_value(), value);
	else
		g_value_set_uint(g_value(), value);
}

void
G::Value::set(const String& value)
{
	g_value_set_string(g_value(), value.c_str());
}

void
G::Value::set(const Boxed *value)
{
	g_value_set_boxed(g_value(), value->g_boxed());
}

void
G::Value::set(const G::Object *value)
{
	g_value_set_object(g_value(), value->g_object());
}

void
G::Value::set(const gpointer value, bool wrapped)
{
	switch (G_TYPE_FUNDAMENTAL(g_value()->g_type))
	{
	case G_TYPE_BOXED:
		g_value_set_boxed(g_value(), wrapped ? static_cast<G::Boxed*>(value)->g_boxed() : value);
		break;

	case G_TYPE_OBJECT:
		g_value_set_object(g_value(), wrapped ? static_cast<G::Object*>(value)->g_object() : value);
		break;

	default:
		g_value_set_pointer(g_value(), value);
	}
}

