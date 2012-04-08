/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  option.cc - C++ interface for GOptionContext and GOptionGroup.
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

#include "option.hh"
#include "error.hh"
#include <glib/gmem.h>
#include <glib/gstrfuncs.h>

namespace Xfc {

namespace G {

/*  G::OptionEntry
 */

class OptionEntry : public GOptionEntry
{
public:
	OptionEntry(const char *long_name_, char short_name_, int flags_, GOptionArg arg_, 
		    void *arg_data_, const char *description_, const char *arg_description_);
	
	OptionEntry(const OptionEntry& src);
	
	~OptionEntry();
	
	OptionEntry& operator=(const OptionEntry& src);
};	
	
OptionEntry::OptionEntry(const char *long_name_, char short_name_, int flags_, GOptionArg arg_, 
	                 void *arg_data_, const char *description_, const char *arg_description_)
{
	long_name = g_strdup(long_name_);	
	short_name = short_name_;
	flags = flags_;
	arg = arg_;
	arg_data = arg_data_;
	description = g_strdup(description_);
	arg_description = g_strdup(arg_description_); 
}

OptionEntry::OptionEntry(const OptionEntry& src)
{
	*this = src;
}

OptionEntry::~OptionEntry()
{
	g_free(const_cast<char*>(long_name));	
	g_free(const_cast<char*>(description));	
	g_free(const_cast<char*>(arg_description));	
}

OptionEntry&
OptionEntry::operator=(const OptionEntry& src)
{
	long_name = g_strdup(src.long_name);	
	short_name = src.short_name;
	flags = src.flags;
	arg = src.arg;
	arg_data = src.arg_data;
	description = g_strdup(src.description);
	arg_description = g_strdup(src.arg_description); 
	return *this;
}

/*  G::OptionEntryArgs
 */

struct OptionEntryArg
{
	GOptionArg type;
	void *cpp_arg;
	union {		
		char *str;
		char **array;
	};
};
	
class OptionEntryArgs : public std::vector<OptionEntryArg*>
{
public:
	OptionEntryArgs();
	~OptionEntryArgs();
	
