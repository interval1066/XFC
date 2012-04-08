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
 
/// @file xfc/atk/hyperlink.hh
/// @brief An AtkHyperlink C++ wrapper interface.
///
/// Provides Hyperlink, an object which encapsulates a link or set of links in a hypertext document.

#ifndef XFC_ATK_HYPERLINK_HH
#define XFC_ATK_HYPERLINK_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_ATK_ACTION_HH
#include <xfc/atk/action.hh>
#endif

#ifndef __ATK_HYPERLINK_H__
#include <atk/atkhyperlink.h>
#endif

namespace Xfc {

namespace Atk {

class Object;

/// @enum HyperlinkStateFlags
/// Describes the type of link.

enum HyperlinkStateFlags
{
	HYPERLINK_IS_INLINE = ATK_HYPERLINK_IS_INLINE ///< The link is inline.
};

/// HyperlinkStateFlagsField holds one or more values from the Atk::HyperlinkStateFlags enumeration OR'd together.

typedef unsigned int HyperlinkStateFlagsField;

/// @class Hyperlink hyperlink.hh xfc/atk/hyperlink.hh
/// @brief An AtkHyperlink C++ wrapper class.
///
/// Hyperlink is an Atk::Object which encapsulates a link or set of links
/// in a hypertext document. It implements the Atk::Action interface.

class Hyperlink : public G::Object, public Action
{
	friend class G::Object;

	Hyperlink(const Hyperlink&);
	Hyperlink& operator=(const Hyperlink&);
	
protected:
/// @name Constructors
/// @{

	explicit Hyperlink(AtkHyperlink *hyperlink, bool owns_reference = true);
	///< Construct a new Hyperlink from an existing AtkHyperlink.
	///< @param hyperlink A pointer to a AtkHyperlink.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>hyperlink</EM> can be a newly created AtkHyperlink or an existing
	///< AtkHyperlink. (see G::Object::Object).

/// @}
/// @name Signal Prototpyes
/// @{

	typedef G::Signal<void> LinkActivatedSignalType;
	typedef G::SignalProxy<TypeInstance, LinkActivatedSignalType> LinkActivatedSignalProxy;
	static const LinkActivatedSignalType link_activated_signal;
	///< Link activated signal (see signal_link_activated()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef AtkHyperlink CObjectType;

/// @name Constructors
/// @{

	virtual ~Hyperlink();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	AtkHyperlink* atk_hyperlink() const;
	///< Get a pointer to the AtkHyperlink structure.

	operator AtkHyperlink* () const;
	///< Conversion operator; safely converts a Hyperlink to an AtkHyperlink pointer.

	String get_uri(int i) const;
	///< Gets the URI associated with the anchor of the link specified by i.
	///< @param i A zero-index integer specifying the desired anchor.
	///< @return A string specifying the URI.
	///<
	///< Multiple anchors are primarily used by client-side image maps.

	Atk::Object* get_object(int i) const;
	///< Returns the item associated with this hyperlink's nth anchor.
	///< @param i A zero-index integer specifying the desired anchor.
	///< @return An Atk::Object associated with this hyperlink's i-th anchor.
	///<
	///< For instance, the returned Atk::Object will implement Text if the link
	///< is a text hyperlink, Image if the link is an image hyperlink etc. Multiple
	///< anchors are primarily used by client-side image maps.
	
	int get_end_index() const;
	///< Gets the index with the hypertext document at which this link ends.
	///< @return The index with the hypertext document at which this link ends.

	int get_start_index() const;
	///< Gets the index with the hypertext document at which this link begins.
	///< @return The index with the hypertext document at which this link begins.
	
	bool is_valid() const;
	///< Since the document that a link is associated with may have changed this
	///< method returns <EM>true</EM> if the link is still valid (with respect to
	///< the document it references) and <EM>false</EM> otherwise.
	///< @return Whether or not this link is still valid.

	bool is_inline() const;
	///< Indicates whether the link currently displays some or all of its content inline.
	///< @return Whether or not this link displays its content inline.
	///<
	///< Ordinary HTML links will usually return false, but an inline source
	///< HTML element will return true.

	int get_n_anchors() const;
	///< Returns the number of anchors associated with this hyperlink.

	bool is_selected_link() const;
	///< Determines whether this hyperlink is selected.
	///< @return <EM>true</EM> if the AtkHyperlink is selected, <EM>false</EM> otherwise.
	
/// @}
/// @name Signal Proxies
/// @{

	const LinkActivatedSignalProxy signal_link_activated();
	///< Connect to the link_activated_signal; emitted when the hyperlink object is activated.

// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/hyperlink.inl>

#endif // XFC_ATK_HYPERLINK_HH

