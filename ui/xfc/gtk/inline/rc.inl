/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  rc.inl - Gtk::RC and Gtk::RcStyle inline functions
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

/*  Gtk::RC
 */

inline void
Xfc::Gtk::RC::add_default_file(const char *filename)
{
	gtk_rc_add_default_file(filename);
}

inline void
Xfc::Gtk::RC::parse(const char *filename)
{
	gtk_rc_parse(filename);
}

inline void
Xfc::Gtk::RC::parse_string(const char *rc_string)
{
	gtk_rc_parse_string(rc_string);
}

inline bool
Xfc::Gtk::RC::reparse_all()
{
	return gtk_rc_reparse_all();
}

/*  Gtk::RcStyle
 */

inline GtkRcStyle*
Xfc::Gtk::RcStyle::gtk_rc_style() const
{
	return reinterpret_cast<GtkRcStyle*>(instance_);
}

inline Xfc::Gtk::RcStyle::operator GtkRcStyle* () const
{
	return this ? gtk_rc_style() : 0;
}

inline bool 
Xfc::Gtk::RcStyle::fg_set(StateType state_type) const
{
	return (gtk_rc_style()->color_flags[state_type] & GTK_RC_FG) != 0;
}	
	
inline bool 
Xfc::Gtk::RcStyle::bg_set(StateType state_type) const
{
	return (gtk_rc_style()->color_flags[state_type] & GTK_RC_BG) != 0;
}	
	
inline bool 
Xfc::Gtk::RcStyle::text_set(StateType state_type) const
{
	return (gtk_rc_style()->color_flags[state_type] & GTK_RC_TEXT) != 0;
}	
	
inline bool 
Xfc::Gtk::RcStyle::base_set(StateType state_type) const
{
	return (gtk_rc_style()->color_flags[state_type] & GTK_RC_BASE) != 0;
}	

inline int 
Xfc::Gtk::RcStyle::xthickness() const
{
	return gtk_rc_style()->xthickness;
}

inline int 
Xfc::Gtk::RcStyle::ythickness() const
{
	return gtk_rc_style()->ythickness;
}

inline void 
Xfc::Gtk::RcStyle::unset_fg(StateType state_type)
{
	((int&)gtk_rc_style()->color_flags[state_type]) &= ~ int(GTK_RC_FG);
}

inline void 
Xfc::Gtk::RcStyle::unset_bg(StateType state_type)
{
	((int&)gtk_rc_style()->color_flags[state_type]) &= ~ int(GTK_RC_BG);
}

inline void 
Xfc::Gtk::RcStyle::unset_text(StateType state_type)
{
	((int&)gtk_rc_style()->color_flags[state_type]) &= ~ int(GTK_RC_TEXT);
}

inline void 
Xfc::Gtk::RcStyle::unset_base(StateType state_type)
{
	((int&)gtk_rc_style()->color_flags[state_type]) &= ~ int(GTK_RC_BASE);
}

inline void 
Xfc::Gtk::RcStyle::set_xthickness(int size)
{
	gtk_rc_style()->xthickness = size;
}

inline void 
Xfc::Gtk::RcStyle::set_ythickness(int size)
{
	gtk_rc_style()->ythickness = size;
}

