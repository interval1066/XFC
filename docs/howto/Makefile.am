## xfc docs/howto directory

EXTRA_DIST = html

xfc_howtodir = $(xfc_docdir)/docs/howto/html

html/index.html:
	-cp html/index.html

install-data-local: html/index.html
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(xfc_howtodir)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$p $(DESTDIR)$(xfc_howtodir)/$$f"; \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(xfc_howtodir)/$$f; \
	done
 
uninstall-local: html/index.html
	@$(NORMAL_UNINSTALL)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(xfc_howtodir)/$$f"; \
	  rm -f $(DESTDIR)$(xfc_howtodir)/$$f; \
	done

all-local: html/index.html
