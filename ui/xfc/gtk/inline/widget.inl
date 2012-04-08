/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  widget.inl - Gtk::Allocation, Gtk::Requisition and Gtk::Widget inline functions
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

/*  Gtk::Allocation
 */

inline GtkAllocation*
Xfc::Gtk::Allocation::gtk_allocation() const
{
	return (GtkAllocation*)this;
}

/*  Gtk::Requisition
 */

inline GtkRequisition*
Xfc::Gtk::Requisition::gtk_requisition() const
{
	return const_cast<GtkRequisition*>(&requisition_);
}

inline Xfc::Gtk::Requisition::operator GtkRequisition* () const
{
	return this ? (const_cast<GtkRequisition*>(&requisition_)) : 0;
}

inline int
Xfc::Gtk::Requisition::width() const
{
	return requisition_.width;
}

inline int
Xfc::Gtk::Requisition::height() const
{
	return requisition_.height;
}

inline void
Xfc::Gtk::Requisition::set(int width, int height)
{
	requisition_.width = width;
	requisition_.height = height;
}

/*  Gtk::Widget
 */

inline GtkWidget*
Xfc::Gtk::Widget::gtk_widget() const
{
	return reinterpret_cast<GtkWidget*>(instance_);
}

inline Xfc::Gtk::Widget::operator GtkWidget* () const
{
	return this ? gtk_widget() : 0;
}

inline bool
Xfc::Gtk::Widget::is_toplevel() const
{
	return GTK_WIDGET_TOPLEVEL(instance_);
}

inline bool
Xfc::Gtk::Widget::has_no_window() const
{
	return GTK_WIDGET_NO_WINDOW(instance_);
}

inline bool
Xfc::Gtk::Widget::is_realized() const
{
	return GTK_WIDGET_REALIZED(instance_);
}

inline bool
Xfc::Gtk::Widget::is_mapped() const
{
	return GTK_WIDGET_MAPPED(instance_);
}

inline bool
Xfc::Gtk::Widget::is_visible() const
{
	return GTK_WIDGET_VISIBLE(instance_);
}

inline bool
Xfc::Gtk::Widget::is_drawable() const
{
	return is_visible() && is_mapped();
}

inline bool
Xfc::Gtk::Widget::sensitive() const
{
	return GTK_WIDGET_SENSITIVE(instance_);
}

inline bool
Xfc::Gtk::Widget::parent_sensitive() const
{
	return GTK_WIDGET_PARENT_SENSITIVE(instance_);
}

inline bool
Xfc::Gtk::Widget::is_sensitive() const
{
	return sensitive() && parent_sensitive();
}

inline bool
Xfc::Gtk::Widget::can_focus() const
{
	return GTK_WIDGET_CAN_FOCUS(instance_);
}

inline bool
Xfc::Gtk::Widget::has_focus() const
{
	return GTK_WIDGET_HAS_FOCUS(instance_);
}

inline bool
Xfc::Gtk::Widget::can_default() const
{
	return GTK_WIDGET_CAN_DEFAULT(instance_);
}

inline bool
Xfc::Gtk::Widget::has_default() const
{

	return GTK_WIDGET_HAS_DEFAULT(instance_);
}

inline bool
Xfc::Gtk::Widget::has_grab() const
{
	return GTK_WIDGET_HAS_GRAB(instance_);
}

inline bool
Xfc::Gtk::Widget::has_rc_style() const
{
	return GTK_WIDGET_RC_STYLE(instance_);
}

inline bool
Xfc::Gtk::Widget::is_composite_child() const
{
	return GTK_WIDGET_COMPOSITE_CHILD(instance_);
}

inline bool
Xfc::Gtk::Widget::is_app_paintable() const
{
	return GTK_WIDGET_APP_PAINTABLE(instance_);
}

inline bool
Xfc::Gtk::Widget::receives_default() const
{
	return GTK_WIDGET_RECEIVES_DEFAULT(instance_);
}

inline bool
Xfc::Gtk::Widget::is_double_buffered() const
{
	return GTK_WIDGET_DOUBLE_BUFFERED(instance_);
}

