inline GtkPaperSize *Xfc::Gtk::PaperSize::gtk_paper_size() const
{
    return reinterpret_cast<GtkPaperSize*>(_obj);
}

inline Xfc::Gtk::PaperSize::operator GtkPaperSize* () const
{
    return this ? ((GtkPaperSize*)_obj) : NULL;
}
