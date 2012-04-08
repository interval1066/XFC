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
 
/// @file xfc/pango/tabs.hh
/// @brief A PangoTabArray C++ wrapper interface.
///
/// Provides TabArray, an object for storing Tab Stops.

#ifndef XFC_PANGO_TABS_HH
#define XFC_PANGO_TABS_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef __PANGO_TABS_H__
#include <pango/pango-tabs.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Pango {

/// @enum TabAlign
/// Specifies where a tab stop appears relative to the text.
/// Currently there is only TAB_LEFT, but TAB_RIGHT, TAB_CENTER and
/// TAB_NUMERIC may be supported in the future.

enum TabAlign
{
	TAB_LEFT = PANGO_TAB_LEFT ///< The tab stop appears to the left of the text.
};

/// @class TabArray tabs.hh xfc/pango/tabs.hh
/// @brief A PangoTabArray C++ wrapper class.
///
///< TabArray is an object that stores Tab Stops.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class TabArray : public G::Boxed
{
public:
/// @name Constructors
/// @{

	TabArray(int initial_size, bool positions_in_pixels = true);
	///< Construct an array of <EM>initial_size</EM> tab stops. 
	///< @param initial_size The initial number of tab stops to allocate, can be 0.
	///< @param positions_in_pixels Whether positions are in pixel units.
	///<
	///< Tab stops are specified in pixel units if <EM>positions_in_pixels</EM> is true,
	///< otherwise in Pango units. All stops are initially at position 0. The TabArray is 
	///< created with a reference count of 1 that the caller owns.

	TabArray(int size, bool positions_in_pixels, int first_position, ...);
	///< This is a convenience constructor that creates a tab array with left alignment
	///< and allows you to specify the position of each tab stop.
	///< @param size The number of tab stops in the array.
	///< @param positions_in_pixels Whether positions are in pixel units.
	///< @param first_position The position of first tab stop.
	///< @param ... Additional positions.
	///<
	///< You must provide a position for all <EM>size</EM> tab stops. This constructor
	///< is the same as the next, but uses the default tab alignment TAB_LEFT. The TabArray
	///< is created with a reference count of 1 that the caller owns.

	TabArray(int size, bool positions_in_pixels, TabAlign first_alignment, int first_position, ...);
	///< This is a convenience constructor that creates a tab array and allows
	///< you to specify the alignment and position of each tab stop.
	///< @param size The number of tab stops in the array.
	///< @param positions_in_pixels Whether positions are in pixel units.
	///< @param first_alignment The alignment of first tab stop.
	///< @param first_position The position of first tab stop.
	///< @param ... Additional alignment/position pairs.
	///<
	///< You must provide an alignment and position for all <EM>size</EM> tab stops. The
	///< TabArray is created with a reference count of 1 that the caller owns.

	TabArray(const std::vector<std::pair<TabAlign , int> >& tabs, bool positions_in_pixels = true);
	///< This is a convenience constructor that creates a tab array and allows
	///< you to specify the alignment and position of each tab stop.
	///< @param tabs A reference to a vector of TabAlign/int pairs that holds
	///<             the alignment and position of each tab stop.
	///< @param positions_in_pixels Whether positions are in pixel units.
	///<
	///< The TabArray is created with a reference count of 1 that the caller owns.

	explicit TabArray(PangoTabArray *tab_array);
	///< Construct a new tab array from an existing PangoTabArray.
	///< @param tab_array A pointer to a PangoTabArray.
	///<
	///< The <EM>tab_array</EM> can be a newly created PangoTabArray or an existing
	///< PangoTabArray. The TabArray object created is a temporary object. It doesn't 
	///< take over the ownership of PangoTabArray and PangoTabArray is not freed by
	///< the destructor. 
	///<
	///< The TabArray is created with a reference count of 1 that the caller owns.
	
	TabArray(PangoTabArray *tab_array, bool copy);
	///< Construct a new tab array from an existing PangoTabArray.
	///< @param tab_array A pointer to a PangoTabArray.
	///< @param copy Whether the TabArray object should make a copy of PangoTabArray or not.
	///<
	///< The <EM>tab_array</EM> can be a newly created PangoTabArray or an existing
	///< PangoTabArray. If <EM>copy</EM> is true TabArray will make a copy of PangoTabArray.
	///< If <EM>copy</EM> is false TabArray wont make a copy but instead takes over the
	///< ownership of PangoTabArray. Either way, the destructor will free PangoTabArray
	///< when the TabArray object is destroyed. This constructor is used by G::Boxed::wrap()
	///< to wrap PangoTabArray objects in a C++ wrapper.
	///<
	///< The TabArray is created with a reference count of 1 that the caller owns.

	TabArray(const TabArray& src);
	///< Copy constructor.
	///< @param src The source TabArray.

	virtual ~TabArray();
	///< Destructor.

	TabArray& operator=(const TabArray& src);
	///< Assignment operator.
	///< @param src The source TabArray.

/// @}
/// @name Accessors
/// @{

	PangoTabArray* pango_tab_array() const;
	///< Get a pointer to the PangoTabArray structure.

	operator PangoTabArray* () const;
	///< Conversion operator; safely converts a TabArray to a PangoTabArray pointer.

	int get_size() const;
	///< Get the number of tab stops in the tab array.
	///< @return The number of tab stops in the array.

	int get_tab(int tab_index, TabAlign *alignment = 0) const;
	///< Gets the alignment and position of a tab stop.
	///< @param tab_index The tab stop index.
	///< @param alignment The location to store the alignment, or null.
	///< @return The tab position.
	///<
	///< The alignment may be null if you aren't interested in the value.

	std::vector<std::pair<TabAlign, int> > get_tabs() const;
	///< Returns a vector of alignment/locations pairs (see Pango::LayoutLine::get_x_ranges()
	///< for an example of using a vector of pairs).
	///< @return A vector of TabAlign/int pairs.
	///<
	///< In the current implementation TabAlign is always TAB_LEFT and so can be ignored.

	bool get_positions_in_pixels() const;
	///< Returns true if the tab positions are in pixels, false if they are in Pango units.
	///< @return Whether positions are in pixels.

/// @}
/// @name Methods
/// @{

	void resize(int new_size);
	///< Resizes a tab array.
	///< @param new_size The new size of the array.
	///<
	///< You must subsequently initialize any tabs that were added
	///< as a result of growing the array.

	void set_tab(int tab_index, int location, TabAlign alignment = TAB_LEFT);
	///< Sets the location of a tab stop.
	///< @param tab_index The index of a tab stop.
	///< @param alignment The tab alignment
	///< @param location The tab location in pango units.
	///<
	///< The alignment must always be TAB_LEFT in the current implementation.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/tabs.inl>

#endif // XFC_PANGO_TABS_HH


