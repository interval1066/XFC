/*
    XFC: Xfce Foundation Classes (User Interface Library)
    Copyright (C) 2004 The XFC Development Team.

    LGPLv2
*/
#ifndef XFC_GTK_SOURCE_LANGUAGE_SIGNALS_HH
#define XFC_GTK_SOURCE_LANGUAGE_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/gtk/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

class SourceLanguageSignals : public ObjectSignals
{
protected:
/// @name Constructors
/// @{

        SourceLanguageSignals(SourceLanguage *buffer);
        ///< Constructs a new TextBufferSignals object.
        ///< @param buffer A TextBuffer object inheriting the TextLanguage Signals implementation.

        virtual ~SourceLanguageSignals() = 0;
        ///< Destructor.

public:
//! @}
//! @name Signal Handlers
//! @{

	virtual void on_tag_style_changed(const String& name);
	//!< Called when a tag style is changed.
	//!< @param name The name of the new tag style.
};

} // Gtk

} // Xfc

#endif
