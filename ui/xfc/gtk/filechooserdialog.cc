/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  filechooserdialog.cc - GtkFileChooserDialog C++ wrapper implementation
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

#include "filechooserdialog.hh"
#include "private/filechooserdialogclass.hh"

using namespace Xfc;

/*  Gtk::FileChooserDialog
 */

Gtk::FileChooserDialog::FileChooserDialog(GtkFileChooserDialog *dialog, bool owns_reference)
: Dialog((GtkDialog*)dialog, owns_reference)
{
}

Gtk::FileChooserDialog::FileChooserDialog(const char *title, FileChooserAction action, const char *backend)
: Dialog((GtkDialog*)FileChooserDialogClass::create(backend))
{
	set_title(title);
	set_action(action);
}	
	
Gtk::FileChooserDialog::FileChooserDialog(const String& title, FileChooserAction action, const char *backend)
: Dialog((GtkDialog*)FileChooserDialogClass::create(backend))
{
	set_title(title);
	set_action(action);
}	
	
Gtk::FileChooserDialog::FileChooserDialog(const char *title, Window *parent, FileChooserAction action, const char *backend)
: Dialog((GtkDialog*)FileChooserDialogClass::create(backend))
{
	set_title(title);
	set_action(action);
	if (parent)
		set_transient_for(parent);
}	
	
Gtk::FileChooserDialog::FileChooserDialog(const String& title, Window *parent, FileChooserAction action, const char *backend)
: Dialog((GtkDialog*)FileChooserDialogClass::create(backend))
{
	set_title(title);
	set_action(action);
	if (parent)
		set_transient_for(parent);
}	
	
Gtk::FileChooserDialog::~FileChooserDialog()
{
}

/*  Gtk::FileChooserOpenDialog
 */

Gtk::FileChooserOpenDialog::FileChooserOpenDialog(Window *parent)
: FileChooserDialog("Open...", parent, Gtk::FILE_CHOOSER_ACTION_OPEN)
{
}	
	
Gtk::FileChooserOpenDialog::FileChooserOpenDialog(const char *title, Window *parent)
: FileChooserDialog(title, parent, Gtk::FILE_CHOOSER_ACTION_OPEN)
{
}	
	
Gtk::FileChooserOpenDialog::FileChooserOpenDialog(const String& title, Window *parent)
: FileChooserDialog(title, parent, Gtk::FILE_CHOOSER_ACTION_OPEN)
{
}	
	
Gtk::FileChooserOpenDialog::~FileChooserOpenDialog()
{
}
	
/*  Gtk::FileChooserSaveAsDialog
 */

Gtk::FileChooserSaveAsDialog::FileChooserSaveAsDialog(Window *parent)
: FileChooserDialog("Save as...", parent, Gtk::FILE_CHOOSER_ACTION_SAVE)
{
}	
	
Gtk::FileChooserSaveAsDialog::FileChooserSaveAsDialog(const char *title, Window *parent)
: FileChooserDialog(title, parent, Gtk::FILE_CHOOSER_ACTION_SAVE)
{
}	
	
Gtk::FileChooserSaveAsDialog::FileChooserSaveAsDialog(const String& title, Window *parent)
: FileChooserDialog(title, parent, Gtk::FILE_CHOOSER_ACTION_SAVE)
{
}	
	
Gtk::FileChooserSaveAsDialog::~FileChooserSaveAsDialog()
{
}

/*  Gtk::FileChooserDialogClass
 */

void
Gtk::FileChooserDialogClass::init(GtkFileChooserDialogClass *g_class)
{
	DialogClass::init((GtkDialogClass*)g_class);
}

GType
Gtk::FileChooserDialogClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_FILE_CHOOSER_DIALOG, (GClassInitFunc)&init);
		G::TypeInstance::add_interface(type, GTK_TYPE_FILE_CHOOSER, (GInterfaceInitFunc)0);
	}
	return type;
}

void*
Gtk::FileChooserDialogClass::create(const char *backend)
{
	return g_object_new(get_type(), "file-system-backend", backend, 0);
}

