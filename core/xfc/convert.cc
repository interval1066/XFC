/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  convert.cc - Miscellaneous XFC conversion functions
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

#include "convert.hh"

std::vector<Xfc::String>
Xfc::array_to_vector_of_string(const char *const *strs)
{
	std::vector<Xfc::String> strings;
	
	int i = 0;
	while (strs[i] && *strs[i])
	{
		Xfc::String s(strs[i]);
		strings.push_back(s);
		++i;
	}
	return strings;
}

char** 
Xfc::vector_of_string_to_array(const std::vector<Xfc::String>& strings)
{
	int count = strings.size();
	char **tmp_str = new char*[count + 1];
	
	int i = 0;
	while (i < count)
	{
		tmp_str[i] = const_cast<char*>(strings[i].c_str());
		++i;
	}
	
	tmp_str[count] = 0;
	return tmp_str;
}

