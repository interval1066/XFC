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
 
/// @file xfc/gdk/visual.hh
/// @brief A GdkVisual C++ wrapper interface.
///
/// Provides Visual, an object that describes a particular video hardware display format.

#ifndef XFC_GDK_VISUAL_HH
#define XFC_GDK_VISUAL_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {

/// @enum VisualType
/// A set of values that describe the manner in which the pixel values
/// for a visual are converted into RGB values for display.

enum VisualType
{
	VISUAL_STATIC_GRAY = GDK_VISUAL_STATIC_GRAY,
	///< Each pixel value indexes a grayscale value directly.
	
	VISUAL_GRAYSCALE = GDK_VISUAL_GRAYSCALE,
	///< Each pixel is an index into a color map that maps pixel values into
	///< grayscale values (the color map can be changed by an application).
	
	VISUAL_STATIC_COLOR = GDK_VISUAL_STATIC_COLOR,
	///< Each pixel value is an index into a predefined, unmodifiable
	///< color map that maps pixel values into RGB values.
	
	VISUAL_PSUEDO_COLOR = GDK_VISUAL_PSEUDO_COLOR,
	///< Each pixel is an index into a color map that maps pixel values
	///< into rgb values (the color map can be changed by an application).
	
	VISUAL_TRUE_COLOR = GDK_VISUAL_TRUE_COLOR,
	///< Each pixel value directly contains red, green, and blue components
	///< (The red_mask, green_mask, and blue_mask fields of the GdkVisual
	///< structure describe how the components are assembled into a pixel value).

	VISUAL_DIRECT_COLOR = GDK_VISUAL_DIRECT_COLOR
	///< Each pixel value contains red, green, and blue components as for
	///< GDK_TRUE_COLOR, but the components are mapped via a color table
	///< into the final output table instead of being converted directly.
};

/// @class Visual visual.hh xfc/gdk/visual.hh
/// @brief A GdkVisual C++ wrapper class.
///
/// A Visual describes a particular video hardware display format. It includes information
/// about the number of bits used for each color, the way the bits are translated into an
/// RGB value for display, and the way the bits are stored in memory. For example, a piece
/// of display hardware might support 24-bit color, 16-bit color, or 8-bit color; meaning
/// 24/16/8-bit pixel sizes. For a given pixel size, pixels can be in different formats;
/// for example the "red" element of an RGB pixel may be in the top 8 bits of the pixel,
/// or may be in the lower 4 bits.
///
/// Usually you can avoid thinking about visuals in GTK+. Visuals are useful to interpret
/// the contents of a Gdk::Image, but you should avoid Gdk::Image precisely because its
/// contents depend on the display hardware; use Gdk::Pixbuf instead, for all but the 
/// most low-level purposes. Also, anytime you provide a Gdk::Colormap, the visual is
/// implied as part of the colormap (Gdk::Colormap::get_visual()), so you won't have to
/// provide a visual in addition.
///
/// There are several standard visuals. The visual returned by get_system() is the system's
/// default visual. A number of methods are provided for determining the "best" available
/// visual. For the purposes of making this determination, higher bit depths are considered
/// better, and for visuals of the same bit depth, VISUAL_PSEUDO_COLOR is preferred at 8bpp,
/// otherwise, the visual types are ranked in the order of (highest to lowest)
/// VISUAL_DIRECT_COLOR, VISUAL_TRUE_COLOR, VISUAL_PSEUDO_COLOR, VISUAL_STATIC_COLOR, 
/// VISUAL_GRAYSCALE, then VISUAL_STATIC_GRAY.

class Visual : public G::Object
{
	friend class G::Object;

	Visual(const Visual&);
	Visual& operator=(const Visual&);

protected:
/// @name Constructors
/// @{

	explicit Visual(GdkVisual *visual, bool owns_reference = true);
	///< Construct a new Visual from an existing GdkVisual.
	///< @param visual A pointer to a GdkVisual.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>visual</EM> can be a newly created GdkVisual or an existing
	///< GdkVisual. (see G::Object::Object).

/// @}

public:
	typedef GdkVisual CObjectType;

/// @name Constructors
/// @{

	virtual ~ Visual();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GdkVisual* gdk_visual() const;
	///< Get a pointer to the GdkVisual structure.

	operator GdkVisual* () const;
	///< Conversion operator; safely converts a Visual to a GdkVisual pointer.

	VisualType type() const;
	///< Returns the type of this visual.

	int depth() const;
	///< Returns the number of bits per pixel.

	ByteOrder byte_order() const;
	///< Returns the byte-order for this visual.

	int colormap_size() const;
	///< Returns the number of entries in the colormap, for visuals of type 
	///< VISUAL_PSEUDO_COLOR or VISUAL_GRAY_SCALE, for other visual types, 
	///< it is the number of possible levels per color component. If the 
	///< visual has different numbers of levels for different components,
	///< the value of this field is undefined.

