/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  action.inl - Gtk::Action inline functions
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

inline GtkAction*
Xfc::Gtk::Action::gtk_action() const
{
	return reinterpret_cast<GtkAction*>(instance_);
}

inline Xfc::Gtk::Action::operator GtkAction* () const
{
	return this ? gtk_action() : 0;
}

inline bool 
Xfc::Gtk::Action::get_sensitive() const
{
	return gtk_action_get_sensitive(gtk_action());
}

inline bool 
Xfc::Gtk::Action::get_visible() const
{
	return gtk_action_get_visible(gtk_action());
}

inline bool 
Xfc::Gtk::Action::is_sensitive() const
{
	return gtk_action_is_sensitive(gtk_action());
}

inline bool 
Xfc::Gtk::Action::is_visible() const
{
	return gtk_action_is_visible(gtk_action());
}

inline void 
Xfc::Gtk::Action::set_sensitive(bool sensitive)
{
	gtk_action_set_sensitive(gtk_action(), sensitive);
}
							
inline void 
Xfc::Gtk::Action::set_visible(bool visible)
{						
	gtk_action_set_visible(gtk_action(), visible);
}

inline void
Xfc::Gtk::Action::activate()
{
	gtk_action_activate(gtk_action());
}

inline void
Xfc::Gtk::Action::connect_accelerator()
{
	gtk_action_connect_accelerator(gtk_action());
}

inline void
Xfc::Gtk::Action::disconnect_accelerator()
{
	gtk_action_disconnect_accelerator(gtk_action());
}

inline void
Xfc::Gtk::Action::set_accel_path(const char *accel_path)
{
	gtk_action_set_accel_path(gtk_action(), accel_path);
}

inline void 
Xfc::Gtk::Action::set_tooltip(const char *tooltip)
{
	g_object_set(gtk_action(), "tooltip", tooltip, 0);
}

inline const Xfc::Gtk::Action::LabelPropertyProxy
Xfc::Gtk::Action::property_label()
{
	return LabelPropertyProxy(this, &label_property);
}

inline const Xfc::Gtk::Action::ShortLabelPropertyProxy
Xfc::Gtk::Action::property_short_label()
{
	return ShortLabelPropertyProxy(this, &short_label_property);
}

inline const Xfc::Gtk::Action::TooltipPropertyProxy
Xfc::Gtk::Action::property_tooltip()
{
	return TooltipPropertyProxy(this, &tooltip_property);
}

inline const Xfc::Gtk::Action::StockIdPropertyProxy
Xfc::Gtk::Action::property_stock_id()
{
	return StockIdPropertyProxy(this, &stock_id_property);
}

inline const Xfc::Gtk::Action::IsImportantPropertyProxy
Xfc::Gtk::Action::property_is_important()
{
	return IsImportantPropertyProxy(this, &is_important_property);
}

inline const Xfc::Gtk::Action::HideIfEmptyPropertyProxy
Xfc::Gtk::Action::property_hide_if_empty()
{
	return HideIfEmptyPropertyProxy(this, &hide_if_empty_property);
}

inline const Xfc::Gtk::Action::SensitivePropertyProxy
Xfc::Gtk::Action::property_sensitive()
{
	return SensitivePropertyProxy(this, &sensitive_property);
}

inline const Xfc::Gtk::Action::VisiblePropertyProxy
Xfc::Gtk::Action::property_visible()
{
	return VisiblePropertyProxy(this, &visible_property);
}

inline const Xfc::Gtk::Action::VisibleHorizontalPropertyProxy
Xfc::Gtk::Action::property_visible_horizontal()
{
	return VisibleHorizontalPropertyProxy(this, &visible_horizontal_property);
}

inline const Xfc::Gtk::Action::VisibleVerticalPropertyProxy
Xfc::Gtk::Action::property_visible_vertical()
{
	return VisibleVerticalPropertyProxy(this, &visible_vertical_property);
}

inline const Xfc::Gtk::Action::VisibleOverflownPropertyProxy
Xfc::Gtk::Action::property_visible_overflown()
{
	return VisibleOverflownPropertyProxy(this, &visible_overflown_property);
}

inline const Xfc::Gtk::Action::ActivateSignalProxy
Xfc::Gtk::Action::signal_activate()
{
	return ActivateSignalProxy(this, &activate_signal);
}

