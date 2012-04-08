/*  
    XFC: Xfce Foundation Classes (User Interface Library)
    Copyright (C) 2004 The XFC Development Team.

    LGPLv2
*/
#ifndef XFC_GTK_SOURCE_BUFFER_SIGNALS_HH
#define XFC_GTK_SOURCE_BUFFER_SIGNALS_HH

#ifndef XFC_GTK_TEXT_BUFFER_SIGNALS_HH
#include <xfc/gtk/textbuffersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

class SourceBufferSignals : public TextBufferSignals 
{
protected:
/// @name Constructors
/// @{

	SourceBufferSignals(SourceBuffer *buffer);
	///< Constructs a new TextBufferSignals object.
	///< @param buffer A TextBuffer object inheriting the TextBufferSignals implementation.

	virtual ~SourceBufferSignals() = 0;
	///< Destructor.

public:
//! @}
//! @name Signal Handlers
//! @{

	virtual void on_can_undo(bool can_undo);
	//!< Called whenever there is a change in the buffer's ability to undo an operation.
	//!< @param can_undo Will be <EM>true</EM> if the buffer can now perform an undo.
	//!<
	//!< <BR>This signal can be used to change the sensitivity of the Undo
	//!< menu item or toolbar button.

	virtual void on_can_redo(bool can_redo);
	//!< Called whenever there is a change in the buffer's ability to redo an operation.
	//!< @param can_redo Will be <EM>true</EM> if the buffer can now perform a redo.
	//!<
	//!< <BR>This signal can be used to change the sensitivity of the Redo
	//!< menu item or toolbar button.

	virtual void on_highlight_updated(TextIter& start, TextIter& end);
	//!< Called whenever the syntax highlighting information has been updated, so that
	//!< views can request a redraw if the region changed is visible.
	//!< @param start The start position of the updated region in the buffer.
	//!< @param end The end position of the updated region in the buffer.
	//!<
	//!< <BR>Usually only view widgets displaying the buffer will be interested in this signal.

	virtual void on_marker_updated(TextIter& where);
	//!< Called whenever a marker of sourcebuffer has changed and needs to be redisplayed by the view.
	//!< @param where The position in the buffer where the change occurred.
	//!<
	//!< <BR>A change in a marker's type or location can trigger this signal. Note that moving
	//!< a marker causes the emission of this signal twice: once for the old location and once
	//!< for the new.

};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_BUFFER_SIGNALS_HH
