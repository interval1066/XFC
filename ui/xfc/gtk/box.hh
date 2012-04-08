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
 
/// @file xfc/gtk/box.hh
/// @brief A GtkBox, GtkHBox and GtkVBox C++ wrapper interface.
///
/// Box is an abstract widget which encapsulates functionallity for a particular kind of container,
/// one that organizes a variable number of widgets into a rectangular area. Box currently has two
/// derived classes, HBox and VBox.

#ifndef XFC_GTK_BOX_HH
#define XFC_GTK_BOX_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef __GTK_HBOX_H__
#include <gtk/gtkhbox.h>
#endif

#ifndef __GTK_VBOX_H__
#include <gtk/gtkvbox.h>
#endif

#ifndef XFC_GTK_BOX_CHILD_HH
#include <xfc/gtk/boxchild.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class Box box.hh xfc/gtk/box.hh
/// @brief A GtkBox C++ wrapper class.
///
/// Box is an abstract widget which encapsulates functionallity for a particular kind of container,
/// one that organizes a variable number of widgets into a rectangular area. Box currently has two
/// derived classes, HBox and VBox. The rectangular area of a Box is organized into either a single
/// row or a single column of child widgets depending upon whether the box is of type HBox or VBox,
/// respectively. Thus, all children of a Box are allocated one dimension in common, which is the
/// height of a row, or the width of a column.
///
/// Box uses a notion of packing. Packing refers to adding widgets with reference to a particular
/// position in a Container. For a Box, there are two reference positions: the start and the end
/// of the box. For a VBox, the start is defined as the top of the box and the end is defined as
/// the bottom. For a HBox the start is defined as the left side and the end is defined as the
/// right side. Use repeated calls to pack_start() to pack widgets into a Box from start to end.
/// Use pack_end() to add widgets from end to start. You may intersperse these calls and add
/// widgets from both ends of the same Box.
/// 
/// Because Box is a Container, you may also use Gtk::Container::add() to insert widgets
/// into the box, and they will be packed as if with pack_start() using the default values:
/// expand true, fill true and padding zero. Use Gtk::Container::remove() to remove widgets
/// from the Box.
/// 
/// Use set_homogeneous() to specify whether or not all children of the Box are forced to
/// get the same amount of space. Use set_spacing() to determine how much space will be 
/// minimally placed between all children in the Box. Use reorder_child() to move a Box child 
/// to a different place in the box. Use set_child_packing() to reset the expand, fill, and
/// padding attributes of any Box child. Use query_child_packing() to query these fields.
///
/// <B>See also:</B> the <A HREF="../../howto/html/boxes.html">Packing Boxes</A> HOWTO and example.

class Box : public Container
{
	friend class G::Object;

	Box(const Box&);
	Box& operator=(const Box&);
	
protected:
/// @name Constructors
/// @{

	explicit Box(GtkBox *box, bool owns_reference = false);
	///< Construct a new Box from an existing GtkBox.
	///< @param box A pointer to a GtkBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>box</EM> can be a newly created GtkBox or an existing
	///< GtkBox. (see G::Object::Object).

	virtual ~Box() = 0;
	///< Destructor.
	
/// @}

public:
	typedef GtkBox CObjectType;

/// @name Accessors
/// @{

	GtkBox* gtk_box() const;
	///< Get a pointer to the GtkBox structure.

	operator GtkBox* () const;
	///< Conversion operator; safely converts a Box to a GtkBox pointer.

	bool children(std::vector<BoxChild*>& child_list) const;
	///< Get a list of children belonging to the Box.
	///< @param child_list A reference to an empty vector of BoxChild* to hold the children.
	///< @return <EM>true</EM> if successful, <EM>false</EM> otherwise.
	///<
	///< The data is a vector of BoxChild pointers. The returned children do not have
	///< a reference added, so you do not need to unref them.

	bool get_homogeneous() const;
	///< Returns whether the box is homogeneous (all children are the same size); see set_homogeneous().
	///< @return <EM>true</EM> if the box is homogeneous.

	int get_spacing() const;
	///< Gets the value set by set_spacing().
	///< @return The spacing between children.
	
/// @}
/// @name Methods
/// @{

