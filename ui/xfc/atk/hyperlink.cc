/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  hyperlink.cc - AtkHyperlink C++ wrapper implementation
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
 
#include "hyperlink.hh"
#include "hyperlinksignals.hh"
#include "object.hh"
#include "private/hyperlinkclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Atk::Hyperlink
 */

Atk::Hyperlink::Hyperlink(AtkHyperlink *hyperlink, bool owns_reference)
: G::Object((GObject*)hyperlink, owns_reference)
{
}
	
Atk::Hyperlink::~Hyperlink() 
{
}
	
String
Atk::Hyperlink::get_uri(int i) const
{
	char *uri = atk_hyperlink_get_uri(atk_hyperlink(), i);
	String s(uri);
	g_free(uri);
	return s;
}

Atk::Object*
Atk::Hyperlink::get_object(int i) const
{
	AtkObject *object = atk_hyperlink_get_object(atk_hyperlink(), i);
	return object ? G::Object::wrap<Atk::Object>(object) : 0;
}

/*  Atk::HyperlinkClass
 */

void
Atk::HyperlinkClass::init(AtkHyperlinkClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->link_activated = &link_activated_proxy;
}

AtkHyperlinkClass*
Atk::HyperlinkClass::get_parent_class(void *instance)
{
	return static_cast<AtkHyperlinkClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Atk::HyperlinkClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(ATK_TYPE_HYPERLINK, (GClassInitFunc)&init);
	}
	return type;
}

void*
Atk::HyperlinkClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Atk::HyperlinkClass::link_activated_proxy(AtkHyperlink *link)
{
	HyperlinkSignals *signals = dynamic_cast<HyperlinkSignals*>(G::ObjectSignals::pointer((GObject*)link));
	if (signals)
		signals->on_link_activated();
	else
	{
		AtkHyperlinkClass *g_class = get_parent_class(link);
		if (g_class && g_class->link_activated)
			g_class->link_activated(link);
	}
}

/*  Atk::Hyperlink signals
 */

const Atk::Hyperlink::LinkActivatedSignalType Atk::Hyperlink::link_activated_signal("link_activated", (GCallback)&G::Marshal::void_callback);

