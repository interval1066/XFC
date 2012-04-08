/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  script.inl - Pango::ScriptIter inline functions
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

/*  Pango::script_for_unichar
 */

inline Xfc::Pango::Script
Xfc::Pango::script_for_unichar(G::Unichar ch)
{
	return (Script)pango_script_for_unichar(ch);
}

/*  Pango::script_get_sample_language
 */

inline PangoLanguage*
Xfc::Pango::script_get_sample_language(Script script)
{
	return pango_script_get_sample_language((PangoScript)script);
}

/*  Pango::language_includes_script
 */

inline bool
Xfc::Pango::language_includes_script(PangoLanguage *language, Script script)
{
	return pango_language_includes_script(language, (PangoScript)script);
}

/*  Pango::ScriptIter
 */

inline PangoScriptIter*
Xfc::Pango::ScriptIter::pango_script_iter() const
{
	return iter_;
}

inline Xfc::Pango::ScriptIter::operator PangoScriptIter* () const
{
	return this ? iter_ : 0;
}

inline bool
Xfc::Pango::ScriptIter::next()
{
	return pango_script_iter_next(iter_);
}

