/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/pango/context.hh
/// @brief A PangoContext C++ wrapper interface.
///
/// Provides Context, an object that stores global information used to control the itemization process.

#ifndef XFC_PANGO_CONTEXT_HH
#define XFC_PANGO_CONTEXT_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_PANGO_TYPES_HH
#include <xfc/pango/types.hh>
#endif

#ifndef __PANGO_CONTEXT_H__
#include <pango/pango-context.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {
class Colormap;
class Screen;
}

namespace Pango {

class AttrList;
class AttrIterator;
class Font;
class FontDescription;
class FontFamily;
class FontMap;
class Fontset;
class FontMetrics;
class Item;

/// @class Context context.hh xfc/pango/context.hh
/// @brief A PangoLogAttr C++ wrapper class.
///
/// The Context object stores global information used to control the itemization process.

class Context : public G::Object
{
	friend class G::Object;

	Context(const Context&);
	Context& operator=(const Context&);
	
protected:
/// @name Constructors
/// @{

	explicit Context(PangoContext *context, bool owns_reference = true);
	///< Construct a new Context from an existing PangoContext.
	///< @param context A pointer to a PangoContext.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>context</EM> can be a newly created PangoContext or an existing
	///< PangoContext. (see G::Object::Object).

/// @}

public:
	typedef PangoContext CObjectType;

/// @name Constructors
/// @{

	virtual ~Context();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	PangoContext* pango_context() const;
	///< Get a pointer to the PangoContext structure.

	operator PangoContext* () const;
	///< Conversion operator; safely converts a Context to a PangoContext pointer.

	FontMap* get_font_map() const;
	///< Gets the Fontmap used to look up fonts for this context.
	///< @return The font map for the Context. 	
	
	Pointer<FontMetrics> get_metrics(const FontDescription& desc, PangoLanguage *language) const;
	///< Get the overall metric information for a particular font description.
	///< @param desc A FontDescription.
	///< @param language A language tag used to determine which script to get the metrics for,
	///<                 or null to indicate to get the metrics for the entire font.
	///< @return A smart pointer to a FontMetrics object.
	///<
	///< Since the metrics may be substantially different for different scripts,
	///< a language tag can be provided to indicate that the metrics should be
	///< retrieved that correspond to the script(s) used by that language.
	///<
	///< The FontDescription is interpreted in the same way as by itemize(),
	///< and the family name may be a comma separated list of figures. If
	///< characters from multiple of these families would be used to render
	///< the string, then the returned fonts would be a composite of the
	///< metrics for the fonts loaded for the individual families.

	Pointer<FontDescription> get_font_description() const;
	///< Retrieve the default font description for the context.
	///< @return A smart pointer to the context's default font description.

	PangoLanguage* get_language() const;
	///< Retrieves the global language tag for the context.
	///< @return The global language tag.

	Direction get_base_dir() const;
	///< Retrieves the base direction for the context.
	///< @return The base direction for the context.

	Pointer<Matrix> get_matrix() const;
	///< Gets the transformation matrix that will be applied when rendering with the context (see set_matrix()).
	///< @return The matrix, or null if no matrix has been set (which is the same as the identity matrix).

/// @}
/// @name Accessors
/// @{

	static Pointer<Pango::Context> get(const Gdk::Screen *screen = 0);
	///< Creates a PangoContext for the specified <EM>screen</EM>.
	///< @param screen The Screen to get the context for, or null for the default screen.
	///< @return A new PangoContext for <EM>screen</EM>
	///<
	///< When using a Gtk::Widget, normally you should use Gtk::Widget::get_pango_context()
	///< instead of this function, to get the appropriate context for the widget you intend to
	///< render text onto.

/// @}
/// @name Methods
/// @{
	
	bool list_families(std::vector<FontFamily*>& families) const;
	///< List all the families for the context's fontmap.
	///< @param families A reference to a vector of FontFamily* to hold the font families.
	///< @return <EM>true</EM> if the vector is not empty.

	Font* load_font(const FontDescription& desc) const;
	///< Loads the font in one of the fontmaps in the context that is the closest match for <EM>desc</EM>.
	///< @param desc A FontDescription describing the font to load.
	///< @return The font loaded, or null if no font matched.

	Fontset* load_fontset(const FontDescription& desc, PangoLanguage *language) const;
	///< Load a set of fonts in the context that can be used to render a font matching <EM>desc</EM>.
	///< @param desc A FontDescription describing the fonts to load.
	///< @param language A PangoLanguage the fonts will be used for.
	///< @return The fontset, or null if no font matched.

	void set_font_description(const FontDescription& desc);
	///< Set the default font description for the context.
	///< @param desc The new pango font description.

