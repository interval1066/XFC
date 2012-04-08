/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  texttag.cc - GtkTextTag and GtkTextTagTable C++ wrapper implementation
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
 
#include "texttag.hh"
#include "texttagsignals.hh"
#include "textiter.hh"
#include "private/marshal.hh"
#include "private/texttagclass.hh"
#include "../gdk/color.hh"
#include "../gdk/bitmap.hh"
#include "../gdk/events.hh"
#include "../pango/font.hh"
#include "../pango/tabs.hh"

using namespace Xfc;

/*  Gtk::TextAppearance
 */

Gdk::Color
Gtk::TextAppearance::bg_color() const
{
	return Gdk::Color(&gtk_text_appearance()->bg_color);
}

Gdk::Color
Gtk::TextAppearance::fg_color() const
{
	return Gdk::Color(&gtk_text_appearance()->fg_color);
}

Gdk::Bitmap*
Gtk::TextAppearance::bg_stipple() const
{
	return G::Object::wrap<Gdk::Bitmap>(appearence_.bg_stipple);
}

Gdk::Bitmap*
Gtk::TextAppearance::fg_stipple() const
{
	return G::Object::wrap<Gdk::Bitmap>(appearence_.fg_stipple);
}

void
Gtk::TextAppearance::set_colors(const Gdk::Color& fg_color, const Gdk::Color& bg_color)
{
	appearence_.fg_color = *fg_color.gdk_color();
	appearence_.bg_color = *bg_color.gdk_color();
}

void
Gtk::TextAppearance::set_bg_color(const Gdk::Color& color)
{
	appearence_.bg_color = *color.gdk_color();
}

void
Gtk::TextAppearance::set_fg_color(const Gdk::Color& color)
{
	appearence_.fg_color = *color.gdk_color();
}

void
Gtk::TextAppearance::set_stipple(const Gdk::Bitmap& fg_mask, const Gdk::Bitmap& bg_mask)
{
	appearence_.fg_stipple = fg_mask.gdk_bitmap();
	appearence_.bg_stipple = bg_mask.gdk_bitmap();
}

void
Gtk::TextAppearance::set_bg_stipple(const Gdk::Bitmap& mask)
{
	appearence_.bg_stipple = mask.gdk_bitmap();
}

void
Gtk::TextAppearance::set_fg_stipple(const Gdk::Bitmap& mask)
{
	appearence_.fg_stipple = mask.gdk_bitmap();
}

/*  Gtk::TextAttributes
 */

Gtk::TextAttributes::TextAttributes()
: G::Boxed(GTK_TYPE_TEXT_ATTRIBUTES, gtk_text_attributes_new(), false)
{
}

Gtk::TextAttributes::TextAttributes(GtkTextAttributes *values)
: G::Boxed(GTK_TYPE_TEXT_ATTRIBUTES, values)
{
}

Gtk::TextAttributes::TextAttributes(GtkTextAttributes *values, bool copy)
: G::Boxed(GTK_TYPE_TEXT_ATTRIBUTES, values, copy)
{
}

Gtk::TextAttributes::TextAttributes(const TextAttributes& src)
: G::Boxed(GTK_TYPE_TEXT_ATTRIBUTES, src.g_boxed(), true)
{
}

Gtk::TextAttributes::~TextAttributes()
{
}

