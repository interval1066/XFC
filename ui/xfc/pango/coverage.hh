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
 
/// @file xfc/pango/coverage.hh
/// @brief A PangoCoverage C++ wrapper interface.
///
/// Provides Coverage, an object used to determine if a particular font can represent
/// a particular character, and also how well it can represent that character.

#ifndef XFC_PANGO_COVERAGE_HH
#define XFC_PANGO_COVERAGE_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __PANGO_COVERAGE_H__
#include <pango/pango-coverage.h>
#endif

namespace Xfc {

namespace Pango {

/// @enum CoverageLevel
/// Used to indicate how well a font can represent a particular ISO 10646 character
/// point for a particular script.

enum CoverageLevel
{
	COVERAGE_NONE = PANGO_COVERAGE_NONE,
	///< The character is not representable with the font.

	COVERAGE_FALLBACK = PANGO_COVERAGE_FALLBACK,
	///< The character is represented in a way that may be comprehensible
	///< but is not the correct graphical form; for instance, a Hangul
	///< character represented as a a sequence of Jamos, or a Latin
	///< transliteration of a Cyrillic word.

	COVERAGE_APPROXIMATE = PANGO_COVERAGE_APPROXIMATE,
	///< The character is represented as basically the correct graphical form,
	///< but with a stylistic variant inappropriate for the current script.

	COVERAGE_EXACT = PANGO_COVERAGE_EXACT
	///< The character is represented as the correct graphical form.
};

/// @class Coverage coverage.hh xfc/pango/coverage.hh
/// @brief A PangoCoverage C++ wrapper class.
///
/// It is often necessary in Pango to determine if a particular font can represent
/// a particular character, and also how well it can represent that character. The
/// Coverage object is used to represent that information.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Coverage : public Xfc::Object
{
	PangoCoverage *coverage_;

public:
/// @name Constructors
/// @{

	Coverage();
	///< Constructs a new coverage object, initialized to COVERAGE_NONE.
	///< The Coverage is created with a reference count of 1 that the caller owns.

	explicit Coverage(PangoCoverage *coverage);
	///< Constructs a new coverage from an existing PangoCoverage.
	///< @param coverage A PangoCoverage.
	///< 
	///< Coverage references the PangoCoverage and releases the reference
	///< when it's no longer required. The Coverage is created with a reference
	///< count of 1 that the caller owns.

	Coverage(const Coverage& src);
	///< Copy constructor.
	///< @param src The source coverage.

	virtual ~Coverage();
	///< Destructor.

	Coverage& operator=(const Coverage& src);
	///< Assignment operator.
	///< @param src The source coverage.

/// @}
/// @name Accessors
/// @{

	PangoCoverage* pango_coverage() const;
	///< Get a pointer to the PangoCoverage structure.

	operator PangoCoverage* () const;
	///< Conversion operator; safely converts a Coverage to a PangoCoverage pointer.

	CoverageLevel get(int index) const;
	///< Determine whether a particular index is covered by coverage.
	///< @param index The index to check.
	///< @return The Pango::CoverageLevel for index.

/// @}
/// @name Methods
/// @{

	void set(int index, CoverageLevel level);
	///< Modify a particular index within the coverage.
	///< @param index The index to modify.
	///< @param level The new level for <EM>index</EM>.

	void max(const Coverage& other);
	///< Set the coverage for each index in <EM>other</EM> to be the max
	///< (better) value of the current coverage for the index and the 
	///< coverage for the corresponding index in <EM>other</EM>.
	///< @param other Another coverage object.

	void to_bytes(unsigned char **bytes, int *n_bytes);
	///< Convert the coverage into a flat binary format.
	///< @param bytes The location to store result (must be freed with g_free()).
	///< @param n_bytes The location to store size of <EM>bytes</EM>.

/// @}
/// @name Methods
/// @{

	static Pointer<Coverage> from_bytes(unsigned char *bytes, int n_bytes);
	///< Convert data generated from to_bytes() back to a Coverage object.
	///< @param bytes A binary data representing a Coverage object.
	///< @param n_bytes The size of <EM>bytes</EM> in bytes.
	///< @return A smart pointer to a newly allocated coverage, or null if the data was invalid.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/coverage.inl>

#endif // XFC_PANGO_COVERAGE_HH

