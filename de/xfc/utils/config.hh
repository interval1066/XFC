/*
    An application-defined domain for storing configuration settings
*/

#ifndef XFC_DE_CONFIG_HH
#define XFC_DE_CONFIG_HH

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_G_VALUE_HH
#include <xfc/glib/value.hh>
#endif

#ifndef __XFCONF_H__
extern "C" {
#ifdef __GNUC__
#pragma GCC system_header
#endif
#include <xfconf/xfconf.h>
}
#endif

// Needed in XFC !
namespace Xfc {
    namespace De { // Desktop env namespace
        /**
            Special helper class to ensure xconf init to be performed when needed.
        */
        class XfconfInit {
        protected:
            XfconfInit();
            
        public:
            virtual ~XfconfInit();
        };

        /**
            An Config is a representation of a restricted domain or
            namespace that an application can define to store configuration
            settings. This is to ensure that different applications do
            not store configuration keys with the same names.
        */
        class Config : public XfconfInit, public G::Object {
        protected:
        
/// @name Constructors
/// @{

            explicit Config( XfconfChannel *channel, bool owns_reference = true );

/// @}            
/// @name Property Prototypes
/// @{
    
            // "channel-name"             gchar*                : Read / Write / Construct Only
            typedef G::ReadableProperty<String> ChannelNamePropertyType;
            typedef G::PropertyProxy<G::Object, ChannelNamePropertyType> ChannelNamePropertyProxy;
            static const ChannelNamePropertyType channel_name_property;
            
            // "property-base"            gchar*                : Read / Write / Construct Only
            typedef G::ReadableProperty<String> PropertyBasePropertyType;
            typedef G::PropertyProxy<G::Object, PropertyBasePropertyType> PropertyBasePropertyProxy;
            static const PropertyBasePropertyType property_base_property;

/// @}
/// @name Signal Prototypes
/// @{

            // "property-changed"                               : Run Last / Has Details
            typedef G::Signal<void, const String &, G::Value &> PropertyChangedSignalType;
            typedef G::SignalProxy<G::TypeInstance, PropertyChangedSignalType> PropertyChangedSignalProxy;
            static const PropertyChangedSignalType property_changed_signal;

        public:
        
/// @}
/// @name Constructors
/// @{
        
            /**
                Opens up a xfconf channel if it exist, and create it if
                it down not.
            */
            Config( const String &channel );
            
            virtual ~Config();

/// @}
/// @name Accessors
/// @{

            XfconfChannel *xfconfchannel() const;
            operator XfconfChannel *() const;
            
            G::Value get( const String &property ) const;
            bool has_a( const String &property ) const;
            bool is_locked( const String &property ) const;
            
            // Syntactic sugar
            G::Value operator[]( const String &property ) const {return get( property );}

/// @}
/// @name Methods
/// @{
            
            bool set( const String &property, const G::Value &val );
            void reset( const String &property, const String &base_property = "/", bool recursive = true );

/// @}
/// @name Property Proxies
/// @{

            const ChannelNamePropertyProxy property_channel_name();

            const PropertyBasePropertyProxy property_property_base();

/// @}
/// @name Signal Proxies
/// @{

            const PropertyChangedSignalProxy signal_property_changed();

            // The Xfce interface has a lot of helpers but is this really needed,
            // when we have the G::Value wrapper ?
/// @}
        };
    } // namespace De
} // namespace Xfc

#include <xfc/utils/inline/config.inl>

#endif
