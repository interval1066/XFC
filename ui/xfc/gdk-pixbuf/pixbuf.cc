/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  pixbuf.cc - GdkPixbufFormat and GdkPixbuf C++ wrapper interface
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
 
#include "pixbuf.hh"
#include "../gdk/bitmap.hh"
#include "../gdk/color.hh"
#include "../gdk/drawable.hh"
#include "../gdk/gc.hh"
#include "../gdk/image.hh"
#include "../gdk/pixmap.hh"
#include "xfc/glib/error.hh"
#include <gdk/gdkpixbuf.h>

using namespace Xfc;

/*  Gdk::Pixbuf
 */

Gdk::Pixbuf::Pixbuf(GdkPixbuf *pixbuf, bool owns_reference)
: G::Object((GObject*)pixbuf, owns_reference)
{
}
	
Gdk::Pixbuf::Pixbuf(const Pixbuf& src, int src_x, int src_y, int width, int height)
: G::Object((GObject*)gdk_pixbuf_new_subpixbuf(src.gdk_pixbuf(), src_x, src_y, width, height))
{
}

Gdk::Pixbuf::Pixbuf(const unsigned char *data, int width, int height, int rowstride, bool has_alpha,
GdkPixbufDestroyNotify destroy_fn, gpointer destroy_fn_data, int bits_per_sample, Colorspace colorspace)
: G::Object((GObject*)gdk_pixbuf_new_from_data(data, (GdkColorspace)colorspace, has_alpha, bits_per_sample, width, height,
  rowstride, destroy_fn, destroy_fn_data))
{
}

Gdk::Pixbuf::Pixbuf(const char **data)
: G::Object((GObject*)gdk_pixbuf_new_from_xpm_data(data))
{
}

Gdk::Pixbuf::~Pixbuf()
{
}
	
Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::create(const char *filename, G::Error *error)
{
	return G::Object::wrap_new<Pixbuf>(gdk_pixbuf_new_from_file(filename, *error), true);
}

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::create(const String& filename, G::Error *error)
{
	return create(filename.c_str(), error);
}

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::create(const char *filename, int width, int height, bool preserve_aspect_ratio, G::Error *error)
{
	return G::Object::wrap_new<Pixbuf>(gdk_pixbuf_new_from_file_at_scale(filename, width, height,
	                                   preserve_aspect_ratio, *error), true);
}

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::create(const String& filename, int width, int height, bool preserve_aspect_ratio, G::Error *error)
{
	return create(filename.c_str(), width, height, preserve_aspect_ratio, error);
}

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::create(int width, int height, bool has_alpha, int bits_per_sample, Colorspace colorspace)
{
	return G::Object::wrap_new<Pixbuf>(gdk_pixbuf_new((GdkColorspace)colorspace, has_alpha, bits_per_sample, width, height), true);
}

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::create(const Drawable& drawable, int x, int y, int width, int height, Colormap *colormap)
{
	return G::Object::wrap_new<Pixbuf>(gdk_pixbuf_get_from_drawable(0, drawable.gdk_drawable(), *colormap,
	
	                                   x, y, 0, 0, width, height), true);
}

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::create(const Image& image, int x, int y, int width, int height, Colormap *colormap)
{
	return G::Object::wrap_new<Pixbuf>(gdk_pixbuf_get_from_image(0, image.gdk_image(), *colormap,
	                                   x, y, 0, 0, width, height), true);
}

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::create(int data_length, const unsigned char *data, bool copy_pixels, G::Error *error)
{
	return G::Object::wrap_new<Pixbuf>(gdk_pixbuf_new_from_inline(data_length, data, copy_pixels, *error), true);
}

bool
Gdk::Pixbuf::get_from_drawable(const Drawable& src, int src_x, int src_y, int dest_x, int dest_y, int width, int height, Colormap *colormap)
{
	return gdk_pixbuf_get_from_drawable(gdk_pixbuf(), src.gdk_drawable(), *colormap, src_x, src_y, dest_x, dest_y, width, height);
}

