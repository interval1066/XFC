/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  button.inl - Gtk::Button inline functions
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

inline GtkButton*
Xfc::Gtk::Button::gtk_button() const
{
	return reinterpret_cast<GtkButton*>(instance_);
}

inline Xfc::Gtk::Button::operator GtkButton* () const
{
	return this ? gtk_button() : 0;
}

inline Xfc::Gtk::ReliefStyle
Xfc::Gtk::Button::get_relief() const
{
	return (ReliefStyle)gtk_button_get_relief(gtk_button());
}

inline bool
Xfc::Gtk::Button::get_use_underline() const
{
	return gtk_button_get_use_underline(gtk_button());
}

inline bool
Xfc::Gtk::Button::get_use_stock() const
{
	return gtk_button_get_use_stock(gtk_button());
}

inline bool
Xfc::Gtk::Button::get_focus_on_click() const
{
	return gtk_button_get_focus_on_click(gtk_button());
}

inline void 
Xfc::Gtk::Button::get_alignment(float *xalign, float *yalign)
{
	gtk_button_get_alignment(gtk_button(), xalign, yalign);
}

inline void
Xfc::Gtk::Button::pressed()
{
	gtk_button_pressed(gtk_button());
}

inline void
Xfc::Gtk::Button::released()
{
	gtk_button_released(gtk_button());
}

inline void
Xfc::Gtk::Button::clicked()
{
	gtk_button_clicked((GtkButton*)instance_);
}

inline void
Xfc::Gtk::Button::enter()
{
	gtk_button_enter(gtk_button());
}

inline void
Xfc::Gtk::Button::leave()
{
	gtk_button_leave(gtk_button());
}

inline void
Xfc::Gtk::Button::set_relief(ReliefStyle newstyle)
{
	gtk_button_set_relief(gtk_button(), (GtkReliefStyle)newstyle);
}

inline void
Xfc::Gtk::Button::set_label(const char *label)
{
	gtk_button_set_label(gtk_button(), label);
}

inline void
Xfc::Gtk::Button::set_use_underline(bool value)
{
	gtk_button_set_use_underline(gtk_button(), value);
}

inline void
Xfc::Gtk::Button::set_use_stock(bool value)
{
	gtk_button_set_use_stock(gtk_button(), value);
}

inline void
Xfc::Gtk::Button::set_focus_on_click(bool focus_on_click)
{
	gtk_button_set_focus_on_click(gtk_button(), focus_on_click);
}

inline void 
Xfc::Gtk::Button::set_alignment(float xalign, float yalign)
{
	gtk_button_set_alignment(gtk_button(), xalign, yalign);
}

inline const Xfc::Gtk::Button::PressedSignalProxy
Xfc::Gtk::Button::signal_pressed()
{
	return PressedSignalProxy(this, &pressed_signal);
}

inline const Xfc::Gtk::Button::ReleasedSignalProxy
Xfc::Gtk::Button::signal_released()
{
	return ReleasedSignalProxy(this, &released_signal);
}

inline const Xfc::Gtk::Button::ClickedSignalProxy
Xfc::Gtk::Button::signal_clicked()
{
	return ClickedSignalProxy(this, &clicked_signal);
}

inline const Xfc::Gtk::Button::EnterSignalProxy
Xfc::Gtk::Button::signal_enter()
{
	return EnterSignalProxy(this, &enter_signal);
}

inline const Xfc::Gtk::Button::LeaveSignalProxy
Xfc::Gtk::Button::signal_leave()
{
	return LeaveSignalProxy(this, &leave_signal);
}

inline const Xfc::Gtk::Button::ActivateSignalProxy
Xfc::Gtk::Button::signal_activate()
{
	return ActivateSignalProxy(this, &activate_signal);
}

