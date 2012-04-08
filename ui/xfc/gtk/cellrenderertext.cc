/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  cellrenderertext.cc - GtkCellRendererText C++ wrapper implementation
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
 
#include "cellrenderertext.hh"
#include "cellrenderertextsignals.hh"
#include "private/cellrenderertextclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::CellRendererText
 */

Gtk::CellRendererText::CellRendererText(GtkCellRendererText *cell, bool owns_reference)
: CellRenderer((GtkCellRenderer*)cell, owns_reference)
{
}

Gtk::CellRendererText::CellRendererText()
: CellRenderer((GtkCellRenderer*)CellRendererTextClass::create())
{
}

Gtk::CellRendererText::~CellRendererText()
{
}

/*  Gtk::CellRendererTextClass
 */

void
Gtk::CellRendererTextClass::init(GtkCellRendererTextClass *g_class)
{
	CellRendererClass::init((GtkCellRendererClass*)g_class);
	g_class->edited = &edited_proxy;
}

GtkCellRendererTextClass*
Gtk::CellRendererTextClass::get_parent_class(void *instance)
{
	return static_cast<GtkCellRendererTextClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::CellRendererTextClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CELL_RENDERER_TEXT, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::CellRendererTextClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::CellRendererTextClass::edited_proxy(GtkCellRendererText *cell_renderer_text, const gchar *path, const gchar *new_text)
{
	CellRendererTextSignals *signals = dynamic_cast<CellRendererTextSignals*>(G::ObjectSignals::pointer((GObject*)cell_renderer_text));
	if (signals)
	{
		String tmp_path(path);
		String tmp_new_text(new_text);
		signals->on_edited(tmp_path, tmp_new_text);
	}
	else
	{
		GtkCellRendererTextClass *g_class = get_parent_class(cell_renderer_text);
		if (g_class && g_class->edited)
			g_class->edited(cell_renderer_text, path, new_text);
	}
}

/*  Gtk::CellRendererText properties
 */

const Gtk::CellRendererText::TextPropertyType Gtk::CellRendererText::text_property("text");

const Gtk::CellRendererText::MarkupPropertyType Gtk::CellRendererText::markup_property("markup");

const Gtk::CellRendererText::AttributePropertyType Gtk::CellRendererText::attribute_property("attribute");

const Gtk::CellRendererText::SingleParagraphModePropertyType Gtk::CellRendererText::single_paragraph_mode_property("single_paragraph_mode");

const Gtk::CellRendererText::WidthCharsPropertyType Gtk::CellRendererText::width_chars_property("width_chars");

const Gtk::CellRendererText::BackgroundPropertyType Gtk::CellRendererText::background_property("background");

const Gtk::CellRendererText::BackgroundGdkPropertyType Gtk::CellRendererText::background_gdk_property("background_gdk");

const Gtk::CellRendererText::ForegroundPropertyType Gtk::CellRendererText::foreground_property("foreground");

const Gtk::CellRendererText::ForegroundGdkPropertyType Gtk::CellRendererText::foreground_gdk_property("foreground_gdk");

const Gtk::CellRendererText::EditablePropertyType Gtk::CellRendererText::editable_property("editable");

const Gtk::CellRendererText::FontPropertyType Gtk::CellRendererText::font_property("font");

const Gtk::CellRendererText::FontDescPropertyType Gtk::CellRendererText::font_desc_property("font_desc");

const Gtk::CellRendererText::FamilyPropertyType Gtk::CellRendererText::family_property("family");

const Gtk::CellRendererText::StylePropertyType Gtk::CellRendererText::style_property("style");

const Gtk::CellRendererText::VariantPropertyType Gtk::CellRendererText::variant_property("variant");

const Gtk::CellRendererText::WeightPropertyType Gtk::CellRendererText::weight_property("weight");

const Gtk::CellRendererText::StretchPropertyType Gtk::CellRendererText::stretch_property("stretch");

const Gtk::CellRendererText::SizePropertyType Gtk::CellRendererText::size_property("size");

const Gtk::CellRendererText::SizePointsPropertyType Gtk::CellRendererText::size_points_property("size_points");

const Gtk::CellRendererText::ScalePropertyType Gtk::CellRendererText::scale_property("scale");

const Gtk::CellRendererText::RisePropertyType Gtk::CellRendererText::rise_property("rise");

const Gtk::CellRendererText::LanguagePropertyType Gtk::CellRendererText::language_property("language");

const Gtk::CellRendererText::StrikethroughPropertyType Gtk::CellRendererText::strikethrough_property("strikethrough");

const Gtk::CellRendererText::UnderlinePropertyType Gtk::CellRendererText::underline_property("underline");

const Gtk::CellRendererText::EllipsizePropertyType Gtk::CellRendererText::ellipsize_property("ellipsize");

const Gtk::CellRendererText::BackgroundSetPropertyType Gtk::CellRendererText::background_set_property("background_set");

const Gtk::CellRendererText::ForegroundSetPropertyType Gtk::CellRendererText::foreground_set_property("foreground_set");

const Gtk::CellRendererText::EditableSetPropertyType Gtk::CellRendererText::editable_set_property("editable_set");

const Gtk::CellRendererText::FamilySetPropertyType Gtk::CellRendererText::family_set_property("family_set");

const Gtk::CellRendererText::StyleSetPropertyType Gtk::CellRendererText::style_set_property("style_set");

const Gtk::CellRendererText::VariantSetPropertyType Gtk::CellRendererText::variant_set_property("variant_set");

const Gtk::CellRendererText::WeightSetPropertyType Gtk::CellRendererText::weight_set_property("weight_set");

const Gtk::CellRendererText::StretchSetPropertyType Gtk::CellRendererText::stretch_set_property("stretch_set");

const Gtk::CellRendererText::SizeSetPropertyType Gtk::CellRendererText::size_set_property("size_set");

const Gtk::CellRendererText::ScaleSetPropertyType Gtk::CellRendererText::scale_set_property("scale_set");

const Gtk::CellRendererText::RiseSetPropertyType Gtk::CellRendererText::rise_set_property("rise_set");

const Gtk::CellRendererText::StrikethroughSetPropertyType Gtk::CellRendererText::strikethrough_set_property("strikethrough_set");

const Gtk::CellRendererText::UnderlineSetPropertyType Gtk::CellRendererText::underline_set_property("underline_set");

const Gtk::CellRendererText::LanguageSetPropertyType Gtk::CellRendererText::language_set_property("language_set");

const Gtk::CellRendererText::EllipsizeSetPropertyType Gtk::CellRendererText::ellipsize_set_property("ellipsize_set");

/*  Gtk::CellRendererText signals
 */

const Gtk::CellRendererText::EditedSignalType Gtk::CellRendererText::edited_signal("edited", (GCallback)&Marshal::void_string_string_callback);

