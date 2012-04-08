/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  cellrenderer.inl - Gtk::CellRenderer inline functions
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

inline GtkCellRenderer*
Xfc::Gtk::CellRenderer::gtk_cell_renderer() const
{
	return reinterpret_cast<GtkCellRenderer*>(instance_);
}

inline Xfc::Gtk::CellRenderer::operator GtkCellRenderer* () const
{
	return this ? gtk_cell_renderer() : 0;
}

inline void
Xfc::Gtk::CellRenderer::get_fixed_size(int *width, int *height) const
{
	gtk_cell_renderer_get_fixed_size(gtk_cell_renderer(), width, height);
}

inline void 
Xfc::Gtk::CellRenderer::editing_canceled()
{
	gtk_cell_renderer_editing_canceled(gtk_cell_renderer());
}

inline void
Xfc::Gtk::CellRenderer::set_fixed_size(int width, int height)
{
	gtk_cell_renderer_set_fixed_size(gtk_cell_renderer(), width, height);
}

inline void 
Xfc::Gtk::CellRenderer::stop_editing(bool canceled)
{
	gtk_cell_renderer_stop_editing(gtk_cell_renderer(), canceled);
}

inline const Xfc::Gtk::CellRenderer::ModePropertyProxy
Xfc::Gtk::CellRenderer::property_mode()
{
	return ModePropertyProxy(this, &mode_property);
}

inline const Xfc::Gtk::CellRenderer::VisiblePropertyProxy
Xfc::Gtk::CellRenderer::property_visible()
{
	return VisiblePropertyProxy(this, &visible_property);
}

inline const Xfc::Gtk::CellRenderer::SensitivePropertyProxy
Xfc::Gtk::CellRenderer::property_sensitive()
{
	return SensitivePropertyProxy(this, &sensitive_property);
}

inline const Xfc::Gtk::CellRenderer::XAlignPropertyProxy
Xfc::Gtk::CellRenderer::property_xalign()
{
	return XAlignPropertyProxy(this, &xalign_property);
}

inline const Xfc::Gtk::CellRenderer::YAlignPropertyProxy
Xfc::Gtk::CellRenderer::property_yalign()
{
	return YAlignPropertyProxy(this, &yalign_property);
}

inline const Xfc::Gtk::CellRenderer::XPadPropertyProxy
Xfc::Gtk::CellRenderer::property_xpad()
{
	return XPadPropertyProxy(this, &xpad_property);
}

inline const Xfc::Gtk::CellRenderer::YPadPropertyProxy
Xfc::Gtk::CellRenderer::property_ypad()
{
	return YPadPropertyProxy(this, &ypad_property);
}

inline const Xfc::Gtk::CellRenderer::WidthPropertyProxy
Xfc::Gtk::CellRenderer::property_width()
{
	return WidthPropertyProxy(this, &width_property);
}

inline const Xfc::Gtk::CellRenderer::HeightPropertyProxy
Xfc::Gtk::CellRenderer::property_height()
{
	return HeightPropertyProxy(this, &height_property);
}

inline const Xfc::Gtk::CellRenderer::IsExpanderPropertyProxy
Xfc::Gtk::CellRenderer::property_is_expander()
{
	return IsExpanderPropertyProxy(this, &is_expander_property);
}

inline const Xfc::Gtk::CellRenderer::IsExpandedPropertyProxy
Xfc::Gtk::CellRenderer::property_is_expanded()
{
	return IsExpandedPropertyProxy(this, &is_expanded_property);
}

inline const Xfc::Gtk::CellRenderer::CellBackgroundPropertyProxy
Xfc::Gtk::CellRenderer::property_cell_background()
{
	return CellBackgroundPropertyProxy(this, &cell_background_property);
}

inline const Xfc::Gtk::CellRenderer::CellBackgroundGdkPropertyProxy
Xfc::Gtk::CellRenderer::property_cell_background_gdk()
{
	return CellBackgroundGdkPropertyProxy(this, &cell_background_gdk_property);
}

inline const Xfc::Gtk::CellRenderer::CellBackgroundSetPropertyProxy
Xfc::Gtk::CellRenderer::property_cell_background_set()
{
	return CellBackgroundSetPropertyProxy(this, &cell_background_set_property);
}

inline const Xfc::Gtk::CellRenderer::EditingCanceledSignalProxy 
Xfc::Gtk::CellRenderer::signal_editing_canceled()
{
	return EditingCanceledSignalProxy(this, &editing_canceled_signal);
}

inline const Xfc::Gtk::CellRenderer::EditingStartedSignalProxy 
Xfc::Gtk::CellRenderer::signal_editing_started()
{
	return EditingStartedSignalProxy(this, &editing_started_signal);
}

