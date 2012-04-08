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
 
/// @file xfc/gtk/image.hh
/// @brief A GtkImage C++ wrapper interface.
///
/// Provides Image, a widget that can dispay various kinds of objects as an image.
/// Most typically, you would load a Gdk::Pixbuf from a file, and then display that.

#ifndef XFC_GTK_IMAGE_HH
#define XFC_GTK_IMAGE_HH

#ifndef XFC_GTK_MISC_HH
#include <xfc/gtk/misc.hh>
#endif

#ifndef __GTK_IMAGE_H__
#include <gtk/gtkimage.h>
#endif

#ifndef __GTK_STOCK_H__
#include <gtk/gtkstock.h>
#endif

namespace Xfc {

namespace Gdk {
class Image;
class Pixbuf;
class PixbufAnimation;
class Pixmap;
}

namespace Gtk {

class IconSet;

// @enum Gtk::ImageType
/// Describes the image data representation used by a GtkImage. If you want to get the
/// image from the widget, you can only get the currently-stored representation. e.g.
/// if the get_storage_type() returns IMAGE_PIXBUF, then you can call get_pixbuf() but
/// not get_stock(). For empty images, you can request any storage type (call any of
/// the "get" functions), but they will all return null values.

enum ImageType
{
	IMAGE_EMPTY = GTK_IMAGE_EMPTY, ///< There is no image displayed by the widget.
	IMAGE_PIXMAP = GTK_IMAGE_PIXMAP, ///< The widget contains a Gdk::Pixmap.
	IMAGE_IMAGE = GTK_IMAGE_IMAGE, ///< The widget contains a Gdk::Image.
	IMAGE_PIXBUF = GTK_IMAGE_PIXBUF, ///< The widget contains a Gdk::Pixbuf.
	IMAGE_STOCK = GTK_IMAGE_STOCK, ///< The widget contains a stock icon name.
	IMAGE_ICON_SET = GTK_IMAGE_ICON_SET, ///< The widget contains a Gtk::IconSet.
	IMAGE_ANIMATION = GTK_IMAGE_ANIMATION, ///< The widget contains a Gdk::PixbufAnimation.
	IMAGE_ICON_NAME = GTK_IMAGE_ICON_NAME ///< The widget contains an image from the current icon theme. 
};

/// @class Image image.hh xfc/gtk/image.hh
/// @brief A GtkImage C++ wrapper class.
///
/// The Image widget displays an image. Various kinds of objects can be displayed as an image;
/// most typically, you would load a Gdk::Pixbuf from a file, and then display that. There's
/// a convenience constructor to do this, used as follows:
/// @code
/// Gtk::Image *image = new Gtk::Image("myfile.png");
/// @endcode
/// 
/// If the file isn't loaded successfully, the image will contain a "broken image" icon similar
/// to that used in many web browsers. If you want to handle errors in loading the file yourself,
/// for example by displaying an error message, then load the image as a Gdk::Pixbuf, then create
/// the Image with the pixbuf, like this:
/// @code
/// G::Error error;
/// Pointer<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create("myfile.png", &error);
/// if (error.get())
/// {
/// 	display_some_message();
/// }
/// else
/// {
/// 	Gtk::Image *image = new Gtk::Image(pixbuf);
/// }
/// @endcode
///
/// A Gdk::Pixbuf smart pointer is used because the new pixbuf must be unreferecned. You don't need
/// to hold on to a reference, the Image will do that.
///
/// The image file may contain an animation, if so the Image will display an animation
/// (Gdk::PixbufAnimation) instead of a static image. Image is a subclass of Misc, which implies that
/// you can align it (center, left, right) and add padding to it, using Misc methods. Image is a 
/// "no window" widget (has no Gdk::Window of its own), so by default does not receive events. If you
/// want to receive events on the image, such as button clicks, place the image inside an EventBox,
/// then connect to the event signals on the event box.
///
/// <B>Example:</B> Handling button press events on an Image.
/// @code
/// #include <xfc/main.hh>
/// #include <xfc/gtk/image.hh>
/// #include <xfc/gtk/eventbox.hh>
/// #include <xfc/gtk/window.hh>
/// #include <xfc/bind.hh>
///
/// using namespace Xfc;
///
/// class Window : public Gtk::Window
/// {
/// protected:
/// 	bool on_image_button_press(GdkEventButton *event, Gtk::Image *image);
/// public:
/// 	Window();
/// };
///
/// Window::Window()
/// {
/// 	set_title("Basic Window");
///
/// 	// Create the event box and image.
/// 	Gtk::EventBox *event_box = new Gtk::EventBox;
/// 	Gtk::Image *image = new Gtk::Image("myfile.png");
///
/// 	// If you have more than one image you could bind the new image to the slot, like this.
/// 	event_box->signal_button_press_event().connect(bind(slot(this, &Window::on_image_button_press), image));
///
/// 	// Add the image to the event box and then the event box to the window.
/// 	event_box->add(*image);
/// 	add(*event_box);
///
/// 	event_box->show_all();
/// 	show();
/// }
///
/// bool
/// Window::on_image_button_press(GdkEventButton *event, Gtk::Image *image)
/// {
/// 	g_print ("Event box clicked at coordinates %.0f,%.0f\n", event->x, event->y);
///
/// 	// The event was handled so return true to stop any further signal emission.
/// 	return true;
/// }
///
/// int main (int argc, char *argv[])
/// {
/// 	using namespace Main;
///
/// 	init(&argc, &argv);
///
/// 	Window window;
/// 	window.signal_destroy().connect(slot(&Xfc::Main::quit));
///
/// 	run();
/// 	return 0;
/// }
/// @endcode
///
/// When handling events on the event box, keep in mind that coordinates in the image may
/// be different from event box coordinates due to the alignment and padding settings on
/// the image (see Misc). The simplest way to solve this is to set the alignment to 0.0
/// (left/top), and set the padding to zero. Then the origin of the image will be the same
/// as the origin of the event box. 
///
/// Sometimes an application will want to avoid depending on external data files, such as
/// image files. GTK+ comes with a program to avoid this, called gdk-pixbuf-csource. This
/// program allows you to convert an image into a C variable declaration, which can then be
/// passed to the Gdk::Pixbuf constructor:
/// @code
/// Pixbuf(int stream_length, const unsigned char *stream, bool copy_pixels, G::Error *error = 0);
/// @endcode
///
/// <B>See also:</B> the <A HREF="../../howto/html/images.html">Image Widget</A> HOWTO.

class Image : public Misc
{
	friend class G::Object;

