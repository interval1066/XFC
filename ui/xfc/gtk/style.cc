/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  style.cc - GtkStyle C++ wrapper implementation
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
 
#include "style.hh"
#include "iconfactory.hh"
#include "stockid.hh"
#include "widget.hh"
#include "private/styleclass.hh"
#include "../gdk/gc.hh"
#include "../gdk/pixmap.hh"
#include "../gdk/window.hh"
#include "../gdk-pixbuf/pixbuf.hh"
#include "../pango/font.hh"
#include "../pango/layout.hh"

using namespace Xfc;

/*  Gtk::draw_insertion_cursor
 */

void 
Gtk::draw_insertion_cursor(Widget& widget, Gdk::Drawable& drawable, const Gdk::Rectangle& location, 
bool is_primary, TextDirection direction, bool draw_arrow, const Gdk::Rectangle *area)
{
	gtk_draw_insertion_cursor(widget.gtk_widget(), drawable.gdk_drawable(), *area, location.gdk_rectangle(),
	                          is_primary, (GtkTextDirection)direction, draw_arrow);
}	

/*  Gtk::Style
 */

Gtk::Style::Style(GtkStyle *style, bool owns_reference)
: G::Object((GObject*)style, owns_reference)
{
}
	
Gtk::Style::~Style()
{
}

Gdk::Color
Gtk::Style::fg(StateType state_type) const
{
	return Gdk::Color(&gtk_style()->fg[state_type]);
}

Gdk::Color
Gtk::Style::bg(StateType state_type) const
{
	return Gdk::Color(&gtk_style()->bg[state_type]);
}

Gdk::Color
Gtk::Style::light(StateType state_type) const
{
	return Gdk::Color(&gtk_style()->light[state_type]);
}

Gdk::Color
Gtk::Style::dark(StateType state_type) const
{
	return Gdk::Color(&gtk_style()->dark[state_type]);
}

Gdk::Color
Gtk::Style::mid(StateType state_type) const
{
	return Gdk::Color(&gtk_style()->mid[state_type]);
}

Gdk::Color
Gtk::Style::text(StateType state_type) const
{
	return Gdk::Color(&gtk_style()->text[state_type]);
}

Gdk::Color
Gtk::Style::base(StateType state_type) const
{
	return Gdk::Color(&gtk_style()->base[state_type]);
}

Gdk::Color
Gtk::Style::text_aa(StateType state_type) const
{
	return Gdk::Color(&gtk_style()->text_aa[state_type]);
}

Gdk::Color
Gtk::Style::black() const
{
	return Gdk::Color(&gtk_style()->black);
}

Gdk::Color
Gtk::Style::white() const
{
	return Gdk::Color(&gtk_style()->white);
}

Pointer<Pango::FontDescription>
Gtk::Style::font_description() const
{
	return G::Boxed::wrap<Pango::FontDescription>(PANGO_TYPE_FONT_DESCRIPTION, gtk_style()->font_desc, true);
}

Gdk::GC*
Gtk::Style::black_gc() const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->black_gc);
}

Gdk::GC*
Gtk::Style::white_gc() const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->white_gc);
}

Gdk::GC*
Gtk::Style::fg_gc(StateType state_type) const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->fg_gc[state_type]);
}

Gdk::GC*
Gtk::Style::bg_gc(StateType state_type) const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->bg_gc[state_type]);
}

Gdk::GC*
Gtk::Style::light_gc(StateType state_type) const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->light_gc[state_type]);
}

Gdk::GC*
Gtk::Style::dark_gc(StateType state_type) const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->dark_gc[state_type]);
}

Gdk::GC*
Gtk::Style::mid_gc(StateType state_type) const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->mid_gc[state_type]);
}

Gdk::GC*
Gtk::Style::text_gc(StateType state_type) const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->text_gc[state_type]);
}

Gdk::GC*
Gtk::Style::base_gc(StateType state_type) const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->base_gc[state_type]);
}

Gdk::GC*
Gtk::Style::text_aa_gc(StateType state_type) const
{
	return G::Object::wrap<Gdk::GC>(gtk_style()->text_aa_gc[state_type]);
}

Gdk::Pixmap*
Gtk::Style::bg_pixmap(StateType state_type) const
{
	return G::Object::wrap<Gdk::Pixmap>(gtk_style()->bg_pixmap[state_type]);
}

void 
Gtk::Style::attach(const Gdk::Window& window)
{
	GtkStyle *old_style = gtk_style();
	g_object_ref(old_style);

	GtkStyle *new_style = gtk_style_attach(old_style, window.gdk_window());

	if (new_style != old_style)
	{
		instance_ = (GTypeInstance*)new_style;
	}

	g_object_unref(old_style);
}

Pointer<Gtk::Style>
Gtk::Style::copy() const
{
	return G::Object::wrap_new<Style>(gtk_style_copy(gtk_style()), true);
}

