#include <stdio.h>
#include <string.h>
#include "mrss.h"

static void print_tags (mrss_tag_t * tag, int index);

int
main (int argc, char **argv)
{
  mrss_t *data;
  mrss_error_t ret;
  mrss_hour_t *hour;
  mrss_day_t *day;
  mrss_category_t *category;
  mrss_item_t *item;
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

  fprintf (stdout, "\nGeneric:\n");
  fprintf (stdout, "\tfile: %s\n", data->file);
  fprintf (stdout, "\tencoding: %s\n", data->encoding);
  fprintf (stdout, "\tsize: %d\n", (int) data->size);

  fprintf (stdout, "\tversion:");
  switch (data->version)
    {
    case MRSS_VERSION_0_91:
      fprintf (stdout, " 0.91\n");
      break;

    case MRSS_VERSION_0_92:
      fprintf (stdout, " 0.92\n");
      break;

    case MRSS_VERSION_1_0:
      fprintf (stdout, " 1.0\n");
      break;

    case MRSS_VERSION_2_0:
      fprintf (stdout, " 2.0\n");
      break;

    case MRSS_VERSION_ATOM_1_0:
      fprintf (stdout, " Atom 1.0\n");
      break;

    case MRSS_VERSION_ATOM_0_3:
      fprintf (stdout, " Atom 0.3\n");
      break;
    }

  fprintf (stdout, "\nChannel:\n");
  fprintf (stdout, "\ttitle: %s\n", data->title);
  fprintf (stdout, "\tdescription: %s\n", data->description);
  fprintf (stdout, "\tlink: %s\n", data->link);
  fprintf (stdout, "\tlanguage: %s\n", data->language);
  fprintf (stdout, "\trating: %s\n", data->rating);
  fprintf (stdout, "\tcopyright: %s\n", data->copyright);
  fprintf (stdout, "\tpubDate: %s\n", data->pubDate);
  fprintf (stdout, "\tlastBuildDate: %s\n", data->lastBuildDate);
  fprintf (stdout, "\tdocs: %s\n", data->docs);
  fprintf (stdout, "\tmanagingeditor: %s\n", data->managingeditor);
  fprintf (stdout, "\twebMaster: %s\n", data->webMaster);
  fprintf (stdout, "\tgenerator: %s\n", data->generator);
  fprintf (stdout, "\tttl: %d\n", data->ttl);
  fprintf (stdout, "\tabout: %s\n", data->about);

  fprintf (stdout, "\nImage:\n");
  fprintf (stdout, "\timage_title: %s\n", data->image_title);
  fprintf (stdout, "\timage_url: %s\n", data->image_url);
  fprintf (stdout, "\timage_link: %s\n", data->image_link);
  fprintf (stdout, "\timage_width: %d\n", data->image_width);
  fprintf (stdout, "\timage_height: %d\n", data->image_height);
  fprintf (stdout, "\timage_description: %s\n", data->image_description);

  fprintf (stdout, "\nTextInput:\n");
  fprintf (stdout, "\ttextinput_title: %s\n", data->textinput_title);
  fprintf (stdout, "\ttextinput_description: %s\n",
	   data->textinput_description);
  fprintf (stdout, "\ttextinput_name: %s\n", data->textinput_name);
  fprintf (stdout, "\ttextinput_link: %s\n", data->textinput_link);

  fprintf (stdout, "\nCloud:\n");
  fprintf (stdout, "\tcloud: %s\n", data->cloud);
  fprintf (stdout, "\tcloud_domain: %s\n", data->cloud_domain);
  fprintf (stdout, "\tcloud_port: %d\n", data->cloud_port);
  fprintf (stdout, "\tcloud_registerProcedure: %s\n",
	   data->cloud_registerProcedure);
  fprintf (stdout, "\tcloud_protocol: %s\n", data->cloud_protocol);

  fprintf (stdout, "\nSkipHours:\n");
  hour = data->skipHours;
  while (hour)
    {
      fprintf (stdout, "\t%s\n", hour->hour);
      hour = hour->next;
    }

  fprintf (stdout, "\nSkipDays:\n");
  day = data->skipDays;
  while (day)
    {
      fprintf (stdout, "\t%s\n", day->day);
      day = day->next;
    }

  fprintf (stdout, "\nCategory:\n");
  category = data->category;
  while (category)
    {
      fprintf (stdout, "\tcategory: %s\n", category->category);
      fprintf (stdout, "\tcategory_domain: %s\n", category->domain);
      category = category->next;
    }

  if (data->other_tags)
    print_tags (data->other_tags, 0);

  fprintf (stdout, "\nItems:\n");
  item = data->item;
  while (item)
    {
      fprintf (stdout, "\ttitle: %s\n", item->title);
      fprintf (stdout, "\tlink: %s\n", item->link);
      fprintf (stdout, "\tdescription: %s\n", item->description);
      fprintf (stdout, "\tauthor: %s\n", item->author);
      fprintf (stdout, "\tcomments: %s\n", item->comments);
      fprintf (stdout, "\tpubDate: %s\n", item->pubDate);
      fprintf (stdout, "\tguid: %s\n", item->guid);
      fprintf (stdout, "\tguid_isPermaLink: %d\n", item->guid_isPermaLink);
      fprintf (stdout, "\tsource: %s\n", item->source);
      fprintf (stdout, "\tsource_url: %s\n", item->source_url);
      fprintf (stdout, "\tenclosure: %s\n", item->enclosure);
      fprintf (stdout, "\tenclosure_url: %s\n", item->enclosure_url);
      fprintf (stdout, "\tenclosure_length: %d\n", item->enclosure_length);
      fprintf (stdout, "\tenclosure_type: %s\n", item->enclosure_type);

      fprintf (stdout, "\tCategory:\n");
      category = item->category;
      while (category)
	{
	  fprintf (stdout, "\t\tcategory: %s\n", category->category);
	  fprintf (stdout, "\t\tcategory_domain: %s\n", category->domain);
	  category = category->next;
	}

      if (item->other_tags)
	print_tags (item->other_tags, 1);

      fprintf (stdout, "\n");
      item = item->next;
    }

  mrss_free (data);

  return 0;
}

static void
print_tags (mrss_tag_t * tag, int index)
{
  mrss_attribute_t *attribute;
  int i;

  for (i = 0; i < index; i++)
    fprintf (stdout, "\t");

  fprintf (stdout, "Other Tags:\n");
  while (tag)
    {
      for (i = 0; i < index; i++)
	fprintf (stdout, "\t");

      fprintf (stdout, "\ttag name: %s\n", tag->name);

      for (i = 0; i < index; i++)
	fprintf (stdout, "\t");

      fprintf (stdout, "\ttag value: %s\n", tag->value);

      for (i = 0; i < index; i++)
	fprintf (stdout, "\t");

      fprintf (stdout, "\ttag ns: %s\n", tag->ns);

      if (tag->children)
	print_tags (tag->children, index + 1);

      for (attribute = tag->attributes; attribute;
	   attribute = attribute->next)
	{
	  for (i = 0; i < index; i++)
	    fprintf (stdout, "\t");

	  fprintf (stdout, "\tattribute name: %s\n", attribute->name);

	  for (i = 0; i < index; i++)
	    fprintf (stdout, "\t");

	  fprintf (stdout, "\tattribute value: %s\n", attribute->value);

	  for (i = 0; i < index; i++)
	    fprintf (stdout, "\t");

	  fprintf (stdout, "\tattribute ns: %s\n", attribute->ns);
	}

      tag = tag->next;
    }
}