	void pack_start(Widget& child, bool expand = true, bool fill = true, unsigned int padding = 0);
	///< Adds child to the box, packed with reference to the start of box.
	///< @param child   The Widget to be added to the box.
	///< @param expand  Set <EM>true</EM> if the new child is to be given extra space allocated to the box.
	///<	            The extra space is divided evenly between all children of box using this option.
	///< @param fill    Set <EM>true</EM> if space given to child by the expand option is actually allocated
	///<                to the child, rather than just padding it. This parameter has no effect if expand
	///<                is set to false. A child is always allocated the full height of a HBox and the
	///<                full width of a VBox. This option affects the other dimension.
	///< @param padding The extra space in pixels to put between this child and its neighbors, over
	///<                and above the global amount specified by spacing in Box. If child is a widget
	///<                at one of the reference ends of the box, then padding pixels are also put
	///<                between child and the reference edge of box.
	///<
	///< The child is packed after any other child packed with reference to the start of box. The default
	///< arguments specified are those most frequently used.
	
	void pack_end(Widget& child, bool expand = true, bool fill = true, unsigned int padding = 0);
	///< Adds child to the box, packed with reference to the end of box.
	///< @param child   The Widget to be added to the box.
	///< @param expand  Set <EM>true</EM> if the new child is to be given extra space allocated to the box.
	///<	            The extra space is divided evenly between all children of box using this option.
	///< @param fill    Set <EM>true</EM> if space given to child by the expand option is actually allocated
	///<                to the child, rather than just padding it. This parameter has no effect if expand
	///<                is set to false. A child is always allocated the full height of a HBox and the
	///<                full width of a VBox. This option affects the other dimension.
	///< @param padding The extra space in pixels to put between this child and its neighbors, over
	///<                and above the global amount specified by spacing in Box. If child is a widget
	///<                at one of the reference ends of the box, then padding pixels are also put
	///<                between child and the reference edge of box.
	///<
	///< The child is packed after (away from end of) any other child packed with reference to the
	///< end of box. The default arguments specified are those most frequently used.

	void insert_start(Widget& child, int position, bool expand = true, bool fill = true, unsigned int padding = 0);
	///< Inserts child into the box at <EM>position</EM>, with reference to the start of box.
	///< @param child    The Widget to be added to the box.
	///< @param position The new position for child at the start, starting from 0.
	///< @param expand   Set <EM>true</EM> if the new child is to be given extra space allocated to the box.
	///<	             The extra space is divided evenly between all children of box using this option.
	///< @param fill     Set <EM>true</EM> if space given to child by the expand option is actually allocated
	///<                 to the child, rather than just padding it. This parameter has no effect if expand
	///<                 is set to false. A child is alwaHys allocated the full height of a HBox and the
	///<                 full width of a VBox. This option affects the other dimension.
	///< @param padding  The extra space in pixels to put between this child and its neighbors, over
	///<                 and above the global amount specified by spacing in Box. If child is a widget
	///<                 at one of the reference ends of the box, then padding pixels are also put
	///<                 between child and the reference edge of box.
	///<
	///< This method is equivalent to calling pack_start() followed by reorder_child(). The default
	///< arguments specified are those most frequently used. Setting <EM>position</EM> to -1 is the same as
	///< calling pack_start(); the position argument is ignored.

	void insert_end(Widget& child, int position, bool expand = true, bool fill = true, unsigned int padding = 0);
	///< Inserts child into the box at <EM>position</EM>, packed with reference to the end of box.
	///< @param child    The Widget to be added to the box.
	///< @param position The new position for child at the end, starting from 0.
	///< @param expand   Set <EM>true</EM> if the new child is to be given extra space allocated to the box.
	///<	             The extra space is divided evenly between all children of box using this option.
	///< @param fill     Set <EM>true</EM> if space given to child by the expand option is actually allocated
	///<                 to the child, rather than just padding it. This parameter has no effect if expand
	///<                 is set to false. A child is always allocated the full height of a HBox and the
	///<                 full width of a VBox. This option affects the other dimension.
	///< @param padding  The extra space in pixels to put between this child and its neighbors, over
	///<                 and above the global amount specified by spacing in Box. If child is a widget
	///<                 at one of the reference ends of the box, then padding pixels are also put
	///<                 between child and the reference edge of box.
	///<
	///< This method is equivalent to calling pack_end() followed by reorder_child(). The default
	///< arguments specified are those most frequently used. Setting <EM>position</EM> to -1 is the same as
	///< calling pack_end(); the position argument is ignored.

	void set_homogeneous(bool homogeneous);
	///< Sets the homogeneous field of the Box, controlling whether or not all children of box
	///< are given equal space in the box.
	///< @param homogeneous A boolean value, <EM>true</EM> to create equal allotments, <EM>false</EM>
	///< for variable allotments.

	void set_spacing(int spacing);
	///< Sets the spacing field of the Box, which is the number of pixels to place between children of box.
	///< @param spacing The number of pixels to put between children.