bool
Gdk::Pixbuf::get_from_image(const Image& src, int src_x, int src_y, int dest_x, int dest_y, int width, int height, Colormap *colormap)
{
	return gdk_pixbuf_get_from_image(gdk_pixbuf(), src.gdk_image(), *colormap, src_x, src_y, dest_x, dest_y, width, height);
}

String
Gdk::Pixbuf::get_option(const char *key) const
{
	return gdk_pixbuf_get_option(gdk_pixbuf(), key);
}

String
Gdk::Pixbuf::get_option(const String& key) const
{
	return gdk_pixbuf_get_option(gdk_pixbuf(), key.c_str());
}

namespace { // collect_save_options (copied from gdk-pixbuf-io.c)

void collect_save_options (va_list opts, char ***keys, char ***vals)
{
	char *key;
	char *val;
	int count = 0;
	*keys = 0;
	*vals = 0;

	char *next = va_arg (opts, char*);
	while (next)
	{
		key = next;
		val = va_arg (opts, char*);

		++count;

		// woo, slow
		*keys = (char**)g_realloc (*keys, sizeof(char*) * (count + 1));
		*vals = (char**)g_realloc (*vals, sizeof(char*) * (count + 1));

		(*keys)[count-1] = g_strdup (key);
		(*vals)[count-1] = g_strdup (val);

		(*keys)[count] = 0;
		(*vals)[count] = 0;

		next = va_arg (opts, char*);
	}
}

} // collect_save_options

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::copy() const
{
	return G::Object::wrap_new<Pixbuf>(gdk_pixbuf_copy(gdk_pixbuf()), true);
}

bool
Gdk::Pixbuf::save(const String& filename, const char *type, G::Error *error, ...)
{
	char **keys = 0;
	char **values = 0;

	va_list args;
	va_start (args, error);
	collect_save_options (args, &keys, &values);
	va_end (args);

	bool result = gdk_pixbuf_savev (gdk_pixbuf(), filename.c_str(), type, keys, values, *error);

	g_strfreev (keys);
	g_strfreev (values);
	return result;
}

bool
Gdk::Pixbuf::save(const char *filename, const char *type, char **option_keys, char **option_values, G::Error *error)
{
	return gdk_pixbuf_savev(gdk_pixbuf(), filename, type, option_keys, option_values, *error);
}

bool
Gdk::Pixbuf::save(const String& filename, const char *type, char **option_keys, char **option_values, G::Error *error)
{
	return save(filename.c_str(), type, option_keys, option_values, error);
}

namespace { // save_slot_callback

gboolean save_slot_callback(const gchar *buffer, gsize count, GError **error, gpointer data)
{
	Gdk::Pixbuf::SaveSlot& slot = *static_cast<Gdk::Pixbuf::SaveSlot*>(data);
	G::Error tmp_error(*error);
	return slot(buffer, count, &tmp_error);
}

} // namespace

bool 
Gdk::Pixbuf::save(const SaveSlot& slot, const char *type, G::Error *error, ...)
{
	char **keys = 0;
	char **values = 0;

	va_list args;
	va_start (args, error);
	collect_save_options (args, &keys, &values);
	va_end (args);

	SaveSlot tmp_slot(slot);
	bool result = gdk_pixbuf_save_to_callbackv(gdk_pixbuf(), &save_slot_callback, &tmp_slot, type, keys, values, *error);

	g_strfreev (keys);
	g_strfreev (values);
	return result;
}

bool 
Gdk::Pixbuf::save(const SaveSlot& slot, const char *type, char **option_keys, char **option_values, G::Error *error)
{
	SaveSlot tmp_slot(slot);
	return gdk_pixbuf_save_to_callbackv(gdk_pixbuf(), &save_slot_callback, &tmp_slot, type,
	                                    option_keys, option_values, *error);
}

bool 
Gdk::Pixbuf::save(char **buffer, size_t *buffer_size, const char *type, G::Error *error, ...)
{
	char **keys = 0;
	char **values = 0;

	va_list args;
	va_start (args, error);
	collect_save_options (args, &keys, &values);
	va_end (args);

	bool result = gdk_pixbuf_save_to_bufferv(gdk_pixbuf(), buffer, (gsize*)buffer_size, type, keys, values, *error);

	g_strfreev (keys);
	g_strfreev (values);
	return result;
}

