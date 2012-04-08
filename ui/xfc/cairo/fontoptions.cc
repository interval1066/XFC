#include <xfc/cairo/fontoptions.hh>

using namespace Xfc;
using namespace Cairo;

FontOptions::FontOptions()
{
    m_font_options = cairo_font_options_create();
}

FontOptions::FontOptions( const cairo_font_options_t *fo )
{
    m_font_options = cairo_font_options_copy( fo );
}

FontOptions::FontOptions( const FontOptions &fo )
{
    m_font_options = cairo_font_options_copy( fo.m_font_options );
}

FontOptions::~FontOptions()
{
    cairo_font_options_destroy( m_font_options );
}

Status FontOptions::status()
{
    cairo_font_options_status( m_font_options );
}

void FontOptions::merge( const FontOptions &other )
{
    cairo_font_options_merge( m_font_options, other );
}

unsigned long FontOptions::hash()
{
    return cairo_font_options_hash( m_font_options );
}

bool FontOptions::equal( const FontOptions &other )
{
    return cairo_font_options_equal( m_font_options, other );
}

void FontOptions::set_antialias( Antialias antialias )
{
    cairo_font_options_set_antialias( m_font_options, (cairo_antialias_t)antialias );
}

Antialias FontOptions::get_antialias()
{
    return (Antialias)cairo_font_options_get_antialias( m_font_options );
}

void FontOptions::set_subpixel_order( SubpixelOrder subpixel_order)
{
    cairo_font_options_set_subpixel_order( m_font_options, 
                                           (cairo_subpixel_order_t)subpixel_order );
}

SubpixelOrder FontOptions::get_subpixel_order()
{
    return (SubpixelOrder)cairo_font_options_get_subpixel_order( m_font_options );
}

void FontOptions::set_hint_style( HintStyle hint_style)
{
    cairo_font_options_set_hint_style( m_font_options, (cairo_hint_style_t)hint_style );
}

HintStyle FontOptions::get_hint_style()
{
    return (HintStyle)cairo_font_options_get_hint_style( m_font_options );
}

void FontOptions::set_hint_metrics( HintMetrics hint )
{
    cairo_font_options_set_hint_metrics( m_font_options, (cairo_hint_metrics_t)hint );
}

HintMetrics FontOptions::get_hint_metrics()
{
    return (HintMetrics)cairo_font_options_get_hint_metrics( m_font_options );
}

FontOptions::operator cairo_font_options_t* () const
{
    return m_font_options;
}
