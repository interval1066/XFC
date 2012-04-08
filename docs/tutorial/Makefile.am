## xfc docs/tutorial directory

EXTRA_DIST = html

xfc_tutorialdir = $(xfc_docdir)/docs/tutorial/html

html/index.html:
	-cp html/index.html

install-data-local: html/index.html
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(xfc_tutorialdir)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$p $(DESTDIR)$(xfc_tutorialdir)/$$f"; \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(xfc_tutorialdir)/$$f; \
	done
 
uninstall-local: html/index.html
	@$(NORMAL_UNINSTALL)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(xfc_tutorialdir)/$$f"; \
	  rm -f $(DESTDIR)$(xfc_tutorialdir)/$$f; \
	done

all-local: html/index.html
