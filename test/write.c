#include <stdio.h>
#include <string.h>

#include "mrss.h"

int
main (int argc, char **argv)
{
  mrss_t *data;
  mrss_error_t ret;

  if (argc != 3)
    {
      fprintf (stderr,
	       "Usage:\n\t%s url_rss output\n\nExample:\n\t%s http://ngvision.org/rss file.rss\n\n",
	       argv[0], argv[0]);
      return 1;
    }

  if (!strncmp (argv[1], "http://", 7))
    ret = mrss_parse_url (argv[1], &data);
  else
    ret = mrss_parse_file (argv[1], &data);

  if (ret)
    {
      fprintf (stderr, "MRSS return error: %s\n", mrss_strerror (ret));
      return 1;
    }

  data->version = MRSS_VERSION_ATOM_1_0;
  ret = mrss_write_file (data, argv[2]);

  if (ret)
    {
      fprintf (stderr, "MRSS return error: %s\n", mrss_strerror (ret));
      return 1;
    }

  mrss_free (data);

  return 0;
}
