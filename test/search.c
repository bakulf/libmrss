#include <stdio.h>
#include <string.h>
#include "mrss.h"

int
main (int argc, char **argv)
{
  mrss_t *data;
  mrss_error_t ret;
  mrss_item_t *item;
  mrss_tag_t *tag;
  CURLcode code;

  if (argc != 2)
    {
      fprintf (stderr,
	       "Usage:\n\t%s url_rss\n\nExample:\n\t%s http://ngvision.org/rss|file.rss\n\n",
	       argv[0], argv[0]);
      return 1;
    }

  if (!strncmp (argv[1], "http://", 7) || !strncmp (argv[1], "https://", 8))
    ret = mrss_parse_url_with_options_and_error (argv[1], &data, NULL, &code);
  else
    ret = mrss_parse_file (argv[1], &data);

  if (ret)
    {
      fprintf (stderr, "MRSS return error: %s\n",
	       ret ==
	       MRSS_ERR_DOWNLOAD ? mrss_curl_strerror (code) :
	       mrss_strerror (ret));
      return 1;
    }

  for (item = data->item; item; item = item->next)
    {
      fprintf (stdout, "Item -%s-: ", item->link);
      if (mrss_search_tag
	  (item, "encoded", "http://purl.org/rss/1.0/modules/content/",
	   &tag) != MRSS_OK || !tag)
	{
	  fprintf (stdout, " no Encoded tag\n");
	}
      else
	fprintf (stdout, " encoded %s\n", tag->value);
    }

  mrss_free (data);

  return 0;
}
