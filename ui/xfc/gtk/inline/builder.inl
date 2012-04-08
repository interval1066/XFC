inline GtkBuilder* Xfc::Gtk::Builder::gtk_builder() const
{
    return reinterpret_cast<GtkBuilder*>(instance_);
}
	
inline Xfc::Gtk::Builder::operator GtkBuilder* () const
{
    return this ? gtk_builder() : NULL;
}
    
template<typename WidgetType>
inline bool
Xfc::Gtk::Builder::get_widget(const String& name, WidgetType *&widget) const
{
	widget = 0;	
	GtkWidget *tmp_widget = GTK_WIDGET(gtk_builder_get_object(gtk_builder(), name.c_str()));
	if (tmp_widget)
	{
		typedef typename WidgetType::CObjectType GtkWidgetType;
		widget = G::Object::wrap<WidgetType>((GtkWidgetType*)tmp_widget);
	}
	return widget != 0; 
}

template<typename WidgetType>
inline bool
Xfc::Gtk::Builder::get_widget(Xfc::Gtk::Window *parent, const String& name, WidgetType *&widget) const
{
	widget = 0;
	GtkWidget *tmp_widget = GTK_WIDGET(gtk_builder_get_object(gtk_builder(), name.c_str()));
	if (tmp_widget)
	{
		typedef typename WidgetType::CObjectType GtkWidgetType;
		widget = G::Object::wrap<WidgetType>((GtkWidgetType*)tmp_widget);
	}
	if ((widget != 0) && (parent != 0))
	{
		widget->set_transient_for(parent);
	}
	return widget != 0;
}

template<typename DerivedType>
inline bool
Xfc::Gtk::Builder::get_widget_derived(const String& name, DerivedType *&widget) const
{
	widget = 0;	
	GtkWidget *tmp_widget = GTK_WIDGET(gtk_builder_get_object(gtk_builder(), name.c_str()));
	if (tmp_widget)
	{
		G::Object *object = G::Object::pointer((GObject*)tmp_widget);
		if (object)
		{
			widget = dynamic_cast<DerivedType*>(object);
			if (!widget)
				g_error("Wrong derived widget argument type passed for \"%s\"\n", name.c_str());
		}
		else
		{
			typedef typename DerivedType::CObjectType GtkWidgetType;
			widget = new DerivedType((GtkWidgetType*)tmp_widget, *this);
		}	
	} 
	return widget != 0;
}
template<typename DerivedType>
inline bool
Xfc::Gtk::Builder::get_widget_derived(Xfc::Gtk::Window *parent, const String& name, DerivedType *&widget) const
{
	widget = 0;
	GtkWidget *tmp_widget = GTK_WIDGET(gtk_builder_get_object(gtk_builder(), name.c_str()));
	if (tmp_widget)
	{
		G::Object *object = G::Object::pointer((GObject*)tmp_widget);
		if (object)
		{
			widget = dynamic_cast<DerivedType*>(object);
			if (!widget)
				g_error("Wrong derived widget argument type passed for \"%s\"\n", name.c_str());
		}
		else
		{
			typedef typename DerivedType::CObjectType GtkWidgetType;
			widget = new DerivedType((GtkWidgetType*)tmp_widget, *this);
		}
	}
	if ((widget != 0) && (parent != 0))
	{
		widget->set_transient_for(parent);
	}
	return widget != 0;
}
