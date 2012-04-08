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

/// @file xfc/gdk/color.hh
/// @brief A GdkColor C++ wrapper interface.
///
/// Provides Color and Colormap, two objects used to manipulation of colors and colormaps.

#ifndef XFC_GDK_COLOR_HH
#define XFC_GDK_COLOR_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __GDK_COLOR_H__
#include <gdk/gdkcolor.h>
#endif

#ifndef _CPP_MAP
#include <map>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {

class Screen;
class Visual;

/// @class Color color.hh xfc/gdk/color.hh
/// @brief A GdkColor C++ wrapper class.
///
/// The Color object is used to describe an allocated or unallocated color.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Color : public G::Boxed
{
public:
/// @name Constructors
/// @{

	Color();
	///< Constructs the default color black with a reference count of 1 that the caller owns.

	explicit Color(const char *spec);
	///< Constructs a color object by parsing the textual specification of a color and
	///< filling in the red, green, and blue fields.
	///< @param spec The string specifying the color.
	///<
	///< The color is not allocated, you must call allocate() or Gdk::Colormap::alloc_color()
	///< yourself. The text string can be in any of the forms accepted by XParseColor; these 
	///< include the name for a color from rgb.txt, such as DarkSlateGray, or a hex specification
	///< such as 305050. Color is created with a reference count of 1 that the caller owns.

	explicit Color(unsigned short value);
	///< Constructs a greyscale color by setting red, green and blue to value.
	///< @param value A value between 0 and 65535.
	///<
	///<  Color is created with a reference count of 1 that the caller owns.

	Color(unsigned short r, unsigned short g, unsigned short b);
	///< Construct a color with the specified values.
	///< @param r The red component of the color, a value between 0 and 65535.
	///< @param g The green component of the color.
	///< @param b The blue component of the color.
	///<
	///<  Color is created with a reference count of 1 that the caller owns.

	explicit Color(GdkColor *color);
	///< Construct a new color from an existing GdkColor.
	///< @param color A pointer to a GdkColor.
	///<
	///< The <EM>color</EM> can be a newly created GdkColor or an existing
	///< GdkColor. The Color object created is a temporary object. It doesn't
	///< take over the ownership of GdkColor and GdkColor is not freed by the
	///< destructor. Color is created with a reference count of 1 that the caller owns.


	Color(GdkColor *color, bool copy);
	///< Construct a new color from an existing GdkColor.
	///< @param color A pointer to a GdkColor.
	///< @param copy Whether the Color object should make a copy of GdkColor or not.
	///<
	///< The <EM>color</EM> can be a newly created GdkColor or an existing GdkColor.
	///< If <EM>copy</EM> is true Color will make a copy of GdkColor. If <EM>copy</EM>
	///< is false Color wont make a copy but instead takes over the ownership of GdkColor.
	///< Either way, the destructor will free GdkColor when the Color object is destroyed.
	///< This constructor is used by G::Boxed::wrap() to wrap GdkColor objects in a
	///< C++ wrapper. Color is created with a reference count of 1 that the caller owns.

	Color(const Color& src);
	///< Copy constructor.
	///< @param src The source color.

	~Color();
	///< Destructor.

	Color& operator=(const Color& src);
	///< Assignment operator.
	///< @param src The source color.

/// @}
/// @name Accessors
/// @{

	GdkColor* gdk_color() const;
	///< Get a pointer to the GdkColor structure.

	operator GdkColor* () const;
	///< Conversion operator; safely converts a Color to a GdkColor pointer.

	double red() const;
	///< Returns the red component of the color. This is a value between 0 and 1,
	///< with 1 indicating full intensitiy.

	double green() const;
	///< Returns the green component of the color. This is a value between 0 and 1,
	///< with 1 indicating full intensitiy.

	double blue() const;
	///< Returns the blue component of the color. This is a value between 0 and 1,
	///< with 1 indicating full intensitiy.
	
	unsigned short get_red() const;
	///< Returns the red component of the color. This is a value between 0 and 65535,
	///< with 65535 indicating full intensitiy.

	unsigned short get_green() const;
	///< Returns the green component of the color. This is a value between 0 and 65535,
	///< with 65535 indicating full intensitiy.

	unsigned short get_blue() const;
	///< Returns the blue component of the color. This is a value between 0 and 65535,
	///< with 65535 indicating full intensitiy.

	unsigned long get_pixel() const;
	///< For allocated colors, returns the value used to draw this color on the screen.

	void get(unsigned short& r, unsigned short& g, unsigned short& b) const;
	///< Returns the red, green and blue component values.
	///< @param r The location to store the red component, a value between 0 and 65535.
	///< @param g The location to store the green component.
	///< @param b The location to store the blue component.

	bool equal(const Color& other) const;
	///< Compares this color with <EM>other</EM>.
	///< @param other The color to compare.
	///< @return <EM>true</EM> if the two colors compare equal.

	bool operator==(const Color& other);
	///< Equality operator; compares this color with <EM>other</EM>.
	///< @param other The color to compare.
	///< @return <EM>true</EM> if the two colors compare equal.

	bool operator!=(const Color& other);
	///< Inequality operator; compares this color with <EM>other</EM>.
	///< @param other The color to compare.
	///< @return <EM>true</EM> if the two colors compare unequal.

/// @}
/// @name Methods
/// @{

 	void red(double r);
	///< Sets the red component of the color.
	///< @param r The red component, a value between 0 and 1.

	void green(double g);
	///< Sets the green component of the color.
	///< @param g The green component, a value between 0 and 1.

	void blue(double b);
	///< Sets the blue component of the color.
	///< @param b The blue component, a value between 0 and 1.

	void set_red(unsigned short r);
	///< Sets the red component of the color.
	///< @param r The red component, a value between 0 and 65535.

	void set_green(unsigned short g);
	///< Sets the green component of the color.
	///< @param g The green component, a value between 0 and 65535.

	void set_blue(unsigned short b);
	///< Sets the blue component of the color.
	///< @param b The blue component, a value between 0 and 65535.

	void set_pixel(unsigned long p);
	///< Sets the pixel value.
	///< @param p The pixel value.

	void set_grey(unsigned short value);
	///< Sets a greyscale color by setting the red, green and blue components to <EM>value</EM>.
	///< @param value A value between 0 and 65535.

	void set(unsigned short r, unsigned short g, unsigned short b);
	///< Sets the red, green and blue components to the specified values.
	///< @param r The red component of the color, a value between 0 and 65535.
	///< @param g The green component of the color.
	///< @param b The blue component of the color.

	bool parse(const char *spec);
	///< Parses a textual specification of a color and fills in the red, green, and blue fields.
	///< @param spec The string specifying the color.
	///< @return <EM>true</EM> if the parsing succeeded.
	///<
	///< The color is not allocated, you must call allocate() or Gdk::Colormap::alloc_color()
	///< yourself. The text string can be in any of the forms accepted by XParseColor; these 
	///< include the name for a color from rgb.txt, such as DarkSlateGray, or a hex specification
	///< such as 305050.

	unsigned int hash() const;
	///< A hash function suitable for using for a hash table that stores Gdk::Color's.
	///< @return The hash function applied to this color.

	bool allocate(const Screen *screen = 0);
	///< Allocates the color as read-only and best match, using the default
	///< system colormap for <EM>screen</EM>.
	///< @param screen The Screen to use, or null for the default screen.

	void free(const Screen *screen = 0);
	///< Frees a color previously allocated by allocate(), using the default
	///< system colormap for <EM>screen</EM>.
	///< @param screen The Screen to use, or null for the default screen.

/// @}
};

