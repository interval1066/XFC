/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  option.inl - G::OptionContext and G::OptionGroup inline functions
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

/*  G::OptionContext
 */

inline GOptionContext*
Xfc::G::OptionContext::g_option_context() const
{
	return context_;
}

inline Xfc::G::OptionContext::operator GOptionContext* () const
{
	return this ? context_ : 0;
}

bool 
Xfc::G::OptionContext::get_help_enabled() const
{
	return g_option_context_get_help_enabled(context_);
}

bool 
Xfc::G::OptionContext::get_ignore_unknown_options() const
{
	return g_option_context_get_ignore_unknown_options(context_);
}

void 
Xfc::G::OptionContext::set_help_enabled(bool help_enabled)
{
	g_option_context_set_help_enabled(context_, help_enabled);
}

void 
Xfc::G::OptionContext::set_ignore_unknown_options(bool ignore_unknown)
{
	g_option_context_set_ignore_unknown_options(context_, ignore_unknown);
}

void 
Xfc::G::OptionContext::add_group(GOptionGroup *group)
{
	g_option_context_add_group(context_, group);
}
	
/*  G::OptionGroup
 */

inline GOptionGroup*
Xfc::G::OptionGroup::g_option_group() const
{
	return group_;
}

inline Xfc::G::OptionGroup::operator GOptionGroup* () const
{
	return this ? group_ : 0;
}

void 
Xfc::G::OptionGroup::set_translation_domain(const char *domain)
{
	g_option_group_set_translation_domain(g_option_group(), domain);
}

