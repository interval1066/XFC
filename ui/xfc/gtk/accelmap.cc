/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  accelmap.cc - GtkAccelMap C++ wrapper implementation
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

#include "accelmap.hh"
#include "private/marshal.hh"
#include "xfc/glib/scanner.hh"

using namespace Xfc;

/*  Gtk::AccelMap
 */

Gtk::AccelMap::AccelMap(GtkAccelMap *map, bool owns_reference)
: G::Object((GObject*)map, owns_reference)
{
}

Gtk::AccelMap::~AccelMap()
{
}

Gtk::AccelMap* 
Gtk::AccelMap::get()
{
	return G::Object::wrap<AccelMap>(gtk_accel_map_get());
}

bool
Gtk::AccelMap::lookup_entry(const String& accel_path, AccelKey *accel_key)
{
	return gtk_accel_map_lookup_entry(accel_path.c_str(), *accel_key);
}

void
Gtk::AccelMap::add_entry(const char *accel_path, const AccelKey& accel_key)
{
	gtk_accel_map_add_entry(accel_path, accel_key.key(), GdkModifierType(accel_key.mods()));
}

void
Gtk::AccelMap::add_entry(const String& accel_path, const AccelKey& accel_key)
{
	gtk_accel_map_add_entry(accel_path.c_str(), accel_key.key(), GdkModifierType(accel_key.mods()));
}

bool
Gtk::AccelMap::change_entry(const char *accel_path, const AccelKey& accel_key, bool replace)
{
	return gtk_accel_map_change_entry(accel_path, accel_key.key(), GdkModifierType(accel_key.mods()), replace);
}

bool
Gtk::AccelMap::change_entry(const String& accel_path, const AccelKey& accel_key, bool replace)
{
	return gtk_accel_map_change_entry(accel_path.c_str(), accel_key.key(), GdkModifierType(accel_key.mods()), replace);
}

void
Gtk::AccelMap::load(const String& filename)
{
	gtk_accel_map_load(filename.c_str());
}

void
Gtk::AccelMap::load(G::Scanner& scanner)
{
	gtk_accel_map_load_scanner(scanner.g_scanner());
}

void
Gtk::AccelMap::save(const String& filename)
{
	gtk_accel_map_save(filename.c_str());
}

namespace {

void accel_map_foreach_slot(gpointer data, const char *accel_path, guint accel_key, GdkModifierType accel_mods, gboolean changed)
{
	Gtk::AccelMap::ForeachSlot& slot = *static_cast<Gtk::AccelMap::ForeachSlot*>(data);
	Gtk::AccelKey tmp_accel_key(accel_key, (Gdk::ModifierTypeField)accel_mods);
	String tmp_accel_path(accel_path);
	slot(tmp_accel_path, tmp_accel_key, changed);
}

} // namespace

void
Gtk::AccelMap::foreach(const ForeachSlot& slot)
{
	ForeachSlot tmp_slot(slot);
	gtk_accel_map_foreach(&tmp_slot, &accel_map_foreach_slot);
}

void
Gtk::AccelMap::lock_path(const String& accel_path)
{
	gtk_accel_map_lock_path(accel_path.c_str());
}

void
Gtk::AccelMap::unlock_path(const String& accel_path)
{
	gtk_accel_map_unlock_path(accel_path.c_str());
}

/*  Gtk::AccelMap signals
 */

const Gtk::AccelMap::ChangedSignalType Gtk::AccelMap::changed_signal("changed",(GCallback)&Marshal::void_string_uint_gdkmodifiertype_callback);


