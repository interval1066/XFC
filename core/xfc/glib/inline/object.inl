/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  object.inl - G::Object inline functions
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

inline GObject*
Xfc::G::Object::g_object() const
{
	return reinterpret_cast<GObject*>(instance_);
}

inline
Xfc::G::Object::operator GObject* () const
{
	return this ? g_object() : 0;
}

inline void*
Xfc::G::Object::get_data(const char *key) const
{
	return g_object_get_qdata(g_object(), g_quark_from_string(key));
}

inline void
Xfc::G::Object::set_data(const char *key, void *data, GDestroyNotify destroy)
{
	g_object_set_qdata_full(g_object(), g_quark_from_string(key), data, destroy);
}

inline void
Xfc::G::Object::stop_emission_by_name(const char *signal_name)
{
	g_signal_stop_emission_by_name(g_object(), signal_name);
}

template<typename T, typename gObject>
inline T*
Xfc::G::Object::wrap(gObject *object, bool owns_reference)
{
	T *t = 0;
	if (object)
	{
		void *ptr = pointer(G_OBJECT(object));
		t = ptr ? static_cast<T*>(ptr) : new T(object, owns_reference);
	}
	return t;
}

template<typename T, typename gObject>
inline T*
Xfc::G::Object::wrap_new(gObject *object, bool owns_reference)
{
	return object ? new T(object, owns_reference) : 0;
}

inline const Xfc::G::Object::NotifySignalProxy
Xfc::G::Object::signal_notify(const char *property_name)
{
	return NotifySignalProxy(this, &notify_signal, property_name);
}

inline const Xfc::G::Object::NotifySignalProxy
Xfc::G::Object::signal_notify(const String& property_name)
{
	return NotifySignalProxy(this, &notify_signal, property_name.c_str());
}

