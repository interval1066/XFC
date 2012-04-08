/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  fontselection.cc - GtkFontSelection and GtkFontSelectionDiaog C++ wrapper implementation
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
 
#include "fontselection.hh"
#include "button.hh"
#include "entry.hh"
#include "label.hh"
#include "private/fontselectionclass.hh"
#include "../pango/font.hh"

using namespace Xfc;

/*  Gtk::FontSelection
 */
 
Gtk::FontSelection::FontSelection(GtkFontSelection *font_selection, bool owns_reference)
: VBox((GtkVBox*)font_selection, owns_reference)
{
}

Gtk::FontSelection::FontSelection()
: VBox((GtkVBox*)FontSelectionClass::create())
{
}

Gtk::FontSelection::~FontSelection()
{
}

Gtk::Entry*
Gtk::FontSelection::size_entry() const
{
	return G::Object::wrap<Entry>((GtkEntry*)gtk_font_selection()->size_entry);
}

Gtk::Entry*
Gtk::FontSelection::preview_entry() const
{
	return G::Object::wrap<Entry>((GtkEntry*)gtk_font_selection()->preview_entry);
}

Pango::FontFamily*
Gtk::FontSelection::get_font_family() const
{
	return G::Object::wrap<Pango::FontFamily>(gtk_font_selection()->family);
}

Pango::FontFace*
Gtk::FontSelection::get_font_face() const
{
	return G::Object::wrap<Pango::FontFace>(gtk_font_selection()->face);
}

String 
Gtk::FontSelection::get_font_name() const
{
	return gtk_font_selection_get_font_name(gtk_font_selection());
}

String 
Gtk::FontSelection::get_preview_text() const
{
	return gtk_font_selection_get_preview_text(gtk_font_selection());
}

bool
Gtk::FontSelection::set_font_name(const String& fontname)
{
	return gtk_font_selection_set_font_name(gtk_font_selection(), fontname.c_str());
}

void
Gtk::FontSelection::set_preview_text(const String& text)
{
	gtk_font_selection_set_preview_text(gtk_font_selection(), text.c_str());
}


/*  Gtk::FontSelectionClass
 */

void
Gtk::FontSelectionClass::init(GtkFontSelectionClass *g_class)
{
	VBoxClass::init((GtkVBoxClass*)g_class);
}

GType
Gtk::FontSelectionClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_FONT_SELECTION, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::FontSelectionClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::FontSelectionDialog
 */

Gtk::FontSelectionDialog::FontSelectionDialog(GtkFontSelectionDialog *font_selection_dialog, bool owns_reference)
: Dialog((GtkDialog*)font_selection_dialog, owns_reference)
{
}

Gtk::FontSelectionDialog::FontSelectionDialog()
: Dialog((GtkDialog*)FontSelectionDialogClass::create())
{
}

Gtk::FontSelectionDialog::FontSelectionDialog(const char *title)
: Dialog((GtkDialog*)FontSelectionDialogClass::create())
{
	set_title(title);
}

Gtk::FontSelectionDialog::FontSelectionDialog(const String& title)
: Dialog((GtkDialog*)FontSelectionDialogClass::create())
{
	set_title(title);
}

Gtk::FontSelectionDialog::~FontSelectionDialog()
{
}

Gtk::FontSelection*
Gtk::FontSelectionDialog::fontsel() const
{
	return G::Object::wrap<FontSelection>((GtkFontSelection*)gtk_font_selection_dialog()->fontsel);
}
  
Gtk::Button*
Gtk::FontSelectionDialog::ok_button() const
{
	return G::Object::wrap<Button>((GtkButton*)gtk_font_selection_dialog()->ok_button);
}
	
Gtk::Button* 
Gtk::FontSelectionDialog::apply_button() const
{
	return G::Object::wrap<Button>((GtkButton*)gtk_font_selection_dialog()->apply_button);
}

Gtk::Button* 
Gtk::FontSelectionDialog::cancel_button() const
{
	return G::Object::wrap<Button>((GtkButton*)gtk_font_selection_dialog()->cancel_button);
}
	
String 
Gtk::FontSelectionDialog::get_font_name() const 
{
	char *font_name = gtk_font_selection_dialog_get_font_name(gtk_font_selection_dialog());
	String s(font_name);
	g_free(font_name);
	return s;
}

String 
Gtk::FontSelectionDialog::get_preview_text() const
{
	return gtk_font_selection_dialog_get_preview_text(gtk_font_selection_dialog());
}

bool
Gtk::FontSelectionDialog::set_font_name(const String& fontname)
{
	return gtk_font_selection_dialog_set_font_name(gtk_font_selection_dialog(), fontname.c_str());
}

void
Gtk::FontSelectionDialog::set_preview_text(const String& text)
{
	gtk_font_selection_dialog_set_preview_text(gtk_font_selection_dialog(), text.c_str());
}

/*  Gtk::FontSelectionDialogClass
 */

void
Gtk::FontSelectionDialogClass::init(GtkFontSelectionDialogClass *g_class)
{
	DialogClass::init((GtkDialogClass*)g_class);
}

GType
Gtk::FontSelectionDialogClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_FONT_SELECTION_DIALOG, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::FontSelectionDialogClass::create()
{
	return g_object_new(get_type(), 0);
}

