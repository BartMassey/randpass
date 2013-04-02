# Copyright © 2013 Bart Massey
# [This work is licensed under the "MIT License"]
# Please see the file COPYING in the source
# distribution of this software for license terms.

randpass: randpass.c
	$(CC) $(CFLAGS) -o randpass randpass.c

clean:
	-rm -f randpass
