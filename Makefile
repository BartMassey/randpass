randpass: randpass.c
	$(CC) $(CFLAGS) -o randpass randpass.c

clean:
	-rm -f randpass
