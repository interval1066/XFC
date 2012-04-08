/**
    Provides simple user interaction functions, like error, warning
    and confirm dialogs.
*/
#ifndef XFC_DE_DIALOGS_HH
#define XFC_DE_DIALOGS_HH

#include <xfc/utfstring.hh>

#include <xfc/gtk/stockid.hh>

namespace Xfc {
namespace De {

    /**
        Displays a modal error dialog to the user and blocks until the
        users clicks the close button.

        @param format printf-style format string.
        @param ... argument list.
    */
    void dialog_show_err(const String &format, ... );

    /**
        Displays a modal warning dialog to the user and blocks until
        the users clicks the close button.

        @param format printf-style format string.
        @param ... argument list. 
    */
    void dialog_show_warn(const String &format, ...);

    /**
        Displays a modal info dialog to the user and blocks until the
        users clicks the close button.
        
        @param format printf-style format string.
        @param ... argument list
    */
    void dialog_show_info(const String &format, ...);

    /**
        Runs a modal confirmation dialog, that has a 'cancel' and a
        'confirm' button. The 'confirm' button text can be set by
        action if given.

        If stock_id is equal to GTK_STOCK_YES, the 'cancel' button
        becomes a 'no' button.

        @param text a question text
        @param stock_id is a stock item name
        @param action if non-NULL, this text is used on the confirm button together with the stock icon.

        @return true if the user confirms, else false.
    */
    bool dialog_show_confirm(const String &text, const Gtk::StockId stock_id, const String &action);
}
}

#endif
