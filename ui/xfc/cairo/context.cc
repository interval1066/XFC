#include <xfc/cairo/context.hh>
#include <pango/pangocairo.h>

using namespace Xfc;
using namespace Cairo;

Context::Context( cairo_t *cr ) 
{
    m_cr = cr;

    cairo_reference( m_cr );
}

Context::Context( const Context &ctx ) 
{
    m_cr = ctx.m_cr;

    cairo_reference( m_cr );
}

Context::~Context()
{
    cairo_destroy( m_cr );
}

Status Context::status()
{
    return (Status)cairo_status( m_cr );
}

void Context::save()
{
    cairo_save( m_cr );
}

void Context::restore()
{
    cairo_restore( m_cr );
}

Surface Context::get_target()
{
    Surface surface( cairo_get_target( m_cr ) );

    return surface;
}

void Context::push_group()
{
    cairo_push_group( m_cr );
}

void Context::push_group_with_content( Content content )
{
    cairo_push_group_with_content( m_cr, (cairo_content_t)content );
}

Pattern Context::pop_group()
{
    return Pattern( cairo_pop_group( m_cr ));
}

void Context::pop_group_to_source()
{
    cairo_pop_group_to_source( m_cr );
}

Surface Context::get_group_target()
{
    Surface surface( cairo_get_group_target( m_cr ));

    return surface;
}

void Context::set_source_rgb( double red, double green, double blue)
{
    cairo_set_source_rgb( m_cr, red, green, blue );
}

void Context::set_source_rgba( double red, double green, double blue, double alpha)
{
    cairo_set_source_rgba( m_cr, red, green, blue, alpha );
}

void Context::set_source( Pattern &pattern )
{
    cairo_set_source( m_cr, pattern );
}

void Context::set_source_surface( Surface &surface, double x, double y)
{
    cairo_set_source_surface( m_cr, surface, x,  y );
}

Pattern Context::get_source()
{
    Pattern pattern( cairo_get_source( m_cr ));

    return pattern;
}

void Context::set_antialias( Antialias antialias )
{
    cairo_set_antialias( m_cr, (cairo_antialias_t)antialias );
}

Antialias Context::get_antialias()
{
    return (Antialias)cairo_get_antialias( m_cr );
}

void Context::set_dash( const double *dashes, int num_dashes, double offset)
{
    cairo_set_dash( m_cr, dashes, num_dashes, offset );
}

void Context::set_fill_rule( FillRule fill_rule )
{
    cairo_set_fill_rule( m_cr, (cairo_fill_rule_t)fill_rule );
}

FillRule Context::get_fill_rule()
{
    return (FillRule)cairo_get_fill_rule( m_cr );
}

void Context::set_line_cap( LineCap line_cap)
{
    cairo_set_line_cap( m_cr, (cairo_line_cap_t)line_cap );
}

LineCap Context::get_line_cap()
{
    return (LineCap)cairo_get_line_cap( m_cr );
}

void Context::set_line_join( LineJoin line_join)
{
    cairo_set_line_join( m_cr, (cairo_line_join_t)line_join );
}

LineJoin Context::get_line_join()
{
    return (LineJoin) cairo_get_line_join( m_cr );
}

void Context::set_line_width( double width )
{
    cairo_set_line_width( m_cr, width );
}

double Context::get_line_width()
{
    return cairo_get_line_width( m_cr );
}

void Context::set_miter_limit( double limit )
{
    cairo_set_miter_limit( m_cr, limit );
}

double Context::get_miter_limit()
{
    return cairo_get_miter_limit( m_cr );
}

void Context::set_operator( Operator op )
{
    cairo_set_operator( m_cr, (cairo_operator_t)op );
}

Operator Context::get_operator()
{
    return (Operator)cairo_get_operator( m_cr );
}

void Context::set_tolerance( double tolerance )
{
    cairo_set_tolerance( m_cr, tolerance );
}

double Context::get_tolerance()
{
    cairo_get_tolerance( m_cr );
}

