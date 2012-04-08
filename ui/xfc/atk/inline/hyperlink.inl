/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  hyperlink.inl - Atk::Hyperlink inline functions
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

inline AtkHyperlink*
Xfc::Atk::Hyperlink::atk_hyperlink() const
{
	return reinterpret_cast<AtkHyperlink*>(instance_);
}

inline Xfc::Atk::Hyperlink::operator AtkHyperlink* () const
{
	return this ? atk_hyperlink() : 0;
}

inline int
Xfc::Atk::Hyperlink::get_end_index() const
{
	return atk_hyperlink_get_end_index(atk_hyperlink());
}

inline int
Xfc::Atk::Hyperlink::get_start_index() const
{
	return atk_hyperlink_get_start_index(atk_hyperlink());
}

inline bool
Xfc::Atk::Hyperlink::is_valid() const
{
	return atk_hyperlink_is_valid(atk_hyperlink());
}

inline bool
Xfc::Atk::Hyperlink::is_inline() const
{
	return atk_hyperlink_is_inline(atk_hyperlink());
}

inline int
Xfc::Atk::Hyperlink::get_n_anchors() const
{
	return atk_hyperlink_get_n_anchors(atk_hyperlink());
}

inline bool 
Xfc::Atk::Hyperlink::is_selected_link() const
{
	return atk_hyperlink_is_selected_link(atk_hyperlink());
}

inline const Xfc::Atk::Hyperlink::LinkActivatedSignalProxy
Xfc::Atk::Hyperlink::signal_link_activated()
{
	return LinkActivatedSignalProxy(this, &link_activated_signal);
}

