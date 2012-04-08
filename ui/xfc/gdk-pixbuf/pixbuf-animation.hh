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

/// @file xfc/gdk-pixbuf/pixbuf-animation.hh
/// @brief A GdkPixbufAnimation and GdkPixbufAnimationIter C++ wrapper interface.
///
/// PixbufAnimationIter and PixbufAnimation provides a simple mechanism to load and display animations.

#ifndef XFC_GDK_PIXBUF_ANIMATION_HH
#define XFC_GDK_PIXBUF_ANIMATION_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef GDK_PIXBUF_H
#include <gdk-pixbuf/gdk-pixbuf.h>
#endif

namespace Xfc {

namespace G {
class Error;
}

namespace Gdk {

class Pixbuf;

/// @class PixbufAnimationIter pixbuf-animation.hh xfc/gdk-pixbuf/pixbuf-animation.hh
/// @brief A GdkPixbufAnimationIter C++ wrapper class.
///
/// PixbufAnimationIter provides the necessary functionality to display an animation
/// by providing the frames that should be displayed at a given time.

class PixbufAnimationIter : public G::Object
{
	friend class G::Object;

	PixbufAnimationIter(const PixbufAnimationIter&);
	PixbufAnimationIter& operator=(const PixbufAnimationIter&);

protected:
/// @name Constructors
/// @{

	explicit PixbufAnimationIter(GdkPixbufAnimationIter *iter, bool owns_reference = true);
	///< Construct a new PixbufAnimationIter from an existing GdkPixbufAnimationIter.
	///< @param iter A pointer to a GdkPixbufAnimationIter.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>iter</EM> can be a newly created GdkPixbufAnimationIter or an existing
	///< GdkPixbufAnimationIter. (see G::Object::Object).

/// @}

public:
	typedef GdkPixbufAnimationIter CObjectType;

/// @name Constructors
/// @{

	virtual ~PixbufAnimationIter();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GdkPixbufAnimationIter* gdk_pixbuf_animation_iter() const;
	///< Get a pointer to the GdkPixbufAnimationIter structure.

	operator GdkPixbufAnimationIter* () const;
	///< Conversion operator; safely converts a PixbufAnimationIter to a GdkPixbufAnimationIter pointer.

	int get_delay_time() const;
	///< Gets the number of milliseconds the current pixbuf should be displayed, or -1 if
	///< the current pixbuf should be displayed forever. 
	///< @return The delay time in milliseconds (thousandths of a second).
	///<
	///< g_timeout_add() conveniently takes a timeout in milliseconds, so you can use
	///< a timeout to schedule the next update.

	Pixbuf* get_pixbuf() const;
	///< Gets the current pixbuf which should be displayed; the pixbuf will be the same size as the
	///< animation itself (Gdk::PixbufAnimation::get_width(), Gdk::PixbufAnimation::get_height()).
	///< @return The pixbuf to be displayed.
	///<
	///< This pixbuf should be displayed for Gdk::PixbufAnimation::get_delay_time() milliseconds.
	///< The caller of this function does not own a reference to the returned pixbuf; the returned
	///< pixbuf will become invalid when the iterator advances to the next frame, which may happen
	///< anytime you call advance(). Copy the pixbuf to keep it (don't just add a reference), as it
	///< may get recycled as you advance the iterator.

	bool on_currently_loading_frame() const;
	///< Used to determine how to respond to the <EM>area_updated</EM> signal on PixbufLoader
	///< when loading an animation. 
	///< @return <EM>true</EM> if the frame we're on is partially loaded, or the last frame.
	///<
	///< The <EM>area_updated</EM> signal is emitted for an area of the frame 
	///< currently streaming in to the loader. So if you're on the currently 
	///< loading frame, you need to redraw the screen for the updated area.

/// @}
/// @name Methods
/// @{

	bool advance(const GTimeVal *current_time = 0);
	///< Possibly advances an animation to a new frame. Chooses the frame based on the start time
	///< passed to Gdk::PixbufAnimation::get_iter().
	///< @param current_time The current time, or null to automatically
	///<                     use the result of g_get_current_time().
	///< @return <EM>true</EM> if the image may need updating.
	///<
	///< The <EM>current_time</EM> would normally come from g_get_current_time(), and must
	///< be greater than or equal to the time passed to Gdk::PixbufAnimation::get_iter(), and
	///< must increase or remain unchanged each time get_pixbuf() is called. That is, you can't
	///< go backward in time; animations only play forward. As a shortcut, pass null for the
	///< current time and g_get_current_time() will be invoked on your behalf. So you only need
	///< to explicitly pass current_time if you're doing something odd like playing the 
	///< animation at double speed.
	///<
	///< If this method returns false, there's no need to update the animation display, assuming
	///< the display had been rendered prior to advancing; if true, you need to call get_pixbuf()
	///< and update the display with the new pixbuf.

/// @}
};

/// @class PixbufAnimation pixbuf-animation.hh xfc/gdk-pixbuf/pixbuf-animation.hh
/// @brief A GdkPixbufAnimation C++ wrapper class.
///
///< PixbufAnimation provides a simple mechanism to load and represent animations.
///< An animation is conceptually a series of frames to be displayed over time.
///< Each frame is the same size. The animation may not be represented as a series
///< of frames internally; for example, it may be stored as a sprite and instructions
///< for moving the sprite around a background. To display an animation you don't 
///< need to understand its representation, however; you just ask gdk-pixbuf what
///< should be displayed at a given point in time.

class PixbufAnimation : public G::Object
{
	friend class G::Object;