inline bool
Xfc::Gtk::Widget::get_no_show_all() const
{
	return gtk_widget_get_no_show_all(gtk_widget());
}

inline Xfc::Gtk::StateType
Xfc::Gtk::Widget::get_state() const
{
	return (StateType)gtk_widget()->state;
}

inline const Xfc::Gtk::Allocation&
Xfc::Gtk::Widget::get_allocation() const
{
	return reinterpret_cast<Allocation&>(gtk_widget()->allocation);
}

inline bool
Xfc::Gtk::Widget::is_focus() const
{
	return gtk_widget_is_focus(gtk_widget());
}

inline bool
Xfc::Gtk::Widget::get_child_visible() const
{
	return gtk_widget_get_child_visible(gtk_widget());
}

inline void
Xfc::Gtk::Widget::get_size_request(int *width, int *height) const
{
	gtk_widget_get_size_request(gtk_widget(), width, height);

}

inline Xfc::Gdk::ExtensionMode
Xfc::Gtk::Widget::get_extension_events() const
{
	return (Gdk::ExtensionMode)gtk_widget_get_extension_events(gtk_widget());
}

inline bool
Xfc::Gtk::Widget::has_screen() const
{
	return gtk_widget_has_screen((GtkWidget*)instance_);
}

inline Xfc::Gdk::EventMaskField
Xfc::Gtk::Widget::get_events() const
{
	return (Gdk::EventMaskField)gtk_widget_get_events(gtk_widget());
}

inline void
Xfc::Gtk::Widget::get_pointer(int *x, int *y) const
{
	gtk_widget_get_pointer(gtk_widget(), x, y);
}

inline Xfc::Gtk::TextDirection
Xfc::Gtk::Widget::get_direction() const
{
	return (TextDirection)gtk_widget_get_direction(gtk_widget());
}

inline Xfc::Gtk::TextDirection
Xfc::Gtk::Widget::get_default_direction()
{
	return (TextDirection)gtk_widget_get_default_direction();
}

inline void
Xfc::Gtk::Widget::set_flags(WidgetFlagsField flags)
{
	GTK_WIDGET_SET_FLAGS(gtk_widget(), (GtkWidgetFlags)flags);
}

inline void
Xfc::Gtk::Widget::unset_flags(WidgetFlagsField flags)
{
	GTK_WIDGET_UNSET_FLAGS(gtk_widget(), (GtkWidgetFlags)flags);
}

inline void
Xfc::Gtk::Widget::unparent()
{
	gtk_widget_unparent(gtk_widget());
}

inline void
Xfc::Gtk::Widget::show()
{
	gtk_widget_show(gtk_widget());
}

inline void
Xfc::Gtk::Widget::hide()
{
	gtk_widget_hide(gtk_widget());
}

inline void
Xfc::Gtk::Widget::show_now()
{
	gtk_widget_show_now(gtk_widget());
}

inline void
Xfc::Gtk::Widget::show_all()
{
	gtk_widget_show_all(gtk_widget());
}

inline void
Xfc::Gtk::Widget::hide_all()
{
	gtk_widget_hide_all(gtk_widget());
}

inline void
Xfc::Gtk::Widget::set_no_show_all(bool no_show_all)
{
	gtk_widget_set_no_show_all(gtk_widget(), no_show_all);
}

inline void
Xfc::Gtk::Widget::map()
{
	gtk_widget_map(gtk_widget());
}

inline void
Xfc::Gtk::Widget::unmap()
{
	gtk_widget_unmap(gtk_widget());
}

inline void
Xfc::Gtk::Widget::realize()
{
	gtk_widget_realize(gtk_widget());
}

inline void
Xfc::Gtk::Widget::unrealize()
{
	gtk_widget_unrealize(gtk_widget());
}

inline void
Xfc::Gtk::Widget::queue_draw()
{
	gtk_widget_queue_draw(gtk_widget());
}

inline void
Xfc::Gtk::Widget::queue_draw_area(int x, int y, int width, int height)
{
	gtk_widget_queue_draw_area(gtk_widget(), x, y, width, height);
}

inline void
Xfc::Gtk::Widget::queue_resize()
{
	gtk_widget_queue_resize(gtk_widget());
}

