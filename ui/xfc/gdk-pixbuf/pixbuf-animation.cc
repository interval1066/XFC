/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  pixbuf-animation.cc - GdkPixbufAnimationIter and GdkPixbufAnimation C++ wrapper interface
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

#include "pixbuf-animation.hh"
#include "pixbuf.hh"
#include "xfc/glib/error.hh"


using namespace Xfc;

/*  Gdk::PixbufAnimationIter
 */

Gdk::PixbufAnimationIter::PixbufAnimationIter(GdkPixbufAnimationIter *iter, bool owns_reference)
: G::Object((GObject*)iter, owns_reference)
{
}

Gdk::PixbufAnimationIter::~PixbufAnimationIter()
{
}

int
Gdk::PixbufAnimationIter::get_delay_time() const
{
	return gdk_pixbuf_animation_iter_get_delay_time(gdk_pixbuf_animation_iter());
}

Gdk::Pixbuf*
Gdk::PixbufAnimationIter::get_pixbuf() const
{
	return G::Object::wrap<Pixbuf>(gdk_pixbuf_animation_iter_get_pixbuf(gdk_pixbuf_animation_iter()));
}

bool
Gdk::PixbufAnimationIter::advance(const GTimeVal *current_time)
{
	return gdk_pixbuf_animation_iter_advance(gdk_pixbuf_animation_iter(), current_time);
}

/* Gdk::PixbufAnimation
 */

Gdk::PixbufAnimation::PixbufAnimation(GdkPixbufAnimation *pixbuf_animation, bool owns_reference)
: G::Object((GObject*)pixbuf_animation, owns_reference)
{
}

Gdk::PixbufAnimation::~PixbufAnimation()
{
}

Pointer<Gdk::PixbufAnimation>
Gdk::PixbufAnimation::create(const char *filename, G::Error *error)
{
	return G::Object::wrap_new<PixbufAnimation>(gdk_pixbuf_animation_new_from_file(filename, *error), true);
}

Pointer<Gdk::PixbufAnimation>
Gdk::PixbufAnimation::create(const String& filename, G::Error *error)
{
	return create(filename.c_str(), error);
}

Gdk::Pixbuf*
Gdk::PixbufAnimation::get_static_image() const
{
	return G::Object::wrap<Pixbuf>(gdk_pixbuf_animation_get_static_image(gdk_pixbuf_animation()));
}

Pointer<Gdk::PixbufAnimationIter>
Gdk::PixbufAnimation::get_iter(const GTimeVal *start_time) const
{
	return G::Object::wrap_new<PixbufAnimationIter>(gdk_pixbuf_animation_get_iter(gdk_pixbuf_animation(), start_time), true);
}