	PixbufAnimation(const PixbufAnimation&);
	PixbufAnimation& operator=(const PixbufAnimation&);

protected:
/// @name Constructors
/// @{

	explicit PixbufAnimation(GdkPixbufAnimation *pixbuf_animation, bool owns_reference = true);
	///< Construct a new PixbufAnimation from an existing GdkPixbufAnimation.
	///< @param pixbuf_animation A pointer to a GdkPixbufAnimation.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>pixbuf_animation</EM> can be a newly created GdkPixbufAnimation or an existing
	///< GdkPixbufAnimation. (see G::Object::Object).

/// @}

public:
	typedef GdkPixbufAnimation CObjectType;

/// @name Constructors
/// @{

	virtual ~PixbufAnimation();
	///< Destructor.

/// @}
/// @name Constructors
/// @{

	static Pointer<PixbufAnimation> create(const char *filename, G::Error *error);
	static Pointer<PixbufAnimation> create(const String& filename, G::Error *error);
	///< Constructs a new animation by loading it from a file.
	///< @param filename Ther name of file to load.
	///< @param error The return location for any error.
	///< @return A PixbufAnimation smart pointer.
	///<
	///< The file format is detected automatically. If the file's format
	///< does not support multi-frame images, then an animation with a single
	///< frame will be created. Possible errors are in the GDK_PIXBUF_ERROR
	///< and G_FILE_ERROR domains. Possible error conditions include: the file
	///< could not be opened, there was no loader for the file's format, there
	///< was not enough memory to allocate the image buffer, or the image file
	///< contained invalid data.

/// @}
/// @name Accessors
/// @{

	GdkPixbufAnimation* gdk_pixbuf_animation() const;
	///< Get a pointer to the GdkPixbufAnimation structure.

	operator GdkPixbufAnimation* () const;
	///< Conversion operator; safely converts a PixbufAnimation to a GdkPixbufAnimation pointer.

	int get_width() const;
	///< Returns the width of the bounding box of a pixbuf animation.

	int get_height() const;
	///< Returns the height of the bounding box of a pixbuf animation.

	bool is_static_image() const;
	///< If you load a file and it turns out to be a plain, unanimated image, then
	///< this method will return true. 
	///< @return <EM>true</EM> if the "animation" was really just an image.
	///<
	///< Use get_static_image() to retrieve the image.
	
	Pixbuf* get_static_image() const;
	///< If an animation is really just a plain image (has only one frame),
	///< this method returns that image. 
	///< @return An unanimated image representing the animation.
	///<
	///< If the animation is an animation, this function returns a reasonable thing
	///< to display as a static unanimated image, which might be the first frame, or
	///< something more sophisticated. If an animation hasn't loaded any frames yet,
	///< this function will return null.

	Pointer<PixbufAnimationIter> get_iter(const GTimeVal *start_time = 0) const;
	///< Get an iterator for displaying an animation. 
	///< @param start_time The time when the animation starts playing, or null to
	///<                   automatically use the result of g_get_current_time().
	///< @return An iterator to move over the animation
	///<
	///< The iterator provides the frames that should be displayed at a given time. 
	///< <EM>start_time</EM> would normally come from g_get_current_time(), and marks
	///< the beginning of animation playback. After creating an iterator, you should 
	///< immediately display the pixbuf returned by Gdk::PixbufAnimationIter::get_pixbuf().
	///< Then, you should install a timeout (with g_timeout_add()) or by some other mechanism
	///< to ensure that you'll update the image after Gdk::PixbufAnimationIter::get_delay_time()
	///< milliseconds. Each time the image is updated, you should reinstall the timeout with
	///< the new, possibly-changed delay time. As a shortcut, if start_time is null, the result
	///< of g_get_current_time() will be used automatically.
	///<
	///< To update the image (i.e. possibly change the result of Gdk::PixbufAnimationIter::get_pixbuf()
	///< to a new frame of the animation), call Gdk::PixbufAnimationIter::advance().
	///<
	///< If you're using PixbufLoader, in addition to updating the image after the delay time,
	///< you should also update it whenever you receive the <EM>area_updated</EM> signal and
	///< Gdk::PixbufAnimationIter::on_currently_loading_frame() returns true. In this case, 
	///< the frame currently being fed into the loader has received new data, so needs to be
	///< refreshed. The delay time for a frame may also be modified after an <EM>area_updated</EM>
	///< signal, for example if the delay time for a frame is encoded in the data after the frame
	///< itself. So your timeout should be reinstalled after any <EM>area_updated</EM> signal.
	///< A delay time of -1 is possible, indicating "infinite."

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk-pixbuf/inline/pixbuf-animation.inl>

#endif // XFC_GDK_PIXBUF_ANIMATION_HH