inline void
Xfc::Gtk::Widget::queue_resize_no_redraw()
{
	gtk_widget_queue_resize_no_redraw(gtk_widget());
}

inline bool
Xfc::Gtk::Widget::can_activate_accel(unsigned int signal_id)
{
	return gtk_widget_can_activate_accel(gtk_widget(), signal_id);
}

inline bool
Xfc::Gtk::Widget::mnemonic_activate(bool group_cycling)
{
	return gtk_widget_mnemonic_activate(gtk_widget(), group_cycling);
}

inline bool
Xfc::Gtk::Widget::activate()
{
	return gtk_widget_activate(gtk_widget());
}

inline void
Xfc::Gtk::Widget::freeze_child_notify()
{
	gtk_widget_freeze_child_notify(gtk_widget());
}

inline void
Xfc::Gtk::Widget::child_notify(const char *child_property)
{
	gtk_widget_child_notify(gtk_widget(), child_property);
}

inline void
Xfc::Gtk::Widget::thaw_child_notify()
{
	gtk_widget_thaw_child_notify(gtk_widget());
}

inline void
Xfc::Gtk::Widget::grab_focus()
{
	gtk_widget_grab_focus(gtk_widget());
}

inline void
Xfc::Gtk::Widget::grab_default()
{
	gtk_widget_grab_default(gtk_widget());
}

inline void
Xfc::Gtk::Widget::set_name(const char *name)
{
	gtk_widget_set_name(gtk_widget(), name);
}

inline void
Xfc::Gtk::Widget::set_state(StateType state)
{
	gtk_widget_set_state(gtk_widget(), (GtkStateType)state);
}

inline void
Xfc::Gtk::Widget::set_sensitive(bool sensitive)
{
	gtk_widget_set_sensitive(gtk_widget(), sensitive);
}

inline void
Xfc::Gtk::Widget::set_app_paintable(bool app_paintable)
{
	gtk_widget_set_app_paintable(gtk_widget(), app_paintable);
}

inline void
Xfc::Gtk::Widget::set_double_buffered(bool double_buffered)
{
	gtk_widget_set_double_buffered(gtk_widget(), double_buffered);
}

inline void
Xfc::Gtk::Widget::set_redraw_on_allocate(bool redraw_on_allocate)
{
	gtk_widget_set_redraw_on_allocate(gtk_widget(), redraw_on_allocate);
}

inline void
Xfc::Gtk::Widget::set_child_visible(bool is_visible)
{
	gtk_widget_set_child_visible(gtk_widget(), is_visible);
}

inline bool
Xfc::Gtk::Widget::child_focus(DirectionType direction)
{
	return gtk_widget_child_focus(gtk_widget(), (GtkDirectionType)direction);
}

inline void
Xfc::Gtk::Widget::set_size_request(int width, int height)
{
	gtk_widget_set_size_request(gtk_widget(), width, height);
}

inline void
Xfc::Gtk::Widget::set_events(Gdk::EventMaskField events)
{
	gtk_widget_set_events(gtk_widget(), (int)events);
}

inline void
Xfc::Gtk::Widget::add_events(Gdk::EventMaskField events)
{
	gtk_widget_add_events(gtk_widget(), (int)events);
}

inline void
Xfc::Gtk::Widget::set_extension_events(Gdk::ExtensionMode mode)
{
	gtk_widget_set_extension_events(gtk_widget(), (GdkExtensionMode)mode);
}

inline void
Xfc::Gtk::Widget::ensure_style()
{
	gtk_widget_ensure_style(gtk_widget());
}

inline void
Xfc::Gtk::Widget::set_composite_name(const char *name)
{
	gtk_widget_set_composite_name(gtk_widget(), name);
}

inline void
Xfc::Gtk::Widget::reset_rc_styles()
{
	gtk_widget_reset_rc_styles(gtk_widget());
}

inline void
Xfc::Gtk::Widget::push_composite_child()
{
	gtk_widget_push_composite_child();
}

inline void
Xfc::Gtk::Widget::pop_composite_child()
{
	gtk_widget_pop_composite_child();
}

inline void
Xfc::Gtk::Widget::pop_colormap()
{
	gtk_widget_pop_colormap();
}