	Image(const Image&);
	Image& operator=(const Image&);
	
protected:
/// @name Constructors
/// @{

	explicit Image(GtkImage *image, bool owns_reference = false);
	///< Construct a new Image from an existing GtkImage.
	///< @param image A pointer to a GtkImage.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>image</EM> can be a newly created GtkImage or an existing
	///< GtkImage (see G::Object::Object).

/// @}

public:
	typedef GtkImage CObjectType;

/// @name Constructors
/// @{

	Image();
	///< Construct an empty Image.

	Image(Gdk::Pixmap& pixmap, Gdk::Bitmap& mask);
	///< Constructs an Image widget displaying a pixmap with a mask.
	///< @param pixmap A Gdk::Pixmap.
	///< @param mask A Gdk::Bitmap.
	///<
	///< The Image does not assume a reference to the pixmap or mask; you still
	///< need to unref them if you own references. Image will add its own reference
	///< rather than adopting yours.

	Image(Gdk::Image& image, Gdk::Bitmap& mask);
	///< Construct an Image widget displaying a image with a mask.
	///< @param image A Gdk::Image.
	///< @param mask A Gdk::Bitmap.
	///<
	///< An Image is a client-side image buffer in the pixel format of the current display.
	///< The Image does not assume a reference to the image or mask; you still need to unref 
	///< them if you own references. Image will add its own reference rather than adopting yours.

	explicit Image(const char *filename);
	explicit Image(const String& filename);
	///< Construct a new Image displaying the file <EM>filename</EM>.
	///< @param filename A filename.
	///<
	///< If the file isn't found or can't be loaded, the resulting Image will display a
	///< "broken image" icon. If the file contains an animation, the image will contain
	///< an animation. If you need to detect failures to load the file, use Gdk::Pixbuf
	///< to load the file yourself, then create the Image from the pixbuf. (Or for
	///< animations, use Gdk::PixbufAnimation. The storage type (get_storage_type()) of
	///< the Image is not defined, it will be whatever is appropriate for displaying the
	///< file.

	explicit Image(Gdk::Pixbuf& pixbuf);
	///< Construct a new Image displaying pixbuf.
	///< @param pixbuf A Gdk::Pixbuf.
	///<
	///< The Image does not assume a reference to the pixbuf; you still need to unref it
	///< if you own references. Image will add its own reference rather than adopting yours.
	///< Note that this method just creates an Image from the pixbuf. The Image created will
	///< not react to state changes. Should you want that, you should use an IconSet.

	explicit Image(const char **xpm_data);
	///< Construct a new Image by parsing XPM data in memory.
	///< @param xpm_data A pointer to inline XPM data.
	///<
	///< The xpm_data is commonly the result of including an XPM file into a program's
	///< C source. This method creates a new GdkPixbuf by parsing XPM data in memory and 
	///< then constructs the Image from the pixbuf.

