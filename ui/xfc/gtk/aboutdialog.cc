/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  aboutdialog.cc - GtkAboutDialog C++ wrapper implementation
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
 
#include "aboutdialog.hh"
#include "private/aboutdialogclass.hh"
#include "../gdk-pixbuf/pixbuf.hh"
#include "xfc/convert.hh"

using namespace Xfc;

/*  Gtk::AboutDialog
 */

Gtk::AboutDialog::AboutDialog(GtkAboutDialog *about, bool owns_reference)
: Dialog((GtkDialog*)about, owns_reference)
{
}

Gtk::AboutDialog::AboutDialog()
: Dialog((GtkDialog*)gtk_about_dialog_new())
{
}
	
Gtk::AboutDialog::AboutDialog(const char *name, const char *version)
: Dialog((GtkDialog*)gtk_about_dialog_new())
{
	g_object_set(g_object(), "name", name, "version", version, 0);
}	

Gtk::AboutDialog::AboutDialog(const String& name, const String& version)
: Dialog((GtkDialog*)gtk_about_dialog_new())
{
	g_object_set(g_object(), "name", name.c_str(), "version", version.c_str(), 0);
}	
	
Gtk::AboutDialog::AboutDialog(const char *name, const char *version, const char *copyright, Gdk::Pixbuf *logo)
: Dialog((GtkDialog*)gtk_about_dialog_new())
{
	g_object_set(g_object(), "name", name, "version", version, "copyright", copyright, "logo", logo->gdk_pixbuf(), 0);
}
	
Gtk::AboutDialog::AboutDialog(const String& name, const String& version, const String& copyright, Gdk::Pixbuf *logo)
: Dialog((GtkDialog*)gtk_about_dialog_new())
{
	g_object_set(g_object(), "name", name.c_str(), "version", version.c_str(), "copyright", copyright.c_str(), "logo", logo->gdk_pixbuf(), 0);
}	

Gtk::AboutDialog::~AboutDialog()
{
}

String 
Gtk::AboutDialog::get_name() const
{
	return gtk_about_dialog_get_name(gtk_about_dialog());
}

String 
Gtk::AboutDialog::get_version() const
{
	return gtk_about_dialog_get_version(gtk_about_dialog());
}
	
String 
Gtk::AboutDialog::get_copyright() const
{
	return gtk_about_dialog_get_copyright(gtk_about_dialog());
}
	
String 
Gtk::AboutDialog::get_comments() const
{
	return gtk_about_dialog_get_comments(gtk_about_dialog());
}

String 
Gtk::AboutDialog::get_license() const
{
	return gtk_about_dialog_get_license(gtk_about_dialog());
}

String 
Gtk::AboutDialog::get_website() const
{
	return gtk_about_dialog_get_website(gtk_about_dialog());
}
	
String 
Gtk::AboutDialog::get_website_label() const
{
	return gtk_about_dialog_get_website_label(gtk_about_dialog());
}
	
std::vector<String> 
Gtk::AboutDialog::get_authors() const
{
	return array_to_vector_of_string(gtk_about_dialog_get_authors(gtk_about_dialog()));
}
	
std::vector<String> 
Gtk::AboutDialog::get_documenters() const
{
	return array_to_vector_of_string(gtk_about_dialog_get_documenters(gtk_about_dialog()));
}
	
std::vector<String> 
Gtk::AboutDialog::get_artists() const
{
	return array_to_vector_of_string(gtk_about_dialog_get_artists(gtk_about_dialog()));
}
	
String 
Gtk::AboutDialog::get_translator_credits() const
{
	return gtk_about_dialog_get_translator_credits(gtk_about_dialog());
}
	
Gdk::Pixbuf* 
Gtk::AboutDialog::get_logo() const
{
	GdkPixbuf *logo = gtk_about_dialog_get_logo(gtk_about_dialog());
	return G::Object::wrap<Gdk::Pixbuf>(logo);
}
	
