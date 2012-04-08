/*  XFC: Xfce Foundation Classes (User Interface Library)
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
 
/// @file xfc/atk/hypertext.hh
/// @brief An AtkHypertext C++ wrapper interface.
///
/// Provides Hypertext, an interface which provides a standard mechanism for manipulating hyperlinks.

#ifndef XFC_ATK_HYPERTEXT_HH
#define XFC_ATK_HYPERTEXT_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __ATK_HYPERTEXT_H__
#include <atk/atkhypertext.h>
#endif

namespace Xfc {

namespace Atk {

class Hyperlink;

/// @class Hypertext hypertext.hh xfc/atk/hypertext.hh
/// @brief An AtkHypertext C++ wrapper class.
///
/// Hypertext is an interface which provides a standard mechanism for manipulating hyperlinks.

class Hypertext : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Hypertext();
	///< Constructs a new Hypertext object.
	
	virtual ~Hypertext() = 0;
	///< Destructor.

/// @}
/// @name Signal Protptypes
/// @{

	typedef G::Signal<void, int> LinkSelectedSignalType;
	typedef G::SignalProxy<TypeInstance, LinkSelectedSignalType> LinkSelectedSignalProxy;
	static const LinkSelectedSignalType link_selected_signal;
	///< Link selected signal (see signal_link_selected()). Calls a slot with the signature:
	///< @code
	///< void function(int link_index);
	///< // link_index: The index of the hyperlink which is selected.
	///< @endcode
	
/// @}

public:
/// @name Accessors
/// @{

	AtkHypertext* atk_hypertext() const;
	///< Get a pointer to the AtkHypertext structure.

	operator AtkHypertext* () const;
	///< Conversion operator; safely converts a Hypertext to an AtkHypertext pointer.

	Hyperlink* get_link(int link_index) const;
	///< Gets the link in this hypertext document at index <EM>link_index</EM>.
	///< @param link_index An integer specifying the desired link.
	///< @return The link in this hypertext document at index <EM>link_index</EM>.

	int get_n_links(int char_index) const;
	///< Returns the number of links within this hypertext document.

	int get_link_index(int char_index) const;
	///< Gets the index into the array of hyperlinks that is associated with the
	///< character specified by <EM>char_index</EM>, or -1 if there is no hyperlink
	///< associated with this character.
	///< @param char_index A character index.
	///< @return An index into the array of hyperlinks in the hypertext.

/// @}
/// @name Signal Proxies
/// @{

	const LinkSelectedSignalProxy signal_link_selected();
	///< Connect to the link_selected_signal; emitted when the hypertext object is selected.

// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/hypertext.inl>

#endif // XFC_ATK_HYPERTEXT_HH