inline void
Xfc::Gtk::Widget::set_direction(TextDirection dir)
{
	gtk_widget_set_direction(gtk_widget(), (GtkTextDirection)dir);
}

inline void
Xfc::Gtk::Widget::set_default_direction(TextDirection dir)
{
	gtk_widget_set_default_direction((GtkTextDirection)dir);
}

inline void
Xfc::Gtk::Widget::shape_combine_mask()
{
	gtk_widget_shape_combine_mask(gtk_widget(), 0, 0, 0);
}

inline Xfc::Gdk::GrabStatus
Xfc::Gtk::Widget::keyboard_grab(bool owner_events, unsigned int time)
{
	return (Gdk::GrabStatus)gdk_keyboard_grab(gtk_widget()->window, owner_events, time);
}

inline bool
Xfc::Gtk::Widget::selection_owner_get(Gdk::Atom selection)
{
	return gdk_selection_owner_get(selection) == gtk_widget()->window;
}

inline void
Xfc::Gtk::Widget::selection_add_target(Gdk::Atom selection, Xfc::Gdk::Atom target, unsigned int info)
{
	gtk_selection_add_target(gtk_widget(), selection, target, info);
}

inline void
Xfc::Gtk::Widget::selection_clear_targets(Gdk::Atom selection)
{
	gtk_selection_clear_targets(gtk_widget(), selection);
}

inline bool
Xfc::Gtk::Widget::selection_convert(Gdk::Atom selection, Xfc::Gdk::Atom target, unsigned int time)
{
	return gtk_selection_convert(gtk_widget(), selection, target, time);
}

inline void
Xfc::Gtk::Widget::selection_remove_all()
{
	gtk_selection_remove_all(gtk_widget());
}

inline void
Xfc::Gtk::Widget::drag_highlight()
{
	gtk_drag_highlight(gtk_widget());
}

inline void
Xfc::Gtk::Widget::drag_unhighlight()
{
	gtk_drag_unhighlight(gtk_widget());
}

inline void
Xfc::Gtk::Widget::drag_dest_unset()
{
	gtk_drag_dest_unset(gtk_widget());
}

inline void 
Xfc::Gtk::Widget::drag_source_add_text_targets()
{
	gtk_drag_source_add_text_targets(gtk_widget());
}

inline void 
Xfc::Gtk::Widget::drag_source_add_image_targets()
{
	gtk_drag_source_add_image_targets(gtk_widget());
}

inline void 
Xfc::Gtk::Widget::drag_source_add_uri_targets()
{
	gtk_drag_source_add_uri_targets(gtk_widget());
}

inline void
Xfc::Gtk::Widget::drag_source_unset()
{
	gtk_drag_source_unset(gtk_widget());
}

inline void 
Xfc::Gtk::Widget::drag_dest_add_text_targets()
{
	gtk_drag_dest_add_text_targets(gtk_widget());
}

inline void 
Xfc::Gtk::Widget::drag_dest_add_image_targets()
{
	gtk_drag_dest_add_image_targets(gtk_widget());
}

inline void 
Xfc::Gtk::Widget::drag_dest_add_uri_targets()
{
	gtk_drag_dest_add_uri_targets(gtk_widget());
}

inline bool
Xfc::Gtk::Widget::drag_check_threshold(int start_x, int start_y, int current_x, int current_y)
{
	return gtk_drag_check_threshold(gtk_widget(), start_x, start_y, current_x, current_y);
}

inline const Xfc::Gtk::Widget::ShowSignalProxy
Xfc::Gtk::Widget::signal_show()
{
	return ShowSignalProxy(this, &show_signal);
}

inline const Xfc::Gtk::Widget::HideSignalProxy
Xfc::Gtk::Widget::signal_hide()
{
	return HideSignalProxy(this, &hide_signal);
}

inline const Xfc::Gtk::Widget::MapSignalProxy
Xfc::Gtk::Widget::signal_map()
{
	return MapSignalProxy(this, &map_signal);
}

inline const Xfc::Gtk::Widget::UnmapSignalProxy
Xfc::Gtk::Widget::signal_unmap()
{
	return UnmapSignalProxy(this, &unmap_signal);
}

