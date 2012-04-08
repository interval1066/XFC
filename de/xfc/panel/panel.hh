/*
    Define the PanelPlugin interface that is the common class for both
    the internal and external interface.

    Please note that this is an interface, and the actual instantiation
    of the object are performed inside the xfce-panel.
*/
#ifndef XFC_DE_PANEL_HH
#define XFC_DE_PANEL_HH

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_MENUITEM_HH
#include <xfc/gtk/menuitem.hh>
#endif

#ifndef __XFCE_PANEL_PLUGIN_IFACE_H__
#include <libxfce4panel/xfce-panel-plugin-iface.h>
#endif

namespace Xfc {
    namespace De {
        enum ScreenPosition {
            NONE = XFCE_SCREEN_POSITION_NONE,

            NW_H = XFCE_SCREEN_POSITION_NW_H,          /* North West Horizontal */
            N    = XFCE_SCREEN_POSITION_N,             /* North                 */
            NE_H = XFCE_SCREEN_POSITION_NE_H,          /* North East Horizontal */

            NW_V = XFCE_SCREEN_POSITION_NW_V,          /* North West Vertical   */
            W    = XFCE_SCREEN_POSITION_W,             /* West                  */
            SW_V = XFCE_SCREEN_POSITION_SW_V,          /* South West Vertical   */

            NE_V = XFCE_SCREEN_POSITION_NE_V,          /* North East Vertical   */
            E    = XFCE_SCREEN_POSITION_E,             /* East                  */
            SE_V = XFCE_SCREEN_POSITION_SE_V,          /* South East Vertical   */

            SW_H = XFCE_SCREEN_POSITION_SW_H,          /* South West Horizontal */
            S    = XFCE_SCREEN_POSITION_S,             /* South                 */
            SE_H = XFCE_SCREEN_POSITION_SE_H,          /* South East Horizontal */

            FLOATING_H = XFCE_SCREEN_POSITION_FLOATING_H,    /* Floating Horizontal */
            FLOATING_V = XFCE_SCREEN_POSITION_FLOATING_V     /* Floating Vertical */
        };
       
        class PanelPluginInterface : public G::TypeInterface {
        protected:
/// @name Constructors
/// @{

            explicit PanelPluginInterface( XfcePanelPlugin *panel, bool owns_reference = false );

/// @}
/// @name Signal Prototypes
/// @{

            // "about"                                          : Run Last / No Recursion / No Hooks
            typedef G::Signal<void> AboutSignalType;
            typedef G::SignalProxy<G::TypeInstance, AboutSignalType> AboutSignalProxy;
            static const AboutSignalType about_signal;
            
            //  "configure-plugin"                               : Run Last / No Recursion / No Hooks
            typedef G::Signal<void> ConfigurePluginSignalType;
            typedef G::SignalProxy<G::TypeInstance, ConfigurePluginSignalType> ConfigurePluginSignalProxy;
            static const ConfigurePluginSignalType configure_plugin_signal;

            // "free-data"                                      : Run Last / No Recursion / No Hooks
            typedef G::Signal<void> FreeDataSignalType;
            typedef G::SignalProxy<G::TypeInstance, FreeDataSignalType> FreeDataSignalProxy;
            static const FreeDataSignalType free_data_signal;

            // "orientation-changed"                            : Run Last / No Recursion / No Hooks
            typedef G::Signal<void, Gtk::Orientation> OrientationChangedSignalType;
            typedef G::SignalProxy<G::TypeInstance, OrientationChangedSignalType> OrientationChangedSignalProxy;
            static const OrientationChangedSignalType orientation_changed_signal;

            //  "save"                                           : Run Last / No Recursion / No Hooks
            typedef G::Signal<void> SaveSignalType;
            typedef G::SignalProxy<G::TypeInstance, SaveSignalType> SaveSignalProxy;
            static const SaveSignalType save_signal;

            //  "screen-position-changed"                        : Run Last / No Recursion / No Hooks
            typedef G::Signal<void, ScreenPosition> ScreenPositionChangedSignalType;
            typedef G::SignalProxy<G::TypeInstance, ScreenPositionChangedSignalType> ScreenPositionChangedSignalProxy;
            static const ScreenPositionChangedSignalType screen_position_changed_signal;

