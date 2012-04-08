ADD_SUBDIRECTORY( inline )

SET( src
 aboutdialog.cc 
 accelgroup.cc accelgroupsignals.cc 
 accelkey.cc 
 accellabel.cc 
 accelmap.cc 
 accessible.cc 
 action.cc actionsignals.cc 
 actiongroup.cc 
 adjustment.cc adjustmentsignals.cc 
 alignment.cc 
 arrow.cc 
 aspectframe.cc 
 bin.cc 
 box.cc 
 boxchild.cc 
 builder.cc 
 button.cc buttonsignals.cc 
 buttonbox.cc 
 calendar.cc calendarsignals.cc 
 celleditable.cc celleditablesignals.cc 
 celllayout.cc 
 cellrenderer.cc 
 cellrenderercombo.cc 
 cellrenderersignals.cc 
 cellrendererpixbuf.cc 
 cellrendererprogress.cc 
 cellrenderertext.cc 
 cellrenderertextsignals.cc 
 cellrenderertoggle.cc 
 cellrenderertogglesignals.cc 
 cellview.cc 
 checkbutton.cc 
 checkmenuitem.cc checkmenuitemsignals.cc 
 clipboard.cc 
 colorbutton.cc colorbuttonsignals.cc 
 colorselection.cc colorselectionsignals.cc 
 combobox.cc 
 comboboxentry.cc comboboxsignals.cc 
 container.cc containersignals.cc 
 curve.cc curvesignals.cc 
 dialog.cc dialogsignals.cc 
 dnd.cc 
 drawingarea.cc 
 editable.cc editablesignals.cc 
 entry.cc 
 entrycompletion.cc entrycompletionsignals.cc 
 entrysignals.cc 
 eventbox.cc 
 expander.cc
 filechooser.cc filechooserbutton.cc filechooserdialog.cc filechooserwidget.cc 
 filefilter.cc 
 fixed.cc 
 fontbutton.cc fontbuttonsignals.cc 
 fontselection.cc 
 frame.cc 
 gammacurve.cc 
 gc.cc 
 handlebox.cc handleboxsignals.cc 
 iconfactory.cc 
 iconset.cc 
 iconsource.cc 
 icontheme.cc iconthemesignals.cc 
 iconview.cc iconviewsignals.cc 
 image.cc 
 imagemenuitem.cc 
 invisible.cc 
 item.cc itemsignals.cc 
 label.cc labelsignals.cc 
 layout.cc layoutsignals.cc 
 liststore.cc 
 marshal.cc 
 menu.cc 
 menubar.cc 
 menuitem.cc menuitemsignals.cc 
 menushell.cc menushellsignals.cc 
 menutoolbutton.cc 
 messagedialog.cc 
 misc.cc 
 notebook.cc notebooksignals.cc 
 object.cc objectsignals.cc 
 paned.cc 
 plug.cc plugsignals.cc 
 printcontext.cc 
 printdialogs.cc
 printjob.cc 
 printoperationpreview.cc printoperationpreviewsignals.cc 
 printoperation.cc printoperationsignals.cc 
 printpagesetup.cc 
 printsetting.cc 
 progressbar.cc 
 radioaction.cc radioactionsignals.cc 
 radiobutton.cc radiobuttonsignals.cc 
 radiomenuitem.cc radiomenuitemsignals.cc 
 radiotoolbutton.cc 
 range.cc rangesignals.cc 
 rc.cc 
 ruler.cc 
 scale.cc scalesignals.cc 
 scrollbar.cc scrolledwindow.cc 
 selection.cc 
 separator.cc 
 separatormenuitem.cc 
 separatortoolitem.cc 
 settings.cc 
 sizegroup.cc 
 socket.cc socketsignals.cc 
 spinbutton.cc spinbuttonsignals.cc 
 statusbar.cc statusbarsignals.cc 
 stock.cc 
 stockid.cc 
 style.cc 
 table.cc 
 tearoffmenuitem.cc 
 textbuffer.cc textbuffersignals.cc 
 textiter.cc 
 texttag.cc 
 texttagsignals.cc 
 textview.cc textviewsignals.cc 
 toggleaction.cc toggleactionsignals.cc 
 togglebutton.cc togglebuttonsignals.cc 
 toggletoolbutton.cc toggletoolbuttonsignals.cc 
 toolbar.cc toolbarsignals.cc 
 toolbutton.cc toolbuttonsignals.cc 
 toolitem.cc toolitemsignals.cc 
 tooltips.cc 
 treednd.cc 
 treemodel.cc 
 treemodelfilter.cc 
 treemodelsignals.cc 
 treemodelsort.cc 
 treeselection.cc 
 treesortable.cc treesortablesignals.cc 
 treestore.cc 
 treeview.cc treeviewsignals.cc 
 treeviewcolumn.cc 
 treeviewcolumnsignals.cc 
 uimanager.cc uimanagersignals.cc 
 viewport.cc viewportsignals.cc 
 widget.cc widgetsignals.cc 
 window.cc windowsignals.cc)

SET(gtk_src "" )
FOREACH(f ${src})
    SET(gtk_src ${gtk_src} "gtk/${f}" )
ENDFOREACH(f)
SET( gtk_src ${gtk_src} PARENT_SCOPE )

