/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
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
 
/// @file xfc/glib/module.hh
/// @brief GModule C++ interface.
///
/// Provides Module, an object for dynamically loading plug-in modules.

#ifndef XFC_G_MODULE_HH
#define XFC_G_MODULE_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __GMODULE_H__
#include <gmodule.h>
#endif

namespace Xfc {

namespace G {

/// enum G::ModuleFlags
/// Flags passed to G::Module::open(). 
///
/// Note that these flags are not supported on all platforms. 

enum ModuleFlags
{
	MODULE_BIND_LAZY = G_MODULE_BIND_LAZY,
	///< Specifies that symbols are only resolved when needed; The default action
	///< is to bind all symbols when the module is loaded. 
	
	MODULE_BIND_LOCAL = G_MODULE_BIND_LOCAL,
	///< Specifies that symbols in the module should not be added to the global name
	///< space. The default action on most platforms is to place symbols in the module
	///< in the global name space, which may cause conflicts with existing symbols.
	
	MODULE_BIND_MASK = G_MODULE_BIND_MASK
	///< Mask for all flags.
};

/// ModuleFlagsField holds one or more flags the G::ModuleFlags enumeration OR'd together.

typedef unsigned int ModuleFlagsField;

/// @class Module module.hh xfc/glib/module.hh
/// @brief A GModule C++ wrapper interface.
///
/// Module provides a portable way to dynamically load object files (commonly known as 'plug-ins').
/// The current implementation supports all systems that provide an implementation of dlopen() 
/// (e.g. Linux/Sun), as well as HP-UX via its shl_load() mechanism, and Windows platforms via DLLs. 
///
/// To use Module you must first determine whether dynamic loading is supported on the platform by
/// calling G::Module::supported(). If it is, you can open a module with G::Module::open(), find the
/// module's symbols (e.g. function names) with G::Module::symbol(), and later close the module with
/// G::Module::close(). G::Module::name() will return the file name of a currently opened module. If
/// any of these methods fail, the error status can be found with G::Module::error(). 
///
/// If your module introduces static data to common subsystems in the running program it must ensure
/// that it is never unloaded, by calling G::Module::make_resident(). 

class Module : public Xfc::Object
{
	Module(const Module&);
	Module& operator=(const Module&);

	GModule *module_;
	
protected:
/// @name Constructors
/// @{
	
	Module(GModule *module);
	///< Constructs a new module from an existing GModule. When the module
	///< is destroyed it close will be called to close the module 
	
/// @}

public:
/// @name Constructors
/// @{

	virtual ~Module();
	///< Destructor.

/// @}
/// @name Accessors
/// @{
	
	GModule* g_module() const;
	///< Get a pointer to the GModule object.

	operator GModule* () const;
	///< Conversion operator; Safely converts a G::Module object into a GModule pointer.
	
	String name() const;
	///< Gets the filename of the module.
	///< @return The filename of the module, or "main" if the module is the main program itself.

/// @}
/// @name Accessors
/// @{
	
	static bool supported();
	///< Checks if modules are supported on the current platform. 
	///< @return <EM>true</EM> if modules are supported. 

	static String error();
	///< Gets a string describing the last module error. 
	///< @return A string describing the last module error.

/// @}
/// @name Methods
/// @{

	bool close();
	///< Closes the module.
	///< @return <EM>true</EM> if successful.
	 	
	void make_resident();
	///< Ensures that the module will never be unloaded. Any future close()
	///< calls on the module will be ignored. 

	bool symbol(const char *symbol_name, void **symbol);
	bool symbol(const String& symbol_name, void **symbol);
	///< Gets a symbol pointer from the module. 
	///< @param symbol_name The name of the symbol to find. 
	///< @param symbol The return location for a pointer to the symbol value. 
	///< @return <EM>true</EM> on success.					    

/// @}
/// @name Methods
/// @{
	
	static Module* open(const char *file_name, ModuleFlagsField flags);	
	static Module* open(const String& file_name, ModuleFlagsField flags);
	///< Opens a module; if the module has already been opened, its reference count is incremented. 
	///< @param file_name The name of the file containing the module. 
	///< @param flags One or more G::ModuleFlags used for opening the module. 
	///< @return A Module on success, or null on failure. 	 
	///<	
	///< First of all this method tries to open <EM>filename</EM> as a module. 
	///< If that fails and <EM>filename</EM> has the ".la" suffix (and is a libtool
	///< archive) it tries to open the corresponding module. If that fails and it
	///< doesn't have the proper module suffix for the platform (G_MODULE_SUFFIX),
	///< this suffix will be appended and the corresponding module will be opended.
	///< If that fails and <EM>filename</EM> doesn't have the ".la"-suffix, this
	///< suffix is appended and open() tries to open the corresponding module. If
	///< eventually that fails as well, null is returned. 

	static String build_path(const char *module_name);	
	static String build_path(const String& module_name);
	///< A portable way to build the filename of a module. 
	///< @param module_name The name of the module. 
	///<
	///< This method is not recommended because it uses the standard platform-specific
	///< directories to build the filename and the wrong module may be found (see
	///< build_path(const String&, const String&)).
	
	static String build_path(const char *directory, const char *module_name);
	static String build_path(const String& directory, const String& module_name);
	///< A portable way to build the filename of a module. 
	///< @param directory The directory where the module is. 
	///< @param module_name The name of the module. 
	///< @return The complete path of the module, including the standard library prefix and suffix.
	///<	
	///< The platform-specific prefix and suffix are added to the filename,
	///< if needed, and the result is added to the directory, using the correct
	///< separator character.
	///<
	///< The directory should specify the directory where the module can be found.
	///< It can be null or an empty string to indicate that the module is in a
	///< standard platform-specific directory, though this is not recommended 
	///< since the wrong module may be found. For example, calling build_path() on 
	///< a Linux system with a directory of /lib and a module_name of "mylibrary"
	///< will return /lib/libmylibrary.so. On a Windows system, using \\Windows as
	///< the directory it will return \\Windows\\mylibrary.dll. To be absoultely sure
	///< to get the correct module, always pass in a directory. 
	 
/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/module.inl>

#endif // XFC_G_MODULE_HH
