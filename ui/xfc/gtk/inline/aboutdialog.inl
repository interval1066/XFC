/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  aboutdialog.inl - Gtk::AboutDialog inline functions
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

inline GtkAboutDialog*
Xfc::Gtk::AboutDialog::gtk_about_dialog() const
{
	return reinterpret_cast<GtkAboutDialog*>(instance_);
}

inline Xfc::Gtk::AboutDialog::operator GtkAboutDialog* () const
{
	return this ? gtk_about_dialog() : 0;
}

inline void 
Xfc::Gtk::AboutDialog::set_name(const char *name)
{
	gtk_about_dialog_set_name(gtk_about_dialog(), name);
}

inline void 
Xfc::Gtk::AboutDialog::set_version(const char *version)
{
	gtk_about_dialog_set_version(gtk_about_dialog(), version);
}
inline void 
Xfc::Gtk::AboutDialog::set_copyright(const char *copyright)
{
	gtk_about_dialog_set_copyright(gtk_about_dialog(), copyright);
}
	
inline void 
Xfc::Gtk::AboutDialog::set_comments(const char *comments)
{
	gtk_about_dialog_set_comments(gtk_about_dialog(), comments);
}
	
inline void 
Xfc::Gtk::AboutDialog::set_license(const char *license)
{
	gtk_about_dialog_set_license(gtk_about_dialog(), license);
}
	
inline void 
Xfc::Gtk::AboutDialog::set_website(const char *website)
{
	gtk_about_dialog_set_website(gtk_about_dialog(), website);
}
	
inline void 
Xfc::Gtk::AboutDialog::set_website_label(const char *website_label)
{
	gtk_about_dialog_set_website_label(gtk_about_dialog(), website_label);
}
	
inline void 
Xfc::Gtk::AboutDialog::set_translator_credits(const char *translator_credits)
{
	gtk_about_dialog_set_translator_credits(gtk_about_dialog(), translator_credits);
}
	
inline void 
Xfc::Gtk::AboutDialog::set_logo_icon_name(const char *icon_name)
{
	gtk_about_dialog_set_logo_icon_name(gtk_about_dialog(), icon_name);
}
	
