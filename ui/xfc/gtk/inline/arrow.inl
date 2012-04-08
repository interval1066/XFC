/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  arrow.inl - Gtk::Arrow inline functions
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

inline GtkArrow*
Xfc::Gtk::Arrow::gtk_arrow() const
{
	return reinterpret_cast<GtkArrow*>(instance_);
}

inline Xfc::Gtk::Arrow::operator GtkArrow* () const
{
	return this ? gtk_arrow() : 0;
}

inline void
Xfc::Gtk::Arrow::set(ArrowType arrow_type, ShadowType shadow_type)
{
	gtk_arrow_set(gtk_arrow(), (GtkArrowType)arrow_type, (GtkShadowType)shadow_type);
}

