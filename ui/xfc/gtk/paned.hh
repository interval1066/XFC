/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
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
 
/// @file xfc/gtk/paned.hh
/// @brief A GtkPaned, GtkHPaned and GtkVPaned C++ wrapper interface.
///
/// Provides Paned, the base class for widgets with two panes, arranged either
/// horizontally (HPaned) or vertically (VPaned).

#ifndef XFC_GTK_PANED_HH
#define XFC_GTK_PANED_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef __GTK_HPANED_H__
#include <gtk/gtkhpaned.h>
#endif

#ifndef __GTK_VPANED_H__
#include <gtk/gtkvpaned.h>
#endif

namespace Xfc {
	
namespace Gtk {

/// @class Paned paned.hh xfc/gtk/paned.hh
/// @brief A GtkPaned C++ wrapper class.
///
/// Paned is the base class for widgets with two panes, arranged either horizontally (HPaned)
/// or vertically (VPaned). Child widgets are added to the panes of the widget with pack1()
/// and pack2(). The division beween the two children is set by default from the size requests
/// of the children, but it can be adjusted by the user. A paned widget draws a separator
/// between the two child widgets and a small handle that the user can drag to adjust the
/// division. It does not draw any relief around the children or around the separator. (The
/// space in which the separator is drawn is called the gutter.) Often, it is useful to put
/// each child inside a Frame with the shadow type set to Gtk::SHADOW_IN so that the gutter
/// appears as a ridge. The application can set the position of the separator as if it were
/// set by the user, by calling set_position().
///
/// Each child has two options that can be set, resize and shrink. If resize is true, then
/// when the Paned is resized, that child will expand or shrink along with the paned widget.
/// If shrink is true, then when that child can be made smaller than it's requisition by the
/// user. Setting shrink to false allows the application to set a minimum size. If resize is
/// false for both children, then this is treated as if resize is true for both children.
///
/// <B>Example:</B> Creating a paned widget with minimum sizes.
/// @code
/// Gtk::HPaned *hpaned = new Gtk::HPaned;
/// hpaned->set_size_request(200, -1);
///
/// Gtk::Frame *frame1 = new Gtk::Frame;
/// frame1->set_shadow_type(Gtk::SHADOW_IN);
/// frame1->set_size_request(50, -1);
///
/// Gtk::Frame *frame2 = new Gtk::Frame;
/// frame2->set_shadow_type(Gtk::SHADOW_IN);
/// frame2->set_size_request(50, -1);
///
/// hpaned->pack1(*frame1, true, false);
/// hpaned->pack2(*frame2, false, false);
/// @endcode
///
/// <B>See also:</B> the <A HREF="../../howto/html/paned.html">Paned Window</A> HOWTO and example.

class Paned : public Container
{
	friend class G::Object;

	Paned(const Paned&);
	Paned& operator=(const Paned&);
	
protected:
/// @name Constructors
/// @{

	Paned();
	///< Construct a new Paned.

	explicit Paned(GtkPaned *paned, bool owns_reference = false);
	///< Construct a new Paned from an existing GtkPaned.
	///< @param paned A pointer to a GtkPaned.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>paned</EM> can be a newly created GtkPaned or an existing
	///< GtkPaned (see G::Object::Object).

	virtual ~Paned() = 0;
	///< Destructor.
	
/// @}

public:
	typedef GtkPaned CObjectType;

/// @name Accessors
/// @{

	GtkPaned* gtk_paned() const;
	///< Get a pointer to the GtkPaned structure.

	operator GtkPaned* () const;
	///< Conversion operator; safely converts a Paned to a GtkPaned pointer.

	Gdk::Window* handle() const;
	///< Returns the handle window in the divider between the two panes.

	int get_position() const;
	///< Obtains the position of the divider between the two panes.
	
	Widget* get_child1() const;
	///< Obtains the first child of the paned widget.
	/// @return The first child, or null if it is not set.

