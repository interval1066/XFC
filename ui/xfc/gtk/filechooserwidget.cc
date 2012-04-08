/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  filechooserwidget.cc - GtkFileChooserWidget C++ wrapper implementation
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

#include "filechooserwidget.hh"
#include "private/filechooserwidgetclass.hh"

using namespace Xfc;

/*  Gtk::FileChooserWidget
 */

Gtk::FileChooserWidget::FileChooserWidget(GtkFileChooserWidget *widget, bool owns_reference)
: VBox((GtkVBox*)widget, owns_reference)
{
}

Gtk::FileChooserWidget::FileChooserWidget(FileChooserAction action, const char *backend)
: VBox((GtkVBox*)FileChooserWidgetClass::create(backend))
{
	set_action(action);
}	
	
Gtk::FileChooserWidget::~FileChooserWidget()
{
}

/*  Gtk::FileChooserWidgetClass
 */

void
Gtk::FileChooserWidgetClass::init(GtkFileChooserWidgetClass *g_class)
{
	VBoxClass::init((GtkVBoxClass*)g_class);
}

GType
Gtk::FileChooserWidgetClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_FILE_CHOOSER_WIDGET, (GClassInitFunc)&init);
		G::TypeInstance::add_interface(type, GTK_TYPE_FILE_CHOOSER, (GInterfaceInitFunc)0);
	}
	return type;
}

void*
Gtk::FileChooserWidgetClass::create(const char *backend)
{
	return g_object_new(get_type(), "file-system-backend", backend, 0);
}

