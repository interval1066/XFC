/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  layout.inl - Pango::Layout inline functions
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

/*  Pango::LayoutRun
 */

inline PangoLayoutRun*
Xfc::Pango::LayoutRun::pango_layout_run() const
{
	return const_cast<PangoLayoutRun*>(&run_);
}

/*  Pango::LayoutLine
 */

inline PangoLayoutLine*
Xfc::Pango::LayoutLine::pango_layout_line() const
{
	return layout_line_;
}

inline Xfc::Pango::LayoutLine::operator PangoLayoutLine* () const
{
	return this ? layout_line_ : 0;
}

inline int
Xfc::Pango::LayoutLine::start_index() const
{
	return layout_line_->start_index;
}

inline int
Xfc::Pango::LayoutLine::length() const
{
	return layout_line_->length;
}

inline bool
Xfc::Pango::LayoutLine::is_paragraph_start() const
{
	return layout_line_->is_paragraph_start != 0;
}

inline bool
Xfc::Pango::LayoutLine::x_to_index(int x_pos, int *index, int *trailing)
{
	return pango_layout_line_x_to_index(layout_line_, x_pos, index, trailing);
}

/*  Pango::LayoutIter
 */

inline PangoLayoutIter*
Xfc::Pango::LayoutIter::pango_layout_iter() const
{
	return reinterpret_cast<PangoLayoutIter*>(boxed_);
}

inline Xfc::Pango::LayoutIter::operator PangoLayoutIter* () const
{
	return this ? pango_layout_iter() : 0;
}

inline int
Xfc::Pango::LayoutIter::get_index() const
{
	return pango_layout_iter_get_index(pango_layout_iter());
}

inline bool
Xfc::Pango::LayoutIter::at_last_line() const
{
	return pango_layout_iter_at_last_line(pango_layout_iter());
}

inline void
Xfc::Pango::LayoutIter::get_line_yrange(int *y0, int *y1) const
{
	pango_layout_iter_get_line_yrange(pango_layout_iter(), y0, y1);
}

inline int
Xfc::Pango::LayoutIter::get_baseline() const
{
	return pango_layout_iter_get_baseline(pango_layout_iter());
}

inline bool
Xfc::Pango::LayoutIter::next_char()
{
	return pango_layout_iter_next_char(pango_layout_iter());
}

inline bool
Xfc::Pango::LayoutIter::next_cluster()
{
	return pango_layout_iter_next_cluster(pango_layout_iter());
}

inline bool
Xfc::Pango::LayoutIter::next_run()
{
	return pango_layout_iter_next_run(pango_layout_iter());
}

inline bool
Xfc::Pango::LayoutIter::next_line()
{
	return pango_layout_iter_next_line(pango_layout_iter());
}

/*  Pango::Layout
 */

inline PangoLayout*
Xfc::Pango::Layout::pango_layout() const
{
	return reinterpret_cast<PangoLayout*>(instance_);
}

inline Xfc::Pango::Layout::operator PangoLayout* () const
{
	return this ? pango_layout() : 0;
}

inline int
Xfc::Pango::Layout::get_width() const
{
	return pango_layout_get_width(pango_layout());
}

inline Xfc::Pango::WrapMode
Xfc::Pango::Layout::get_wrap() const
{
	return (WrapMode)pango_layout_get_wrap(pango_layout());
}

inline int
Xfc::Pango::Layout::get_indent() const
{
	return pango_layout_get_indent(pango_layout());
}

inline int
Xfc::Pango::Layout::get_spacing() const
{
	return pango_layout_get_spacing(pango_layout());
}

inline bool
Xfc::Pango::Layout::get_justify() const
{
	return pango_layout_get_justify(pango_layout());
}

inline bool 
Xfc::Pango::Layout::get_auto_dir() const
{
	return pango_layout_get_auto_dir(pango_layout());
}

inline Xfc::Pango::Alignment
Xfc::Pango::Layout::get_alignment() const
{
	return (Alignment)pango_layout_get_alignment(pango_layout());
}

inline bool
Xfc::Pango::Layout::get_single_paragraph_mode() const
{
	return pango_layout_get_single_paragraph_mode(pango_layout());
}

inline Xfc::Pango::EllipsizeMode
Xfc::Pango::Layout::get_ellipsize() const
{
	return (EllipsizeMode)pango_layout_get_ellipsize(pango_layout());
}
	
inline void
Xfc::Pango::Layout::get_size(int *width, int *height) const
{
	pango_layout_get_size(pango_layout(), width, height);
}

inline void
Xfc::Pango::Layout::get_pixel_size(int *width, int *height) const
{
	pango_layout_get_pixel_size(pango_layout(), width, height);
}

inline int
Xfc::Pango::Layout::get_line_count() const
{
	return pango_layout_get_line_count(pango_layout());
}

inline void
Xfc::Pango::Layout::set_text(const char *text)
{
	pango_layout_set_text(pango_layout(), text, -1);
}

inline void
Xfc::Pango::Layout::set_markup(const char *markup)
{
	pango_layout_set_markup(pango_layout(), markup, -1);
}

inline void
Xfc::Pango::Layout::set_markup(const char *markup, gunichar accel_marker, gunichar *accel_char)
{
	pango_layout_set_markup_with_accel(pango_layout(), markup, -1, accel_marker, accel_char);
}

inline void
Xfc::Pango::Layout::set_width(int width)
{
	pango_layout_set_width(pango_layout(), width);
}

inline void
Xfc::Pango::Layout::set_wrap(WrapMode wrap)
{
	pango_layout_set_wrap(pango_layout(), (PangoWrapMode)wrap);
}

inline void
Xfc::Pango::Layout::set_indent(int indent)
{
	pango_layout_set_indent(pango_layout(), indent);
}

inline void
Xfc::Pango::Layout::set_spacing(int spacing)
{
	pango_layout_set_spacing(pango_layout(), spacing);
}

inline void
Xfc::Pango::Layout::set_justify(bool justify)
{
	pango_layout_set_justify(pango_layout(), justify);
}

inline void 
Xfc::Pango::Layout::set_auto_dir(bool auto_dir)
{
	pango_layout_set_auto_dir(pango_layout(), auto_dir);
}

inline void
Xfc::Pango::Layout::set_alignment(Alignment alignment)
{
	pango_layout_set_alignment(pango_layout(), (PangoAlignment)alignment);
}

inline void
Xfc::Pango::Layout::set_single_paragraph_mode(bool setting)
{
	pango_layout_set_single_paragraph_mode(pango_layout(), setting);
}

inline void 
Xfc::Pango::Layout::set_ellipsize(EllipsizeMode ellipsize)
{
	pango_layout_set_ellipsize(pango_layout(), (PangoEllipsizeMode)ellipsize);
}

inline void
Xfc::Pango::Layout::context_changed()
{
	pango_layout_context_changed(pango_layout());
}

inline bool
Xfc::Pango::Layout::xy_to_index(int x, int y, int *index, int *trailing)
{
	return pango_layout_xy_to_index(pango_layout(), x, y, index, trailing);
}

