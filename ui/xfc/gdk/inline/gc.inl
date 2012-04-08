/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  gc.inl - Gdk::GCValues and Gdk::GC inline functions
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

/* Gdk::GCValues
 */

inline bool
Xfc::Gdk::GCValues::foreground_set() const
{
	return (mask_ & GDK_GC_FOREGROUND) != 0;
}

inline bool
Xfc::Gdk::GCValues::background_set() const
{
	return (mask_ & GDK_GC_BACKGROUND) != 0;
}

inline Xfc::Gdk::Function
Xfc::Gdk::GCValues::function() const
{
	return (Function)values_.function;
}

inline bool
Xfc::Gdk::GCValues::function_set() const
{
	return (mask_ & GDK_GC_FUNCTION) != 0;
}

inline Xfc::Gdk::Fill
Xfc::Gdk::GCValues::fill() const
{
	return (Fill)values_.fill;
}

inline bool
Xfc::Gdk::GCValues::fill_set() const
{
	return (mask_ & GDK_GC_FILL) != 0;
}

inline bool
Xfc::Gdk::GCValues::tile_set() const
{
	return (mask_ & GDK_GC_TILE) != 0;
}

inline bool
Xfc::Gdk::GCValues::stipple_set () const
{
	return (mask_ & GDK_GC_STIPPLE) != 0;
}

inline bool
Xfc::Gdk::GCValues::clip_mask_set() const
{
	return (mask_ & GDK_GC_CLIP_MASK) != 0;
}

inline Xfc::Gdk::SubwindowMode
Xfc::Gdk::GCValues::subwindow_mode() const
{
	return (SubwindowMode)values_.subwindow_mode;
}

inline bool
Xfc::Gdk::GCValues::subwindow_mode_set() const
{
	return (mask_ & GDK_GC_SUBWINDOW) != 0;
}

inline int
Xfc::Gdk::GCValues::ts_x_origin() const
{
	return values_.ts_x_origin;
}

inline bool
Xfc::Gdk::GCValues::ts_x_origin_set() const
{
	return (mask_ & GDK_GC_TS_X_ORIGIN) != 0;
}

inline int
Xfc::Gdk::GCValues::ts_y_origin() const
{
	return values_.ts_y_origin;
}

inline bool
Xfc::Gdk::GCValues::ts_y_origin_set() const
{
	return (mask_ & GDK_GC_TS_Y_ORIGIN) != 0;
}

inline int
Xfc::Gdk::GCValues::clip_x_origin() const
{
	return values_.clip_x_origin;
}

inline bool
Xfc::Gdk::GCValues::clip_x_origin_set() const
{
	return (mask_ & GDK_GC_CLIP_X_ORIGIN) != 0;
}

inline int
Xfc::Gdk::GCValues::clip_y_origin() const
{
	return values_.clip_y_origin;
}

inline bool
Xfc::Gdk::GCValues::clip_y_origin_set () const
{
	return (mask_ & GDK_GC_CLIP_Y_ORIGIN) != 0;
}

inline bool
Xfc::Gdk::GCValues::graphics_exposures() const
{
	return values_.graphics_exposures;
}

inline bool
Xfc::Gdk::GCValues::graphics_exposures_set() const
{
	return (mask_ & GDK_GC_EXPOSURES) != 0;
}

inline int
Xfc::Gdk::GCValues::line_width() const
{
	return values_.line_width;
}

inline bool
Xfc::Gdk::GCValues::line_width_set() const
{
	return (mask_ & GDK_GC_LINE_WIDTH) != 0;
}

inline Xfc::Gdk::LineStyle
Xfc::Gdk::GCValues::line_style() const
{
	return (LineStyle)values_.line_style;
}

inline bool
Xfc::Gdk::GCValues::line_style_set() const
{
	return (mask_ & GDK_GC_LINE_STYLE) != 0;
}

inline Xfc::Gdk::CapStyle
Xfc::Gdk::GCValues::cap_style () const
{
	return (CapStyle)values_.cap_style;
}

inline bool
Xfc::Gdk::GCValues::cap_style_set() const
{
	return (mask_ & GDK_GC_CAP_STYLE) != 0;
}

inline Xfc::Gdk::JoinStyle
Xfc::Gdk::GCValues::join_style() const
{
	return (JoinStyle)values_.join_style;
}

inline bool
Xfc::Gdk::GCValues::join_style_set() const
{
	return (mask_ & GDK_GC_JOIN_STYLE) != 0;
}

inline void
Xfc::Gdk::GCValues::unset_foreground()
{
	mask_ &= ~GDK_GC_FOREGROUND;
}

inline void
Xfc::Gdk::GCValues::unset_background()
{
	mask_ &= ~GDK_GC_BACKGROUND;
}

inline void
Xfc::Gdk::GCValues::set_function(Function function)
{
	values_.function = (GdkFunction)function;
	mask_ |= GDK_GC_FUNCTION;
}

inline void
Xfc::Gdk::GCValues::unset_function()
{
	mask_ &= ~GDK_GC_FUNCTION;
}

inline void
Xfc::Gdk::GCValues::set_fill(Fill fill)
{
	values_.fill = (GdkFill)fill;
	mask_ |= GDK_GC_FILL;
}

inline void
Xfc::Gdk::GCValues::unset_fill()
{
	mask_ &= ~GDK_GC_FILL;
}

inline void
Xfc::Gdk::GCValues::set_subwindow_mode(SubwindowMode mode)
{
	values_.subwindow_mode = (GdkSubwindowMode)mode;
	mask_ |= GDK_GC_SUBWINDOW;
}

