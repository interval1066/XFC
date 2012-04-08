inline const Xfc::De::Config::ChannelNamePropertyProxy Xfc::De::Config::property_channel_name()
{
     return ChannelNamePropertyProxy(this, &channel_name_property);
}

inline const Xfc::De::Config::PropertyBasePropertyProxy Xfc::De::Config::property_property_base()
{
     return PropertyBasePropertyProxy(this, &property_base_property);
}

inline const Xfc::De::Config::PropertyChangedSignalProxy Xfc::De::Config::signal_property_changed()
{
    return PropertyChangedSignalProxy(this, &property_changed_signal);
}

inline XfconfChannel* Xfc::De::Config::xfconfchannel() const
{
	return reinterpret_cast<XfconfChannel*>(instance_);
}

inline Xfc::De::Config::operator XfconfChannel * () const
{
	return this ? xfconfchannel() : 0;
}