bool 
Gdk::Pixbuf::save(char **buffer, size_t *buffer_size, const char *type, char **keys, char **values, G::Error *error)
{
	return gdk_pixbuf_save_to_bufferv(gdk_pixbuf(), buffer, buffer_size, type, keys, values, *error);
}
	
Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::add_alpha(bool substitute_color, unsigned char red, unsigned char green, unsigned char blue)
{
	GdkPixbuf *pixbuf = gdk_pixbuf_add_alpha(gdk_pixbuf(), substitute_color, red, green, blue);
	return pixbuf ? G::Object::wrap_new<Gdk::Pixbuf>(pixbuf, true) : 0;
}

void
Gdk::Pixbuf::copy_area(const Pixbuf& src, int src_x, int src_y, int width, int height, int dest_x, int dest_y)
{
	gdk_pixbuf_copy_area(src.gdk_pixbuf(), src_x, src_y, width, height, gdk_pixbuf(), dest_x, dest_y);
}

void
Gdk::Pixbuf::copy_area(const Pixbuf& src, const Rectangle& src_rect, int dest_x, int dest_y)
{
	gdk_pixbuf_copy_area(src.gdk_pixbuf(), src_rect.x(), src_rect.y(), src_rect.width(),
	                     src_rect.height(), gdk_pixbuf(), dest_x, dest_y);
}

void
Gdk::Pixbuf::saturate_and_pixelate(const Pixbuf& src, float saturation, bool pixelate)
{
	gdk_pixbuf_saturate_and_pixelate(src.gdk_pixbuf(), gdk_pixbuf(), saturation, pixelate);
}

void
Gdk::Pixbuf::saturate_and_pixelate(float saturation, bool pixelate)
{
	gdk_pixbuf_saturate_and_pixelate(gdk_pixbuf(), gdk_pixbuf(), saturation, pixelate);
}

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::scale_simple(int width, int height, InterpType interp_type)
{
	return G::Object::wrap_new<Pixbuf>(gdk_pixbuf_scale_simple(gdk_pixbuf(), width, height,
	                                   (GdkInterpType)interp_type), true);
}

void
Gdk::Pixbuf::scale(const Pixbuf& src, int dest_x, int dest_y, int dest_width, int dest_height, 
                   double offset_x, double offset_y, double scale_x, double scale_y, InterpType interp_type)
{
	gdk_pixbuf_scale(src.gdk_pixbuf(), gdk_pixbuf(), dest_x, dest_y, dest_width, dest_height, 
	                 offset_x, offset_y, scale_x, scale_y, (GdkInterpType)interp_type);
}

void
Gdk::Pixbuf::scale(const Pixbuf& src, const Rectangle& dest_rect, double offset_x, double offset_y,
                   double scale_x, double scale_y, InterpType interp_type)
{
	gdk_pixbuf_scale(src.gdk_pixbuf(), gdk_pixbuf(), dest_rect.x(), dest_rect.y(), dest_rect.width(), 
	                 dest_rect.height(), offset_x, offset_y, scale_x, scale_y, (GdkInterpType)interp_type);
}

Pointer<Gdk::Pixbuf>
Gdk::Pixbuf::composite_color_simple(int width, int height, InterpType interp_type, int overall_alpha,
                                         int check_size, unsigned int color1, unsigned int color2)
{
	return G::Object::wrap_new<Pixbuf>(gdk_pixbuf_composite_color_simple(gdk_pixbuf(), 
	                                   width, height, (GdkInterpType)interp_type, 
					   overall_alpha, check_size, color1, color2), true);
}

void
Gdk::Pixbuf::composite(const Pixbuf& src, int dest_x, int dest_y, int dest_width, int dest_height, double offset_x, 
                       double offset_y, double scale_x, double scale_y, InterpType interp_type, int overall_alpha)
{
	gdk_pixbuf_composite(src.gdk_pixbuf(), gdk_pixbuf(), dest_x, dest_y, dest_width, dest_height,
	                     offset_x, offset_y, scale_x, scale_y, (GdkInterpType)interp_type, overall_alpha);
}

