/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  completion.cc - GCompletion C++ wrapper implementation
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

#include "completion.hh"
#include <glib/gmessages.h>

using namespace Xfc;

G::Completion::Completion()
: completion_(g_completion_new(0))
{
}
	
G::Completion::Completion(GCompletionFunc func)
: completion_(g_completion_new(func))
{
}
	
G::Completion::~Completion()
{
	if (completion_)
	{
		g_completion_free(completion_);
		completion_ = 0;
	}	
}

namespace { // string_vector_to_glist

GList* string_vector_to_glist(const std::vector<String>& items)	
{
	g_return_val_if_fail(!items.empty(), 0);
	GList *tmp_items = 0;
	int count = items.size();
	
	int i = 0;
	while (i < count)
	{
		tmp_items = g_list_append(tmp_items, const_cast<char*>(items[i].c_str()));
		++i;
	}
	return tmp_items;
}

} // namespace	
	
void 
G::Completion::add_items(const std::vector<String>& items)
{
	GList *tmp_items = string_vector_to_glist(items);
	g_completion_add_items(completion_, tmp_items);
  	g_list_free(tmp_items);
}			
	
void 
G::Completion::remove_items(const std::vector<String>& items)
{
	GList *tmp_items = string_vector_to_glist(items);
	g_completion_remove_items(completion_, tmp_items);
  	g_list_free(tmp_items);
}			
	
void 
G::Completion::clear_items()
{
	g_completion_clear_items(completion_);
}
	 
String 
G::Completion::complete(const char *prefix, std::vector<String>& items)
{
	g_return_val_if_fail(items.empty(), 0);
	char *new_prefix = 0;
	GList *first = g_completion_complete_utf8(completion_, prefix, &new_prefix);
	GList *next = first;

	while (next)
	{
		const char *item = (const char*)next->data;		
		items.push_back(item);	
		next = g_list_next(next);
	}
	
	return new_prefix;
}

String 
G::Completion::complete(const String& prefix, std::vector<String>& items)
{
	return complete(prefix.c_str(), items);
}

void 
G::Completion::set_compare(GCompletionStrncmpFunc strncmp_func)
{
	g_completion_set_compare(completion_, strncmp_func);
}

