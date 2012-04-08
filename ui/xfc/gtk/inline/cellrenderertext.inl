/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  cellrenderertext.inl - Gtk::CellRendererText inline functions
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

inline GtkCellRendererText*
Xfc::Gtk::CellRendererText::gtk_cell_renderer_text() const
{
	return reinterpret_cast<GtkCellRendererText*>(instance_);
}

inline Xfc::Gtk::CellRendererText::operator GtkCellRendererText* () const
{
	return this ? gtk_cell_renderer_text() : 0;
}

inline void
Xfc::Gtk::CellRendererText::set_fixed_height_from_font(int number_of_rows)
{
	gtk_cell_renderer_text_set_fixed_height_from_font(gtk_cell_renderer_text(), number_of_rows);
}

inline const Xfc::Gtk::CellRendererText::TextPropertyProxy
Xfc::Gtk::CellRendererText::property_text()
{
	return TextPropertyProxy(this, &text_property);
}

inline const Xfc::Gtk::CellRendererText::MarkupPropertyProxy
Xfc::Gtk::CellRendererText::property_markup()
{
	return MarkupPropertyProxy(this, &markup_property);
}

inline const Xfc::Gtk::CellRendererText::AttributePropertyProxy
Xfc::Gtk::CellRendererText::property_attribute()
{
	return AttributePropertyProxy(this, &attribute_property);
}

inline const Xfc::Gtk::CellRendererText::SingleParagraphModePropertyProxy 
Xfc::Gtk::CellRendererText::property_single_paragraph_mode()
{
	return SingleParagraphModePropertyProxy(this, &single_paragraph_mode_property);
}

inline const Xfc::Gtk::CellRendererText::WidthCharsPropertyProxy
Xfc::Gtk::CellRendererText::property_width_chars()
{
	return WidthCharsPropertyProxy(this, &width_chars_property);
}

inline const Xfc::Gtk::CellRendererText::BackgroundPropertyProxy
Xfc::Gtk::CellRendererText::property_background()
{
	return BackgroundPropertyProxy(this, &background_property);
}

inline const Xfc::Gtk::CellRendererText::BackgroundGdkPropertyProxy
Xfc::Gtk::CellRendererText::property_background_gdk()
{
	return BackgroundGdkPropertyProxy(this, &background_gdk_property);
}

inline const Xfc::Gtk::CellRendererText::ForegroundPropertyProxy
Xfc::Gtk::CellRendererText::property_foreground()
{
	return ForegroundPropertyProxy(this, &foreground_property);
}

inline const Xfc::Gtk::CellRendererText::ForegroundGdkPropertyProxy
Xfc::Gtk::CellRendererText::property_foreground_gdk()
{
	return ForegroundGdkPropertyProxy(this, &foreground_gdk_property);
}

inline const Xfc::Gtk::CellRendererText::EditablePropertyProxy
Xfc::Gtk::CellRendererText::property_editable()
{
	return EditablePropertyProxy(this, &editable_property);
}

inline const Xfc::Gtk::CellRendererText::FontPropertyProxy
Xfc::Gtk::CellRendererText::property_font()
{
	return FontPropertyProxy(this, &font_property);
}

inline const Xfc::Gtk::CellRendererText::FontDescPropertyProxy
Xfc::Gtk::CellRendererText::property_font_desc()
{
	return FontDescPropertyProxy(this, &font_desc_property);
}

inline const Xfc::Gtk::CellRendererText::FamilyPropertyProxy
Xfc::Gtk::CellRendererText::property_family()
{
	return FamilyPropertyProxy(this, &family_property);
}

inline const Xfc::Gtk::CellRendererText::StylePropertyProxy
Xfc::Gtk::CellRendererText::property_style()
{
	return StylePropertyProxy(this, &style_property);
}

inline const Xfc::Gtk::CellRendererText::VariantPropertyProxy
Xfc::Gtk::CellRendererText::property_variant()
{
	return VariantPropertyProxy(this, &variant_property);
}

inline const Xfc::Gtk::CellRendererText::WeightPropertyProxy
Xfc::Gtk::CellRendererText::property_weight()
{
	return WeightPropertyProxy(this, &weight_property);
}

inline const Xfc::Gtk::CellRendererText::StretchPropertyProxy
Xfc::Gtk::CellRendererText::property_stretch()
{
	return StretchPropertyProxy(this, &stretch_property);
}

inline const Xfc::Gtk::CellRendererText::SizePropertyProxy
Xfc::Gtk::CellRendererText::property_size()
{
	return SizePropertyProxy(this, &size_property);
}

inline const Xfc::Gtk::CellRendererText::SizePointsPropertyProxy
Xfc::Gtk::CellRendererText::property_size_points()
{
	return SizePointsPropertyProxy(this, &size_points_property);
}