	void convert_args();
};

OptionEntryArgs::OptionEntryArgs()
{
}
	
OptionEntryArgs::~OptionEntryArgs()
{
	iterator it = begin();
	while (it != end())
	{
		delete (*it);
		++it;
	}
	clear();
}
	
void 
OptionEntryArgs::convert_args()
{
	iterator it = begin();
	while (it != end())
	{
		switch ((*it)->type)
		{
		case G_OPTION_ARG_STRING:
			reinterpret_cast<String*>((*it)->cpp_arg)->assign((*it)->str);
			g_free((*it)->str);
			break;
			
		case G_OPTION_ARG_FILENAME:   
			reinterpret_cast<std::string*>((*it)->cpp_arg)->assign((*it)->str);
			g_free((*it)->str);
			break;
			
		case G_OPTION_ARG_STRING_ARRAY: 
		{
			std::vector<String>& strings = *reinterpret_cast<std::vector<String>*>((*it)->cpp_arg);
			int i = 0;
			while ((*it)->array[i])
			{
				String s((*it)->array[i]);
				strings.push_back(s);
				++i;
			}
			g_strfreev((*it)->array);
			break;
		}						
		
		case G_OPTION_ARG_FILENAME_ARRAY: 
		{
			std::vector<std::string>& strings = *reinterpret_cast<std::vector<std::string>*>((*it)->cpp_arg);
			int i = 0;
			while ((*it)->array[i])
			{
				std::string s((*it)->array[i]);
				strings.push_back(s);
				++i;
			}
			g_strfreev((*it)->array);
			break;
		}
		
		default:
			break;
		}
		++it;
	}						
}

/*  G::OptionGroupData
 */

struct OptionGroupData
{
	typedef std::vector<OptionEntry> OptionEntries;
	OptionEntries entries;
	OptionEntryArgs entry_args;
};

} // namespace G

/*  G::OptionContext
 */

G::OptionContext::OptionContext(const char *parameter_string)
: context_(g_option_context_new(parameter_string)), can_free_(true)
{
}

G::OptionContext::OptionContext(const String& parameter_string)
: context_(g_option_context_new(parameter_string.c_str())), can_free_(true)
{
}

G::OptionContext::OptionContext(const char *parameter_string, OptionGroup& main_group)
: context_(g_option_context_new(parameter_string)), can_free_(true)
{
	set_main_group(main_group);
}
	
G::OptionContext::OptionContext(const String& parameter_string, OptionGroup& main_group)
: context_(g_option_context_new(parameter_string.c_str())), can_free_(true)
{
	set_main_group(main_group);
}
		
G::OptionContext::OptionContext(GOptionContext *context, bool can_free)
: context_(context), can_free_(can_free)
{
}
		
G::OptionContext::~OptionContext()
{
	if (context_ && can_free_)
	{
		g_option_context_free(context_);
		context_ = 0;
	}
}	

Pointer<G::OptionGroup> 
G::OptionContext::get_main_group() const
{
	GOptionGroup *group = g_option_context_get_main_group(context_);
	return new OptionGroup(group, false);
}

bool 
G::OptionContext::parse(int *argc, char ***argv, Error *error)
{
	return g_option_context_parse(context_, argc, argv, *error);
}

void 
G::OptionContext::add_group(OptionGroup& group)
{
	g_option_group_add_entries(group.g_option_group(), &group.data_->entries[0]);	
	g_option_context_add_group(context_, group.g_option_group());
	group.can_free_ = false;	
}
	
void 
G::OptionContext::set_main_group(OptionGroup& group)
{
	g_option_group_add_entries(group.g_option_group(), &group.data_->entries[0]);	
	g_option_context_set_main_group(context_, group.g_option_group());
	group.can_free_ = false;	
}

/*  G::OptionGroup
 */

namespace { // Callback and helper functions

gboolean 
option_pre_parse_func(GOptionContext *context, GOptionGroup*, void *data, GError **error)
{
	G::OptionGroup *group = reinterpret_cast<G::OptionGroup*>(data);
	G::OptionContext tmp_context(context, false);
	G::Error tmp_error;
	bool result = group->on_pre_parse(tmp_context, tmp_error);
	if (tmp_error.get())
		g_propagate_error(error, tmp_error);
	return result;
}

gboolean 
option_post_parse_func(GOptionContext *context, GOptionGroup*, void *data, GError **error)
{
	G::OptionGroup *group = reinterpret_cast<G::OptionGroup*>(data);
	G::OptionContext tmp_context(context, false);
	G::Error tmp_error;
	bool result = group->on_post_parse(tmp_context, tmp_error);
	if (tmp_error.get())
		g_propagate_error(error, tmp_error);
	return result;
}

void 
option_error_func(GOptionContext *context, GOptionGroup *, void *data, GError **error)
{
	G::OptionGroup *group = reinterpret_cast<G::OptionGroup*>(data);
	G::OptionContext tmp_context(context, false);
	G::Error tmp_error;
	g_propagate_error(tmp_error, *error);
	group->on_error(tmp_context, tmp_error);
}

void init_option_group(GOptionGroup *group, G::OptionGroupData *&data)
{
	data = new G::OptionGroupData;
	g_option_group_set_parse_hooks(group, &option_pre_parse_func, &option_post_parse_func);
	g_option_group_set_error_hook(group, &option_error_func);
	data->entries.push_back(G::OptionEntry(0, 0, 0, (GOptionArg)0, 0, 0, 0));
}

} // namespace

G::OptionGroup::OptionGroup()
: group_(g_option_group_new(0, 0, 0, this, 0)), can_free_(true), data_(0)
{
	init_option_group(*this, data_);		
}

G::OptionGroup::OptionGroup(const char *name, const char *description, const char  *help_description)
: group_(g_option_group_new(name, description, help_description, this, 0)), can_free_(true), data_(0)
{
	init_option_group(*this, data_);		
}

G::OptionGroup::OptionGroup(GOptionGroup *group, bool can_free)
: group_(group), can_free_(can_free), data_(0)
{
}
		
G::OptionGroup::~OptionGroup()
{
	if (data_)
		delete data_;
			
	if (group_ && can_free_)
	{
		g_option_group_free(group_);
	}
}

const GOptionEntry* 
G::OptionGroup::get_entries() const
{
	return &data_->entries[0];
}

bool 
G::OptionGroup::on_parse(const char */*option_name*/, const char */*value*/, Error& /*error*/)
{
	return true;
}	

bool 
G::OptionGroup::on_pre_parse(OptionContext& /*context*/, Error& /*error*/)
{
	return true;
}

bool 
G::OptionGroup::on_post_parse(OptionContext& /*context*/, Error& /*error*/)
{
	data_->entry_args.convert_args();	
	return true;
}

void 
G::OptionGroup::on_error(OptionContext& /*context*/, const Error& /*error*/)
{
}
 
void 
G::OptionGroup::set_translation_domain(const String& domain)
{
	set_translation_domain(domain.c_str());
}

namespace { // option_arg_slot_callback

gboolean option_arg_slot_callback(const char *option_name, const char *value, void *data, GError **error)
{
	G::OptionGroup *group = reinterpret_cast<G::OptionGroup*>(data);
	G::Error tmp_error;
	bool result = group->on_parse(option_name, value, tmp_error);
	if (tmp_error.get())
		g_propagate_error(error, tmp_error);
	return result;
}

} // namespace

void 
G::OptionGroup::add(const char *long_name, char short_name, const char *description, const char *arg_description)
{
	add(long_name, short_name, OptionFlagsField(0), description, arg_description);
}
	
void 
G::OptionGroup::add(const char *long_name, char short_name, OptionFlagsField flags, 
                    const char *description, const char *arg_description)
{
	OptionEntry entry(long_name, short_name, flags, G_OPTION_ARG_CALLBACK, 
	                  (void*)&option_arg_slot_callback, description, arg_description);
	data_->entries.insert(--data_->entries.end(), 1, entry);
}

void 
G::OptionGroup::add(const char *long_name, char short_name, bool& arg, const char *description)
{
	add(long_name, short_name, OptionFlagsField(0), arg, description);
}
	
void 
G::OptionGroup::add(const char *long_name, char short_name, OptionFlagsField flags, bool& arg, const char *description)
{
	OptionEntry entry(long_name, short_name, flags, G_OPTION_ARG_NONE, &arg, description, 0);
	data_->entries.insert(--data_->entries.end(), 1, entry);
}

void 
G::OptionGroup::add(const char *long_name, char short_name, int& arg, const char *description, const char *arg_description)
{
	add(long_name, short_name, OptionFlagsField(0), arg, description, arg_description);
}
	
void 
G::OptionGroup::add(const char *long_name, char short_name, OptionFlagsField flags, int& arg, 
                    const char *description, const char *arg_description)
{
	OptionEntry entry(long_name, short_name, flags, G_OPTION_ARG_INT, &arg, description, arg_description);
	data_->entries.insert(--data_->entries.end(), 1, entry);
}

void 
G::OptionGroup::add(const char *long_name, char short_name, String& arg, const char *description, const char *arg_description)
{
	add(long_name, short_name, OptionFlagsField(0), arg, description, arg_description);
}
	
void 
G::OptionGroup::add(const char *long_name, char short_name, OptionFlagsField flags, String& arg, 
                    const char *description, const char *arg_description)
{
	OptionEntryArg *entry_arg = new OptionEntryArg;
	entry_arg->type = G_OPTION_ARG_STRING;
	entry_arg->cpp_arg = &arg;
	entry_arg->str = 0;
	data_->entry_args.push_back(entry_arg); 
	OptionEntry entry(long_name, short_name, flags, G_OPTION_ARG_STRING, &entry_arg->str, description, arg_description);
	data_->entries.insert(--data_->entries.end(), 1, entry);
}

void 
G::OptionGroup::add(const char *long_name, char short_name, std::vector<String>& arg, 
                    const char *description, const char *arg_description)
{
	add(long_name, short_name, OptionFlagsField(0), arg, description, arg_description);
}
	
void 
G::OptionGroup::add(const char *long_name, char short_name, OptionFlagsField flags, std::vector<String>& arg, 
                    const char *description, const char *arg_description)
{
	OptionEntryArg *entry_arg = new OptionEntryArg;
	entry_arg->type = G_OPTION_ARG_STRING_ARRAY;
	entry_arg->cpp_arg = &arg;
	entry_arg->array = 0;
	data_->entry_args.push_back(entry_arg); 
	OptionEntry entry(long_name, short_name, flags, G_OPTION_ARG_STRING_ARRAY, &entry_arg->array, description, arg_description);
	data_->entries.insert(--data_->entries.end(), 1, entry);
}

void 
G::OptionGroup::add(const char *long_name, char short_name, std::string& arg, 
                    const char *description, const char *arg_description)
{
	add(long_name, short_name, OptionFlagsField(0), arg, description, arg_description);
}
	
void 
G::OptionGroup::add(const char *long_name, char short_name, OptionFlagsField flags, std::string& arg, 
                    const char *description, const char *arg_description)
{
	OptionEntryArg *entry_arg = new OptionEntryArg;
	entry_arg->type = G_OPTION_ARG_FILENAME;
	entry_arg->cpp_arg = &arg;
	entry_arg->str = 0;
	data_->entry_args.push_back(entry_arg); 
	OptionEntry entry(long_name, short_name, flags, G_OPTION_ARG_FILENAME, &entry_arg->str, description, arg_description);
	data_->entries.insert(--data_->entries.end(), 1, entry);
}

void 
G::OptionGroup::add(const char *long_name, char short_name, std::vector<std::string>& arg, 
                    const char *description, const char *arg_description)
{
	add(long_name, short_name, OptionFlagsField(0), arg, description, arg_description);
}
	
void 
G::OptionGroup::add(const char *long_name, char short_name, OptionFlagsField flags, std::vector<std::string>& arg,
                    const char *description, const char *arg_description)
{
	OptionEntryArg *entry_arg = new OptionEntryArg;
	entry_arg->type = G_OPTION_ARG_FILENAME_ARRAY;
	entry_arg->cpp_arg = &arg;
	entry_arg->array = 0;
	data_->entry_args.push_back(entry_arg); 
	OptionEntry entry(long_name, short_name, flags, G_OPTION_ARG_FILENAME_ARRAY,
	                  &entry_arg->array, description, arg_description);
	data_->entries.insert(--data_->entries.end(), 1, entry);
}

} // namespace Xfc	

