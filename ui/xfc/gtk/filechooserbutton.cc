
/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  filechooserbutton.cc - GtkFileChooserButton C++ wrapper implementation
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
 
#include "filechooserbutton.hh"
#include "filechooserdialog.hh"
#include "private/filechooserbuttonclass.hh"

using namespace Xfc;

/*  Gtk::FileChooserButton
 */

Gtk::FileChooserButton::FileChooserButton(GtkFileChooserButton *button, bool owns_reference)
: HBox((GtkHBox*)button, owns_reference)
{
}

Gtk::FileChooserButton::FileChooserButton(FileChooserAction action, const char *backend)
: HBox((GtkHBox*)FileChooserButtonClass::create(backend))
{
	set_action(action);
}	
	
Gtk::FileChooserButton::FileChooserButton(const char *title, FileChooserAction action, const char *backend)
: HBox((GtkHBox*)FileChooserButtonClass::create(backend))
{
	set_title(title);
	set_action(action);
}	
	
Gtk::FileChooserButton::FileChooserButton(const String& title, FileChooserAction action, const char *backend)
: HBox((GtkHBox*)FileChooserButtonClass::create(backend))
{
	set_title(title);
	set_action(action);
}	
	
Gtk::FileChooserButton::FileChooserButton(FileChooserDialog& dialog)
: HBox((GtkHBox*)FileChooserButtonClass::create(dialog))
{
}	
	
Gtk::FileChooserButton::~FileChooserButton()
{
}

String 
Gtk::FileChooserButton::get_title() const
{
	return gtk_file_chooser_button_get_title(gtk_file_chooser_button());
}
	
void 
Gtk::FileChooserButton::set_title(const String& title)
{
	set_title(title.c_str());
}

/*  Gtk::FileChooserOpenButton
 */

Gtk::FileChooserOpenButton::FileChooserOpenButton()
: FileChooserButton("Open...", Gtk::FILE_CHOOSER_ACTION_OPEN)
{
}	
	
Gtk::FileChooserOpenButton::FileChooserOpenButton(const char *title)
: FileChooserButton(title, Gtk::FILE_CHOOSER_ACTION_OPEN)
{
}	
	
Gtk::FileChooserOpenButton::FileChooserOpenButton(const String& title)
: FileChooserButton(title, Gtk::FILE_CHOOSER_ACTION_OPEN)
{
}	
	
Gtk::FileChooserOpenButton::~FileChooserOpenButton()
{
}

/*  Gtk::FileChooserButtonClass
 */

void
Gtk::FileChooserButtonClass::init(GtkFileChooserButtonClass *g_class)
{
	HBoxClass::init((GtkHBoxClass*)g_class);
}

GType
Gtk::FileChooserButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_FILE_CHOOSER_BUTTON, (GClassInitFunc)&init);
		G::TypeInstance::add_interface(type, GTK_TYPE_FILE_CHOOSER, (GInterfaceInitFunc)0);
	}
	return type;
}

void*
Gtk::FileChooserButtonClass::create(const char *backend)
{
	return g_object_new(get_type(), "file-system-backend", backend, 0);
}

void*
Gtk::FileChooserButtonClass::create(FileChooserDialog& dialog)
{
	return g_object_new(get_type(), "dialog", dialog.gtk_file_chooser_dialog(), 0);
}