void
Gdk::Pixbuf::composite(const Pixbuf& src, const Rectangle& dest_rect, double offset_x, double offset_y,
                       double scale_x, double scale_y, InterpType interp_type, int overall_alpha)
{
	gdk_pixbuf_composite(src.gdk_pixbuf(), gdk_pixbuf(), dest_rect.x(), dest_rect.y(), 
	                     dest_rect.width(), dest_rect.height(), offset_x, offset_y, 
			     scale_x, scale_y, (GdkInterpType)interp_type, overall_alpha);
}

void
Gdk::Pixbuf::composite_color(const Pixbuf& src, int dest_x, int dest_y, int dest_width, int dest_height, 
                             double offset_x, double offset_y, double scale_x, double scale_y, 
			     InterpType interp_type, int overall_alpha, int check_x, int check_y,
			     int check_size, unsigned int color1, unsigned int color2)
{
	gdk_pixbuf_composite_color(src.gdk_pixbuf(), gdk_pixbuf(), dest_x, dest_y, dest_width, dest_height, 
	                           offset_x, offset_y, scale_x, scale_y, (GdkInterpType)interp_type, 
				   overall_alpha, check_x, check_y, check_size, color1, color2);
}

void
Gdk::Pixbuf::composite_color(const Pixbuf& src, const Rectangle& dest_rect, double offset_x, double offset_y,
                             double scale_x, double scale_y, InterpType interp_type, int overall_alpha,
                             const Point& check_offset, int check_size, unsigned int color1, unsigned int color2)
{
	gdk_pixbuf_composite_color(src.gdk_pixbuf(), gdk_pixbuf(), dest_rect.x(), dest_rect.y(),
	                           dest_rect.width(), dest_rect.height(), offset_x, offset_y,
	                           scale_x, scale_y, (GdkInterpType)interp_type, overall_alpha,
	                           check_offset.x(), check_offset.y(), check_size, color1, color2);
}

Pointer<Gdk::Pixbuf> 
Gdk::Pixbuf::rotate_simple(PixbufRotation angle)
{
	GdkPixbuf *pixbuf = gdk_pixbuf_rotate_simple(gdk_pixbuf(), (GdkPixbufRotation)angle);
	return pixbuf ? G::Object::wrap_new<Gdk::Pixbuf>(pixbuf, true) : 0;
}

Pointer<Gdk::Pixbuf> 
Gdk::Pixbuf::flip(bool horizontal)
{
	GdkPixbuf *pixbuf = gdk_pixbuf_flip(gdk_pixbuf(), horizontal);
	return pixbuf ? G::Object::wrap_new<Gdk::Pixbuf>(pixbuf, true) : 0;
}					      

void
Gdk::Pixbuf::render_threshold_alpha(Bitmap& bitmap, int src_x, int src_y, int dest_x, int dest_y,
                                    int width, int height, int alpha_threshold)
{
	gdk_pixbuf_render_threshold_alpha(gdk_pixbuf(), bitmap.gdk_bitmap(), src_x, src_y, 
	                                  dest_x, dest_y, width, height, alpha_threshold);
}

void
Gdk::Pixbuf::render_pixmap_and_mask(Pointer<Pixmap> *pixmap_return, Pointer<Bitmap> *mask_return, 
                                    int alpha_threshold, Colormap *colormap)
{
	GdkPixmap *pixmap = 0;
	GdkBitmap *mask = 0;
	GdkColormap *cmap = colormap ? colormap->gdk_colormap() : gdk_rgb_get_colormap();
	gdk_pixbuf_render_pixmap_and_mask_for_colormap(gdk_pixbuf(), cmap, &pixmap, &mask, alpha_threshold);

	if (pixmap_return)
		*pixmap_return = G::Object::wrap_new<Pixmap>(pixmap, true);

	if (mask_return)
		*mask_return = G::Object::wrap_new<Bitmap>(mask, true);
}

