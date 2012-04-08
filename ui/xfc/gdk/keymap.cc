/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  keymap.cc - GdkKeymap C++ wrapper implementation
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
 
#include "keymap.hh"
#include "keymapsignals.hh"
#include "display.hh"
#include "keyval.hh"
#include "private/keymapclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gdk::KeymapKey
 */

Gdk::KeymapKey::KeymapKey()
{
	set(0, 0, 0);
}

Gdk::KeymapKey::KeymapKey(unsigned int keycode, int group, int level)
{
	set(keycode, group, level);
}

void
Gdk::KeymapKey::set(unsigned int keycode, int group, int level)
{
	key_.keycode = keycode;
	key_.group = group;
	key_.level = level;
}

/*  Gdk::Keymap
 */

Gdk::Keymap::Keymap(GdkKeymap *keymap, bool owns_reference)
: G::Object((GObject*)keymap, owns_reference)
{
}

Gdk::Keymap::~Keymap()
{
}

Gdk::Keymap*
Gdk::Keymap::get(const Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	return G::Object::wrap<Keymap>(gdk_keymap_get_for_display(tmp_display));
}

Gdk::Keyval
Gdk::Keymap::lookup_key(const KeymapKey& key)
{
	return gdk_keymap_lookup_key(gdk_keymap(), key.gdk_keymap_key());
}

bool
Gdk::Keymap::translate_keyboard_state(unsigned int hardware_keycode, ModifierTypeField state, int group, Keyval& keyval,
                                      int *effective_group, int *level, ModifierTypeField *consumed_modifiers)
{
	unsigned int value;
	bool result = gdk_keymap_translate_keyboard_state(gdk_keymap(), hardware_keycode, (GdkModifierType)state, group, &value,
	                                                  effective_group, level, (GdkModifierType*)consumed_modifiers);
	keyval = value;
	return result;
}

bool
Gdk::Keymap::get_entries_for_keyval(const Keyval& keyval, std::vector<KeymapKey>& keys)
{
	g_return_val_if_fail(keys.empty(), false);
	
	GdkKeymapKey *tmp_keys = 0;
	int n_keys = 0;
	
	bool result = gdk_keymap_get_entries_for_keyval(gdk_keymap(), keyval, &tmp_keys, &n_keys);
	if (result)
	{
		int i = 0;
		while (i < n_keys)
		{

			keys.push_back(reinterpret_cast<KeymapKey&>(tmp_keys[i]));
			++i;
		}
		result = !keys.empty();
		g_free(tmp_keys);
	}
	return result;
}

bool
Gdk::Keymap::get_entries_for_keycode(unsigned int hardware_keycode, std::vector<KeymapKey> *keys, std::vector<Keyval> *keyvals)
{
	g_return_val_if_fail(!keys || keys->empty(), false);
	g_return_val_if_fail(!keyvals || keyvals->empty(), false);

	GdkKeymapKey *tmp_keys = 0;
	unsigned int *tmp_keyvals = 0;
	int n_entries = 0;
	
	bool result = gdk_keymap_get_entries_for_keycode(gdk_keymap(), hardware_keycode, &tmp_keys, &tmp_keyvals, &n_entries);
	if (result)
	{
		int i = 0;
		while (i < n_entries)
		{
			if (keys)
				keys->push_back(reinterpret_cast<KeymapKey&>(tmp_keys[i]));
			if (keyvals)
				keyvals->push_back(tmp_keyvals[i]);
			++i;
		}
		g_free(tmp_keys);
		g_free(tmp_keyvals);
	}
	return result;
}

/*  Gdk::KeymapClass
 */

void
Gdk::KeymapClass::init(GdkKeymapClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->direction_changed = &direction_changed_proxy;
	g_class->keys_changed = &keys_changed_proxy;
}

GdkKeymapClass*
Gdk::KeymapClass::get_parent_class(void *instance)
{
	return static_cast<GdkKeymapClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gdk::KeymapClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_KEYMAP, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::KeymapClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gdk::KeymapClass::direction_changed_proxy(GdkKeymap *keymap)
{
	KeymapSignals *signals = dynamic_cast<KeymapSignals*>(G::ObjectSignals::pointer((GObject*)keymap));
	if (signals)
		signals->on_direction_changed();
	else
	{
		GdkKeymapClass *g_class = get_parent_class(keymap);
		if (g_class && g_class->direction_changed)
			g_class->direction_changed(keymap);
	}
}

void
Gdk::KeymapClass::keys_changed_proxy(GdkKeymap *keymap)
{
	KeymapSignals *signals = dynamic_cast<KeymapSignals*>(G::ObjectSignals::pointer((GObject*)keymap));
	if (signals)
		signals->on_keys_changed();
	else
	{
		GdkKeymapClass *g_class = get_parent_class(keymap);
		if (g_class && g_class->keys_changed)
			g_class->keys_changed(keymap);
	}
}

/*  Gdk::Keymap signals
 */

const Gdk::Keymap::DirectionChangedSignalType Gdk::Keymap::direction_changed_signal("direction_changed", (GCallback)&G::Marshal::void_callback);

const Gdk::Keymap::KeysChangedSignalType Gdk::Keymap::keys_changed_signal("keys_changed", (GCallback)&G::Marshal::void_callback);

