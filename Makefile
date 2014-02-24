# Copyright © 2013 Bart Massey
# [This work is licensed under the "MIT License"]
# Please see the file COPYING in the source
# distribution of this software for license terms.

BINDIR = /usr/local/bin

install: randpass.py
	cp randpass.py $(BINDIR)/randpass
	chmod 755 $(BINDIR)/randpass
