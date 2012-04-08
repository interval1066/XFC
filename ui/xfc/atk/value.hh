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
 
/// @file xfc/atk/value.hh
/// @brief An AtkValue C++ wrapper interface.
///
/// Provides AtkValue, an interface implemented by valuators and components which
/// display or select a value from a bounded range of values.

#ifndef XFC_ATK_VALUE_HH
#define XFC_ATK_VALUE_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __ATK_VALUE_H__
#include <atk/atkvalue.h>
#endif

namespace Xfc {

namespace G {
class Value;
}

namespace Atk {

/// @class Value value.hh xfc/atk/value.hh
/// @brief An AtkValue C++ wrapper class.
///
/// Value should be implemented for components which either display a value from a bounded range,
/// or which allow the user to specify a value from a bounded range, or both. For instance, most
/// sliders and range controls, as well as dials, should have Atk::Object representations which
/// implement Value on the component's behalf. Values may be read-only, in which case attempts
/// to alter the value return false to indicate failure.

class Value : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{
	
	Value();
	///< Constructs a new Value object.
	
	virtual ~Value() = 0;
	
/// @}

public:
/// @name Accessors
/// @{

	AtkValue* atk_value() const;
	///< Get a pointer to the AtkValue structure.

	operator AtkValue* () const;
	///< Conversion operator; safely converts a Value to an AtkValue pointer.

	void get_current_value(G::Value& value) const;
	///< Gets the value of this object.
	///< @param value A G::Value representing the current accessible value.

	void get_maximum_value(G::Value& value) const;
	///< Gets the maximum value for this object.
	///< @param value A G::Value representing the maximum accessible value.

	void get_minimum_value(G::Value& value) const;
	///< Gets the minimum value for this object.
	///< @param value A G::Value representing the minimum accessible value.

/// @}
/// @name Methods
/// @{

	bool set_current_value(const G::Value& value);
	///< Sets the value of this object.
	///< @param value A G::Value which is the desired new accessible value.
	///< @return <EM>true</EM> if the new value is successfully set, <EM>false</EM> otherwise.
	
/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/value.inl>

#endif // XFC_ATK_VALUE_HH

