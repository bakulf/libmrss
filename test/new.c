#include <stdio.h>
#include <stdlib.h>
#include "mrss.h"

void
check (mrss_error_t ret)
{
  puts (mrss_strerror (ret));
  if (ret != MRSS_OK)
    exit (1);
}

int
main (int argc, char **argv)
{
  mrss_t *data;
  mrss_error_t ret;
  char *buffer;
  int i;

  data = NULL;
  fprintf (stdout, "New data... ");
  ret = mrss_new (&data);
  check (ret);

  fprintf (stdout, "Set some values... ");
  ret = mrss_set (data,
		  MRSS_FLAG_VERSION, MRSS_VERSION_2_0,
		  MRSS_FLAG_TITLE, "a title",
		  MRSS_FLAG_DESCRIPTION, "a description",
		  MRSS_FLAG_LINK, "a link",
		  MRSS_FLAG_LANGUAGE, "it_IT",
		  MRSS_FLAG_RATING, "rating",
		  MRSS_FLAG_COPYRIGHT, "the copyright",
		  MRSS_FLAG_PUBDATE, "today",
		  MRSS_FLAG_LASTBUILDDATE, "yesterday",
		  MRSS_FLAG_DOCS, "http://github.com/bakulf",
		  MRSS_FLAG_MANAGINGEDITOR, "vim",
		  MRSS_FLAG_WEBMASTER, "b",
		  MRSS_FLAG_GENERATOR, "none!",
		  MRSS_FLAG_TTL, 255,
		  MRSS_FLAG_IMAGE_TITLE, "title of the image",
		  MRSS_FLAG_IMAGE_URL, "http://github.com/bakulf/img.png",
		  MRSS_FLAG_IMAGE_LINK, "http://github.com/bakulf/",
		  MRSS_FLAG_IMAGE_WIDTH, 1000,
		  MRSS_FLAG_IMAGE_HEIGHT, 2000,
		  MRSS_FLAG_IMAGE_DESCRIPTION, "no image description",
		  MRSS_FLAG_TEXTINPUT_TITLE, "textinput title",
		  MRSS_FLAG_TEXTINPUT_DESCRIPTION, "textinput description",
		  MRSS_FLAG_TEXTINPUT_NAME, "textinput name",
		  MRSS_FLAG_TEXTINPUT_LINK, "http://github.com/bakulf",
		  MRSS_FLAG_CLOUD, "Cloud!",
		  MRSS_FLAG_CLOUD_DOMAIN, "github.com",
		  MRSS_FLAG_CLOUD_PORT, 8080,
		  MRSS_FLAG_CLOUD_PATH, "/bakulf/libmrss",
		  MRSS_FLAG_CLOUD_REGISTERPROCEDURE, "none",
		  MRSS_FLAG_CLOUD_PROTOCOL, "gopher", MRSS_FLAG_END);
  check (ret);

  for (i = 0; i < 10; i++)
    {
      mrss_hour_t *hour = NULL;
      char s[1024];

      fprintf (stdout, "New skipHours element... ");
      ret = mrss_new_subdata (data, MRSS_ELEMENT_SKIPHOURS, &hour);
      check (ret);

      snprintf (s, sizeof (s), "Element %d", i);
      fprintf (stdout, "Set skipHours value... ");
      ret = mrss_set (hour, MRSS_FLAG_HOUR, s, MRSS_FLAG_END);
      check (ret);
    }

  for (i = 0; i < 10; i++)
    {
      mrss_day_t *day = NULL;
      char s[1024];

      fprintf (stdout, "New skipDays element... ");
      ret = mrss_new_subdata (data, MRSS_ELEMENT_SKIPDAYS, &day);
      check (ret);

      snprintf (s, sizeof (s), "Element %d", i);
      fprintf (stdout, "Set skipDays value... ");
      ret = mrss_set (day, MRSS_FLAG_DAY, s, MRSS_FLAG_END);
      check (ret);
    }

  for (i = 0; i < 10; i++)
    {
      mrss_category_t *category = NULL;
      char s1[1024];
      char s2[1024];

      fprintf (stdout, "New category element... ");
      ret = mrss_new_subdata (data, MRSS_ELEMENT_CATEGORY, &category);
      check (ret);

      snprintf (s1, sizeof (s1), "Element %d", i);
      snprintf (s2, sizeof (s2), "Domain %d", i);
      fprintf (stdout, "Set category values... ");
      ret = mrss_set (category,
		      MRSS_FLAG_CATEGORY, s1,
		      MRSS_FLAG_CATEGORY_DOMAIN, s2, MRSS_FLAG_END);
      check (ret);
    }

  for (i = 0; i < 10; i++)
    {
      mrss_tag_t *tag = NULL;
      char s1[1024];
      char s2[1024];
      char s3[1024];

      fprintf (stdout, "New tag element... ");
      ret = mrss_new_subdata (data, MRSS_ELEMENT_TAG, &tag);
      check (ret);

      snprintf (s1, sizeof (s1), "Element %d", i);
      snprintf (s2, sizeof (s2), "element_%d", i);
      snprintf (s3, sizeof (s3), "http://www.something.net/");
      fprintf (stdout, "Set tag value... ");
      ret = mrss_set (tag, MRSS_FLAG_TAG_NAME, s2,
		      MRSS_FLAG_TAG_VALUE, s1,
		      MRSS_FLAG_TAG_NS, s3, MRSS_FLAG_END);
      check (ret);
    }

  for (i = 0; i < 10; i++)
    {
      mrss_item_t *item = NULL;
      int j;

      fprintf (stdout, "New item element... ");
      ret = mrss_new_subdata (data, MRSS_ELEMENT_ITEM, &item);
      check (ret);

      fprintf (stdout, "Set item values... ");
      ret = mrss_set (item,
		      MRSS_FLAG_ITEM_TITLE, "item title",
		      MRSS_FLAG_ITEM_LINK, "item link",
		      MRSS_FLAG_ITEM_DESCRIPTION, "item description",
		      MRSS_FLAG_ITEM_AUTHOR, "item author",
		      MRSS_FLAG_ITEM_COMMENTS, "item comments",
		      MRSS_FLAG_ITEM_PUBDATE, "item pubdate",
		      MRSS_FLAG_ITEM_GUID, "item guid",
		      MRSS_FLAG_ITEM_GUID_ISPERMALINK, 1 /* 0 is false */ ,
		      MRSS_FLAG_ITEM_SOURCE, "item source",
		      MRSS_FLAG_ITEM_SOURCE_URL, "item source url",
		      MRSS_FLAG_ITEM_ENCLOSURE, "item enclosure",
		      MRSS_FLAG_ITEM_ENCLOSURE_URL, "item enclosure url",
		      MRSS_FLAG_ITEM_ENCLOSURE_LENGTH, 1234,
		      MRSS_FLAG_ITEM_ENCLOSURE_TYPE, "item enclosure type",
		      MRSS_FLAG_END);

      for (j = 0; j < 10; j++)
	{
	  mrss_category_t *category = NULL;
	  char s1[1024];
	  char s2[1024];

	  fprintf (stdout, "New category element... ");
	  ret = mrss_new_subdata (item, MRSS_ELEMENT_CATEGORY, &category);
	  check (ret);

	  snprintf (s1, sizeof (s1), "Element %d", j);
	  snprintf (s2, sizeof (s2), "Domain %d", j);
	  fprintf (stdout, "Set category values... ");
	  ret = mrss_set (category,
			  MRSS_FLAG_CATEGORY, s1,
			  MRSS_FLAG_CATEGORY_DOMAIN, s2, MRSS_FLAG_END);
	  check (ret);
	}

      for (i = 0; i < 10; i++)
	{
	  mrss_tag_t *tag = NULL;
	  char s1[1024];
	  char s2[1024];
	  char s3[1024];
	  int j;

	  fprintf (stdout, "New tag element... ");
	  ret = mrss_new_subdata (item, MRSS_ELEMENT_TAG, &tag);
	  check (ret);

	  snprintf (s1, sizeof (s1), "Element %d", i);
	  snprintf (s2, sizeof (s2), "element_%d", i);
	  snprintf (s3, sizeof (s3), "http://www.something%d.net/", i);
	  fprintf (stdout, "Set tag value... ");
	  ret = mrss_set (tag, MRSS_FLAG_TAG_NAME, s2,
			  MRSS_FLAG_TAG_VALUE, s1,
			  MRSS_FLAG_TAG_NS, s3, MRSS_FLAG_END);
	  check (ret);

	  for (j = 0; j < 10; j++)
	    {
	      mrss_attribute_t *attribute = NULL;
	      char s1[1024];
	      char s2[1024];
	      char s3[1024];

	      fprintf (stdout, "New attribute element... ");
	      ret =
		mrss_new_subdata (tag, MRSS_ELEMENT_ATTRIBUTE, &attribute);
	      check (ret);

	      snprintf (s1, sizeof (s1), "Element %d", j);
	      snprintf (s2, sizeof (s2), "element_%d", j);
	      snprintf (s3, sizeof (s3), "http://www.something%d.net/", j);
	      fprintf (stdout, "Set attribute value... ");
	      ret = mrss_set (attribute, MRSS_FLAG_ATTRIBUTE_NAME, s2,
			      MRSS_FLAG_ATTRIBUTE_VALUE, s1,
			      MRSS_FLAG_ATTRIBUTE_NS, s3, MRSS_FLAG_END);
	      check (ret);
	    }
	}

      check (ret);
    }

  buffer = NULL;
  fprintf (stdout, "Create the RSS in memory... ");
  ret = mrss_write_buffer (data, &buffer);
  check (ret);

  puts (buffer);
  free (buffer);
  mrss_free (data);

  return 0;
}
