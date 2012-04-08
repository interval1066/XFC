/*  XFC: Xfce Foundation Classes (Glade Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  xml.inl - Glade::Xml inline functions
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

inline GladeXML*
Xfc::Glade::Xml::glade_xml() const
{
	return reinterpret_cast<GladeXML*>(instance_);
}

inline Xfc::Glade::Xml::operator GladeXML* () const
{
	return this ? glade_xml() : 0;
}

template<typename WidgetType>
inline bool
Xfc::Glade::Xml::get_widget(const String& name, WidgetType *&widget) const
{
	widget = 0;	
	GtkWidget *tmp_widget = glade_xml_get_widget(glade_xml(), name.c_str());
	if (tmp_widget)
	{
		typedef typename WidgetType::CObjectType GtkWidgetType;
		widget = G::Object::wrap<WidgetType>((GtkWidgetType*)tmp_widget);
	}
	return widget != 0; 
}

template<typename DerivedType>
inline bool
Xfc::Glade::Xml::get_widget_derived(const String& name, DerivedType *&widget) const
{
	widget = 0;	
	GtkWidget *tmp_widget = glade_xml_get_widget(glade_xml(), name.c_str());
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