/// @class Colormap color.hh xfc/gdk/color.hh
/// @brief A GdkColormap C++ wrapper class.
///
/// A colormap is an object that contains the mapping between the color values
/// stored in memory and the RGB values that are used to display color values.
/// In general, colormaps only contain significant information for pseudo-color
/// visuals, but even for other visual types, a colormap object is required in
/// some circumstances.
///
/// There are a couple of special colormaps that can be retrieved. The system
/// colormap (retrieved with get_system()) is the default colormap of the 
/// system. There is another colormap that was important - the colormap in which
/// GdkRGB works, retrieved with gdk_rgb_get_colormap(). Historically you had to
/// use this colormap for all RGB functions because RGB could only render to
/// this colormap. Since GTK+-2.2 RGB can render to any colormap and visual, 
/// so there is no need to call this function, and it hasn't been wrapped. Note
/// when using GdkRGB, it is not generally necessary to allocate colors directly.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Colormap : public G::Object
{
	friend class G::Object;

	Colormap(const Colormap&);
	Colormap& operator=(const Colormap&);
	
protected:
/// @name Constructors
/// @{

	explicit Colormap(GdkColormap *colormap, bool owns_reference = true);
	///< Construct a new Colormap from an existing GdkColormap.
	///< @param colormap A pointer to a GdkColormap.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>colormap</EM> can be a newly created GdkColormap or an existing
	///< GdkColormap. (see G::Object::Object).

/// @}
	
public:
	typedef GdkColormap CObjectType;

/// @name Constructors
/// @{

	Colormap(const Visual& visual, bool allocate = false);
	///< Constructs a new colormap for the given visual with a reference count of 1 that the caller owns.
	///< @param visual A Visual.
	///< @param allocate If <EM>true</EM>, the newly created colormap will be a private
	///< colormap, and all colors in it will be allocated for the applications use.
	
	virtual ~Colormap();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	static Colormap* get_system(const Screen *screen = 0);
	///< Gets the system's default colormap for <EM>screen</EM>.
	///< @param screen The Screen to use, or null for the default screen.
	///< @return The default system colormap for <EM>screen</EM>,

/// @}
/// @name Accessors
/// @{

	GdkColormap* gdk_colormap() const;
	///< Get a pointer to the GdkColormap structure.

	operator GdkColormap* () const;
	///< Conversion operator; safely converts a Colormap to a GdkColormap pointer.

	const Visual* get_visual() const;
	///< Gets the visual for which this colormap was created.
	///< @return The visual of the colormap.

	Screen* get_screen() const;
	///< Gets the screen for which this colormap was created.
	///< @return The screen for which the colormap was created.

/// @}
/// @name Methods
/// @{

	bool alloc_color(Color& color, bool best_match = true, bool writeable = false);
	///< Allocates a single color from a colormap.
	///< @param color The color to allocate. 
	///< @param best_match If <EM>true</EM>, GDK will attempt to do matching against existing
	///<                   colors if the colors cannot be allocated as requested.
	///< @param writeable If <EM>true</EM>, the colors are allocated writeable.
	///< @return <EM>true</EM> if the allocation succeeded.
	///<
	///< On return the color's pixel field will be filled in if allocation succeeds.
	///< Writeable colors cannot be shared between applications.

	int alloc_colors(const std::vector<Color>& colors, std::vector<bool>& successes, bool best_match = true, bool writeable = false);
	///< Allocates colors from the colormap.
	///< @param colors A reference to a vector of Color that holds the color values to allocate.
	///< @param successes A reference to a vector of bool to hold the allocation success/failure.
	///< @param best_match If <EM>true</EM>, GDK will attempt to do matching against existing
	///<                   colors if the colors cannot be allocated as requested.
	///< @param writeable If <EM>true</EM>, the colors are allocated writeable.
	///< @return The number of colors that were not sucessfully allocated.
	///<
	///< On return, the pixel values for the allocated colors will be filled in. If the return
	///< value is 0, all colors were successfully allocated and <EM>successes</EM> was ignored
	///< (i.e. not filled in). If there are any unallocated colors <EM>successes</EM> will be filled
	///< in with the success/failure of each color allocation, in the same order the colors appear
	///< in <EM>colors</EM>. Writable colors can have their values changed later using change(), and
	///< cannot be shared between applications.

	void free_color(const Color& color);
	///< Frees a previously allocated color.
	///< @param color The Color to free.

	void free_colors(const std::vector<Color>& colors);
	///< Frees previously allocated colors.
	///< @param colors A reference to a vector of Color that holds the colors to free.

	void query_color(unsigned long pixel, Color& result) const;
	///< Locates the RGB color in the colormap corresponding to the given hardware pixel <EM>pixel</EM>.
	///< @param pixel The pixel value in hardware display format.
	///< @param result A Color with the red, green and blue fields initialized.
	///<
	///< <EM>pixel</EM> must be a valid pixel in the colormap; it's a programmer error to call this
	///< method with a pixel which is not in the colormap. Hardware pixels are normally obtained from
	///< alloc_colors(), or from a Gdk::Image. (A Gdk::Image contains image data in hardware format, a
	///< Gdk::Pixbuf contains image data in a canonical 24-bit RGB format.)
	///<
	///< This method is rarely useful; it's used for example to implement the eyedropper feature in
	///< Gtk::ColorSelection.

	Color query_color(unsigned long pixel) const;
	///< Locates the RGB color in the colormap corresponding to the given hardware pixel <EM>pixel</EM>.
	///< @param pixel The pixel value in hardware display format.
	///< @return A Color with the red, green and blue fields initialized.
	///<
	///< <EM>pixel</EM> must be a valid pixel in the colormap; it's a programmer error to call this
	///< method with a pixel which is not in the colormap. Hardware pixels are normally obtained from
	///< alloc_colors(), or from a Gdk::Image. (A Gdk::Image contains image data in hardware format, a
	///< Gdk::Pixbuf contains image data in a canonical 24-bit RGB format.)
	///<
	///< This method is rarely useful; it's used for example to implement the eyedropper feature in
	///< Gtk::ColorSelection.

/// @}
/// @name RGB Methods
/// @{

	void rgb_find_color(Color& color) const;
	///< Finds the best matching color for <EM>color</EM> in the colormap.
	///< @param color A color.
	///<
	///< <EM>colormap</EM> should be the colormap for the graphics context and drawable
	///< you're using to draw. If you're drawing to a Gtk::Widget, call Gtk::Widget::get_colormap().
	///< <EM>color</EM> should have its red, green, and blue fields initialized; rgb_find_color() 
	///< will fill in the pixel field with the best matching pixel from a color cube. The color is
	///< then ready to be used for drawing, e.g. you can call Gdk::GC::set_foreground() which 
	///< expects pixel to be initialized.
	///<
	///< In many cases, you can avoid this whole issue by calling Gdk::GC::set_rgb_fg_color() or 
	///< Gdk::GC::set_rgb_bg_color(), which do not expect pixel to be initialized in advance.
	///< If you use those methods, there's no need for rgb_find_color().

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/color.inl>

#endif // XFC_GDK_COLORMAP_HH

