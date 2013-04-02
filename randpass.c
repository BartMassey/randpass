/* Random password generator. Nothing fancy. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHANUM \
  "abcdefghijklmnopqrstuvwxyz" \
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
  "0123456789"
#define PUNCT "!#$%^&*-;,./"

static char *pwchars = ALPHANUM PUNCT;

int main(int argc, char **argv) {
  FILE *rf = 0;
  int alphanum = 0;
  int len = 8;
  int l, q, p, i;
  i = 1;
  while (argc > 1) {
      if (!strcmp(argv[i], "-u")) {
          rf = fopen("/dev/urandom", "r");
          if (!rf) {
              perror("randpass: /dev/urandom");
              exit(1);
          }
          i++;
          --argc;
          continue;
      }
      if (!strcmp(argv[i], "-a")) {
	  alphanum = 1;
	  i++;
	  --argc;
	  continue;
      }
      if (!strcmp(argv[i], "-n") && argc > 2) {
	  len = atoi(argv[i + 1]);
	  if (len <= 0)
	      break;
	  i += 2;
	  argc -= 2;
	  continue;
      }
      break;
  }
  if (argc != 1) {
      fprintf(stderr, "randpass: usage: randpass [-u] [-a] [-n length]\n");
      exit(1);
  }
  if (!rf)
      rf = fopen("/dev/random", "r");
  if (!rf) {
      perror("randpass: /dev/random");
      exit(1);
  }
  l = strlen(pwchars);
  if (alphanum)
      l = strlen(ALPHANUM);
  q = 256 / l;
  p = l * q;
  for (i = 0; i < len; i++) {
    int ch;
    do {
      ch = fgetc(rf);
      if (ch == EOF)
	abort();
    } while (ch >= p);
    putchar(pwchars[ch % l]);
  }
  putchar('\n');
  exit(0);
}
