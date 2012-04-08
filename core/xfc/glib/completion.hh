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

/// @file xfc/glib/completion.hh
/// @brief A GCompletion C++ wrapper interface.
///
/// Provides Completion, an object that supports automatic string completion 
/// using a group of target strings.

#ifndef XFC_G_COMPLETION_HH
#define XFC_G_COMPLETION_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_COMPLETION_H__
#include <glib/gcompletion.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {

/// @class Completion completion.hh xfc/glib/completion.hh
/// @brief A GCompletion C++ wrapper interface.
///
/// Completion provides support for automatic completion of a string using any group
/// of target strings. It is typically used for file name completion as is common 
/// in many UNIX shells. 
///
/// The default constructor creates a completion object that uses strings as the 
/// completion items. The other constructor creates a completion object that uses
/// pointers to arbitrary data structures as the completion items. Target items are
/// added and removed with add_items(), remove_items() and clear_items(). A 
/// completion attempt is requested with complete(). 
///
/// Items in the completion can be simple strings (e.g. filenames), or pointers to 
/// arbitrary data structures. If data structures are used you must provide a 
/// GCompletionFunc (in the second constructor) which retrieves the item's string
/// from the data structure. You can change the way in which strings are compared
/// by setting a different GCompletionStrncmpFunc in set_compare(). 

class Completion : public Xfc::Object
{
	GCompletion *completion_;

public:
/// @name Constructors
/// @{

	Completion();
	///< Constructs a new Completion object that uses strings as the completion items.
	
	Completion(GCompletionFunc func);
	///< Constructs a new Completion object that uses data structures as the completion items.
	///< @param func The function to be called to return the string representing an item in the completion. 
	///<
	///< The GCompletionFunc should return the string corresponding to the given target item.
	
	~Completion();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GCompletion* g_completion() const;
	///< Get a pointer to the GDate object.

	operator GCompletion* () const;
	///< Conversion operator; Safely converts a G::Completion object into a GCompletion pointer.

/// @}
/// @name Methods
/// @{

	void add_items(const std::vector<String>& items);
	///< Adds items to the completion. 
	///< @param items The vector of strings to add.
	
	void remove_items(const std::vector<String>& items);
	///< Removes items from the completion. 
	///< @param items The vector of strings to remove.
	
	void clear_items();
	///< Removes all items from the completion.
	 
	String complete(const char *prefix, std::vector<String>& items);
	String complete(const String& prefix, std::vector<String>& items);
	///< Attempts to complete the string prefix using the completion target items.
	///< @param prefix The prefix string, typically used by the user, which is compared
	///<               with each of the items. 
	///< @param items A vector of String to store the strings that begin with <EM>prefix</EM>.
	///< @return The longest prefix common to all items that matched <EM>prefix</EM>, 
	///< or null if no items matched <EM>prefix</EM>. 
	///<
	///< This method returns the largest common prefix that is a valid UTF-8 string,
	///< omitting a possible common partial character. 
	
	void set_compare(GCompletionStrncmpFunc strncmp_func);
	///< Sets the function to use for string comparisons. The default string comparison function is strncmp(). 
	///< @param strncmp_func The string comparison function.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/completion.inl>

#endif // XFC_G_COMPLETION_HH