Pointer<Gtk::IconSet>
Gtk::Style::lookup_icon_set(const StockId& stock_id)
{
	return G::Boxed::wrap<IconSet>(GTK_TYPE_ICON_SET, gtk_style_lookup_icon_set(gtk_style(), stock_id), true);
}

void
Gtk::Style::set_background(Gdk::Window& window, StateType state_type)
{
	gtk_style_set_background(gtk_style(), window.gdk_window(), (GtkStateType)state_type);
}

void 
Gtk::Style::set_font_description(const Pango::FontDescription& font_desc) const
{
	pango_font_description_free(gtk_style()->font_desc);
	gtk_style()->font_desc = pango_font_description_copy(font_desc.pango_font_description());	
}

void 
Gtk::Style::set_fg(StateType state_type, const Gdk::Color& color)
{
	gtk_style()->fg[state_type] = *color.gdk_color();
}
     
void 
Gtk::Style::set_bg(StateType state_type, const Gdk::Color& color)
{
	gtk_style()->bg[state_type] = *color.gdk_color();
}
      
void 
Gtk::Style::set_light(StateType state_type, const Gdk::Color& color)
{
	gtk_style()->light[state_type] = *color.gdk_color();
}
      
void 
Gtk::Style::set_dark(StateType state_type, const Gdk::Color& color)
{
	gtk_style()->dark[state_type] = *color.gdk_color();
}
      
void 
Gtk::Style::set_mid(StateType state_type, const Gdk::Color& color)
{
	gtk_style()->mid[state_type] = *color.gdk_color();
}
      
void 
Gtk::Style::set_text(StateType state_type, const Gdk::Color& color)
{
	gtk_style()->text[state_type] = *color.gdk_color();
}
      
void 
Gtk::Style::set_base(StateType state_type, const Gdk::Color& color)
{
	gtk_style()->base[state_type] = *color.gdk_color();
}

void
Gtk::Style::apply_default_background(Gdk::Window& window, bool set_bg, StateType state_type, int x, int y,
                                     int width, int height, const Gdk::Rectangle *area)
{
	gtk_style_apply_default_background(gtk_style(), window.gdk_window(), set_bg, (GtkStateType)state_type, *area, x, y, width, height);
}

Pointer<Gdk::Pixbuf>
Gtk::Style::render_icon(const IconSource& source, TextDirection direction, StateType state, IconSize size,
                        Widget *widget, const char *detail)
{
	return G::Object::wrap<Gdk::Pixbuf>(gtk_style_render_icon(gtk_style(), source.gtk_icon_source(), (GtkTextDirection)direction,
	                                    (GtkStateType)state, (GtkIconSize)size, *widget, detail), true);
}

void
Gtk::Style::draw_hline(Gdk::Window& window, StateType state_type, int x1, int x2, int y,
                       const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_hline)
		g_class->draw_hline(gtk_style(), window.gdk_window(), (GtkStateType)state_type,
		                    *area, *widget, detail, x1, x2, y);
}

void
Gtk::Style::draw_vline(Gdk::Window& window, StateType state_type, int y1, int y2, int x,
                       const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_vline)
		g_class->draw_vline(gtk_style(), window.gdk_window(), (GtkStateType)state_type,
		                    *area, *widget, detail, y1, y2, x);
}

void
Gtk::Style::draw_shadow(Gdk::Window& window, StateType state_type, ShadowType shadow_type, int x, int y,
                        int width, int height, const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_shadow)
		g_class->draw_shadow(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                     *area, *widget, detail, x, y, width, height);
}

void
Gtk::Style::draw_polygon(Gdk::Window& window, StateType state_type, ShadowType shadow_type, const Gdk::Point *points,
                         int npoints, bool fill, const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_polygon)
		g_class->draw_polygon(gtk_style(), window.gdk_window(), (GtkStateType)state_type,
		                      (GtkShadowType)shadow_type, *area, *widget, detail,
		                       points->gdk_point(), npoints, fill);
}

void
Gtk::Style::draw_arrow(Gdk::Window& window, StateType state_type, ShadowType shadow_type, ArrowType arrow_type, bool fill,
                       int x, int y, int width, int height, const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_arrow)
		g_class->draw_arrow(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                    *area, *widget, detail, (GtkArrowType)arrow_type, fill, x, y, width, height);
}

void
Gtk::Style::draw_diamond(Gdk::Window& window, StateType state_type, ShadowType shadow_type, int x, int y,
                         int width, int height, const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_diamond)
		g_class->draw_diamond(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                                *area, *widget, detail, x, y, width, height);
}

void
Gtk::Style::draw_box(Gdk::Window& window, StateType state_type, ShadowType shadow_type, int x, int y,
                     int width, int height, const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_box)
		g_class->draw_box(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                  *area, *widget, detail, x, y, width, height);
}

