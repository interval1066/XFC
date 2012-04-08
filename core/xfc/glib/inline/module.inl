/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  module.inl - G::Module inline functions
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

inline GModule*
Xfc::G::Module::g_module() const
{
	return module_;
}

inline Xfc::G::Module::operator GModule* () const
{
	return this ? module_ : 0;
}

inline bool 
Xfc::G::Module::supported()
{
	return g_module_supported();
}

inline bool 
Xfc::G::Module::close()
{
	return g_module_close(module_);
}		

inline void 
Xfc::G::Module::make_resident()
{
	g_module_make_resident(module_);
}

inline bool 
Xfc::G::Module::symbol(const char *symbol_name, void **symbol)
{
	return g_module_symbol(module_, symbol_name, symbol);
}

