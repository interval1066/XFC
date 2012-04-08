/*
    XFC: Xfce Foundation Classes (User Interface Library)
    Copyright (C) 2004 The XFC Development Team.

    LGPLv2
*/
#ifndef XFC_GTK_SOURCE_PRINT_JOB_SIGNALS_HH
#define XFC_GTK_SOURCE_PRINT_JOB_SIGNALS_HH

#ifndef XFC_GTK_TEXT_BUFFER_SIGNALS_HH
#include <xfc/gtk/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

class SourcePrintJobSignals : public ObjectSignals
{
protected:
/// @name Constructors
/// @{

        SourcePrintJobSignals(SourcePrintJob *job);
        ///< Constructs a new TextPrintJobSignals object.
        ///< @param job A SourcePrintJob object inheriting the Signals implementation.

        virtual ~SourcePrintJobSignals() = 0;
        ///< Destructor.

public:
//! @}
//! @name Signal Handlers
//! @{

	virtual void on_begin_page();
	//!< Called whenever the print job is about to print a new text page.
	//!< You can connect to this signal to provide the user with feedback
	//!< about the progress of printing, or to customize the printed page
	//!< by for example, printing your own headers and footers.

	virtual void on_finished();
	//!< Called whenever an asynchronous print job has finished. You can
	//!< connect to this signal to get notification when a job has finished
	//!< printing. When it's emitted, the GnomePrintJob the print job was
	//!< producing has been closed and it can be either previewed or printed
	//!< to the physical device.
};

}

}

#endif
