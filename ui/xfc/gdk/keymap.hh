/*  XFC: Xfce Foundation Classes (User Interface Library)
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
 
/// @file xfc/gdk/keymap.hh
/// @brief A GdkKeymap C++ wrapper interface.
///
/// Provides Keymap and KeymapKey, two objects that can be used for manipulating keyboard codes.

#ifndef XFC_GDK_KEYS_HH
#define XFC_GDK_KEYS_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef XFC_PANGO_TYPES_HH
#include <xfc/pango/types.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {

class Display;
class Keyval;

/// @class KeymapKey keymap.hh xfc/gdk/keymap.hh
/// @brief A GdkKeymapKey C++ wrapper class.
///
/// KeymapKey represents a hardware key that can be mapped to a keyval.

class KeymapKey
{
	GdkKeymapKey key_;

public:
/// @name Constructors
/// @{

	KeymapKey();
	///< Construct an empty KeymapKey (see Gdk::KeymapKey::set() for details).

	KeymapKey(unsigned int keycode, int group, int level);
	///< Construct a new KeymapKey (see Gdk::KeymapKey::set() for details).
	///< @param keycode The hardware keycode; this is an identifying number for a physical key.
	///< @param group Indicates movement in a horizontal direction.
	///< @param level Indicates which symbol on the key will be used, in a vertical direction.

/// @}
/// @name Accessors
/// @{

	GdkKeymapKey* gdk_keymap_key() const;
	///< Get a pointer to the GdkKeymapKey structure.

	unsigned int keycode() const;
	///< Returns the hardware key code. The keycode is an identifying number for a physical key.

	int group() const;
	///< Returns the group. The group indicates movement in a horizontal direction.

	int level() const;
	///< Returns the level. The level indicates which symbol on the key will be used,
	///< in a vertical direction.

/// @name Methods
/// @{

	void set(unsigned int keycode, int group, int level);
	///< Sets the keycode, group and level for the key.
	///< @param keycode The hardware keycode; this is an identifying number for a physical key.
	///< @param group Indicates movement in a horizontal direction.
	///< @param level Indicates which symbol on the key will be used, in a vertical direction.
	///<
	///< On a standard US keyboard, the key with the number "1" on it also has the
	///< exclamation point ("!") character on it. The level indicates whether to use the "1"
	///< or the "!" symbol. The letter keys are considered to have a lowercase letter at level 0,
	///< and an uppercase letter at level 1, though only the uppercase letter is printed.
	///<
	///< Usually groups are used for two different languages. In group 0, a key might have
	///< two English characters, and in group 1 it might have two Hebrew characters. The Hebrew
	///< characters will be printed on the key next to the English characters.

/// @}
};

/// @class Keymap keymap.hh xfc/gdk/keymap.hh
/// @brief A GdkKeymap C++ wrapper class.
///
/// Key values are the codes which are sent whenever a key is pressed or released. They appear in
/// the keyval field of the GdkEventKey structure. They are also returned by the keyval() accessor
/// in the Gdk::EventKey object, which is passed to the virutal signal handlers for the "key-press"
/// and "key-release" event signals. Examples of key values are GDK_a, GDK_Enter, GDK_F1, etc.
/// The complete list of key values can be found in the <gdk/gdkkeysyms.h> header file. This file
/// is not included by XFC, it must be included independently, because the file is quite large.
///
/// The Keyval object represents a GDK key value. A key value can be converted into a 
/// string representation with Gdk::Keyval::name(). The reverse, a Keyval can be constructed
/// from string. The case of key values can be determined using Gdk::Keyval::is_upper() and
/// Gdk::Keyval::is_lower(). Key values can be converted to upper or lower case using 
/// Gdk::Keyval::to_upper() and Gdk::Keyval::to_lower(). When it makes sense, key values can
/// be converted to and from Unicode characters with Gdk::Keyval::to_unicode() and 
/// Gdk::Keyval::from_unicode().
///
/// One Gdk::Keymap object exists for each user display. Gdk::Keymap::get() returns the keymap
/// for the specified display, or the default display if no display is specified. A keymap is a
/// mapping from Gdk::KeymapKey to key values. You can think of a Gdk::KeymapKey as a 
/// representation of a symbol printed on a physical keyboard key. That is, it contains three
/// pieces of information. First, it contains the hardware keycode; this is an identifying number
/// for a physical key. Second, it contains the level of the key. The level indicates which
/// symbol on the key will be used, in a vertical direction. So on a standard US keyboard, the
/// key with the number "1" on it also has the exclamation point ("!") character on it. The level
/// indicates whether to use the "1" or the "!" symbol. The letter keys are considered to have a
/// lowercase letter at level 0, and an uppercase letter at level 1, though only the uppercase 
/// letter is printed. Third, the Gdk::KeymapKey contains a group; groups are not used on standard
/// US keyboards, but are used in many other countries. On a keyboard with groups, there can be 
/// 3 or 4 symbols printed on a single key. The group indicates movement in a horizontal direction.
/// Usually groups are used for two different languages. In group 0, a key might have two English
/// characters, and in group 1 it might have two Hebrew characters. The Hebrew characters will be
/// printed on the key next to the English characters.
///
/// In order to use a keymap to interpret a key event, it's necessary to first convert the keyboard
/// state into an effective group and level. This is done via a set of rules that varies widely 
/// according to type of keyboard and user configuration. The method translate_keyboard_state()
/// accepts a keyboard state -- consisting of hardware keycode pressed, active modifiers, and 
/// active group -- applies the appropriate rules, and returns the group/level to be used to index
/// the keymap, along with the modifiers which did not affect the group and level. i.e. it returns
/// "unconsumed modifiers." The keyboard group may differ from the effective group used for keymap
/// lookups because some keys don't have multiple groups - e.g. the Enter key is always in group 0
/// regardless of keyboard state.
///
/// Note that translate_keyboard_state() also returns the keyval, i.e. it goes ahead and performs
/// the keymap lookup in addition to telling you which effective group/level values were used for
/// the lookup. Gdk::EventKey already contains this keyval, however, so you don't normally need
/// to call translate_keyboard_state() just to get the keyval.

class Keymap : public G::Object
{
	friend class G::Object;

	Keymap(const Keymap&);
	Keymap& operator=(const Keymap&);
	
protected:
/// @name Constructors
/// @{

	explicit Keymap(GdkKeymap *keymap, bool owns_reference = true);
	///< Construct a new Keymap from an existing GdkKeymap.
	///< @param keymap A pointer to a GdkKeymap.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>keymap</EM> can be a newly created GdkKeymap or an existing
	///< GdkKeymap. (see G::Object::Object).

/// @}
/// @name Signal Prototpyes
/// @{

	typedef G::Signal<void> DirectionChangedSignalType;
	typedef G::SignalProxy<TypeInstance, DirectionChangedSignalType> DirectionChangedSignalProxy;
	static const DirectionChangedSignalType direction_changed_signal;
	///< Direction changed signal (see signal_direction_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> KeysChangedSignalType;
	typedef G::SignalProxy<TypeInstance, KeysChangedSignalType> KeysChangedSignalProxy;
	static const KeysChangedSignalType keys_changed_signal;
	///< Keys changed signal (see signal_keys_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GdkKeymap CObjectType;

/// @name Constructors
/// @{

	virtual ~Keymap();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GdkKeymap* gdk_keymap() const;
	///< Get a pointer to the GdkKeymap structure.

	operator GdkKeymap* () const;
	///< Conversion operator; safely converts a Keymap to a GdkKeymap pointer.

	Pango::Direction get_direction() const;
	///< Returns the direction of the keymap, either Pango::DIRECTION_LTR or Pango::DIRECTION_RTL.
	
/// @}
/// @name Accessors
/// @{

	static Keymap* get(const Display *display = 0);
	///< Gets the GdkKeymap attached to <EM>display</EM>.
	///< @param display The display to use, or null for the default display.
	///< @return The keymap attached to <EM>display</EM>.

/// @}
/// @name Methods
/// @{

	Keyval lookup_key(const KeymapKey& key);
	///< Looks up the keyval mapped to <EM>key</EM> (keycode/group/level triplet). 
	///< @param key A KeymapKey with keycode, group, and level initialized.
	///< @returns A Keyval, or 0 if none was mapped to the given key.
	///<
	///< If no keyval is bound to key, returns 0. For normal user input, you want
	///< to use translate_keyboard_state() instead of this method, since the effective
	///< group/level may not be the same as the current keyboard state.

	bool translate_keyboard_state
	(
		unsigned int hardware_keycode,
		ModifierTypeField state,
		int group,
		Keyval& keyval,
		int *effective_group,
		int *level,
		ModifierTypeField *consumed_modifiers
	);
	///< Translates the contents of an EventKey into a keyval, effective group, and level.
	///< @param hardware_keycode A keycode.
	///< @param state A modifier state.
	///< @param group The active keyboard group.
	///< @param keyval The return location for the keyval.
	///< @param effective_group The return location for the effective group.
	///< @param level The return location for the level.
	///< @param consumed_modifiers The return location for modifiers that were
	///<                           used to determine the group or level.
	///< @return <EM>true</EM> if there was a keyval bound to the keycode/state/group.
	///<
	///< Modifiers that affected the translation and are thus unavailable for application
	///< use are returned in consumed_modifiers. See Gdk::Keyval::get_keys() for an explanation
	///< of groups and levels. The <EM>effective_group</EM> is the group that was actually used
	///< for the translation; some keys such as Enter are not affected by the active keyboard
	///< group. The <EM>level</EM> is derived from state. For convenience, EventKey already
	///< contains the translated keyval, so this function isn't as useful as you might think.

	bool get_entries_for_keyval(const Keyval& keyval, std::vector<KeymapKey>& keys);
	///< Obtains a list of KeymapKey (keycode/group/level combinations) that
	///< will generate the specified keyval.
	///< @param keyval A keyval, such as GDK_a, GDK_Up, GDK_Return, etc.
	///< @param keys A reference to a vector of KeymapKey to hold the list of keys.
	///< @return <EM>true</EM> if keys were found and returned.
	///<
	///< Groups and levels are two kinds of keyboard mode; in general, the level
	///< determines whether the top or bottom symbol on a key is used, and the group
	///< determines whether the left or right symbol is used. On US keyboards, the 
	///< shift key changes the keyboard level, and there are no groups. A group switch
	///< key might convert a keyboard between Hebrew to English modes, for example.
	///< EventKey contains a group field that indicates the active keyboard group. The
	///< level is computed from the modifier mask.

	bool get_entries_for_keycode(unsigned int hardware_keycode, std::vector<KeymapKey> *keys, std::vector<Keyval> *keyvals);
	///< Returns the keyvals bound to <EM>hardware_keycode</EM>.
	///< @param hardware_keycode A keycode.
	///< @param keys A reference to a vector of KeymapKey to hold the keys, or null.
	///< @param keyvals A reference to a vector of Keyval to hold the key values, or null.
	///< @return <EM>true</EM> if there were any entries returned in keys and/or keyvals.
	///<
	///<  When a keycode is pressed by the user, the keyval from this list of entries
	///< is selected by considering the effective keyboard group and level. See
	///< translate_keyboard_state().

/// @}
/// @name Signal Proxies
/// @{

	const DirectionChangedSignalProxy signal_direction_changed();
	///< Connect to the direction_changed_signal; emitted when the direction of the keymap changes;

	const KeysChangedSignalProxy signal_keys_changed();
	///< Connect to the keys_changed_signal; emitted when the keyboard mapping changes.
	
/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/keymap.inl>

#endif // XFC_GDK_KEYS_HH

