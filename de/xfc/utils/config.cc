/**
    Impl. the xfconf client wrapper for XFC.
*/
#include "config.hh"
#include <stdexcept>
#include <sstream>
#include <xfc/glib/error.hh>

#include <xfc/glib/private/connection.hh>

using namespace std;

namespace Xfc {
    namespace De {

        XfconfInit::XfconfInit()
        {
            G::Error error;
            
            if( !xfconf_init( error ))
                throw error;
        }

        XfconfInit::~XfconfInit()
        {
            xfconf_shutdown(); // xconf takes care of refcounting !
        }

        Config::Config( XfconfChannel *channel, bool owns_reference ) : G::Object((GObject *)channel, owns_reference ) {}

        Config::Config( const String &ch_name ) : G::Object((GObject *)xfconf_channel_get( ch_name.c_str()), false) {}
        
        Config::~Config() {}

        bool Config::set( const String &property, const G::Value &val )
        {
            return xfconf_channel_set_property( xfconfchannel(), property.c_str(), val );
        }
        
        G::Value Config::get( const String &property ) const
        {
            G::Value val;
            
            if( xfconf_channel_get_property( xfconfchannel(), property.c_str(), val ))
                return val;

            ostringstream os;
            os << "Can't get " << property << " from xconf";
            
            throw invalid_argument( os.str() );
        }

        bool Config::has_a( const String &property ) const
        {
            return xfconf_channel_has_property( xfconfchannel(), property.c_str() );
        }
        
        void Config::reset( const String &property, const String &property_base, bool recursive )
        {
            xfconf_channel_reset_property( xfconfchannel(), property_base.c_str(), recursive );
        }
        
        bool Config::is_locked( const String &property ) const
        {
            return xfconf_channel_is_property_locked( xfconfchannel(), property.c_str() );
        }

        // This is normally defined in the Marshal class .. but we only need this ones
        static void void_string_value_callback( void *data, const char *pname, GValue *pval )
        {
            G::Connection *c = static_cast<G::Connection*>(data);
            if (c) {
                typedef sigc::slot<void, const String &, G::Value &> SlotType;
                SlotType& slot = static_cast<SlotType&>(c->slot_);

                String name( pname );
                G::Value value( pval );
                
                slot( name, value );
            }
        }

        const Config::PropertyChangedSignalType Config::property_changed_signal("property_changed", (GCallback)&void_string_value_callback);

        const Config::ChannelNamePropertyType Config::channel_name_property( "channel_name" );

        const Config::PropertyBasePropertyType Config::property_base_property( "property_base" );
    }
}