INSTALL( FILES
 aboutdialog.hh 
 accelgroup.hh 
 accelgroupsignals.hh 
 accelkey.hh 
 accellabel.hh 
 accelmap.hh 
 accessible.hh 
 action.hh 
 actionsignals.hh 
 actiongroup.hh 
 adjustment.hh 
 adjustmentsignals.hh 
 alignment.hh 
 arrow.hh 
 aspectframe.hh 
 bin.hh 
 box.hh 
 boxchild.hh 
 builder.hh 
 button.hh 
 buttonsignals.hh 
 buttonbox.hh 
 calendar.hh 
 calendarsignals.hh 
 celleditable.hh 
 celleditablesignals.hh 
 celllayout.hh 
 cellrenderer.hh 
 cellrenderercombo.hh 
 cellrenderersignals.hh 
 cellrendererpixbuf.hh 
 cellrendererprogress.hh 
 cellrenderertext.hh 
 cellrenderertextsignals.hh 
 cellrenderertoggle.hh 
 cellrenderertogglesignals.hh 
 cellview.hh 
 checkbutton.hh 
 checkmenuitem.hh 
 checkmenuitemsignals.hh 
 clipboard.hh 
 colorbutton.hh 
 colorbuttonsignals.hh 
 colorselection.hh 
 colorselectionsignals.hh 
 combobox.hh 
 comboboxentry.hh 
 comboboxsignals.hh 
 container.hh 
 containersignals.hh 
 curve.hh 
 curvesignals.hh 
 dialog.hh 
 dialogsignals.hh 
 dnd.hh 
 drawingarea.hh 
 editable.hh 
 editablesignals.hh 
 entry.hh 
 entrycompletion.hh 
 entrycompletionsignals.hh 
 entrysignals.hh 
 enums.hh 
 eventbox.hh 
 expander.hh 
 filechooser.hh 
 filechooserbutton.hh 
 filechooserdialog.hh 
 filechooserwidget.hh 
 filefilter.hh 
 fixed.hh 
 fontbutton.hh 
 fontbuttonsignals.hh 
 fontselection.hh 
 frame.hh 
 gammacurve.hh 
 gc.hh 
 gtk.hh 
 handlebox.hh 
 handleboxsignals.hh 
 iconfactory.hh 
 iconset.hh 
 iconsource.hh 
 icontheme.hh 
 iconthemesignals.hh 
 iconview.hh 
 iconviewsignals.hh 
 image.hh 
 imagemenuitem.hh 
 invisible.hh 
 item.hh 
 itemsignals.hh 
 label.hh 
 labelsignals.hh 
 layout.hh 
 layoutsignals.hh 
 liststore.hh 
 menu.hh 
 menubar.hh 
 menuitem.hh 
 menuitemsignals.hh 
 menushell.hh 
 menushellsignals.hh 
 menutoolbutton.hh 
 messagedialog.hh 
 misc.hh 
 notebook.hh 
 notebooksignals.hh 
 object.hh 
 objectsignals.hh 
 paned.hh 
 plug.hh 
 plugsignals.hh 
 progressbar.hh 
 printer.hh 
 printcontext.hh 
 printdialogs.hh 
 printjob.hh 
 printoperationpreview.hh 
 printoperationpreviewsignals.hh 
 printoperation.hh 
 printoperationsignals.hh 
 printpagesetup.hh 
 printsetting.hh 
 radioaction.hh 
 radioactionsignals.hh 
 radiobutton.hh 
 radiobuttonsignals.hh 
 radiomenuitem.hh 
 radiomenuitemsignals.hh 
 radiotoolbutton.hh 
 range.hh 
 rangesignals.hh 
 rc.hh 
 ruler.hh 
 scale.hh 
 scalesignals.hh 
 scrollbar.hh 
 scrolledwindow.hh 
 selection.hh 
 separator.hh 
 separatormenuitem.hh 
 separatortoolitem.hh 
 settings.hh 
 sizegroup.hh 
 socket.hh 
 socketsignals.hh 
 spinbutton.hh 
 spinbuttonsignals.hh 
 statusbar.hh 
 statusbarsignals.hh 
 stock.hh 
 stockid.hh 
 style.hh 
 table.hh 
 tearoffmenuitem.hh 
 textbuffer.hh 
 textbuffersignals.hh 
 textiter.hh 
 texttag.hh 
 texttagsignals.hh 
 textview.hh 
 textviewsignals.hh 
 toggleaction.hh 
 toggleactionsignals.hh 
 togglebutton.hh 
 togglebuttonsignals.hh 
 toggletoolbutton.hh 
 toggletoolbuttonsignals.hh 
 toolbar.hh 
 toolbarsignals.hh 
 toolbutton.hh 
 toolbuttonsignals.hh 
 toolitem.hh 
 toolitemsignals.hh 
 tooltips.hh 
 treednd.hh 
 treemodel.hh 
 treemodelfilter.hh 
 treemodelsignals.hh 
 treemodelsort.hh 
 treeselection.hh 
 treesortable.hh 
 treesortablesignals.hh 
 treestore.hh 
 treeview.hh 
 treeviewsignals.hh 
 treeviewcolumn.hh 
 treeviewcolumnsignals.hh 
 uimanager.hh 
 uimanagersignals.hh 
 viewport.hh 
 viewportsignals.hh 
 widget.hh 
 widgetsignals.hh 
 window.hh 
 windowsignals.hh
 DESTINATION include/xfce4/xfc/gtk)
