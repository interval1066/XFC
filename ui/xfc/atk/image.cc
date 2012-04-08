/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  image.cc - AtkImage C++ wrapper implementation
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
 
#include "image.hh"

using namespace Xfc;

/*  Atk::Image
 */

Atk::Image::Image()
{
}

Atk::Image::~Image()
{
}
	
String
Atk::Image::get_image_description() const
{
	return atk_image_get_image_description(atk_image());
}

bool
Atk::Image::set_image_description(const String& description)
{
	return atk_image_set_image_description(atk_image(), description.c_str());
}