            //  "size-changed"                                   : Run Last / No Recursion / No Hooks
            typedef G::Signal<void> SizeChangedSignalType;
            typedef G::SignalProxy<G::TypeInstance, SizeChangedSignalType> SizeChangedSignalProxy;
            static const SizeChangedSignalType size_changed_signal;
            
/// @}
/// @name Property Prototypes
/// @{
    
            // "display-name"             gchar*                : Read
            typedef G::ReadableProperty<String> DisplayNamePropertyType;
            typedef G::PropertyProxy<G::Object, DisplayNamePropertyType> DisplayNamePropertyProxy;
            static const DisplayNamePropertyType display_name_property;

            // "expand"                   gboolean              : Read / Write
            typedef G::Property<bool> ExpandPropertyType;
            typedef G::PropertyProxy<G::Object, ExpandPropertyType> ExpandPropertyProxy;
            static const ExpandPropertyType expand_property;
             
            //  "id"                       gchar*                : Read
            typedef G::ReadableProperty<String> IdPropertyType;
            typedef G::PropertyProxy<G::Object, IdPropertyType> IdPropertyProxy;
            static const IdPropertyType id_property;
            
            //  "name"                     gchar*                : Read
            typedef G::ReadableProperty<String> NamePropertyType;
            typedef G::PropertyProxy<G::Object, NamePropertyType> NamePropertyProxy;
            static const NamePropertyType name_property;

            //  "screen-position"          XfceScreenPosition    : Read
            typedef G::ReadableProperty<XfceScreenPosition> ScreenPositionPropertyType;
            typedef G::PropertyProxy<G::Object, NamePropertyType> ScreenPositionPropertyProxy;
            static const ScreenPositionPropertyType screen_position_property;

            //  "size"                     gint                  : Read
            typedef G::ReadableProperty<int> SizePropertyType;
            typedef G::PropertyProxy<G::Object, SizePropertyType> SizePropertyProxy;
            static const SizePropertyType size_property;

        public:

/// @}
/// @name Accessors
/// @{

            XfcePanelPlugin *xfce_panel_plugin() const;
            operator XfcePanelPlugin *() const;

            String get_name() const;
            String get_id() const;
            String get_display_name() const;
            int get_size() const;
            ScreenPosition get_screen_position() const;
            bool get_expand() const;
            Gtk::Orientation get_orientation() const;
            String lookup_rc_file() const;

/// @}
/// @name Methods
/// @{
        
            void set_expand(bool expand);
            void add_action_widget(Gtk::Widget *widget);
            void menu_insert_item(Gtk::MenuItem *item);
            void menu_show_about();
            void menu_show_configure();
            void block_menu();
            void unblock_menu();
            void register_menu(Gtk::Menu *menu);
            String save_location(bool create);
            void focus_widget(Gtk::Widget *widget);
            void set_panel_hidden(bool hidden);

/// @}
/// @name Property Proxies
/// @{

            const DisplayNamePropertyProxy property_display_name();
            
            const ExpandPropertyProxy property_expand();

            const IdPropertyProxy property_id();

            const NamePropertyProxy property_name();

            const ScreenPositionPropertyProxy property_screen_position();

            const SizePropertyProxy property_size();
            
/// @}
/// @name Signal Proxies
/// @{
            
            AboutSignalProxy signal_about();
            
            ConfigurePluginSignalProxy signal_configure_plugin();
            
            FreeDataSignalProxy signal_free_data();
            
            OrientationChangedSignalProxy signal_orientation_changed();
            
            SaveSignalProxy signal_save();
            
            ScreenPositionChangedSignalProxy signal_screen_position_changed();
            
            SizeChangedSignalProxy signal_size_changed();
/// @}
        };

        class PanelPlugin : public PanelPluginInterface, public G::Object {
        };

    } // namespace De
} // namespace Xfc

#include <xfc/panel/inline/panel.inl>

#endif // XFC_DE_PANEL_HH
