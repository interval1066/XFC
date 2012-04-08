/*
    XFC: Xfce Foundation Classes (User Interface Library)
    Copyright (C) 2004 The XFC Development Team.

    LGPLv2
*/
#ifndef XFC_GTK_SOURCE_TAG_SIGNALS_HH
#define XFC_GTK_SOURCE_TAG_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/gtk/texttagsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

class SourceTagTableSignals : public TextTagTableSignals
{
protected:
/// @name Constructors
/// @{

    SourceTagTableSignals(SourceTagTable *buffer);
    ///< Constructs a new TextBufferSignals object.
    ///< @param buffer A TextBuffer object inheriting the TextLanguage Signals implementation.

    virtual ~SourceTagTableSignals() = 0;
    ///< Destructor.

public:
//! @}
//! @name Signal Handlers
//! @{

	virtual void on_changed();
	//!< Called whenever tags are added to or removed from the table.

};

}

}

#endif