	Widget* get_child2() const;
	///< Obtains the second child of the paned widget.
	/// @return The second child, or null if it is not set.

/// @}
/// @name Methods
/// @{

	void add1(Widget& child);
	///< Adds a child to the top or left pane with default parameters. 
	///< @param child The child to add.
	///<
	///< This is equivalent to pack1(child, false, true).

	void add2(Widget& child);
	///< Adds a child to the bottom or right pane with default parameters. 
	///< @param child The child to add.
	///<
	///< This is equivalent to pack2(child, true, true).
	
	void pack1(Widget& child, bool resize = false, bool shrink = true);
	///< Adds a child to the top or left pane.
	///< @param child The child to add.
	///< @param resize Should this child expand when the paned widget is resized.
	///< @param shrink Can this child be made smaller than its requsition.

	void pack2(Widget& child, bool resize = true, bool shrink = true);
	///< Adds a child to the bottom or right pane.
	///< @param child The child to add.
	///< @param resize Should this child expand when the paned widget is resized.
	///< @param shrink Can this child be made smaller than its requsition.

	void set_position(int position);
	///< Sets the position of the divider between the two panes.
	///< @param position The pixel position of divider, a negative value means that the position is unset.

/// @}
};

/// @class HPaned paned.hh xfc/gtk/paned.hh
/// @brief A GtkHPaned C++ wrapper class.
///
/// The HPaned widget is a container widget with two children arranged horizontally. 
/// The division between the two panes is adjustable by the user by dragging a handle.
/// See Paned for details.
///
/// <B>See also:</B> the <A HREF="../../howto/html/paned.html">Paned Window</A> HOWTO and example.

class HPaned : public Paned
{
	friend class G::Object;

	HPaned(const HPaned&);
	HPaned& operator=(const HPaned&);
	
protected:
/// @name Constructor
/// @{

	explicit HPaned(GtkHPaned *hpaned, bool owns_reference = false);
	///< Construct a new HPaned from an existing GtkHPaned.
	///< @param hpaned A pointer to a GtkHPaned.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>hpaned</EM> can be a newly created GtkHPaned or an existing
	///< GtkHPaned (see G::Object::Object).
	
/// @}

public:
	typedef GtkHPaned CObjectType;

/// @name Constructors
/// @{

	HPaned();
	///< Construct a new HPaned.

	virtual ~HPaned();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkHPaned* gtk_hpaned() const;
	///< Get a pointer to the GtkHPaned structure.

	operator GtkHPaned* () const;
	///< Conversion operator; safely converts a HPaned to a GtkHPaned pointer.

/// @}
};

/// @class VPaned paned.hh xfc/gtk/paned.hh
/// @brief A GtkVPaned C++ wrapper class.
///
/// The VPaned widget is a container widget with two children arranged vertically.
/// The division between the two panes is adjustable by the user by dragging a
/// handle. See Paned for details.
///
/// <B>See also:</B> the <A HREF="../../howto/html/paned.html">Paned Window</A> HOWTO and example.

class VPaned : public Paned
{
	friend class G::Object;

	VPaned(const VPaned&);
	VPaned& operator=(const VPaned&);
	
protected:
/// @name Constructors
/// @{

	explicit VPaned(GtkVPaned *vpaned, bool owns_reference = false);
	///< Construct a new VPaned from an existing GtkVPaned.
	///< @param vpaned A pointer to a GtkVPaned.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>vpaned</EM> can be a newly created GtkVPaned or an existing
	///< GtkVPaned (see G::Object::Object).

/// @}

public:
	typedef GtkVPaned CObjectType;

/// @name Constructors
/// @{

	VPaned();
	///< Construct a new VPaned.

	virtual ~VPaned();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkVPaned* gtk_vpaned() const;
	///< Get a pointer to the GtkVPaned structure.

	operator GtkVPaned* () const;
	///< Conversion operator; safely converts a VPaned to a GtkVPaned pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/paned.inl>

#endif // XFC_GTK_PANED_HH

