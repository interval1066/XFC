/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  keymap.inl - Gdk::KeymapKey and Gdk::Keymap inline functions
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

/*  Gdk::KeymapKey
 */

inline GdkKeymapKey*
Xfc::Gdk::KeymapKey::gdk_keymap_key() const
{
	return const_cast<GdkKeymapKey*>(&key_);
}

inline unsigned int
Xfc::Gdk::KeymapKey::keycode() const
{
	return key_.keycode;
}

inline int
Xfc::Gdk::KeymapKey::group() const
{
	return key_.group;
}

inline int
Xfc::Gdk::KeymapKey::level() const
{
	return key_.level;
}

/*  Gdk::Keymap
 */

inline GdkKeymap*
Xfc::Gdk::Keymap::gdk_keymap() const
{
	return reinterpret_cast<GdkKeymap*>(instance_);
}

inline Xfc::Gdk::Keymap::operator GdkKeymap* () const
{
	return this ? gdk_keymap() : 0;
}

inline Xfc::Pango::Direction
Xfc::Gdk::Keymap::get_direction() const
{
	return (Pango::Direction)gdk_keymap_get_direction(gdk_keymap());
}

inline const Xfc::Gdk::Keymap::DirectionChangedSignalProxy
Xfc::Gdk::Keymap::signal_direction_changed()
{
	return DirectionChangedSignalProxy(this, &direction_changed_signal);
}

inline const Xfc::Gdk::Keymap::KeysChangedSignalProxy
Xfc::Gdk::Keymap::signal_keys_changed()
{
	return KeysChangedSignalProxy(this, &keys_changed_signal);
}

