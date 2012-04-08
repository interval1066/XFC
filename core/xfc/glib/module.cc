/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  module.cc - GModule C++ implementation
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
 
#include "module.hh"

using namespace Xfc;

/*  G::Module
 */

G::Module::Module(GModule *module)
: module_(module)
{
} 
	
G::Module::~Module()
{
}

G::Module* 
G::Module::open(const char *file_name, ModuleFlagsField flags)
{
	GModule *module = g_module_open(file_name, (GModuleFlags)flags);
	return module ? new Module(module) : 0;
}
	
G::Module* 
G::Module::open(const String& file_name, ModuleFlagsField flags)
{
	return open(file_name.c_str(), flags);
}

String 
G::Module::build_path(const char *module_name)
{
	return build_path(0, module_name);
}
	
String 
G::Module::build_path(const String& module_name)
{
	return build_path(0, module_name.c_str());
}
	
String 
G::Module::build_path(const char *directory, const char *module_name)
{
	char *path = g_module_build_path(directory, module_name);
	String s(path);	
	g_free(path);
	return s;
}
	
String 
G::Module::build_path(const String& directory, const String& module_name)
{
	return build_path(directory.c_str(), module_name.c_str());
}
	 
String 
G::Module::error()
{
	return g_module_error();
}

String 
G::Module::name() const
{
	return g_module_name(module_);
}

bool 
G::Module::symbol(const String& symbol_name, void **symbol)
{
	return g_module_symbol(module_, symbol_name.c_str(), symbol);
}

