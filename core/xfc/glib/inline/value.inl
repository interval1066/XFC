/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  value.inl - G::Value inline functions
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

inline GValue*
Xfc::G::Value::g_value() const
{
	return reinterpret_cast<GValue*>(boxed_);
}

inline Xfc::G::Value::operator GValue* () const
{
	return this ? g_value() : 0;
}

inline bool
Xfc::G::Value::is_valid() const
{
	return G_IS_VALUE(boxed_);
}

inline GType
Xfc::G::Value::type() const
{
	return g_value()->g_type;
}

inline bool
Xfc::G::Value::holds(GType type) const
{
	return G_VALUE_HOLDS(boxed_, type);
}

inline void
Xfc::G::Value::get(bool& value) const
{
	value = g_value_get_boolean(g_value());
}

inline void
Xfc::G::Value::get(gchar& value) const
{
	value = g_value_get_char(g_value());
}

inline void
Xfc::G::Value::get(guchar& value) const
{
	value = g_value_get_uchar(g_value());
}

inline void
Xfc::G::Value::get(gint64& value) const
{
	value = g_value_get_int64(g_value());
}

inline void
Xfc::G::Value::get(guint64& value) const
{
	value = g_value_get_uint64(g_value());
}

inline void
Xfc::G::Value::get(gfloat& value) const
{
	value = g_value_get_float(g_value());
}

inline void
Xfc::G::Value::get(gdouble& value) const
{
	value = g_value_get_double(g_value());
}

inline void
Xfc::G::Value::set(bool value)
{
	g_value_set_boolean(g_value(), value);
}

inline void
Xfc::G::Value::set(gchar value)
{
	g_value_set_char(g_value(), value);
}

inline void
Xfc::G::Value::set(guchar value)
{
	g_value_set_uchar(g_value(), value);
}

inline void
Xfc::G::Value::set(gint64 value)
{
	g_value_set_int64(g_value(), value);
}

inline void
Xfc::G::Value::set(guint64 value)
{
	g_value_set_uint64(g_value(), value);
}

inline void
Xfc::G::Value::set(gfloat value)
{
	g_value_set_float(g_value(), value);
}

inline void
Xfc::G::Value::set(gdouble value)
{
	g_value_set_double(g_value(), value);
}

