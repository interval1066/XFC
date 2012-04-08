/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  colorselection.cc - GtkColorSelection and GtkColorSelectionDialog C++ wrapper implementation
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
 
#include "colorselection.hh"
#include "colorselectionsignals.hh"
#include "button.hh"
#include "private/colorselectionclass.hh"
#include "private/marshal.hh"
#include "../gdk/color.hh"

using namespace Xfc;

/*  Gtk::ColorSelection
 */
 
Gtk::ColorSelection::ColorSelection(GtkColorSelection *color_selection, bool owns_reference)
: VBox((GtkVBox*)color_selection, owns_reference)
{
}

Gtk::ColorSelection::ColorSelection()
: VBox((GtkVBox*)ColorSelectionClass::create())
{
}

Gtk::ColorSelection::~ColorSelection()
{
}

Gdk::Color
Gtk::ColorSelection::get_current_color() const
{
	GdkColor color;
	gtk_color_selection_get_current_color(gtk_color_selection(), &color);
	return Gdk::Color(&color, true);
}

Gdk::Color
Gtk::ColorSelection::get_previous_color() const
{
	GdkColor color;
	gtk_color_selection_get_previous_color(gtk_color_selection(), &color);
	return Gdk::Color(&color, true);
}

void
Gtk::ColorSelection::set_current_color(const Gdk::Color& color)
{
	gtk_color_selection_set_current_color(gtk_color_selection(), color.gdk_color());
}

void
Gtk::ColorSelection::set_previous_color(const Gdk::Color& color)
{
	gtk_color_selection_set_previous_color(gtk_color_selection(), color.gdk_color());
}

bool
Gtk::ColorSelection::palette_from_string(const String& str, std::vector<Gdk::Color>& colors)
{
	g_return_val_if_fail(colors.empty(), false);
	GdkColor *tmp_colors = 0;
	int n_colors = 0;
	
	bool result = gtk_color_selection_palette_from_string(str.c_str(), &tmp_colors, &n_colors);
	
	if (result)
	{
		int i = 0;
		while (i < n_colors)
		{
			colors.push_back(Gdk::Color(&tmp_colors[i], true));
			++i;
		}
		result = !colors.empty();
		g_free(tmp_colors);
	}
	return result;
}
	
String
Gtk::ColorSelection::palette_to_string(const std::vector<Gdk::Color>& colors)
{
	g_return_val_if_fail(!colors.empty(), "");
	int count = colors.size();
	GdkColor *tmp_colors = new GdkColor[count];

	int i = 0;
	while (i < count)
	{
		tmp_colors[i] = *colors[i].gdk_color();
		++i;
	}
	
	char *s = gtk_color_selection_palette_to_string(tmp_colors, count);
	String str(s);
	g_free(s);
	delete [] tmp_colors;
	return str;
}

/*  Gtk::ColorSelectionClass
 */

void
Gtk::ColorSelectionClass::init(GtkColorSelectionClass *g_class)
{
	VBoxClass::init((GtkVBoxClass*)g_class);
	g_class->color_changed = &color_changed_proxy;
}

GtkColorSelectionClass*
Gtk::ColorSelectionClass::get_parent_class(void *instance)
{
	return static_cast<GtkColorSelectionClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ColorSelectionClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_COLOR_SELECTION, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ColorSelectionClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ColorSelectionClass::color_changed_proxy(GtkColorSelection *color_selection)
{
	ColorSelectionSignals *signals = dynamic_cast<ColorSelectionSignals*>(G::ObjectSignals::pointer((GObject*)color_selection));
	if (signals)
		signals->on_color_changed();
	else
	{
		GtkColorSelectionClass *g_class = get_parent_class(color_selection);
		if (g_class && g_class->color_changed)
			g_class->color_changed(color_selection);
	}
}

/*  Gtk::ColorSelection signals
 */

const Gtk::ColorSelection::ColorChangedSignalType Gtk::ColorSelection::color_changed_signal("color_changed", (GCallback)&G::Marshal::void_callback);

/*  Gtk::ColorSelectionDialog
 */

Gtk::ColorSelectionDialog::ColorSelectionDialog(GtkColorSelectionDialog *color_selection_dialog, bool owns_reference)
: Dialog((GtkDialog*)color_selection_dialog, owns_reference)
{
}

Gtk::ColorSelectionDialog::ColorSelectionDialog() 
: Dialog((GtkDialog*)ColorSelectionDialogClass::create())
{
}

Gtk::ColorSelectionDialog::ColorSelectionDialog(const char *title)
: Dialog((GtkDialog*)ColorSelectionDialogClass::create())
{
	set_title(title);
}

Gtk::ColorSelectionDialog::ColorSelectionDialog(const String& title)
: Dialog((GtkDialog*)ColorSelectionDialogClass::create())
{
	set_title(title);
}

Gtk::ColorSelectionDialog::~ColorSelectionDialog()
{
}

Gtk::ColorSelection*
Gtk::ColorSelectionDialog::colorsel() const
{
	return G::Object::wrap<ColorSelection>((GtkColorSelection*)gtk_color_selection_dialog()->colorsel);
}

Gtk::Button*
Gtk::ColorSelectionDialog::ok_button() const
{
	return G::Object::wrap<Button>((GtkButton*)gtk_color_selection_dialog()->ok_button);
}

Gtk::Button*
Gtk::ColorSelectionDialog::cancel_button() const
{
	return G::Object::wrap<Button>((GtkButton*)gtk_color_selection_dialog()->cancel_button);
}

Gtk::Button*
Gtk::ColorSelectionDialog::help_button() const
{
	return G::Object::wrap<Button>((GtkButton*)gtk_color_selection_dialog()->help_button);
}

/*  Gtk::ColorSelectionDialogClass
 */

void
Gtk::ColorSelectionDialogClass::init(GtkColorSelectionDialogClass *g_class)
{
	DialogClass::init((GtkDialogClass*)g_class);
}

GType
Gtk::ColorSelectionDialogClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_COLOR_SELECTION_DIALOG, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ColorSelectionDialogClass::create()
{
	return g_object_new(get_type(), 0);
}

