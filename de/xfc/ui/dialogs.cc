#include "dialogs.hh"

extern "C" {
#include <libxfcegui4/dialogs.h>
}

namespace Xfc {
    namespace De {
        void dialog_show_err(const String &format, ... )
        {
            va_list args;
            
            va_start (args, format);
            xfce_verr(format.c_str(), args);
            va_end (args);
        }
        
        void dialog_show_warn(const String &format, ...)
        {
            va_list args;
            
            va_start (args, format);
            xfce_vwarn(format.c_str(), args);
            va_end (args);
        }
        
        void dialog_show_info(const String &format, ...)
        {
            va_list args;
            
            va_start (args, format);
            xfce_vinfo(format.c_str(), args);
            va_end (args);

        }
        
        bool dialog_show_confirm(const String &text, const Gtk::StockId stock_id, const String &action)
        {
            return (bool)xfce_confirm( text.c_str(), stock_id, action.c_str());
        }
    }
}