	Image(const StockId& stock_id, IconSize size);
	///< Construct an Image displaying a stock icon.
	///< @param stock_id A stock icon ID.
	///< @param size A stock icon size.
	///<
	///< Sample stock icon names are Gtk:StockId::OPEN, Gtk:StockId::EXIT. Sample stock
	///< sizes are ICON_SIZE_MENU, ICON_SIZE_SMALL_TOOLBAR. If the stock icon name isn't
	///< known, a "broken image" icon will be displayed instead. You can register your own
	///< stock icon names, see Gtk::IconFactory::add_default() and Gtk::IconFactory::add().
	
	Image(IconSet& icon_set, IconSize size);
	///< Construct an Image displaying an icon set.
	///< @param icon_set An IconSet.
	///< @param size A stock icon size.
	///<
	///< Sample stock sizes are ICON_SIZE_MENU, ICON_SIZE_SMALL_TOOLBAR. Instead of
	///< using this method, usually it's better to create an IconFactory, put your icon
	///<  sets in the icon factory, add the icon factory to the list of default factories
	///< with Gtk::IconFactory::add_default(), and then contruct the Image from the stock
	///< ID and icon size. This will allow themes to override the icon you ship with your
	///< application. The Image does not assume a reference to the icon set; you still need
	///< to unref it if you own references. Image will add its own reference rather than
	///< adopting yours.

	explicit Image(Gdk::PixbufAnimation& animation);
	///< Construct an Image displaying the given animation.
	///< @param animation An animation.
	///<
	///< The Image does not assume a reference to the animation; you still need to unref it
	///< if you own references. Image will add its own reference rather than adopting yours.

	Image(const char *icon_name, IconSize size);
	Image(const String& icon_name, IconSize size);
	///< Construct an Image displaying an icon from the current icon theme. 
	///< @param icon_name An icon name. 
	///< @param size A stock icon size. 
	///< 	
	///< If the icon name isn't known, a "broken image" icon will be displayed instead.
	///< If the current icon theme is changed, the icon will be updated appropriately.

	virtual ~Image();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkImage* gtk_image() const;
	///< Get a pointer to the GtkImage structure.

	operator GtkImage* () const;
	///< Conversion operator; safely converts an Image to a GtkImage pointer.

	ImageType get_storage_type() const;
	///< Gets the type of representation being used by the Image to store image data.
	///< @return The image representation being used.
	///<
	///< If the GtkImage has no image data, the return value will be IMAGE_EMPTY.
	
	void get_pixmap(Gdk::Pixmap **pixmap, Gdk::Bitmap **mask) const;
	///< Gets the pixmap and mask being displayed by the Image. 
	///< @param pixmap The location to store the pixmap, or null.
	///< @param mask The location to store the mask, or null.
	///<
	///< The storage type of the image must be IMAGE_EMPTY or IMAGE_PIXMAP
	///< (see get_storage_type()). The caller of this function does not own
	///< a reference to the returned pixmap and mask.

	void get_image(Gdk::Image **gdk_image, Gdk::Bitmap **mask) const;
	///< Gets the Gdk::Image and mask being displayed by the Image.
	///< @param gdk_image The return location for the Gdk::Image.
	///< @param mask The return location for the Gdk::Bitmap.
	///<
	///<  The storage type of the image must be IMAGE_EMPTY or IMAGE_IMAGE 
	///< (see get_storage_type()). The caller of this method does not own a 
	///< reference to the returned image and mask.

	Gdk::Pixbuf* get_pixbuf() const;
	///< Gets the Gdk::Pixbuf being displayed by the Image.
	///< @return The displayed pixbuf, or null if the image is empty.
	///<
	///< The storage type of the image must be IMAGE_EMPTY or IMAGE_PIXBUF
	///< (see get_storage_type()). The caller of this function does not own a
	///< reference to the returned pixbuf.

	void get_stock(StockId *stock_id, IconSize *size) const;
	///< Gets the stock icon name and size being displayed by the Image.
	///< @param stock_id The place to store the stock icon ID.
	///< @param size The place to store the stock icon size.
	///<
	///< The storage type of the image must be IMAGE_EMPTY or IMAGE_STOCK
	///< (see get_storage_type()). In the version of this function that sets
	///< a char* string, the string is owned by the Image and should not be freed.

	void get_icon_set(Pointer<IconSet> *icon_set, IconSize *size) const;
	///< Gets the icon set and size being displayed by the Image.
	///< @param icon_set An IconSet smart pointer to store a pointer to the IconSet.
	///< @param size The location to store a stock icon size.
	///<
	///< The storage type of the image must be IMAGE_EMPTY or IMAGE_ICON_SET (see get_storage_type()).

	Gdk::PixbufAnimation* get_animation() const;
	///< Gets the Gdk::PixbufAnimation being displayed by the Image. 
	///< @return The displayed animation, or null if the image is empty.
	///<
	///< The storage type of the image must be IMAGE_EMPTY or IMAGE_ANIMATION
	///< (see get_storage_type()). The caller of this method does not own a reference
	///< to the returned animation.

