/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  iochannel.cc - A GIOChannel C++ wrapper implementation
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

#include "iochannel.hh"
#include "error.hh"
#include "main.hh"

using namespace Xfc;

/*  G::IOChannel
 */

G::IOChannel::IOChannel(GIOChannel *channel, bool owns_reference)
: channel_(channel)

{
	set_owns_reference(owns_reference);
}

G::IOChannel::~IOChannel()
{
	if (channel_)
	{
		g_io_channel_unref(channel_);
		channel_ = 0;
	}
}

Pointer<G::IOChannel>
G::IOChannel::create(const String& filename, const char *mode, G::Error *error)
{
	GIOChannel *io = g_io_channel_new_file(filename.c_str(), mode, *error);
	return io ? new IOChannel(io) : 0;
}

Pointer<G::IOChannel>
G::IOChannel::create(int fd, bool close_on_unref)
{
	IOChannel *channel = 0;
	GIOChannel *io = g_io_channel_unix_new(fd);
	if (io)
	{
		if (close_on_unref)
			g_io_channel_set_close_on_unref(io, TRUE);
		channel = new IOChannel(io);
	}
	return channel;
}

String
G::IOChannel::get_line_term() const
{
	int length;
	const char *line_term = g_io_channel_get_line_term(channel_, &length);
	String s(line_term, length);
	return s;
}

String
Xfc::G::IOChannel::get_encoding() const
{
	return g_io_channel_get_encoding(channel_);
}

void
G::IOChannel::ref()
{
	g_io_channel_ref(channel_);
}

void
G::IOChannel::unref()
{
	bool last_unref = channel_->ref_count == 1;
	g_io_channel_unref(channel_);
	if (last_unref && is_dynamic())
	{
		channel_ = 0;
		delete this;
	}
}

G::IOStatus
G::IOChannel::close(bool flush, G::Error *error)
{
	return (IOStatus)g_io_channel_shutdown(channel_, flush, *error);
}

G::IOStatus
G::IOChannel::set_flags(IOFlagsField flags, G::Error *error)
{
	return (IOStatus)g_io_channel_set_flags(channel_, (GIOFlags)flags, *error);
}

void
G::IOChannel::set_line_term(const String& line_term)
{
	g_io_channel_set_line_term(channel_, line_term.c_str(), line_term.size());
}

G::IOStatus
G::IOChannel::set_encoding(const char *encoding, G::Error *error)
{
	return (IOStatus)g_io_channel_set_encoding(channel_, encoding, *error);
}

G::IOStatus
G::IOChannel::flush(G::Error *error)
{
	return (IOStatus)g_io_channel_flush(channel_, *error);
}

G::IOStatus
G::IOChannel::read_line(String& str, size_t *bytes_read, G::Error *error)
{
	char *tmp_str = 0;
	gsize bytes;
	GIOStatus status = g_io_channel_read_line(channel_, &tmp_str, &bytes, 0, *error);

	if (tmp_str)
	{
		str.assign(tmp_str, tmp_str + bytes);
		g_free(tmp_str);
	}

	if (bytes_read)
		*bytes_read = bytes;

	return (IOStatus)status;
}

G::IOStatus
G::IOChannel::read_to_end(String& str, size_t *bytes_read, G::Error *error)
{
	char *tmp_str = 0;
	gsize bytes;
	GIOStatus status = g_io_channel_read_to_end(channel_, &tmp_str, &bytes, *error);

	if (tmp_str)
	{
		str.assign(tmp_str, tmp_str + bytes);
		g_free(tmp_str);
	}

	if (bytes_read)
		*bytes_read = bytes;

	return (IOStatus)status;
}

G::IOStatus
G::IOChannel::read(char *buffer, size_t count, size_t *bytes_read, G::Error *error)
{
	return (IOStatus)g_io_channel_read_chars(channel_, buffer, (gsize)count, (gsize*)bytes_read, *error);
}

G::IOStatus
G::IOChannel::read(String& str, size_t *bytes_read, G::Error *error)
{
	int count = str.size();
	char *tmp_str = new char[count];
	gsize bytes;
	GIOStatus status = g_io_channel_read_chars(channel_, tmp_str, count, &bytes, *error);

	if (tmp_str)
	{
		str.assign(tmp_str, tmp_str + bytes);
		g_free(tmp_str);
	}

	if (bytes_read)
		*bytes_read = bytes;

	return (IOStatus)status;
}

G::IOStatus
G::IOChannel::read(G::Unichar& unichar, G::Error *error)
{
	gunichar tmp_unichar;
	GIOStatus status = g_io_channel_read_unichar(channel_, &tmp_unichar, *error);
	unichar = tmp_unichar;
	return (IOStatus)status;
}

G::IOStatus
G::IOChannel::write(const char *buffer, size_t count, size_t *bytes_written, G::Error *error)
{
	return (IOStatus)g_io_channel_write_chars(channel_, buffer, (gssize)count, (gsize*)bytes_written, *error);
}

G::IOStatus
G::IOChannel::write(const String& str, size_t *bytes_written, G::Error *error)
{
	return (IOStatus)g_io_channel_write_chars(channel_, str.data(), (gssize)str.size(), (gsize*)bytes_written, *error);
}

G::IOStatus
G::IOChannel::write(G::Unichar unichar, G::Error *error)
{
	return (IOStatus)g_io_channel_write_unichar(channel_, unichar, *error);
}

G::IOStatus
G::IOChannel::seek(gint64 offset, SeekType type, G::Error *error)
{
	return (IOStatus)g_io_channel_seek_position(channel_, offset, (GSeekType)type, *error);
}

