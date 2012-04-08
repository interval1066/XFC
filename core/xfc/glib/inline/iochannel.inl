/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  iochannel.inl - G::IOChannel inline functions
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

inline GIOChannel*
Xfc::G::IOChannel::g_io_channel() const
{
	return channel_;
}

inline Xfc::G::IOChannel::operator GIOChannel* () const
{
	return this ? channel_ : 0;
}

inline Xfc::G::IOChannelError
Xfc::G::IOChannel::error_from_errno(int errno_number)
{
	return (IOChannelError)g_io_channel_error_from_errno(errno_number);
}

inline size_t
Xfc::G::IOChannel::get_buffer_size() const
{
	return g_io_channel_get_buffer_size(channel_);
}

inline Xfc::G::IOConditionField
Xfc::G::IOChannel::get_buffer_condition() const
{
	return (IOConditionField)g_io_channel_get_buffer_condition(channel_);
}

inline Xfc::G::IOFlagsField
Xfc::G::IOChannel::get_flags() const
{
	return (IOFlagsField)g_io_channel_get_flags(channel_);
}

inline bool
Xfc::G::IOChannel::get_buffered() const
{
	return g_io_channel_get_buffered(channel_);
}

inline bool
Xfc::G::IOChannel::get_close_on_unref() const
{
	return g_io_channel_get_close_on_unref(channel_);
}

inline int
Xfc::G::IOChannel::get_fd() const
{
	return g_io_channel_unix_get_fd(channel_);
}

inline void
Xfc::G::IOChannel::set_buffer_size(size_t size)
{
	g_io_channel_set_buffer_size(channel_, size);
}

inline void
Xfc::G::IOChannel::set_buffered(bool buffered)
{
	g_io_channel_set_buffered(channel_, buffered);
}

inline void
Xfc::G::IOChannel::set_close_on_unref(bool do_close)
{
	g_io_channel_set_close_on_unref(channel_, do_close);
}

