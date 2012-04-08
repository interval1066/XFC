inline GtkPrintOperationPreview *Xfc::Gtk::PrintOperationPreview::gtk_printoperationpreview() const
{
    return reinterpret_cast<GtkPrintOperationPreview*>(instance_);
}

inline Xfc::Gtk::PrintOperationPreview::operator GtkPrintOperationPreview* () const
{
    return this ? ((GtkPrintOperationPreview*)instance_) : 0;
}