inline const Xfc::Gtk::CellRendererText::ScalePropertyProxy
Xfc::Gtk::CellRendererText::property_scale()
{
	return ScalePropertyProxy(this, &scale_property);
}

inline const Xfc::Gtk::CellRendererText::RisePropertyProxy
Xfc::Gtk::CellRendererText::property_rise()
{
	return RisePropertyProxy(this, &rise_property);
}

inline const Xfc::Gtk::CellRendererText::LanguagePropertyProxy 
Xfc::Gtk::CellRendererText::property_language()
{
	return LanguagePropertyProxy(this, &language_property);
}	

inline const Xfc::Gtk::CellRendererText::StrikethroughPropertyProxy
Xfc::Gtk::CellRendererText::property_strikethrough()
{
	return StrikethroughPropertyProxy(this, &strikethrough_property);
}

inline const Xfc::Gtk::CellRendererText::UnderlinePropertyProxy
Xfc::Gtk::CellRendererText::property_underline()
{
	return UnderlinePropertyProxy(this, &underline_property);
}

inline const Xfc::Gtk::CellRendererText::EllipsizePropertyProxy 
Xfc::Gtk::CellRendererText::property_ellipsize()
{
	return EllipsizePropertyProxy(this, &ellipsize_property);
}

inline const Xfc::Gtk::CellRendererText::BackgroundSetPropertyProxy
Xfc::Gtk::CellRendererText::property_background_set()
{
	return BackgroundSetPropertyProxy(this, &background_set_property);
}

inline const Xfc::Gtk::CellRendererText::ForegroundSetPropertyProxy
Xfc::Gtk::CellRendererText::property_foreground_set()
{
	return ForegroundSetPropertyProxy(this, &foreground_set_property);
}

inline const Xfc::Gtk::CellRendererText::EditableSetPropertyProxy
Xfc::Gtk::CellRendererText::property_editable_set()
{
	return EditableSetPropertyProxy(this, &editable_set_property);
}

inline const Xfc::Gtk::CellRendererText::FamilySetPropertyProxy
Xfc::Gtk::CellRendererText::property_family_set()
{
	return FamilySetPropertyProxy(this, &family_set_property);
}

inline const Xfc::Gtk::CellRendererText::StyleSetPropertyProxy
Xfc::Gtk::CellRendererText::property_style_set()
{
	return StyleSetPropertyProxy(this, &style_set_property);
}

inline const Xfc::Gtk::CellRendererText::VariantSetPropertyProxy
Xfc::Gtk::CellRendererText::property_variant_set()
{
	return VariantSetPropertyProxy(this, &variant_set_property);
}

inline const Xfc::Gtk::CellRendererText::WeightSetPropertyProxy
Xfc::Gtk::CellRendererText::property_weight_set()
{
	return WeightSetPropertyProxy(this, &weight_set_property);
}

inline const Xfc::Gtk::CellRendererText::StretchSetPropertyProxy
Xfc::Gtk::CellRendererText::property_stretch_set()
{
	return StretchSetPropertyProxy(this, &stretch_set_property);
}

inline const Xfc::Gtk::CellRendererText::SizeSetPropertyProxy
Xfc::Gtk::CellRendererText::property_size_set()
{
	return SizeSetPropertyProxy(this, &size_set_property);
}

inline const Xfc::Gtk::CellRendererText::ScaleSetPropertyProxy
Xfc::Gtk::CellRendererText::property_scale_set()
{
	return ScaleSetPropertyProxy(this, &scale_set_property);
}

inline const Xfc::Gtk::CellRendererText::RiseSetPropertyProxy
Xfc::Gtk::CellRendererText::property_rise_set()
{
	return RiseSetPropertyProxy(this, &rise_set_property);
}

inline const Xfc::Gtk::CellRendererText::StrikethroughSetPropertyProxy
Xfc::Gtk::CellRendererText::property_strikethrough_set()
{
	return StrikethroughSetPropertyProxy(this, &strikethrough_set_property);
}

inline const Xfc::Gtk::CellRendererText::UnderlineSetPropertyProxy
Xfc::Gtk::CellRendererText::property_underline_set()
{
	return UnderlineSetPropertyProxy(this, &underline_set_property);
}

inline const Xfc::Gtk::CellRendererText::LanguageSetPropertyProxy 
Xfc::Gtk::CellRendererText::property_language_set()
{
	return LanguageSetPropertyProxy(this, &language_set_property);
}

inline const Xfc::Gtk::CellRendererText::EllipsizeSetPropertyProxy 
Xfc::Gtk::CellRendererText::property_ellipsize_set()
{
	return EllipsizeSetPropertyProxy(this, &ellipsize_set_property);
}

inline const Xfc::Gtk::CellRendererText::EditedSignalProxy
Xfc::Gtk::CellRendererText::signal_edited()
{
	return EditedSignalProxy(this, &edited_signal);
}

