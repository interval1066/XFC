/*
    XFC: Xfce Foundation Classes (User Interface Library)
    Copyright (C) 2004 The XFC Development Team.

    LGPLv2
*/
#ifndef XFC_GTK_SOURCE_STYLE_SCHEME_SIGNALS_HH
#define XFC_GTK_SOURCE_STYLE_SCHEME_SIGNALS_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace Gtk {

class SourceStyleSchemeSignals : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

    virtual ~SourceStyleSchemeSignals() = 0;
    ///< Destructor.

/// }@
public:
//! @}
//  Override these do_ methods when you want to change the default behaviour of the GtkSourceStyleScheme.

	virtual const char* do_get_name();

	virtual GtkSourceTagStyle* do_get_tag_style(const char *style_name);

	virtual GSList* do_get_style_names();

//! @name Signal Handlers
//! @{

	virtual void on_style_changed(const String& tag_id);
	//!< Called whenever the tag style changes.
	//!< @param tag_id The tag identifier for the new style.

//! @}
//  Signals
};

}

}

#endif