	int bits_per_rgb() const;
	///< Returns the number of significant bits per red, green, or blue when specifying
	///< colors for this visual (for instance, for Gdk::Colormap::alloc_color()).

	unsigned int red_mask() const;
	///< Returns a mask giving the bits in a pixel value that correspond to the red field.
	///< Significant only for VISUAL_PSEUDOCOLOR and VISUAL_DIRECTCOLOR.

	int red_shift() const;
	///< Returns the red_shift. The red_shift() and red_prec() give an alternate presentation
	///< of the information in red_mask(). The <EM>red_mask</EM> is a contiguous sequence of
	///< <EM>red_prec</EM> bits starting at bit number <EM>red_shift</EM>. 
	///< 
	///< <B>Example:</B> Constructing a pixel value out of three 16 bit color values.
	///< @code
	///< unsigned int
	///< pixel_from_rgb(const Gdk::Visual& visual, unsigned short r, unsigned short b, unsigned short g)
	///< {
	///< 	return ((r >> (16 - visual.red_prec()))   << visual->red_shift()) |
	///< 	       ((g >> (16 - visual.green_prec())) << visual->green_shift()) |
	///< 	       ((r >> (16 - visual.blue_prec()))  << visual->blue_shift());
	///< }
	///< @endcode

	int red_prec() const;
	///< Returns the red_prec (see red_shift()).

	unsigned int green_mask() const;
	///< Returns a mask giving the bits in a pixel value that correspond to the green field.

	int green_shift() const;
	///< Returns the green_shift. The green_shift and green_prec give an alternate presentation
	///< of the information in green_mask (see example in red_shift()).

	int green_prec() const;
	///< Returns the green_prec (see green_shift()).

	unsigned int blue_mask() const;
	///< Returns a mask giving the bits in a pixel value that correspond to the blue field.
	
	int blue_shift() const;
	///< Returns the blue_shift. The blue_shift and blue_prec give an alternate presentation
	///< of the information in blue_mask (see example in red_shift()).

	int blue_prec() const;
	///< Returns the blue_prec (see blue_shift()).

	int get_best_depth() const;
	///< Get the best available depth for the default Gdk::Screen.
	///< @return The best available depth.
	///<
	///< "Best" means "largest," i.e. 32 preferred over 24 preferred over 8 bits per pixel.

	VisualType get_best_type() const;
	///< Return the best available visual type for the default Gdk::Screen.
	///< @return The best visual type.

/// @}
/// @name Accessors
/// @{
	
	static const Visual* get_best();
	///< Returns the visual with the most available colors for the default Gdk::Screen.

	static const Visual* get_best(int depth);
	///< Get the best visual with depth <EM>depth</EM> for the default Gdk::Screen.
	///< @param depth A bit depth.
	///< @return The best visual for the given depth, or null if no visual supports <EM>depth</EM>.
	///<
	///< Color visuals and visuals with mutable colormaps are preferred over
	///< grayscale or fixed-colormap visuals. Null may be returned if no visual supports depth.
	
	static const Visual* get_best(VisualType visual_type);
	///< Get the best visual of the given visual_type for the default Gdk::Screen.
	///< @param visual_type A visual type.
	///< @return The best visual of the given type; or null if no visual has type <EM>visual_type</EM>.
	///<
	///< Visuals with higher color depths are considered better. 
	
	static const Visual* get_best(int depth, VisualType visual_type);
	///< Get the best visual of the given <EM>visual_type</EM> with depth <EM>depth</EM>
	///< for the default Gdk::Screen.
	///< @param depth A bit depth.
	///< @param visual_type A visual type.
	///< @return The best visual with both <EM>depth</EM> and <EM>visual_type</EM>, or null if none.

	static const Visual* get_system();
	///< Returns the system's default visual for the default Gdk::Screen.
	///< This is the visual for the root window of the display.

/// @}
/// @name Methods
/// @{
	
	static std::vector<int> query_depths();
	///< This method returns the available bit depths for the default screen.
	///< @return A vector of int holding the available depths.
	///<
	///< It's equivalent to listing the visuals (list_visuals()) and then looking at the
	///< depth() field in each visual, removing duplicates.

	static bool query_visual_types(std::vector<VisualType>& visual_types);
	///< This method returns the available visual types for the default screen.
	///< @param visual_types A reference to a vector of VisualType to hold the available visual types.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< It's equivalent to listing the visuals (list_visuals()) and then looking at the
	///< type() field in each visual, removing duplicates.

	static bool list_visuals(std::vector<const Visual*>& visuals);
	///< Lists the available visuals for the default screen (see Gdk::Screen::list_visuals()).
	///< @param visuals A reference to a vector of const Visual* to hold the list of available visuals.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< A visual describes a hardware image data format. For example, a visual might support
	///< 24-bit color, or 8-bit color, and might expect pixels to be in a certain format.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/visual.inl>

#endif // XFC_GDK_VISUAL_HH

