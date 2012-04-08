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

/// @file xfc/pango/script.hh
/// @brief A Pango Script C++ wrapper interface.
///
/// Provides PangoScript and PangoScriptIter which are used to identify the writing system,
/// or script of individual characters and of ranges within a larger text string.

#ifndef XFC_PANGO_SCRIPT_HH
#define XFC_PANGO_SCRIPT_HH

#ifndef XFC_G_UNICODE_HH
#include <xfc/glib/unicode.hh>
#endif

#ifndef XFC_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __PANGO_SCRIPT_H__
#include <pango/pango-script.h>
#endif

namespace Xfc {

namespace Pango {

/// @enum Script
/// Identifies different writing systems. The values correspond to the names defined
/// in the Unicode standard (see Unicode Standard Annex 24: Script names).

enum Script
{
	SCRIPT_INVALID_CODE = PANGO_SCRIPT_INVALID_CODE, ///< A value never used for any unicode character.
	SCRIPT_COMMON = PANGO_SCRIPT_COMMON, ///< Zyyy; a character used by multiple different scripts.
	SCRIPT_INHERITED = PANGO_SCRIPT_INHERITED, ///< Qaai; a mark glyph that takes its script from the base glyph to which it is attached.
	SCRIPT_ARABIC = PANGO_SCRIPT_ARABIC, ///< Arab.
	SCRIPT_ARMENIAN = PANGO_SCRIPT_ARMENIAN, ///< Armn.
	SCRIPT_BENGALI = PANGO_SCRIPT_BENGALI, ///< Beng.
	SCRIPT_BOPOMOFO = PANGO_SCRIPT_BOPOMOFO, ///< Bopo.
	SCRIPT_CHEROKEE = PANGO_SCRIPT_CHEROKEE, ///< Cher.
	SCRIPT_COPTIC = PANGO_SCRIPT_COPTIC, ///< Qaac.
	SCRIPT_CYRILLIC = PANGO_SCRIPT_CYRILLIC, ///< Cyrl (Cyrs).
	SCRIPT_DESERET = PANGO_SCRIPT_DESERET, ///< Dsrt.
	SCRIPT_DEVANAGARI = PANGO_SCRIPT_DEVANAGARI, ///<  Deva.
	SCRIPT_ETHIOPIC = PANGO_SCRIPT_ETHIOPIC, ///< Ethi.
	SCRIPT_GEORGIAN = PANGO_SCRIPT_GEORGIAN, ///<  Geor (Geon, Geoa).
	SCRIPT_GOTHIC = PANGO_SCRIPT_GOTHIC, ///< Goth.
	SCRIPT_GREEK = PANGO_SCRIPT_GREEK, ///< Grek.
	SCRIPT_GUJARATI = PANGO_SCRIPT_GUJARATI, ///< Gujr.
	SCRIPT_GURMUKHI = PANGO_SCRIPT_GURMUKHI, ///< Guru.
	SCRIPT_HAN = PANGO_SCRIPT_HAN, ///< Hani.
	SCRIPT_HANGUL = PANGO_SCRIPT_HANGUL, ///< Hang.
	SCRIPT_HEBREW = PANGO_SCRIPT_HEBREW, ///< Hebr.
	SCRIPT_HIRAGANAPANGO_SCRIPT_HIRAGANA, ///< Hira.
	SCRIPT_KANNADA = PANGO_SCRIPT_KANNADA, ///< Knda.
	SCRIPT_KATAKANA = PANGO_SCRIPT_KATAKANA, ///< Kana.
	SCRIPT_KHMER = PANGO_SCRIPT_KHMER, ///< Khmr.
	SCRIPT_LAO = PANGO_SCRIPT_LAO, ///< Laoo.
	SCRIPT_LATIN = PANGO_SCRIPT_LATIN, ///< Latn (Latf, Latg).
	SCRIPT_MALAYALAM = PANGO_SCRIPT_MALAYALAM, ///< Mlym.
	SCRIPT_MONGOLIAN = PANGO_SCRIPT_MONGOLIAN, ///< Mong.
	SCRIPT_MYANMAR = PANGO_SCRIPT_MYANMAR, ///< Mymr.
	SCRIPT_OGHAM = PANGO_SCRIPT_OGHAM, ///< Ogam.
	SCRIPT_OLD_ITALIC = PANGO_SCRIPT_OLD_ITALIC, ///< Ital.
	SCRIPT_ORIYA = PANGO_SCRIPT_ORIYA, ///< Orya.
	SCRIPT_RUNIC = PANGO_SCRIPT_RUNIC, ///< Runr.
	SCRIPT_SINHALA = PANGO_SCRIPT_SINHALA, ///< Sinh.
	SCRIPT_SYRIAC = PANGO_SCRIPT_SYRIAC, ///< Syrc (Syrj, Syrn, Syre).
	SCRIPT_TAMIL = PANGO_SCRIPT_TAMIL, ///< Taml.
	SCRIPT_TELUGU = PANGO_SCRIPT_TELUGU, ///< Telu.
	SCRIPT_THAANA = PANGO_SCRIPT_THAANA, ///< Thaa.
	SCRIPT_THAI = PANGO_SCRIPT_THAI, ///< Thai.
	SCRIPT_TIBETAN = PANGO_SCRIPT_TIBETAN, ///< Tibt.
	SCRIPT_CANADIAN_ABORIGINAL = PANGO_SCRIPT_CANADIAN_ABORIGINAL, ///< Cans.
	SCRIPT_YI = PANGO_SCRIPT_YI, ///< Yiii.
	SCRIPT_TAGALOG = PANGO_SCRIPT_TAGALOG, ///< Tglg.
	SCRIPT_HANUNOO = PANGO_SCRIPT_HANUNOO, ///< Hano.
	SCRIPT_BUHID = PANGO_SCRIPT_BUHID, ///< Buhd.
	SCRIPT_TAGBANWA = PANGO_SCRIPT_TAGBANWA, ///< Tagb.

