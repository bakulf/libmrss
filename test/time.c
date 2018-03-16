#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "mrss.h"

int
main (int argc, char **argv)
{
  time_t t;
  mrss_error_t err;
  char *buf;
  struct tm *k;

  if (argc != 2)
    {
      fprintf (stderr, "Usage: %s url\n\n", argv[0]);
      return 1;
    }

  if ((err = mrss_get_last_modified (argv[1], &t)) != MRSS_OK)
    {
      fprintf (stderr, "ERROR: %s\n", mrss_strerror (err));
      return 1;
    }

  if (!(k = localtime (&t)))
    {
      fprintf (stderr, "ERROR: %s\n", strerror (errno));
      return 1;
    }

  if (!(buf = asctime (k)))
    {
      fprintf (stderr, "ERROR: %s\n", strerror (errno));
      return 1;
    }

  fprintf (stdout, "Last Modified: %s\n", buf);
  return 0;
}
