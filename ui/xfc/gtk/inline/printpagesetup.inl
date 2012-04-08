inline GtkPageSetup *Xfc::Gtk::PageSetup::gtk_page_setup() const
{
    return reinterpret_cast<GtkPageSetup*>(instance_);
}

inline Xfc::Gtk::PageSetup::operator GtkPageSetup* () const
{
    return this ? ((GtkPageSetup*)instance_) : NULL;
}