	// Unicode 4.0 additions
	SCRIPT_BRAILLE = PANGO_SCRIPT_BRAILLE, ///< Brai.
	SCRIPT_CYPRIOTPANGO_SCRIPT_CYPRIOT, ///< Cprt.
	SCRIPT_LIMBUPANGO_SCRIPT_LIMBU, ///<  Limb.
	SCRIPT_OSMANYA = PANGO_SCRIPT_OSMANYA, ///< Osma.
	SCRIPT_SHAVIAN = PANGO_SCRIPT_SHAVIAN, ///< Shaw.
	SCRIPT_LINEAR_B = PANGO_SCRIPT_LINEAR_B, ///< Linb.
	SCRIPT_TAI_LE = PANGO_SCRIPT_TAI_LE, ///< Tale.
	SCRIPT_UGARITIC = PANGO_SCRIPT_UGARITIC ///< Ugar.
};

/// @name Script Methods
/// @{

Script script_for_unichar(G::Unichar ch);
///< Looks up the Pango::Script for a particular character (as defined by Unicode Technical report 24).
///< @param ch A unicode character
///< @return The PangoScript for the character.
///<
///< No check is made for <EM>ch</EM> being valid unicode character; if you pass in an invalid
///< character, the result is undefined.

PangoLanguage* script_get_sample_language(Script script);
///< Given a script, finds a language tag that is reasonably representative of that script.
///< @param script A Pango::Script
///< @return A PangoLanguage that is representative of the script, or null if no such language exists.
///<
///< This will usually be the most widely spoken or used language written in that
///< script: for instance, the sample language for Pango::SCRIPT_CYRILLIC is ru (Russian),
///< the sample lanugage for Pango::SCRIPT_ARABIC is ar. For some scripts, no sample
///< language will be returned because there is no language that is sufficiently
///< representative. The best example of this is Pango::SCRIPT_HAN, where various
///< different variants of written Chinese, Japanese, and Korean all use significantly
///< different sets of Han characters and forms of shared characters. No sample language
///< can be provided for many historical scripts as well.

bool language_includes_script(PangoLanguage *language, Script script);
///< Determines if <EM>script</EM> is one of the scripts used to write <EM>language</EM>.
///< @param language A PangoLanguage.
///< @param script A Pango::Script
///< @return <EM>true</EM> if <EM>script</EM> is one of the scripts used to write <EM>language</EM>,
///< or if nothing is known about <EM>language</EM>.
///<
///< The returned value is conservative; if nothing is known about the language tag
///< <EM>language</EM>, true will be returned, since, as far as Pango knows, <EM>script</EM>
///< might be used to write <EM>language</EM>.
///<
///< This routine is used in Pango's itemization process when determining if a supplied
///< language tag is relevant to a particular section of text. It probably is not useful
///< for applications in most circumstances.

/// @}

/// @class ScriptIter script.hh xfc/pango/script.hh
/// @brief A PangoScriptIter C++ wrapper class.
///
/// ScriptIter is used to iterate through a string and identify ranges in different scripts.

class ScriptIter
{
	ScriptIter(const ScriptIter&);
	ScriptIter& operator=(const ScriptIter&);

	PangoScriptIter *iter_;

public:
/// @name Constructors
/// @{

	explicit ScriptIter(const char *text, int length = -1);
	///< Construct a new script iterator, used to break a string of Unicode into runs by text.
	///< @param text A UTF-8 string.
	///< @param length The length of text, or -1 if text is null-terminated.
	///<
	///< No copy is made of text, so the caller needs to make sure it remains valid
	///< until the iterator is destroyed. The newly created script iterator, initialized to
	///< point at the first range in the text. If the string is empty, it will point at an
	///< empty range.

	explicit ScriptIter(const String& text);
	///< Construct a new script iterator, used to break a string of Unicode into runs by text.
	///< @param text A String.
	///<
	///< No copy is made of text, so the caller needs to make sure it remains valid
	///< until the iterator is destroyed. The newly created script iterator, initialized to
	///< point at the first range in the text. If the string is empty, it will point at an
	///< empty range.

	~ScriptIter();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	PangoScriptIter* pango_script_iter() const;
	///< Get a pointer to the PangoScriptIter structure.

	operator PangoScriptIter* () const;
	///< Conversion operator; safely converts a ScriptIter to a PangoScriptIter pointer.

	Script get_range(const char **start, const char **end);
	///< Gets information about the range to which the iterator currently points.
	///< @param start The location to store the start position of the range, or null.
	///< @param end The location to store end position of the range, or null.
	///< @return The script for range.
	///<
	///< The range is the set of locations p where *start <= p < *end. (That is,
	///< it doesn't include the character stored at *end).

	Script get_range(String *range = 0);
	///< Gets information about the range to which the iterator currently points.
	///< @param range The location to store the characters of the range, or null.
	///< @return The script for range.

/// @}
/// @name Methods
/// @{

	bool next();
	///< Advances a script iterator to the next range.
	///< @return <EM>true</EM> if the iter was succesfully advanced.
	///<
	///< If the iter is already at the end, it is left unchanged and false is returned.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/script.inl>

#endif // XFC_PANGO_SCRIPT_HH