Gtk::TextAttributes&
Gtk::TextAttributes::operator=(const TextAttributes& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

Gtk::TextAppearance&
Gtk::TextAttributes::appearance() const
{
	return reinterpret_cast<TextAppearance&>(gtk_text_attributes()->appearance);
}

Pointer<Pango::FontDescription>
Gtk::TextAttributes::font() const
{
	return G::Boxed::wrap<Pango::FontDescription>(PANGO_TYPE_FONT_DESCRIPTION, gtk_text_attributes()->font, true);
}

Pointer<Pango::TabArray>
Gtk::TextAttributes::tabs() const
{
	return G::Boxed::wrap<Pango::TabArray>(PANGO_TYPE_TAB_ARRAY, gtk_text_attributes()->tabs, true);
}

PangoLanguage*
Gtk::TextAttributes::language() const
{
	return gtk_text_attributes()->language;
}

void
Gtk::TextAttributes::set_tab_array(Pango::TabArray& tabs)
{
	gtk_text_attributes()->tabs = tabs.pango_tab_array();
}

void
Gtk::TextAttributes::set_language(PangoLanguage *language)
{
	gtk_text_attributes()->language = language;
}

void
Gtk::TextAttributes::set_pixels(int pixels_above_lines, int pixels_below_lines, int pixels_inside_wrap)
{
	gtk_text_attributes()->pixels_above_lines = pixels_above_lines;
	gtk_text_attributes()->pixels_below_lines = pixels_above_lines;
	gtk_text_attributes()->pixels_inside_wrap = pixels_inside_wrap;
}

/*  Gtk::TextTag
 */

Gtk::TextTag::TextTag(GtkTextTag *tag, bool owns_reference)
: G::Object((GObject*)tag, owns_reference)
{
}

Gtk::TextTag::TextTag()
: G::Object((GObject*)TextTagClass::create(0))
{
}

Gtk::TextTag::TextTag(const char *name)
: G::Object((GObject*)TextTagClass::create(name))
{
}

Gtk::TextTag::TextTag(const String& name)
: G::Object((GObject*)TextTagClass::create(name.c_str()))
{
}

Gtk::TextTag::~TextTag()
{
}

Gtk::TextTagTable*
Gtk::TextTag::table() const
{
	return G::Object::wrap<TextTagTable>(gtk_text_tag()->table);
}

Pointer<Gtk::TextAttributes>
Gtk::TextTag::values() const
{
	return G::Boxed::wrap<TextAttributes>(GTK_TYPE_TEXT_ATTRIBUTES, gtk_text_tag()->values, true);
}

bool
Gtk::TextTag::event(G::Object& event_object, Gdk::Event& event, const TextIter& iter)
{
	return gtk_text_tag_event(gtk_text_tag(), event_object.g_object(), event.gdk_event(), iter.gtk_text_iter());
}

/*  Gtk::TextTagClass
 */

void
Gtk::TextTagClass::init(GtkTextTagClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->event = &event_proxy;
}

GtkTextTagClass*
Gtk::TextTagClass::get_parent_class(void *instance)
{
	return static_cast<GtkTextTagClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::TextTagClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TEXT_TAG, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TextTagClass::create(const char *name)
{
	return g_object_new(get_type(), "name", name, 0);
}

gboolean
Gtk::TextTagClass::event_proxy(GtkTextTag *tag, GObject *event_object, GdkEvent *event, const GtkTextIter *iter)
{
	gboolean result = FALSE;
	TextTagSignals *signals = dynamic_cast<TextTagSignals*>(G::ObjectSignals::pointer((GObject*)tag));
	if (signals)
	{
		G::Object *object = G::Object::wrap<G::Object>(event_object);
		Gdk::Event tmp_event(event);
		TextIter tmp_iter(const_cast<GtkTextIter*>(iter));
		result = signals->on_event(*object, tmp_event, tmp_iter);
	}
	else
	{
		GtkTextTagClass *g_class = get_parent_class(tag);
		if (g_class && g_class->event)
			result = g_class->event(tag, event_object, event, iter);
	}
	return result;
}

/*  Gtk::TextTag properties
 */

const Gtk::TextTag::NamePropertyType Gtk::TextTag::name_property("name");

const Gtk::TextTag::BackgroundPropertyType Gtk::TextTag::background_property("background");

const Gtk::TextTag::BackgroundGdkPropertyType Gtk::TextTag::background_gdk_property("background_gdk");

const Gtk::TextTag::BackgroundFullHeightPropertyType Gtk::TextTag::background_full_height_property("background_full_height");

const Gtk::TextTag::BackgroundStipplePropertyType Gtk::TextTag::background_stipple_property("background_stipple");

const Gtk::TextTag::ForegroundPropertyType Gtk::TextTag::foreground_property("foreground");

const Gtk::TextTag::ForegroundGdkPropertyType Gtk::TextTag::foreground_gdk_property("foreground_gdk");

const Gtk::TextTag::ForegroundStipplePropertyType Gtk::TextTag::foreground_stipple_property("foreground_stipple");

const Gtk::TextTag::DirectionPropertyType Gtk::TextTag::direction_property("direction");

const Gtk::TextTag::EditablePropertyType Gtk::TextTag::editable_property("editable");

const Gtk::TextTag::FontPropertyType Gtk::TextTag::font_property("font");

const Gtk::TextTag::FontDescPropertyType Gtk::TextTag::font_desc_property("font_desc");

const Gtk::TextTag::FamilyPropertyType Gtk::TextTag::family_property("family");

const Gtk::TextTag::StylePropertyType Gtk::TextTag::style_property("style");

const Gtk::TextTag::VariantPropertyType Gtk::TextTag::variant_property("variant");

const Gtk::TextTag::WeightPropertyType Gtk::TextTag::weight_property("weight");

const Gtk::TextTag::StretchPropertyType Gtk::TextTag::stretch_property("stretch");

const Gtk::TextTag::SizePropertyType Gtk::TextTag::size_property("size");

const Gtk::TextTag::ScalePropertyType Gtk::TextTag::scale_property("scale");

const Gtk::TextTag::SizePointsPropertyType Gtk::TextTag::size_points_property("size_points");

const Gtk::TextTag::JustificationPropertyType Gtk::TextTag::justification_property("justification");

const Gtk::TextTag::LanguagePropertyType Gtk::TextTag::language_property("language");

const Gtk::TextTag::LeftMarginPropertyType Gtk::TextTag::left_margin_property("left_margin");

const Gtk::TextTag::RightMarginPropertyType Gtk::TextTag::right_margin_property("right_margin");

const Gtk::TextTag::IndentPropertyType Gtk::TextTag::indent_property("indentindent");

const Gtk::TextTag::RisePropertyType Gtk::TextTag::rise_property("rise");

const Gtk::TextTag::PixelsAboveLinesPropertyType Gtk::TextTag::pixels_above_lines_property("pixels_above_lines");

const Gtk::TextTag::PixelsBelowLinesPropertyType Gtk::TextTag::pixels_below_lines_property("pixels_below_lines");

const Gtk::TextTag::PixelsInsideWrapPropertyType Gtk::TextTag::pixels_inside_wrap_property("pixels_inside_wrap");

const Gtk::TextTag::StrikethroughPropertyType Gtk::TextTag::strikethrough_property("strikethrough");

const Gtk::TextTag::UnderlinePropertyType Gtk::TextTag::underline_property("underline");

const Gtk::TextTag::WrapModePropertyType Gtk::TextTag::wrap_mode_property("wrap_mode");

const Gtk::TextTag::TabsPropertyType Gtk::TextTag::tabs_property("tabs");

const Gtk::TextTag::InvisiblePropertyType Gtk::TextTag::invisible_property("invisible");

const Gtk::TextTag::BackgroundSetPropertyType Gtk::TextTag::background_set_property("background_set");

const Gtk::TextTag::BackgroundFullHeightSetPropertyType Gtk::TextTag::background_full_height_set_property("background_full_height_set");

const Gtk::TextTag::BackgroundStippleSetPropertyType Gtk::TextTag::background_stipple_set_property("background_stipple_set");

const Gtk::TextTag::ForegroundSetPropertyType Gtk::TextTag::foreground_set_property("foreground_set");

const Gtk::TextTag::ForegroundStippleSetPropertyType Gtk::TextTag::foreground_stipple_set_property("foreground_stipple_set");

const Gtk::TextTag::EditableSetPropertyType Gtk::TextTag::editable_set_property("editable_set");

const Gtk::TextTag::FamilySetPropertyType Gtk::TextTag::family_set_property("family_set");

const Gtk::TextTag::StyleSetPropertyType Gtk::TextTag::style_set_property("style_set");

const Gtk::TextTag::VariantSetPropertyType Gtk::TextTag::variant_set_property("variant_set");

const Gtk::TextTag::WeightSetPropertyType Gtk::TextTag::weight_set_property("weight_set");

const Gtk::TextTag::StretchSetPropertyType Gtk::TextTag::stretch_set_property("stretch_set");

const Gtk::TextTag::SizeSetPropertyType Gtk::TextTag::size_set_property("size_set");

const Gtk::TextTag::ScaleSetPropertyType Gtk::TextTag::scale_set_property("scale_set");

const Gtk::TextTag::JustificationSetPropertyType Gtk::TextTag::justification_set_property("justification_set");

const Gtk::TextTag::LanguageSetPropertyType Gtk::TextTag::language_set_property("language_set");

const Gtk::TextTag::LeftMarginSetPropertyType Gtk::TextTag::left_margin_set_property("left_margin_set");

const Gtk::TextTag::IndentSetPropertyType Gtk::TextTag::indent_set_property("indent_set");

const Gtk::TextTag::RiseSetPropertyType Gtk::TextTag::rise_set_property("rise_set");

const Gtk::TextTag::PixelsAboveLinesSetPropertyType Gtk::TextTag::pixels_above_lines_set_property("pixels_above_lines_set");

const Gtk::TextTag::PixelsBelowLinesSetPropertyType Gtk::TextTag::pixels_below_lines_set_property("pixels_below_lines_set");

const Gtk::TextTag::PixelsInsideWrapSetPropertyType Gtk::TextTag::pixels_inside_wrap_set_property("pixels_inside_wrap_set");

const Gtk::TextTag::StrikethroughSetPropertyType Gtk::TextTag::strikethrough_set_property("strikethrough_set");

const Gtk::TextTag::RightMarginSetPropertyType Gtk::TextTag::right_margin_set_property("right_margin_set");

const Gtk::TextTag::UnderlineSetPropertyType Gtk::TextTag::underline_set_property("underline_set");

const Gtk::TextTag::WrapModeSetPropertyType Gtk::TextTag::wrap_mode_set_property("wrap_mode_set");

const Gtk::TextTag::TabsSetPropertyType Gtk::TextTag::tabs_set_property("tabs_set");

const Gtk::TextTag::InvisibleSetPropertyType Gtk::TextTag::invisible_set_property("invisible_set");

/*  Gtk::TextTag signals
 */

const Gtk::TextTag::EventSignalType Gtk::TextTag::event_signal("event", (GCallback)&Marshal::bool_gobject_gdkevent_textiter_callback);

/*  Gtk::TextTagTable
 */

Gtk::TextTagTable::TextTagTable(GtkTextTagTable *table, bool owns_reference)
: G::Object((GObject*)table, owns_reference)
{
}

Gtk::TextTagTable::TextTagTable()
: G::Object((GObject*)TextTagTableClass::create())
{
}

Gtk::TextTagTable::~TextTagTable()
{
}
	
Gtk::TextTag*
Gtk::TextTagTable::lookup(const char *name)
{
	return G::Object::wrap<TextTag>(gtk_text_tag_table_lookup(gtk_text_tag_table(), name));
}

Gtk::TextTag*
Gtk::TextTagTable::lookup(const String& name)
{
	return lookup(name.c_str());
}

void
Gtk::TextTagTable::add(TextTag& tag)
{
	gtk_text_tag_table_add(gtk_text_tag_table(), tag.gtk_text_tag());
}

void
Gtk::TextTagTable::remove(TextTag& tag)
{
	gtk_text_tag_table_remove(gtk_text_tag_table(), tag.gtk_text_tag());
}

namespace { // foreach_slot_callback

void foreach_slot_callback(GtkTextTag *tag, gpointer data)
{
	Gtk::TextTagTable::ForeachSlot& slot = *static_cast<Gtk::TextTagTable::ForeachSlot*>(data);
	slot(*G::Object::wrap<Gtk::TextTag>(tag));
}

} // foreach_slot_callback

void
Gtk::TextTagTable::foreach(const ForeachSlot& each)
{
	ForeachSlot tmp_each(each);
	gtk_text_tag_table_foreach(gtk_text_tag_table(), &foreach_slot_callback, &tmp_each);
}

/*  Gtk::TextTagTableClass
 */

void
Gtk::TextTagTableClass::init(GtkTextTagTableClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->tag_changed = &tag_changed_proxy;
	g_class->tag_added = &tag_added_proxy;
	g_class->tag_removed = &tag_removed_proxy;
}

GtkTextTagTableClass*
Gtk::TextTagTableClass::get_parent_class(void *instance)
{
	return static_cast<GtkTextTagTableClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::TextTagTableClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TEXT_TAG_TABLE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TextTagTableClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::TextTagTableClass::tag_changed_proxy(GtkTextTagTable *table, GtkTextTag *tag, gboolean size_changed)
{
	void *ptr = g_object_get_qdata((GObject*)table, G::ObjectSignals::quark());
	if (ptr)
		static_cast<TextTagTableSignals*>(ptr)->on_tag_changed(*G::Object::wrap<Gtk::TextTag>(tag), size_changed);
	else
	{
		GtkTextTagTableClass *g_class = get_parent_class(table);
		if (g_class && g_class->tag_changed)
			g_class->tag_changed(table, tag, size_changed);
	}
}

void
Gtk::TextTagTableClass::tag_added_proxy(GtkTextTagTable *table, GtkTextTag *tag)
{
	void *ptr = g_object_get_qdata((GObject*)table, G::ObjectSignals::quark());
	if (ptr)
		static_cast<TextTagTableSignals*>(ptr)->on_tag_added(*G::Object::wrap<Gtk::TextTag>(tag));
	else
	{
		GtkTextTagTableClass *g_class = get_parent_class(table);
		if (g_class && g_class->tag_added)
			g_class->tag_added(table, tag);
	}
}

void
Gtk::TextTagTableClass::tag_removed_proxy(GtkTextTagTable *table, GtkTextTag *tag)
{
	void *ptr = g_object_get_qdata((GObject*)table, G::ObjectSignals::quark());
	if (ptr)
		static_cast<TextTagTableSignals*>(ptr)->on_tag_removed(*G::Object::wrap<Gtk::TextTag>(tag));
	else
	{
		GtkTextTagTableClass *g_class = get_parent_class(table);
		if (g_class && g_class->tag_removed)
			g_class->tag_removed(table, tag);
	}
}

/*  Gtk::TextTagTable signals
 */

const Gtk::TextTagTable::TagChangedSignalType Gtk::TextTagTable::tag_changed_signal("tag_changed", (GCallback)&Marshal::void_texttag_bool_callback);

const Gtk::TextTagTable::TagAddedSignalType Gtk::TextTagTable::tag_added_signal("tag_added", (GCallback)&Marshal::void_texttag_callback);

const Gtk::TextTagTable::TagRemovedSignalType Gtk::TextTagTable::tag_removed_signal("tag_removed", (GCallback)&Marshal::void_texttag_callback);