	void get_icon_name(String& icon_name, IconSize *size) const;
	///< Gets the icon name and size being displayed by the GtkImage. 
	///< @param icon_name A String to hold the icon name. 
	///< @param size A place to store the icon size.
	///< 	
	///< The storage type of the image must be Gtk::IMAGE_EMPTY or Gtk::IMAGE_ICON_NAME
	///< (see get_storage_type()).
		
	int get_pixel_size() const;
	///< Gets the pixel size used for named icons.
	///< @return The pixel size used for named icons.
	
/// @}
/// @name Methods
/// @{

	void set(Gdk::Pixmap *pixmap, Gdk::Bitmap *mask);
	///< Set the pixmap and mask to be displayed by the Image.
	///< @param pixmap A Gdk::Pixmap, or null.
	///< @param mask A Gdk::Bitmap, or null.
	///<
	///< The Image does not assume a reference to the pixmap or mask; you still
	///< need to unref them if you own references. Image will add its own reference
	///< rather than adopting yours.

	void set(Gdk::Image *image, Gdk::Bitmap *mask);
	///< Set the image and mask to be displayed by the Image.
	///< @param image A Gdk::Image, or null.
	///< @param mask A Gdk::Bitmap, or null.
	///<
	///< An Image is a client-side image buffer in the pixel format of the current display.
	///< The Image does not assume a reference to the image or mask; you still need to unref 
	///< them if you own references. Image will add its own reference rather than adopting yours.

	void set(const char* filename);
	void set(const String& filename);
	///< Set the file to be displayed by the Image.
	///< @param filename The name of the file to display.
	///<
	///< If the file isn't found or can't be loaded, the resulting Image will display a
	///< "broken image" icon. If the file contains an animation, the image will contain
	///< an animation. If you need to detect failures to load the file, use Gdk::Pixbuf
	///< to load the file yourself, then create the Image from the pixbuf. (Or for
	///< animations, use Gdk::PixbufAnimation. The storage type (get_storage_type()) of
	///< the Image is not defined, it will be whatever is appropriate for displaying the
	///< file.

	void set(Gdk::Pixbuf *pixbuf);
	///< Set the pixbuf to be displayed by the Image.
	///< @param pixbuf A Gdk::Pixbuf, or null.
	///<
	///< The Image does not assume a reference to the pixbuf; you still need to unref it
	///< if you own references. Image will add its own reference rather than adopting yours.
	///< Note that this method just creates an Image from the pixbuf. The Image created will
	///< not react to state changes. Should you want that, you should use an IconSet.

	void set(const StockId& stock_id, IconSize size);
	///< Set the stock icon name and size to be displayed by the Image.
	///< @param stock_id The stock icon ID.
	///< @param size The stock icon size.
	///<
	///< The storage type of the image must be IMAGE_EMPTY or IMAGE_STOCK
	///< (see get_storage_type()).

	void set(Gtk::IconSet *icon_set, IconSize size);
	///< Set the icon set and icon size to be displayed by the image.
	///< @param icon_set An IconSet.
	///< @param size A stock icon size.
	///<
	///< Sample stock sizes are ICON_SIZE_MENU, ICON_SIZE_SMALL_TOOLBAR. Instead of
	///< using this method, usually it's better to create an IconFactory, put your icon
	///<  sets in the icon factory, add the icon factory to the list of default factories
	///< with Gtk::IconFactory::add_default(), and then contruct the Image from the stock
	///< ID and icon size. This will allow themes to override the icon you ship with your
	///< application. The Image does not assume a reference to the icon set; you still need
	///< to unref it if you own references. Image will add its own reference rather than
	///< adopting yours.

	void set(Gdk::PixbufAnimation& animation);
	///< Set the animation to be displayed by the image.
	///< @param animation An animation.
	///<
	///< The Image does not assume a reference to the animation; you still need to unref it
	///< if you own references. Image will add its own reference rather than adopting yours.
	
	void set(const char *icon_name, IconSize size);
	void set(const String& icon_name, IconSize size);
	///< Set the icon to be displayed by the image from an icon name in the current icon theme. 
	///< @param icon_name An icon name. 
	///< @param size A stock icon size. 
	///< 	
	///< If the icon name isn't known, a "broken image" icon will be displayed instead.
	///< If the current icon theme is changed, the icon will be updated appropriately.

	void reset();
	///< Clears the image and resets its size to zero width and height. After calling this
	///< this method the actual image size will be the xpad and ypad values set by calling
	///< Gtk::Misc::set_padding().

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/image.inl>

#endif // XFC_GTK_IMAGE_HH