inline void
Xfc::Gdk::GCValues::unset_subwindow_mode()
{
	mask_ &= ~GDK_GC_SUBWINDOW;
}

inline void
Xfc::Gdk::GCValues::set_ts_x_origin(int origin)
{
	values_.ts_x_origin = origin;
	mask_ |= GDK_GC_TS_X_ORIGIN;
}

inline void
Xfc::Gdk::GCValues::unset_ts_x_origin()
{
	mask_ &= ~GDK_GC_TS_X_ORIGIN;
}

inline void
Xfc::Gdk::GCValues::set_ts_y_origin(int origin)
{
	values_.ts_y_origin = origin;
	mask_ |= GDK_GC_TS_Y_ORIGIN;
}

inline void
Xfc::Gdk::GCValues::unset_ts_y_origin()
{
	mask_ &= ~GDK_GC_TS_Y_ORIGIN;
}

inline void
Xfc::Gdk::GCValues::set_clip_x_origin(int origin)
{
	values_.clip_x_origin = origin;
	mask_ |= GDK_GC_CLIP_X_ORIGIN;
}

inline void
Xfc::Gdk::GCValues::unset_clip_x_origin()
{
	mask_ &= ~GDK_GC_CLIP_X_ORIGIN;
}

inline void
Xfc::Gdk::GCValues::set_clip_y_origin(int origin)
{
	values_.clip_y_origin = origin;
	mask_ |= GDK_GC_CLIP_Y_ORIGIN;
}

inline void
Xfc::Gdk::GCValues::unset_clip_y_origin()
{
	mask_ &= ~GDK_GC_CLIP_Y_ORIGIN;
}

inline void
Xfc::Gdk::GCValues::set_graphics_exposures(bool exposures)
{
	values_.graphics_exposures = exposures;
	mask_ |= GDK_GC_EXPOSURES;
}

inline void
Xfc::Gdk::GCValues::unset_graphics_exposures()
{
	mask_ &= ~GDK_GC_EXPOSURES;
}

inline void
Xfc::Gdk::GCValues::set_line_width(int width)
{
	values_.line_width = width;
	mask_ |= GDK_GC_LINE_WIDTH;
}

inline void
Xfc::Gdk::GCValues::unset_line_width()
{
	mask_ &= ~GDK_GC_LINE_WIDTH;
}

inline void
Xfc::Gdk::GCValues::set_line_style(LineStyle style)
{
	values_.line_style = (GdkLineStyle)style;
	mask_ |= GDK_GC_LINE_STYLE;
}

inline void
Xfc::Gdk::GCValues::unset_line_style()
{
	mask_ &= ~GDK_GC_LINE_STYLE;
}

inline void
Xfc::Gdk::GCValues::set_cap_style(CapStyle style)
{
	values_.cap_style = (GdkCapStyle)style;
	mask_ |= GDK_GC_CAP_STYLE;
}

inline void
Xfc::Gdk::GCValues::unset_cap_style()
{
	mask_ &= ~GDK_GC_CAP_STYLE;
}

inline void
Xfc::Gdk::GCValues::set_join_style(JoinStyle style)
{
	values_.join_style = (GdkJoinStyle)style;
	mask_ |= GDK_GC_JOIN_STYLE;
}

inline void
Xfc::Gdk::GCValues::unset_join_style()
{
	mask_ &= ~GDK_GC_JOIN_STYLE;
}

/* Gdk::GC
 */

inline GdkGC*
Xfc::Gdk::GC::gdk_gc() const
{
	return reinterpret_cast<GdkGC*>(instance_);
}

inline Xfc::Gdk::GC::operator GdkGC* () const
{
	return this ? gdk_gc() : 0;
}

inline int
Xfc::Gdk::GC::clip_x_origin() const
{
	return gdk_gc()->clip_x_origin;
}

inline int
Xfc::Gdk::GC::clip_y_origin() const
{
	return gdk_gc()->clip_y_origin;
}

inline int
Xfc::Gdk::GC::ts_x_origin() const
{
	return gdk_gc()->ts_x_origin;
}

inline int
Xfc::Gdk::GC::ts_y_origin() const
{
	return gdk_gc()->ts_y_origin;
}

inline void
Xfc::Gdk::GC::set_function(Function function)
{
	gdk_gc_set_function(gdk_gc(), (GdkFunction)function);
}

inline void
Xfc::Gdk::GC::set_fill(Fill fill)
{
	gdk_gc_set_fill(gdk_gc(), (GdkFill)fill);
}

inline void
Xfc::Gdk::GC::set_ts_origin(int x, int y)
{
	gdk_gc_set_ts_origin(gdk_gc(), x, y);
}

inline void
Xfc::Gdk::GC::set_clip_origin(int x, int y)
{
	gdk_gc_set_clip_origin(gdk_gc(), x, y);
}

inline void
Xfc::Gdk::GC::set_subwindow(SubwindowMode mode)
{
	gdk_gc_set_subwindow(gdk_gc(), (GdkSubwindowMode)mode);
}

inline void
Xfc::Gdk::GC::set_exposures(bool exposures)
{
	gdk_gc_set_exposures(gdk_gc(), exposures);
}

inline void
Xfc::Gdk::GC::set_line_attributes(int line_width, LineStyle line_style, CapStyle cap_style, JoinStyle join_style)
{
	gdk_gc_set_line_attributes(gdk_gc(), line_width, (GdkLineStyle)line_style, (GdkCapStyle)cap_style, (GdkJoinStyle)join_style);
}

inline void
Xfc::Gdk::GC::offset(int x_offset, int y_offset)
{
	gdk_gc_offset(gdk_gc(), x_offset, y_offset);
}