	void set_language(PangoLanguage *language);
	///< Sets the global language tag for the context.
	///< @param language The new language tag.

	void set_base_dir(Direction direction);
	///< Sets the base direction for the context.
	///< @param direction The new base direction.

	void set_matrix(const Matrix *matrix);
	///< Sets the transformation matrix that will be applied when rendering with the context.
	///< @param matrix A Pango::Matrix, or null to unset any existing matrix.	 
	///<
	///< No matrix set is the same as setting the identity matrix. The reported metrics are
	///< in the user space coordinates before the application of the matrix, not device-space
	///< coordiantes after the application of the matrix. So, they don't scale with the matrix,
	///< though they may change slightly for different matrices, depending on how the text is
	///< fit to the pixel grid.

	std::vector<Pointer<Item> > 
	itemize(const String& text, const AttrList& attrs, AttrIterator *cached_iter = 0) const;
	///< Breaks a piece of text into segments with consistent directional level and shaping engine.
	///< @param text The text to itemize.
	///< @param attrs The set of attributes that apply to text.
	///< @param cached_iter A cached attribute iterator, or null.
	///< @return A vector of Pointer<Item>.
	///<
	///< Each byte of text will be contained in exactly one of the items
	///< in the returned vector. The generated vector of items will be in
	///< logical order (the start offsets of the items are ascending).
	///<
	///< <EM>cached_iter</EM> should be an iterator over <EM>attrs</EM> currently
	///< positioned at a range before or containing <EM>start_index</EM>;
	///< <EM>cached_iter</EM> will be advanced to the range covering the
	///< position just after <EM>start_index</EM> + <EM>length</EM>. (i.e. if
	///< itemizing in a loop, just keep passing in the same cached_iter).

	std::vector<Pointer<Item> > 
	itemize(const char *text, int start_index, int length, const AttrList& attrs, AttrIterator *cached_iter = 0) const;
	///< Breaks a piece of text into segments with consistent directional level and shaping engine.
	///< @param text The text to itemize, starting at <EM>start_index</EM>
	///< @param start_index The first byte in text to process.
	///< @param length The number of bytes (not characters) to process after start_index. This must be >= 0.
	///< @param attrs The set of attributes that apply to text.
	///< @param cached_iter A cached attribute iterator, or null.
	///< @return A vector of Pointer<Item>.
	///<
	///< Each byte of text will be contained in exactly one of the items
	///< in the returned vector. The generated vector of items will be in
	///< logical order (the start offsets of the items are ascending).
	///<
	///< <EM>cached_iter</EM> should be an iterator over <EM>attrs</EM> currently
	///< positioned at a range before or containing <EM>start_index</EM>;
	///< <EM>cached_iter</EM> will be advanced to the range covering the
	///< position just after <EM>start_index</EM> + <EM>length</EM>. (i.e. if
	///< itemizing in a loop, just keep passing in the same cached_iter).

	std::vector<Pointer<Item> > 
	itemize(Direction direction, const String& text, const AttrList& attrs, AttrIterator *cached_iter = 0) const;
	///< Breaks a piece of text into segments using the specified base <EM>direction</EM>.
	///< @param direction The base direction to use for bidirectional processing. 	
	///< @param text The text to itemize.
	///< @param attrs The set of attributes that apply to text.
	///< @param cached_iter A cached attribute iterator, or null.
	///< @return A vector of Pointer<Item>.
	///<
	///< See itemize(const String&, const AttrList&, AttrIterator*).
	
	std::vector<Pointer<Item> > 
	itemize(Direction direction, const char *text, int start_index, int length, const AttrList& attrs, AttrIterator *cached_iter = 0) const;
	///< Breaks a piece of text into segments using the specified base <EM>direction</EM>.
	///< @param direction The base direction to use for bidirectional processing. 	
	///< @param text The text to itemize, starting at <EM>start_index</EM>
	///< @param start_index The first byte in text to process.
	///< @param length The number of bytes (not characters) to process after start_index. This must be >= 0.
	///< @param attrs The set of attributes that apply to text.
	///< @param cached_iter A cached attribute iterator, or null.
	///< @return A vector of Pointer<Item>.
	///<
	///< See itemize(const char*, int, int, const AttrList&, AttrIterator*).

/// @}
/// @name GDK Pango Methods
/// @{

	void set_colormap(const Gdk::Colormap& colormap);
	///< Sets the colormap to be used for drawing with the context.
	///< @param colormap A Gdk::colormap.
	///<
	///< If you obtained your context from Gtk::Widget::get_pango_context() or
	///< Gtk::Widget::create_pango_context(), the colormap will already be set to
	///< the colormap for the widget, so you shouldn't need this method.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/context.inl>

#endif // XFC_PANGO_CONTEXT_HH