	void reorder_child(Widget& child, int position);
	///< Moves child to a new position in the list of box children.	
	///< @param child The Widget to move.
	///< @param position The new position for child in the children list, starting from 0.
	///<
	///< The list is the children field of GtkBox, and contains both widgets packed Gtk::PACK_START
	///< as well as widgets packed Gtk::PACK_END, in the order that these widgets were added to box. A
	///< negative value indicates the end of the list. 
	///<
	///< A widget's position in the box children list determines where the widget is packed into box.
	///< A child widget at some position in the list will be packed just after all other widgets of the
	///< same packing type that appear earlier in the list.

	void query_child_packing(Widget& child, bool *expand, bool *fill, unsigned int *padding, PackType *pack_type) const;
	///< Returns information about how child is packed into the box. 
	///< @param child The Widget of the child to query.
	///< @param expand The returned value of the expand field in BoxChild.
	///< @param fill The returned value of the fill field in BoxChild.
	///< @param padding The returned value of the padding field in BoxChild.
	///< @param pack_type The returned value of the pack field in BoxChild.

	void set_child_packing(Widget& child, bool expand, bool fill, unsigned int padding, PackType pack_type);
	///< Sets the way child is packed into the box.
	///< @param child The Widget of the child to set.
	///< @param expand The new value of the expand field in BoxChild.
	///< @param fill The new value of the fill field in BoxChild.
	///< @param padding The new value of the padding field in BoxChild.
	///< @param pack_type The new value of the pack field in BoxChild.

/// @}
};

/// @class HBox box.hh xfc/gtk/box.hh
/// @brief A GtkHBox C++ wrapper class.
///
/// HBox is a container that organizes child widgets into a single row. All children are
/// allocated the same height. Use the Box packing interface to determine the arrangement,
/// spacing, width, and alignment of HBox children.
///
/// <B>See also:</B> the <A HREF="../../howto/html/boxes.html">Packing Boxes</A> HOWTO and example.

class HBox : public Box
{
	friend class G::Object;

	HBox(const HBox&);
	HBox& operator=(const HBox&);

protected:
/// @name Constructors
/// @{

	explicit HBox(GtkHBox *hbox, bool owns_reference = false);
	///< Construct a new HBox from an existing GtkHBox.
	///< @param hbox A pointer to a GtkHBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>hbox</EM> can be a newly created GtkHBox or an existing
	///< GtkHBox. (see G::Object::Object).

/// @}

public:
	typedef GtkHBox CObjectType;
	
/// @name Constructors
/// @{

	explicit HBox(bool homogeneous = false, int spacing = 0);
	///< Construct a new HBox with the specified homogeneous and spacing values.
	///< @param homogeneous Set <EM>true</EM> if all children are to be given equal space allotments.
	///< @param spacing The number of pixels to place by default between children.

	virtual ~HBox();

	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkHBox* gtk_hbox() const;
	///< Get a pointer to the GtkHBox structure.

	operator GtkHBox* () const;
	///< Conversion operator; safely converts a HBox to a GtkHBox pointer.

/// @}
};

/// @class VBox box.hh xfc/gtk/box.hh
/// @brief A GtkVBox C++ wrapper class.
///
/// VBox is a container that organizes child widgets into a single column. All children are
/// allocated the same width. Use the Box packing interface to determine the arrangement,
/// spacing, width, and alignment of VBox children.
///
/// <B>See also:</B> the <A HREF="../../howto/html/boxes.html">Packing Boxes</A> HOWTO and example.

class VBox : public Box
{
	friend class G::Object;

	VBox(const VBox&);
	VBox& operator=(const VBox&);

protected:
/// @name Constructors
/// @{

	explicit VBox(GtkVBox *vbox, bool owns_reference = false);
	///< Construct a new VBox from an existing GtkVBox.
	///< @param vbox A pointer to a GtkVBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>vbox</EM> can be a newly created GtkVBox or an existing
	///< GtkVBox. (see G::Object::Object).

/// @}

public:
	typedef GtkVBox CObjectType;

/// @name Constructors
/// @{

	explicit VBox(bool homogeneous = false, int spacing = 0);
	///< Construct a new VBox with the specified homogeneous and spacing values.
	///< @param homogeneous Set <EM>true</EM> if all children are to be given equal space allotments.
	///< @param spacing The number of pixels to place by default between children.

	virtual ~VBox();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkVBox* gtk_vbox() const;
	///< Get a pointer to the GtkVBox structure.

	operator GtkVBox* () const;
	///< Conversion operator; safely converts a VBox to a GtkVBox pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/box.inl>

#endif // XFC_GTK_BOX_HH


