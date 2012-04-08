namespace Xfc {
    namespace De {
        XfcePanelPlugin *PanelPlugin::xfce_panel_plugin() const
        {
            return reinterpret_cast<XfcePanelPlugin*>(instance_);
        }
        
        PanelPlugin::operator XfcePanelPlugin * () const
        {
            return this ? xfce_panel_plugin() : 0;
        }
        
        inline const PanelPlugin::DisplayNamePropertyProxy PanelPlugin::property_display_name()
        {
            return DisplayNamePropertyProxy(this, &display_name_property );
        }
            
        inline const PanelPlugin::ExpandPropertyProxy PanelPlugin::property_expand()
        {
            return ExpandPropertyProxy(this, &expand_property);
        }

        inline const PanelPlugin::IdPropertyProxy property_id()
        {
            return IdPropertyProxy(this, &id_property);
        }

        const PanelPlugin::NamePropertyProxy PanelPlugin::property_name()
        {
            return NamePropertyProxy(this, &name_property);
        }

        const PanelPlugin::ScreenPositionPropertyProxy PanelPlugin::property_screen_position()
        {
            return ScreenPositionPropertyProxy(this, &screen_position_property );
        }

        const PanelPlugin::SizePropertyProxy PanelPlugin::property_size()
        {
            return SizePropertyProxy(this,&size_property);
        }
    }
}