inline const Xfc::Gtk::Widget::RealizeSignalProxy
Xfc::Gtk::Widget::signal_realize()
{
	return RealizeSignalProxy(this, &realize_signal);
}

inline const Xfc::Gtk::Widget::UnrealizeSignalProxy
Xfc::Gtk::Widget::signal_unrealize()
{
	return UnrealizeSignalProxy(this, &unrealize_signal);
}

inline const Xfc::Gtk::Widget::SizeRequestSignalProxy
Xfc::Gtk::Widget::signal_size_request()
{
	return SizeRequestSignalProxy(this, &size_request_signal);
}

inline const Xfc::Gtk::Widget::SizeAllocateSignalProxy
Xfc::Gtk::Widget::signal_size_allocate()
{
	return SizeAllocateSignalProxy(this, &size_allocate_signal);
}

inline const Xfc::Gtk::Widget::StateChangedSignalProxy
Xfc::Gtk::Widget::signal_state_changed()
{
	return StateChangedSignalProxy(this, &state_changed_signal);
}

inline const Xfc::Gtk::Widget::ParentSetSignalProxy
Xfc::Gtk::Widget::signal_parent_set()
{
	return ParentSetSignalProxy(this, &parent_set_signal);
}

inline const Xfc::Gtk::Widget::HierarchyChangedSignalProxy
Xfc::Gtk::Widget::signal_hierarchy_changed()
{
	return HierarchyChangedSignalProxy(this, &hierarchy_changed_signal);
}

inline const Xfc::Gtk::Widget::StyleSetSignalProxy
Xfc::Gtk::Widget::signal_style_set()
{
	return StyleSetSignalProxy(this, &style_set_signal);
}

inline const Xfc::Gtk::Widget::DirectionChangedSignalProxy
Xfc::Gtk::Widget::signal_direction_changed()
{
	return DirectionChangedSignalProxy(this, &direction_changed_signal);
}

inline const Xfc::Gtk::Widget::GrabNotifySignalProxy
Xfc::Gtk::Widget::signal_grab_notify()
{
	return GrabNotifySignalProxy(this, &grab_notify_signal);
}

inline const Xfc::Gtk::Widget::ChildNotifySignalProxy
Xfc::Gtk::Widget::signal_child_notify(const char *property_name)
{
	return ChildNotifySignalProxy(this, &child_notify_signal, property_name);
}

inline const Xfc::Gtk::Widget::ChildNotifySignalProxy
Xfc::Gtk::Widget::signal_child_notify(const String& property_name)
{
	return ChildNotifySignalProxy(this, &child_notify_signal, property_name.c_str());
}

inline const Xfc::Gtk::Widget::MnemonicActivateSignalProxy
Xfc::Gtk::Widget::signal_mnemonic_activate()
{
	return MnemonicActivateSignalProxy(this, &mnemonic_activate_signal);
}

inline const Xfc::Gtk::Widget::GrabFocusSignalProxy
Xfc::Gtk::Widget::signal_grab_focus()
{
	return GrabFocusSignalProxy(this, &grab_focus_signal);
}

inline const Xfc::Gtk::Widget::FocusSignalProxy
Xfc::Gtk::Widget::signal_focus()
{
	return FocusSignalProxy(this, &focus_signal);
}

inline const Xfc::Gtk::Widget::AccelClosuresChangedSignalProxy
Xfc::Gtk::Widget::signal_accel_closures_changed()
{
	return AccelClosuresChangedSignalProxy(this, &accel_closures_changed_signal);
}

inline const Xfc::Gtk::Widget::ScreenChangedSignalProxy
Xfc::Gtk::Widget::signal_screen_changed()
{
	return ScreenChangedSignalProxy(this, &screen_changed_signal);
}

inline const Xfc::Gtk::Widget::CanActivateAccelSignalProxy
Xfc::Gtk::Widget::signal_can_activate_accel()
{
	return CanActivateAccelSignalProxy(this, &can_activate_accel_signal);
}

inline const Xfc::Gtk::Widget::SelectionGetSignalProxy
Xfc::Gtk::Widget::signal_selection_get()
{
	return SelectionGetSignalProxy(this, &selection_get_signal);
}