void Context::clip()
{
    cairo_clip( m_cr );
}

void Context::clip_preserve()
{
    cairo_clip_preserve( m_cr );
}

void Context::reset_clip()
{
    cairo_reset_clip( m_cr );
}

void Context::fill()
{
    cairo_fill( m_cr );
}

void Context::fill_preserve()
{
    cairo_fill_preserve( m_cr );
}

void Context::fill_extents( double *x1, double *y1, double *x2, double *y2)
{
    cairo_fill_extents( m_cr, x1, y1, x2, y2 );
}

bool Context::in_fill( double x, double y)
{
    return cairo_in_fill( m_cr, x, y );
}

void Context::mask( Pattern &pattern )
{
    cairo_mask( m_cr, pattern );
}

void Context::mask_surface ( Surface &surface, double surface_x, double surface_y)
{
    cairo_mask_surface( m_cr, surface,surface_x, surface_y );
}

void Context::paint()
{
    cairo_paint( m_cr );
}

void Context::paint_with_alpha( double alpha )
{
    return cairo_paint_with_alpha( m_cr, alpha );
}

void Context::stroke()
{
    cairo_stroke( m_cr );
}

void Context::stroke_preserve()
{
    cairo_stroke_preserve( m_cr );
}

void Context::stroke_extents( double *x1, double *y1, double *x2, double *y2)
{
    cairo_stroke_extents( m_cr, x1, y1, x2, y2 );
}

bool Context::in_stroke( double x, double y)
{
    cairo_in_stroke( m_cr, x, y );
}

void Context::copy_page()
{
    cairo_copy_page( m_cr );
}

void Context::show_page()
{
    cairo_show_page( m_cr );
}

// Path interface

void Context::get_current_point( double *x, double *y )
{
    cairo_get_current_point( m_cr, x, y );
}

void Context::new_path()
{
    cairo_new_path( m_cr );
}

void Context::new_sub_path()
{
    cairo_new_sub_path( m_cr );
}

void Context::close_path()
{
    cairo_close_path( m_cr );
}

void Context::arc( double xc, double yc, double radius, double angle1, double angle2)
{
    cairo_arc( m_cr, xc, yc, radius, angle1, angle2 );
}

void Context::arc_negative( double xc, double yc, double radius, double angle1, double angle2)
{
    cairo_arc_negative( m_cr, xc, yc, radius, angle1, angle2 );
}

void Context::curve_to( double x1, double y1, double x2, double y2, double x3, double y3)
{
    cairo_curve_to( m_cr, x1, y1, x2, y2, x3,  y3 );
}

void Context::line_to( double x, double y )
{
    cairo_line_to( m_cr, x, y );
}

void Context::move_to( double x, double y)
{
    cairo_move_to( m_cr, x, y);
}

void Context::rectangle( double x, double y, double width, double height)
{
    cairo_rectangle( m_cr, x, y, width, height);
}

void Context::text_path( const string &utf8 )
{
    cairo_text_path( m_cr, utf8.c_str() );
}

void Context::rel_curve_to( double dx1, double dy1, double dx2, double dy2, double dx3, double dy3)
{
    cairo_rel_curve_to( m_cr, dx1, dy1, dx2, dy2, dx3, dy3);
}

void Context::rel_line_to( double dx, double dy)
{
    cairo_rel_line_to( m_cr, dx, dy);
}

void Context::rel_move_to( double dx, double dy)
{
    cairo_rel_move_to( m_cr, dx, dy);
}

void Context::translate( double tx, double ty )
{
    cairo_translate( m_cr, tx, ty );
}

void Context::scale( double sx, double sy )
{
    cairo_scale( m_cr, sx, sy );
}

void Context::rotate( double angle )
{
    cairo_rotate( m_cr, angle );
}

void Context::show_layout( Pango::Layout &layout )
{
    pango_cairo_show_layout( m_cr, layout.pango_layout());
}