String 
Gtk::AboutDialog::get_logo_icon_name() const
{
	return gtk_about_dialog_get_logo_icon_name(gtk_about_dialog());
}

void 
Gtk::AboutDialog::set_name(const String& name)
{
	set_name(name.c_str());
}
	
void 
Gtk::AboutDialog::set_version(const String& version)
{
	set_version(version.c_str());
}
	
void 
Gtk::AboutDialog::set_copyright(const String& copyright)
{
	set_copyright(copyright.c_str());
}
	
void 
Gtk::AboutDialog::set_comments(const String& comments)
{
	set_comments(comments.c_str());
}

void 
Gtk::AboutDialog::set_license(const String& license)
{
	set_license(license.c_str());
}

void 
Gtk::AboutDialog::set_website(const String& website)
{
	set_website(website.c_str());
}
	
void 
Gtk::AboutDialog::set_website_label(const String& website_label)
{
	set_website_label(website_label.c_str());
}

void 
Gtk::AboutDialog::set_authors(const std::vector<String>& authors)
{
	char **tmp_authors = vector_of_string_to_array(authors);	
	gtk_about_dialog_set_authors(gtk_about_dialog(), const_cast<const char**>(tmp_authors));
	delete [] tmp_authors;
}
	
void 
Gtk::AboutDialog::set_documenters(const std::vector<String>& documenters)
{
	char **tmp_documenters = vector_of_string_to_array(documenters);	
	gtk_about_dialog_set_documenters(gtk_about_dialog(), const_cast<const char**>(tmp_documenters));
	delete [] tmp_documenters;
}

void 
Gtk::AboutDialog::set_artists(const std::vector<String>& artists)
{
	char **tmp_artists = vector_of_string_to_array(artists);	
	gtk_about_dialog_set_artists(gtk_about_dialog(), const_cast<const char**>(tmp_artists));
	delete [] tmp_artists;
}

void 
Gtk::AboutDialog::set_translator_credits(const String& translator_credits)
{
	set_translator_credits(translator_credits.c_str());
}
		
void 
Gtk::AboutDialog::set_logo(Gdk::Pixbuf *logo)
{
	gtk_about_dialog_set_logo(gtk_about_dialog(), *logo);
}

void 
Gtk::AboutDialog::set_logo_icon_name(const String& icon_name)
{
	set_logo_icon_name(icon_name.c_str());
}
	 
namespace { // LinkCallback

struct LinkCallback
{
	typedef Gtk::AboutDialog::ActivateLinkSlot ActivateLinkSlot;
	ActivateLinkSlot slot_;

	LinkCallback(const ActivateLinkSlot& slot)
	: slot_(slot)
	{
	}

	static void notify(GtkAboutDialog *about, const char *link, void *data)
	{
		LinkCallback *cb = static_cast<LinkCallback*>(data);
		Gtk::AboutDialog *tmp_about = G::Object::wrap<Gtk::AboutDialog>(about);
		String s(link);
		cb->slot_(*tmp_about, s);
	}

	static void destroy(void *data)
	{
		LinkCallback *cb = static_cast<LinkCallback*>(data);
		delete cb;
	}
};

} // namespace

void 
Gtk::AboutDialog::set_email_hook(const ActivateLinkSlot& slot)
{
	LinkCallback *cb = new LinkCallback(slot);
	gtk_about_dialog_set_email_hook(&LinkCallback::notify, cb, &LinkCallback::destroy);
}

void 
Gtk::AboutDialog::set_url_hook(const ActivateLinkSlot& slot)
{
	LinkCallback *cb = new LinkCallback(slot);
	gtk_about_dialog_set_url_hook(&LinkCallback::notify, cb, &LinkCallback::destroy);
}

/*  Gtk::AboutDialogClass
 */

void
Gtk::AboutDialogClass::init(GtkAboutDialogClass *g_class)
{
	DialogClass::init((GtkDialogClass*)g_class);
}

GType
Gtk::AboutDialogClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ABOUT_DIALOG, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::AboutDialogClass::create()
{
	return g_object_new(get_type(), 0);
}

