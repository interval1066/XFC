/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  streamablecontent.cc - AtkStreamableContent C++ wrapper interface
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
 
#include "streamablecontent.hh"
#include "xfc/glib/iochannel.hh"

using namespace Xfc;

/*  Atk::StreamableContent
 */

Atk::StreamableContent::StreamableContent()
{
}

Atk::StreamableContent::~StreamableContent()
{
}
	
String
Atk::StreamableContent::get_mime_type(int i) const
{
	return atk_streamable_content_get_mime_type(atk_streamable_content(), i);
}

Pointer<G::IOChannel>
Atk::StreamableContent::get_stream(const char *mime_type) const
{
	GIOChannel *ioc = atk_streamable_content_get_stream(atk_streamable_content(), mime_type);
	return ioc ? new G::IOChannel(ioc) : 0;
}

Pointer<G::IOChannel>
Atk::StreamableContent::get_stream(const String& mime_type) const
{
	return get_stream(mime_type.c_str());
}