void
Gtk::Style::draw_flat_box(Gdk::Window& window, StateType state_type, ShadowType shadow_type, int x, int y,
                          int width, int height, const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_flat_box)
		g_class->draw_flat_box(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                       *area, *widget, detail, x, y, width, height);
}

void
Gtk::Style::draw_check(Gdk::Window& window, StateType state_type, ShadowType shadow_type, int x, int y,
                       int width, int height, const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_check)
		g_class->draw_check(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type, *area,
		                    *widget, detail, x, y, width, height);
}

void
Gtk::Style::draw_option(Gdk::Window& window, StateType state_type, ShadowType shadow_type, int x, int y,
                        int width, int height, const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_option)
		g_class->draw_option(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                     *area, *widget, detail, x, y, width, height);
}

void
Gtk::Style::draw_tab(Gdk::Window& window, StateType state_type, ShadowType shadow_type, int x, int y,
                     int width, int height, const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_tab)
		g_class->draw_tab(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                  *area, *widget, detail, x, y, width, height);
}

void
Gtk::Style::draw_shadow_gap(Gdk::Window& window, StateType state_type, ShadowType shadow_type, int x, int y,
                            int width, int height, PositionType  gap_side, int gap_x, int gap_width,
                            const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_shadow_gap)
		g_class->draw_shadow_gap(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                         *area, *widget, detail, x, y, width, height, (GtkPositionType)gap_side, gap_x, gap_width);
}

void
Gtk::Style::draw_box_gap(Gdk::Window& window, StateType state_type, ShadowType shadow_type, int x, int y,
                         int width, int height, PositionType  gap_side, int gap_x, int gap_width,
                         const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_box_gap)
		g_class->draw_box_gap(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                      *area, *widget, detail, x, y, width, height, (GtkPositionType)gap_side, gap_x, gap_width);
}

void
Gtk::Style::draw_extension(Gdk::Window& window, StateType state_type, ShadowType shadow_type,
                           int x, int y, int width, int height, PositionType gap_side,
                           const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_extension)
		g_class->draw_extension(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                        *area, *widget, detail, x, y, width, height, (GtkPositionType)gap_side);
}

void
Gtk::Style::draw_focus(Gdk::Window& window, StateType state_type, int x, int y, int width, int height,
                       const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_focus)
		g_class->draw_focus(gtk_style(), window.gdk_window(), (GtkStateType)state_type,
		                    *area, *widget, detail, x, y, width, height);
}

void
Gtk::Style::draw_slider(Gdk::Window& window, StateType state_type, ShadowType shadow_type,
                        int x, int y, int width, int height, Orientation orientation,
                        const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_slider)
		g_class->draw_slider(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                     *area, *widget, detail, x, y, width, height, (GtkOrientation)orientation);
}

void
Gtk::Style::draw_handle(Gdk::Window& window, StateType state_type, ShadowType shadow_type,
                        int x, int y, int width, int height, Orientation orientation,
                        const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_handle)
		g_class->draw_handle(gtk_style(), window.gdk_window(), (GtkStateType)state_type, (GtkShadowType)shadow_type,
		                     *area, *widget, detail, x, y, width, height, (GtkOrientation)orientation);
}

void
Gtk::Style::draw_expander(Gdk::Window& window, StateType state_type, int x, int y, ExpanderStyle expander_style,
                          const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_expander)
		g_class->draw_expander(gtk_style(), window.gdk_window(), (GtkStateType)state_type,
		                       *area, *widget, detail, x, y, (GtkExpanderStyle)expander_style);
}

void
Gtk::Style::draw_layout(Gdk::Window& window, StateType state_type, bool use_text, int x, int y, Pango::Layout& layout,
                        const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_layout)
		g_class->draw_layout(gtk_style(), window.gdk_window(), (GtkStateType)state_type, use_text,
		                      *area, *widget, detail, x, y, layout.pango_layout());
}

void
Gtk::Style::draw_resize_grip(Gdk::Window& window, StateType state_type, Gdk::WindowEdge edge, int x, int y, int width, int height,
                             const Gdk::Rectangle *area, Widget *widget, const char *detail)
{
	GtkStyleClass *g_class = StyleClass::get_parent_class(instance_);
	if (g_class && g_class->draw_resize_grip)
		g_class->draw_resize_grip(gtk_style(), window.gdk_window(), (GtkStateType)state_type,
		                          *area, *widget, detail, (GdkWindowEdge)edge, x, y, width, height);
}

/*  Gtk::StyleClass
 */

void
Gtk::StyleClass::init(GtkStyleClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GtkStyleClass*
Gtk::StyleClass::get_parent_class(void *instance)
{
	return static_cast<GtkStyleClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::StyleClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_STYLE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::StyleClass::create()
{
	return g_object_new(get_type(), 0);
}