inline const Xfc::Gtk::Widget::SelectionReceivedSignalProxy
Xfc::Gtk::Widget::signal_selection_received()
{
	return SelectionReceivedSignalProxy(this, &selection_received_signal);
}

inline const Xfc::Gtk::Widget::DragBeginSignalProxy
Xfc::Gtk::Widget::signal_drag_begin()
{
	return DragBeginSignalProxy(this, &drag_begin_signal);
}

inline const Xfc::Gtk::Widget::DragEndSignalProxy
Xfc::Gtk::Widget::signal_drag_end()
{
	return DragEndSignalProxy(this, &drag_end_signal);
}

inline const Xfc::Gtk::Widget::DragDataGetSignalProxy
Xfc::Gtk::Widget::signal_drag_data_get()
{
	return DragDataGetSignalProxy(this, &drag_data_get_signal);
}

inline const Xfc::Gtk::Widget::DragDataDeleteSignalProxy
Xfc::Gtk::Widget::signal_drag_data_delete()
{
	return DragDataDeleteSignalProxy(this, &drag_data_delete_signal);
}

inline const Xfc::Gtk::Widget::DragLeaveSignalProxy
Xfc::Gtk::Widget::signal_drag_leave()
{
	return DragLeaveSignalProxy(this, &drag_leave_signal);
}

inline const Xfc::Gtk::Widget::DragMotionSignalProxy
Xfc::Gtk::Widget::signal_drag_motion()
{
	return DragMotionSignalProxy(this, &drag_motion_signal);
}

inline const Xfc::Gtk::Widget::DragDropSignalProxy
Xfc::Gtk::Widget::signal_drag_drop()
{
	return DragDropSignalProxy(this, &drag_drop_signal);
}

inline const Xfc::Gtk::Widget::DragDataReceivedSignalProxy
Xfc::Gtk::Widget::signal_drag_data_received()
{
	return DragDataReceivedSignalProxy(this, &drag_data_received_signal);
}

inline const Xfc::Gtk::Widget::EventSignalProxy
Xfc::Gtk::Widget::signal_event()
{
	return EventSignalProxy(this, &event_signal);
}

inline const Xfc::Gtk::Widget::EventAfterSignalProxy
Xfc::Gtk::Widget::signal_event_after()
{
	return EventAfterSignalProxy(this, &event_after_signal);
}

inline const Xfc::Gtk::Widget::ButtonPressEventSignalProxy
Xfc::Gtk::Widget::signal_button_press_event()
{
	return ButtonPressEventSignalProxy(this, &button_press_event_signal);
}

inline const Xfc::Gtk::Widget::ButtonReleaseEventSignalProxy
Xfc::Gtk::Widget::signal_button_release_event()
{
	return ButtonReleaseEventSignalProxy(this, &button_release_event_signal);
}

inline const Xfc::Gtk::Widget::ScrollEventSignalProxy
Xfc::Gtk::Widget::signal_scroll_event()
{
	return ScrollEventSignalProxy(this, &scroll_event_signal);
}

inline const Xfc::Gtk::Widget::MotionNotifyEventSignalProxy
Xfc::Gtk::Widget::signal_motion_notify_event()
{
	return MotionNotifyEventSignalProxy(this, &motion_notify_event_signal);
}

inline const Xfc::Gtk::Widget::DeleteEventSignalProxy
Xfc::Gtk::Widget::signal_delete_event()
{
	return DeleteEventSignalProxy(this, &delete_event_signal);
}

inline const Xfc::Gtk::Widget::DestroyEventSignalProxy
Xfc::Gtk::Widget::signal_destroy_event()
{
	return DestroyEventSignalProxy(this, &destroy_event_signal);
}

inline const Xfc::Gtk::Widget::ExposeEventSignalProxy
Xfc::Gtk::Widget::signal_expose_event()
{
	return ExposeEventSignalProxy(this, &expose_event_signal);
}

inline const Xfc::Gtk::Widget::KeyPressEventSignalProxy
Xfc::Gtk::Widget::signal_key_press_event()
{
	return KeyPressEventSignalProxy(this, &key_press_event_signal);
}

