#include "panel.hh"

namespace Xfc {
    namespace De {

    PanelPlugin::PanelPlugin( XfcePanelPlugin *panel, bool owns_reference = false )
    {
    }

    String PanelPlugin::get_name() const
    {
        return xfce_panel_plugin_get_name( xfce_panel_plugin() );
    }

    String PanelPlugin::get_id() const
    {
        return xfce_panel_plugin_get_id( xfce_panel_plugin() );
    }
    
    String PanelPlugin::get_display_name() const
    {
        return xfce_panel_plugin_get_display_name( xfce_panel_plugin());
    }
    
    int PanelPlugin::get_size() const
    {
        return xfce_panel_plugin_get_size( xfce_panel_plugin());
    }
    
    ScreenPosition PanelPlugin::get_screen_position() const
    {
        return xfce_panel_plugin_get_screen_position( xfce_panel_plugin());
    }
    
    bool PanelPlugin::get_expand() const
    {
        return xfce_panel_plugin_get_expand( xfce_panel_plugin());
    }
    
    Gtk::Orientation PanelPlugin::get_orientation() const
    {
        return xfce_panel_plugin_get_orientation( xfce_panel_plugin());
    }
    
    String PanelPlugin::lookup_rc_file() const
    {
        return xfce_panel_plugin_loogup_rc_file( xfce_panel_plugin());
    }

    void PanelPlugin::set_expand(bool expand)
    {
        xfce_panel_plugin_set_expand( xfce_panel_plugin(), expand );
    }
    
    void PanelPlugin::add_action_widget(Gtk::Widget *widget)
    {
        xfce_panel_plugin_add_action_widget( xfce_panel_plugin(), widget );
    }
    
    void PanelPlugin::menu_insert_item(Gtk::MenuItem *item)
    {
        xfce_panel_plugin_menu_insert_item(xfce_panel_plugin(), item );
    }
    
    void PanelPlugin::menu_show_about()
    {
        xfce_panel_plugin_menu_show_about( xfce_panel_plugin());
    }
    
    void PanelPlugin::menu_show_configure()
    {
        xfce_panel_plugin_menu_show_configure( xfce_panel_plugin());
    }
    
    void PanelPlugin::block_menu()
    {
        xfce_panel_plugin_block_menu( xfce_panel_plugin());
    }
    
    void PanelPlugin::unblock_menu()
    {
        xfce_panel_plugin_unblock_menu( xfce_panel_plugin());
    }
    
    void register_menu(Gtk::Menu *menu)
    {
        xfce_panel_plugin_register_menu( xfce_panel_plugin(), menu );
    }
    
    String PanelPlugin::save_location(bool create)
    {
        return xfce_panel_plugin_save_location( xfce_panel_plugin(), create );
    }
    
    void PanelPlugin::focus_widget(Gtk::Widget *widget)
    {
        xfce_panel_plugin_focus_widget( xfce_panel_plugin(), widget );
    }
    
    void PanelPlugin::set_panel_hidden(bool hidden)
    {
        xfce_panel_plugin_set_panel_hidden( xfce_panel_plugin(), hidden );
    }

    // Marshal
    static void marshal_void_void( void *data )
    {
        G::Connection *c = static_cast<G::Connection*>(data);
        if (c) {
            typedef sigc::slot<void> SlotType;
            SlotType& slot = static_cast<SlotType&>(c->slot_);

            slot();
        }
    }

    static void marshal_void_orientation( void *data, GtkOrientaion orig )
    {
        G::Connection *c = static_cast<G::Connection*>(data);
        if (c) {
            typedef sigc::slot<void, Gtk::Orientation> SlotType;
            SlotType& slot = static_cast<SlotType&>(c->slot_);

            slot((Gtk::Orientation)orig);
        }
    }

    static void marshal_void_screen_position( void *data, XfceScreenPosition pos)
    {
        G::Connection *c = static_cast<G::Connection*>(data);
        if (c) {
            typedef sigc::slot<void, ScreenPosition> SlotType;
            SlotType& slot = static_cast<SlotType&>(c->slot_);

            slot((ScreenPosition)pos);
        }
    }

    static void marshal_void_int( void *data, gint n)
    {
        G::Connection *c = static_cast<G::Connection*>(data);
        if (c) {
            typedef sigc::slot<void, int> SlotType;
            SlotType& slot = static_cast<SlotType&>(c->slot_);

            slot( n );
        }
    }

    const PanelPlugin::AboutSignalType PanelPlugin::about_signal( "about", (GCallback)&marshal_void_void );
    
    const PanelPlugin::ConfigurePluginSignalType PanelPlugin::configure_plugin_signal( "configure-plugin", (GCallback)&marshal_void_void );
    
    const PanelPlugin::FreeDataSignalType PanelPlugin::free_data_signal( "free-data", (GCallback)&marshal_void_void );
    
    const PanelPlugin::OrientationChangedSignalType PanelPlugin::orientation_changed_signal( "orientation-changed", (GCallback)&marshal_void_orientaion);
    
    const PanelPlugin::SaveSignalType PanelPlugin::save_signal( "save". (GCallback)&marshal_void_void);
    
    const PanelPlugin::ScreenPositionChangedSignalType PanelPlugin::screen_position_changed_signal( "screen-position-changed", (GCallback)&marshal_void_screen_position);
    
    const PanelPlugin::SizeChangedSignalType PanelPlugin::size_changed_signal( "size-changed", (GCallback)&marshal_void_int);
    

    const PanelPlugin::DisplayNamePropertyType PanelPlugin::display_name_property( "display-name" );

    const PanelPlugin::ExpandPropertyType PanelPlugin::expand_property( "expand" );
             
    const PanelPlugin::IdPropertyType PanelPlugin::id_property( "id" );
            
    const PanelPlugin::NamePropertyType PanelPlugin::name_property( "name" );

    const PanelPlugin::ScreenPositionPropertyType PanelPlugin::screen_position_property( "screen-position" );

    const PanelPlugin::SizePropertyType PanelPlugin::size_property( "size" );
    }
}
