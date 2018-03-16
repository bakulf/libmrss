/* mRss - Copyright (C) 2005-2007 baku - Andrea Marchesini
 *                                     <baku@ippolita.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include <mrss.h>

#define PHP_MRSS_VERSION "0.2"
#define PHP_MRSS_EXTNAME "mrss"

PHP_FUNCTION(mrss_parse_url);
PHP_FUNCTION(mrss_parse_url_with_options);
PHP_FUNCTION(mrss_parse_file);
PHP_FUNCTION(mrss_parse_buffer);

PHP_FUNCTION(mrss_write_file);
PHP_FUNCTION(mrss_write_buffer);

PHP_FUNCTION(mrss_free);

PHP_FUNCTION(mrss_error);
PHP_FUNCTION(mrss_strerror);

PHP_FUNCTION(mrss_get);

PHP_FUNCTION(mrss_get_last_modified);
PHP_FUNCTION(mrss_get_last_modified_with_options);

PHP_FUNCTION(mrss_options_new);
PHP_FUNCTION(mrss_options_free);

zend_module_entry mrss_module_entry;

PHP_MINIT_FUNCTION(mrss) {
REGISTER_LONG_CONSTANT("MRSS_OK", MRSS_OK, CONST_CS | CONST_PERSISTENT);
REGISTER_LONG_CONSTANT("MRSS_ERR_POSIX", MRSS_ERR_POSIX, CONST_CS | CONST_PERSISTENT);
REGISTER_LONG_CONSTANT("MRSS_ERR_PARSER", MRSS_ERR_PARSER, CONST_CS | CONST_PERSISTENT);
REGISTER_LONG_CONSTANT("MRSS_ERR_VERSION", MRSS_ERR_VERSION, CONST_CS | CONST_PERSISTENT);
REGISTER_LONG_CONSTANT("MRSS_ERR_DATA", MRSS_ERR_DATA, CONST_CS | CONST_PERSISTENT);
return SUCCESS;
}

static function_entry mrss_functions[] = {
  PHP_FE (mrss_parse_url, NULL) 
  PHP_FE (mrss_parse_url_with_options, NULL) 
  PHP_FE (mrss_parse_file, NULL) 
  PHP_FE (mrss_parse_buffer, NULL) 

  PHP_FE (mrss_write_file, NULL) 
  PHP_FE (mrss_write_buffer, NULL) 

  PHP_FE (mrss_free, NULL)

  PHP_FE (mrss_error, NULL)
  PHP_FE (mrss_strerror, NULL)

  PHP_FE (mrss_get, NULL)

  PHP_FE (mrss_get_last_modified, NULL)
  PHP_FE (mrss_get_last_modified_with_options, NULL)

  PHP_FE (mrss_options_new, NULL)
  PHP_FE (mrss_options_free, NULL)

  {NULL, NULL, NULL}

};

zend_module_entry mrss_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
  STANDARD_MODULE_HEADER,
#endif
  PHP_MRSS_EXTNAME,
  mrss_functions,
  PHP_MINIT(mrss),
  NULL,
  NULL,
  NULL,
  NULL,
#if ZEND_MODULE_API_NO >= 20010901
  PHP_MRSS_VERSION,
#endif
  STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE (mrss);

struct phpmrss_data {
  char		magic_code[5];

  mrss_t	*mrss;
  mrss_error_t	error;
};

PHP_FUNCTION (mrss_parse_url)
{
  char *url;
  int url_len;
  struct phpmrss_data *data;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &url,&url_len) == FAILURE) return;

  data=(struct phpmrss_data *)malloc(sizeof(struct phpmrss_data));
  memset(data, 0, sizeof(struct phpmrss_data));
  strcpy(data->magic_code, PHP_MRSS_EXTNAME);

  if((data->error=mrss_parse_url(url, &data->mrss))!=MRSS_OK)
	  data->mrss=NULL;
  
  RETURN_LONG((long)data);
}

PHP_FUNCTION (mrss_parse_url_with_options)
{
  char *url;
  int url_len;
  struct phpmrss_data *data;
  mrss_options_t *options;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &url,&url_len, &options) == FAILURE) return;

  data=(struct phpmrss_data *)malloc(sizeof(struct phpmrss_data));
  memset(data, 0, sizeof(struct phpmrss_data));
  strcpy(data->magic_code, PHP_MRSS_EXTNAME);

  if((data->error=mrss_parse_url_with_options(url, &data->mrss, options))!=MRSS_OK)
	  data->mrss=NULL;
  
  RETURN_LONG((long)data);
}

PHP_FUNCTION (mrss_parse_file)
{
  char *file;
  int file_len;
  struct phpmrss_data *data;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file,&file_len) == FAILURE) return;

  data=(struct phpmrss_data *)malloc(sizeof(struct phpmrss_data));
  memset(data, 0, sizeof(struct phpmrss_data));
  strcpy(data->magic_code, PHP_MRSS_EXTNAME);

  if((data->error=mrss_parse_file(file, &data->mrss))!=MRSS_OK)
	  data->mrss=NULL;
  
  RETURN_LONG((long)data);
}

PHP_FUNCTION (mrss_parse_buffer)
{
  char *buffer;
  int buffer_len;
  struct phpmrss_data *data;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &buffer,&buffer_len) == FAILURE) return;

  data=(struct phpmrss_data *)malloc(sizeof(struct phpmrss_data));
  memset(data, 0, sizeof(struct phpmrss_data));
  strcpy(data->magic_code, PHP_MRSS_EXTNAME);

  if((data->error=mrss_parse_buffer(buffer, buffer_len, &data->mrss))!=MRSS_OK)
	  data->mrss=NULL;
  
  RETURN_LONG((long)data);
}

PHP_FUNCTION (mrss_write_file)
{
  char *file;
  int file_len;
  struct phpmrss_data *data;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &data, &file,&file_len) == FAILURE) return;

  if(!data ||
     data->magic_code[0]!='m' || 
     data->magic_code[1]!='r' ||
     data->magic_code[2]!='s' ||
     data->magic_code[3]!='s' ||
     data->magic_code[4]!='\0') {
	  php_error(E_ERROR, "The data object must be a MRSS element!");
	  return;
  }

  if(!data->mrss) {
	  php_error(E_ERROR, "The data object must be a MRSS element not empty!");
	  return;
  }

  data->error=mrss_write_file(data->mrss, file);
  
  RETURN_BOOL(0);
}

PHP_FUNCTION (mrss_write_buffer)
{
  struct phpmrss_data *data;
  char *buffer=NULL;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &data) == FAILURE) return;

  if(!data ||
     data->magic_code[0]!='m' || 
     data->magic_code[1]!='r' ||
     data->magic_code[2]!='s' ||
     data->magic_code[3]!='s' ||
     data->magic_code[4]!='\0') {
	  php_error(E_ERROR, "The data object must be a MRSS element!");
	  return;
  }

  if(!data->mrss) {
	  php_error(E_ERROR, "The data object must be a MRSS element not empty!");
	  return;
  }

  data->error=mrss_write_buffer(data->mrss, &buffer);
  
  if(data->error!=MRSS_OK)
  {
    RETURN_EMPTY_STRING();
  }
  else
  {
    RETURN_STRING(buffer, 1);
  }
}

PHP_FUNCTION (mrss_free)
{
  struct phpmrss_data *data;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &data) == FAILURE) return;

  if(!data ||
     data->magic_code[0]!='m' || 
     data->magic_code[1]!='r' ||
     data->magic_code[2]!='s' ||
     data->magic_code[3]!='s' ||
     data->magic_code[4]!='\0') {
	  php_error(E_ERROR, "The data object must be a MRSS element!");
	  return;
  }

  mrss_free(data->mrss);
  free(data);

  RETURN_NULL();
}

PHP_FUNCTION (mrss_error)
{
  struct phpmrss_data *data;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &data) == FAILURE) return;

  if(!data ||
     data->magic_code[0]!='m' || 
     data->magic_code[1]!='r' ||
     data->magic_code[2]!='s' ||
     data->magic_code[3]!='s' ||
     data->magic_code[4]!='\0') {
	  php_error(E_ERROR, "The data object must be a MRSS element!");
	  return;
  }

  RETURN_LONG(data->error);
}

PHP_FUNCTION (mrss_strerror)
{
  struct phpmrss_data *data;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &data) == FAILURE) return;

  if(!data ||
     data->magic_code[0]!='m' || 
     data->magic_code[1]!='r' ||
     data->magic_code[2]!='s' ||
     data->magic_code[3]!='s' ||
     data->magic_code[4]!='\0') {
	  php_error(E_ERROR, "The data object must be a MRSS element!");
	  return;
  }

  RETURN_STRING(mrss_strerror(data->error), 1);
}

PHP_FUNCTION (mrss_get) {
  struct phpmrss_data *data;
  zval  *hour, *day, *category, *item, *category_zval, *item_zval;
  mrss_hour_t *h;
  mrss_day_t *d;
  mrss_category_t *c;
  mrss_item_t *ip;
  int i, j;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &data) == FAILURE) return;

  if(!data ||
     data->magic_code[0]!='m' || 
     data->magic_code[1]!='r' ||
     data->magic_code[2]!='s' ||
     data->magic_code[3]!='s' ||
     data->magic_code[4]!='\0') {
	  php_error(E_ERROR, "The data object must be a MRSS element!");
	  return;
  }

  if(!data->mrss) {
	  php_error(E_ERROR, "The data object must be a MRSS element not empty!");
	  return;
  }

  if (array_init(return_value) == FAILURE) {
     FREE_ZVAL(return_value);
     return;
  }

#define INSERT_STRING( x , y , z ) add_assoc_string (x, y, z ? z : "", 1)

  INSERT_STRING(return_value, "file", data->mrss->file);
  add_assoc_long(return_value, "size", data->mrss->size);
  INSERT_STRING(return_value, "encoding", data->mrss->encoding);

  add_assoc_long(return_value, "version", data->mrss->version);

  INSERT_STRING(return_value, "title", data->mrss->title);
  INSERT_STRING(return_value, "title_type", data->mrss->title_type);
  INSERT_STRING(return_value, "description", data->mrss->description);
  INSERT_STRING(return_value, "description_type", data->mrss->description_type);
  INSERT_STRING(return_value, "link", data->mrss->link);
  INSERT_STRING(return_value, "id", data->mrss->id);
  INSERT_STRING(return_value, "language", data->mrss->language);
  INSERT_STRING(return_value, "rating", data->mrss->rating);
  INSERT_STRING(return_value, "copyright", data->mrss->copyright);
  INSERT_STRING(return_value, "copyright_type", data->mrss->copyright_type);
  INSERT_STRING(return_value, "pubDate", data->mrss->pubDate);
  INSERT_STRING(return_value, "lastBuildDate", data->mrss->lastBuildDate);
  INSERT_STRING(return_value, "docs", data->mrss->docs);

  INSERT_STRING(return_value, "managingeditor", data->mrss->managingeditor);
  INSERT_STRING(return_value, "managingeditor_email", data->mrss->managingeditor_email);
  INSERT_STRING(return_value, "managingeditor_uri", data->mrss->managingeditor_uri);

  INSERT_STRING(return_value, "webMaster", data->mrss->webMaster);
  add_assoc_long(return_value, "ttl", data->mrss->ttl);
  INSERT_STRING(return_value, "about", data->mrss->about);
  
  INSERT_STRING(return_value, "contributor", data->mrss->contributor);
  INSERT_STRING(return_value, "contributor_email", data->mrss->contributor_email);
  INSERT_STRING(return_value, "contributor_uri", data->mrss->contributor_uri);

  INSERT_STRING(return_value, "generator", data->mrss->generator);
  INSERT_STRING(return_value, "generator_uri", data->mrss->generator_uri);
  INSERT_STRING(return_value, "generator_version", data->mrss->generator_version);

  INSERT_STRING(return_value, "image_title", data->mrss->image_title);
  INSERT_STRING(return_value, "image_url", data->mrss->image_url);
  INSERT_STRING(return_value, "image_link", data->mrss->image_link);
  add_assoc_long(return_value, "image_width", data->mrss->image_width);
  add_assoc_long(return_value, "image_height", data->mrss->image_height);
  INSERT_STRING(return_value, "image_description", data->mrss->image_description);

  INSERT_STRING(return_value, "textinput_title", data->mrss->textinput_title);
  INSERT_STRING(return_value, "textinput_description", data->mrss->textinput_description);
  INSERT_STRING(return_value, "textinput_name", data->mrss->textinput_name);
  INSERT_STRING(return_value, "textinput_link", data->mrss->textinput_link);

  INSERT_STRING(return_value, "cloud", data->mrss->cloud);
  INSERT_STRING(return_value, "cloud_domain", data->mrss->cloud_domain);
  add_assoc_long(return_value, "cloud_port", data->mrss->cloud_port);
  INSERT_STRING(return_value, "cloud_path", data->mrss->cloud_path);
  INSERT_STRING(return_value, "cloud_registerProcedure", data->mrss->cloud_registerProcedure);
  INSERT_STRING(return_value, "cloud_protocol", data->mrss->cloud_protocol);
  
  MAKE_STD_ZVAL(hour);
  if (array_init(hour) == FAILURE) {
     FREE_ZVAL(hour);
     return;
  }

  h=data->mrss->skipHours;
  i=0;

  while(h) {
   add_index_string(hour, i++, h->hour ? h->hour : "", 1);
   h=h->next;
  }

  add_assoc_zval(return_value,"skipHours", hour);

  MAKE_STD_ZVAL(day);
  if (array_init(day) == FAILURE) {
     FREE_ZVAL(day);
     return;
  }

  d=data->mrss->skipDays;
  i=0;

  while(d) {
  add_index_string(day, i++, d->day ? d->day : "", 1);
   d=d->next;
  }

  add_assoc_zval(return_value,"skipDays", day);

  MAKE_STD_ZVAL(category);
  if (array_init(category) == FAILURE) {
     FREE_ZVAL(category);
     return;
  }

  c=data->mrss->category;
  i=0;

  while(c) {
    MAKE_STD_ZVAL(category_zval);
    if (array_init(category_zval) == FAILURE) {
       FREE_ZVAL(category_zval);
       return;
    }
    INSERT_STRING(category_zval, "category", c->category);
    INSERT_STRING(category_zval, "domain", c->domain);
    INSERT_STRING(category_zval, "label", c->label);

    add_index_zval(category, i++, category_zval);
    c=c->next;
  }

  add_assoc_zval(return_value,"category", category);

  MAKE_STD_ZVAL(item);
  if (array_init(item) == FAILURE) {
     FREE_ZVAL(item);
     return;
  }

  ip=data->mrss->item;
  i=0;

  while(ip) {
    MAKE_STD_ZVAL(item_zval);
    if (array_init(item_zval) == FAILURE) {
       FREE_ZVAL(item_zval);
       return;
    }

    INSERT_STRING(item_zval, "title", ip->title);
    INSERT_STRING(item_zval, "title_type", ip->title_type);
    INSERT_STRING(item_zval, "link", ip->link);
    INSERT_STRING(item_zval, "description", ip->description);
    INSERT_STRING(item_zval, "description_type", ip->description_type);
    INSERT_STRING(item_zval, "copyright", ip->copyright);
    INSERT_STRING(item_zval, "copyright_type", ip->copyright_type);

    INSERT_STRING(item_zval, "author", ip->author);
    INSERT_STRING(item_zval, "author_email", ip->author_email);
    INSERT_STRING(item_zval, "author_uri", ip->author_uri);

    INSERT_STRING(item_zval, "contributor", ip->contributor);
    INSERT_STRING(item_zval, "contributor_email", ip->contributor_email);
    INSERT_STRING(item_zval, "contributor_uri", ip->contributor_uri);

    INSERT_STRING(item_zval, "comments", ip->comments);
    INSERT_STRING(item_zval, "pubDate", ip->pubDate);
    INSERT_STRING(item_zval, "guid", ip->guid);
    add_assoc_long(item_zval, "guid_isPermaLink", ip->guid_isPermaLink);
  
    INSERT_STRING(item_zval, "source", ip->source);
    INSERT_STRING(item_zval, "source_url", ip->source_url);
    
    INSERT_STRING(item_zval, "enclosure", ip->enclosure);
    INSERT_STRING(item_zval, "enclosure_url", ip->enclosure_url);
    add_assoc_long(item_zval, "enclosure_length", ip->enclosure_length);
    INSERT_STRING(item_zval, "enclosure_type", ip->enclosure_type);

    MAKE_STD_ZVAL(category);
    if (array_init(category) == FAILURE) {
       FREE_ZVAL(category);
       return;
    }

    c=data->mrss->category;
    j=0;

    while(c) {
      MAKE_STD_ZVAL(category_zval);
      if (array_init(category_zval) == FAILURE) {
         FREE_ZVAL(category_zval);
         return;
      }
      INSERT_STRING(category_zval, "category", c->category);
      INSERT_STRING(category_zval, "domain", c->domain);
      INSERT_STRING(category_zval, "label", c->label);

      add_index_zval(category, j++, category_zval);
      c=c->next;
    }

    add_assoc_zval(item_zval,"category", category);

    add_index_zval(item, i++, item_zval);
    ip=ip->next;
  }

  add_assoc_zval(return_value,"item", item);
}

PHP_FUNCTION (mrss_get_last_modified)
{
  char *url;
  int url_len;
  time_t t;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &url,&url_len) == FAILURE) return;

  if(mrss_get_last_modified(url, &t)!=MRSS_OK) {
    RETURN_LONG(0);
  } else {
    RETURN_LONG((long)t);
  }
}

PHP_FUNCTION (mrss_get_last_modified_with_options)
{
  char *url;
  int url_len;
  time_t t;
  mrss_options_t *options;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &url,&url_len, &options) == FAILURE) return;

  if(mrss_get_last_modified_with_options(url, &t, options)!=MRSS_OK) {
    RETURN_LONG(0);
  } else {
    RETURN_LONG((long)t);
  }
}

PHP_FUNCTION (mrss_options_new)
{
  mrss_options_t *options;
  char *proxy, *certfile, *password, *authentication, *proxy_authentication, *user_agent, *cacert;
  int proxy_len, certfile_len, password_len, verifypeer, authentication_len, timeout, proxy_authentication_len, user_agent_len, cacert_len;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lssssslss", &timeout, &proxy, &proxy_len, &proxy_authentication, &proxy_authentication_len, &certfile, &certfile_len, &password, &password_len, &cacert, &cacert_len, &verifypeer, &authentication, &authentication_len, user_agent, user_agent_len) == FAILURE) return;

  options=mrss_options_new(timeout, proxy, proxy_authentication, certfile, password, cacert, verifypeer, authentication, user_agent);
  RETURN_LONG((long) options);
}

PHP_FUNCTION (mrss_options_free)
{
  mrss_options_t *options;

  if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &options) == FAILURE) return;

  if(options)
    mrss_options_free(options);

  RETURN_NULL();
}