inline const Xfc::Gtk::Widget::KeyReleaseEventSignalProxy
Xfc::Gtk::Widget::signal_key_release_event()
{
	return KeyReleaseEventSignalProxy(this, &key_release_event_signal);
}

inline const Xfc::Gtk::Widget::EnterNotifyEventSignalProxy
Xfc::Gtk::Widget::signal_enter_notify_event()
{
	return EnterNotifyEventSignalProxy(this, &enter_notify_event_signal);
}

inline const Xfc::Gtk::Widget::LeaveNotifyEventSignalProxy
Xfc::Gtk::Widget::signal_leave_notify_event()
{
	return LeaveNotifyEventSignalProxy(this, &leave_notify_event_signal);
}

inline const Xfc::Gtk::Widget::ConfigureEventSignalProxy
Xfc::Gtk::Widget::signal_configure_event()
{
	return ConfigureEventSignalProxy(this, &configure_event_signal);
}

inline const Xfc::Gtk::Widget::FocusInEventSignalProxy
Xfc::Gtk::Widget::signal_focus_in_event()
{
	return FocusInEventSignalProxy(this, &focus_in_event_signal);
}

inline const Xfc::Gtk::Widget::FocusOutEventSignalProxy
Xfc::Gtk::Widget::signal_focus_out_event()
{
	return FocusOutEventSignalProxy(this, &focus_out_event_signal);
}

inline const Xfc::Gtk::Widget::MapEventSignalProxy
Xfc::Gtk::Widget::signal_map_event()
{
	return MapEventSignalProxy(this, &map_event_signal);
}

inline const Xfc::Gtk::Widget::UnmapEventSignalProxy
Xfc::Gtk::Widget::signal_unmap_event()
{
	return UnmapEventSignalProxy(this, &unmap_event_signal);
}

inline const Xfc::Gtk::Widget::PropertyNotifyEventSignalProxy
Xfc::Gtk::Widget::signal_property_notify_event()
{
	return PropertyNotifyEventSignalProxy(this, &property_notify_event_signal);
}

inline const Xfc::Gtk::Widget::SelectionClearEventSignalProxy
Xfc::Gtk::Widget::signal_selection_clear_event()
{
	return SelectionClearEventSignalProxy(this, &selection_clear_event_signal);
}

inline const Xfc::Gtk::Widget::SelectionRequestEventSignalProxy
Xfc::Gtk::Widget::signal_selection_request_event()
{
	return SelectionRequestEventSignalProxy(this, &selection_request_event_signal);
}

inline const Xfc::Gtk::Widget::SelectionNotifyEventSignalProxy
Xfc::Gtk::Widget::signal_selection_notify_event()
{
	return SelectionNotifyEventSignalProxy(this, &selection_notify_event_signal);
}

inline const Xfc::Gtk::Widget::ProximityInEventSignalProxy
Xfc::Gtk::Widget::signal_proximity_in_event()
{
	return ProximityInEventSignalProxy(this, &proximity_in_event_signal);
}

inline const Xfc::Gtk::Widget::ProximityOutEventSignalProxy
Xfc::Gtk::Widget::signal_proximity_out_event()
{
	return ProximityOutEventSignalProxy(this, &proximity_out_event_signal);
}

inline const Xfc::Gtk::Widget::VisibilityNotifyEventSignalProxy
Xfc::Gtk::Widget::signal_visibility_notify_event()
{
	return VisibilityNotifyEventSignalProxy(this, &visibility_notify_event_signal);
}

inline const Xfc::Gtk::Widget::ClientEventSignalProxy
Xfc::Gtk::Widget::signal_client_event()
{
	return ClientEventSignalProxy(this, &client_event_signal);
}

inline const Xfc::Gtk::Widget::NoExposeEventSignalProxy
Xfc::Gtk::Widget::signal_no_expose_event()
{
	return NoExposeEventSignalProxy(this, &no_expose_event_signal);
}

inline const Xfc::Gtk::Widget::WindowStateEventSignalProxy
Xfc::Gtk::Widget::signal_window_state_event()
{
	return WindowStateEventSignalProxy(this, &window_state_event_signal);
}

