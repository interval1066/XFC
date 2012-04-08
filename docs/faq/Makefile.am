## xfc docs/faq directory

EXTRA_DIST = html

xfc_faqdir = $(xfc_docdir)/docs/faq/html

html/index.html:
	-cp html/index.html

install-data-local: html/index.html
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(xfc_faqdir)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$p $(DESTDIR)$(xfc_faqdir)/$$f"; \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(xfc_faqdir)/$$f; \
	done
 
uninstall-local: html/index.html
	@$(NORMAL_UNINSTALL)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(xfc_faqdir)/$$f"; \
	  rm -f $(DESTDIR)$(xfc_faqdir)/$$f; \
	done

all-local: html/index.html
