/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  messagedialog.cc - GtkMessageDialog C++ wrapper implementation
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
 
#include "messagedialog.hh"
#include "private/messagedialogclass.hh"
#include <gtk/gtklabel.h>

using namespace Xfc;

/*  Gtk::MessageDialog
 */

Gtk::MessageDialog::MessageDialog(GtkMessageDialog *dialog, bool owns_reference)
: Dialog((GtkDialog*)dialog, owns_reference)
{
}

namespace {

using namespace Gtk;

void
set_dialog_data(MessageDialog *dialog, Window *parent, DialogFlagsField flags)
{
	if (parent)
		dialog->set_transient_for(parent);
	if (flags & DIALOG_MODAL)
		dialog->set_modal(true);
	if (flags & DIALOG_DESTROY_WITH_PARENT)
		dialog->set_destroy_with_parent(true);
	if (flags & DIALOG_NO_SEPARATOR)
		dialog->set_has_separator(false);
}

} // namespace

Gtk::MessageDialog::MessageDialog(Window *parent, DialogFlagsField flags)
{
	set_dialog_data(this, parent, flags);
}

Gtk::MessageDialog::MessageDialog(MessageType type, ButtonType buttons, Window *parent, DialogFlagsField flags)
: Dialog((GtkDialog*)MessageDialogClass::create((GtkMessageType)type, (GtkButtonsType)buttons))
{
	set_dialog_data(this, parent, flags);
}

Gtk::MessageDialog::MessageDialog(MessageType type, ButtonType buttons, const String& message, Window *parent, DialogFlagsField flags)
: Dialog((GtkDialog*)MessageDialogClass::create((GtkMessageType)type, (GtkButtonsType)buttons))
{
	set_dialog_data(this, parent, flags);
	set_message(message);
}

Gtk::MessageDialog::~MessageDialog()
{
}

void
Gtk::MessageDialog::set_message(const char *message)
{
	gtk_label_set_text(GTK_LABEL(gtk_message_dialog()->label), message);
}

void
Gtk::MessageDialog::set_message(const String& message)
{
	set_message(message.c_str());
}

void
Gtk::MessageDialog::format_message(const char *message_format, ...)
{
	va_list args;
	va_start(args, message_format);
	char* msg = g_strdup_vprintf(message_format, args);
	va_end(args);
	gtk_label_set_text(GTK_LABEL(gtk_message_dialog()->label), msg);
	g_free(msg);
}

void
Gtk::MessageDialog::set_markup(const String& message)
{
	set_markup(message.c_str());
}

void
Gtk::MessageDialog::format_markup(const char *message_format, ...)
{
	va_list args;
	va_start(args, message_format);
	char* msg = g_strdup_vprintf(message_format, args);
	va_end(args);
	gtk_message_dialog_set_markup(gtk_message_dialog(), msg);
	g_free(msg);
}

void 
Gtk::MessageDialog::set_secondary_text(const String& message)
{
	set_secondary_text(message.c_str());
}
	
void 
Gtk::MessageDialog::format_secondary_text(const char *message_format, ...)
{
	va_list args;
	va_start(args, message_format);
	char* msg = g_strdup_vprintf(message_format, args);
	va_end(args);
	gtk_message_dialog_format_secondary_text(gtk_message_dialog(), msg);
	g_free(msg);
}

void 
Gtk::MessageDialog::set_secondary_markup(const String& message)
{
	set_secondary_markup(message.c_str());
}

void 
Gtk::MessageDialog::format_secondary_markup(const char *message_format, ...)
{
	va_list args;
	va_start(args, message_format);
	char* msg = g_strdup_vprintf(message_format, args);
	va_end(args);
	gtk_message_dialog_format_secondary_markup(gtk_message_dialog(), msg);
	g_free(msg);
}

/*  Gtk::MessageDialogClass
 */

void
Gtk::MessageDialogClass::init(GtkMessageDialogClass *g_class)
{
	DialogClass::init((GtkDialogClass*)g_class);
}

GType
Gtk::MessageDialogClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_MESSAGE_DIALOG, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::MessageDialogClass::create(GtkMessageType type, GtkButtonsType buttons)
{
	return g_object_new(get_type(), "message_type", type, "buttons", buttons, 0);
}

