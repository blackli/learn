#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "php_ifeng.h"
#include "php_ini.h" 
#include "ext/json/php_json.h" 

zend_class_entry *ifengidc_app_ce;

size_t memory_callback(void *data, size_t size, size_t nmemb, void *content)
{
    size_t realsize = size * nmemb;
    char *p = *(char **)content;
    size_t len = p ? strlen(p) : 0;
    *(char **)content = realloc(p, len + realsize + 1);
    p = *(char **)content;

    if (NULL == p)
    {
        fprintf(stderr,"not enouth memory");
        return -1;
    }

    memcpy(p + len, data, realsize);
    p[len + realsize] = '\0';

    return  realsize;
}

size_t get_content(char *url, char **content, char *args)
{
    CURL *curl_handle;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "PHP Ifeng Extension");
    curl_easy_setopt(curl_handle, CURLOPT_COPYPOSTFIELDS, (char *)args);
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, memory_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)content);
    res = curl_easy_perform(curl_handle);
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();

    return res;
}

PHP_INI_BEGIN()
	PHP_INI_ENTRY("ifengidc.app_api", "https://example.com/", PHP_INI_ALL, NULL)
	PHP_INI_ENTRY("ifengidc.app_id", "18", PHP_INI_ALL, NULL)
	PHP_INI_ENTRY("ifengidc.app_key", "syPOn4ESxas733erOdA", PHP_INI_ALL, NULL)
PHP_INI_END()

ZEND_METHOD(ifengidc_app, productList)
{
	zval *api_url =  zend_read_property(ifengidc_app_ce, getThis(), "api_url", sizeof("api_url")-1, 0 TSRMLS_DC);
	zval *api_id =  zend_read_property(ifengidc_app_ce, getThis(), "api_id", sizeof("api_id")-1, 0 TSRMLS_DC);
	zval *api_key =  zend_read_property(ifengidc_app_ce, getThis(), "api_key", sizeof("api_key")-1, 0 TSRMLS_DC);

	char api[100];
	sprintf(api, "%sproduct/list", Z_STRVAL_P(api_url));

	char curlargs[200];
	sprintf(curlargs, "app=%d&key=%s", Z_LVAL_P(api_id), Z_STRVAL_P(api_key));

	char *content = NULL;
	get_content((char *)api, &content, (char *)curlargs);
	// php_printf("%s\n", Z_STRVAL_P(api_url_zp));
	// php_printf("%s\n", content);
	zval *json;
	MAKE_STD_ZVAL(json);
 	php_json_decode(json, content, strlen(content), 1, 512 TSRMLS_CC);
	// ZVAL_LONG(return_value, 42);
	zval **data;
	zend_hash_find(Z_ARRVAL_P(json), "code", strlen("code") + 1, (void **) &data);
	if (0 != Z_LVAL_PP(data))
	{
		zend_hash_find(Z_ARRVAL_P(json), "msg", strlen("msg") + 1, (void **) &data);
		// char *error_msg = "APP.IFENG say: ";
		// strcat(error_msg, (const char *)Z_STRVAL_PP(data));
		zend_throw_exception_ex(NULL, 1 TSRMLS_CC, Z_STRVAL_PP(data));
		// php_printf("%ld\n", Z_LVAL_PP(data));
	}
	// zend_hash_find(Z_ARRVAL_P(return_value), "data", strlen("data") + 1, (void **) &data);
	// Z_ARRVAL_P(return_value) = data;
	zend_hash_find(Z_ARRVAL_P(json), "data", strlen("data") + 1, (void **) &data);
	RETVAL_ZVAL(*data, 0, 1);
	if (content) free(content);
}


ZEND_METHOD(ifengidc_app, productListauth)
{
	zval *api_url =  zend_read_property(ifengidc_app_ce, getThis(), "api_url", sizeof("api_url")-1, 0 TSRMLS_DC);
	zval *api_id =  zend_read_property(ifengidc_app_ce, getThis(), "api_id", sizeof("api_id")-1, 0 TSRMLS_DC);
	zval *api_key =  zend_read_property(ifengidc_app_ce, getThis(), "api_key", sizeof("api_key")-1, 0 TSRMLS_DC);

	char *prod_abbr;
	int prod_abbr_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &prod_abbr, &prod_abbr_len) == FAILURE)
		RETURN_NULL();

	char api[100];
	sprintf(api, "%sproduct/listauth", Z_STRVAL_P(api_url));

	char curlargs[200];
	sprintf(curlargs, "app=%d&key=%s&prod_abbr=%s", Z_LVAL_P(api_id), Z_STRVAL_P(api_key), prod_abbr);

	char *content = NULL;
	get_content((char *)api, &content, (char *)curlargs);

	zval *json;
	MAKE_STD_ZVAL(json);
 	php_json_decode(json, content, strlen(content), 1, 512 TSRMLS_CC);

	zval **data;
	zend_hash_find(Z_ARRVAL_P(json), "code", strlen("code") + 1, (void **) &data);
	if (0 != Z_LVAL_PP(data))
	{
		zend_hash_find(Z_ARRVAL_P(json), "msg", strlen("msg") + 1, (void **) &data);
		zend_throw_exception_ex(NULL, 1 TSRMLS_CC, Z_STRVAL_PP(data));
	}

	zend_hash_find(Z_ARRVAL_P(json), "data", strlen("data") + 1, (void **) &data);
	RETVAL_ZVAL(*data, 0, 1);
	if (content) free(content);
}


ZEND_METHOD(ifengidc_app, productGet)
{
	zval *api_url =  zend_read_property(ifengidc_app_ce, getThis(), "api_url", sizeof("api_url")-1, 0 TSRMLS_DC);
	zval *api_id =  zend_read_property(ifengidc_app_ce, getThis(), "api_id", sizeof("api_id")-1, 0 TSRMLS_DC);
	zval *api_key =  zend_read_property(ifengidc_app_ce, getThis(), "api_key", sizeof("api_key")-1, 0 TSRMLS_DC);

	char *prod_abbr;
	int prod_abbr_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &prod_abbr, &prod_abbr_len) == FAILURE)
		RETURN_NULL();

	char api[100];
	sprintf(api, "%sproduct/get", Z_STRVAL_P(api_url));

	char curlargs[200];
	sprintf(curlargs, "app=%d&key=%s&prod_abbr=%s", Z_LVAL_P(api_id), Z_STRVAL_P(api_key), prod_abbr);

	char *content = NULL;
	get_content((char *)api, &content, (char *)curlargs);

	zval *json;
	MAKE_STD_ZVAL(json);
 	php_json_decode(json, content, strlen(content), 1, 512 TSRMLS_CC);

	zval **data;
	zend_hash_find(Z_ARRVAL_P(json), "code", strlen("code") + 1, (void **) &data);
	if (0 != Z_LVAL_PP(data))
	{
		zend_hash_find(Z_ARRVAL_P(json), "msg", strlen("msg") + 1, (void **) &data);
		zend_throw_exception_ex(NULL, 1 TSRMLS_CC, Z_STRVAL_PP(data));
	}

	zend_hash_find(Z_ARRVAL_P(json), "data", strlen("data") + 1, (void **) &data);
	RETVAL_ZVAL(*data, 0, 1);
	if (content) free(content);
}

ZEND_METHOD(ifengidc_app, serverList)
{
	zval *api_url =  zend_read_property(ifengidc_app_ce, getThis(), "api_url", sizeof("api_url")-1, 0 TSRMLS_DC);
	zval *api_id =  zend_read_property(ifengidc_app_ce, getThis(), "api_id", sizeof("api_id")-1, 0 TSRMLS_DC);
	zval *api_key =  zend_read_property(ifengidc_app_ce, getThis(), "api_key", sizeof("api_key")-1, 0 TSRMLS_DC);

	char *prod_abbr;
	int prod_abbr_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &prod_abbr, &prod_abbr_len) == FAILURE)
		RETURN_NULL();

	char api[100];
	sprintf(api, "%sproduct/server/list", Z_STRVAL_P(api_url));

	char curlargs[200];
	sprintf(curlargs, "app=%d&key=%s&prod_abbr=%s", Z_LVAL_P(api_id), Z_STRVAL_P(api_key), prod_abbr);

	char *content = NULL;
	get_content((char *)api, &content, (char *)curlargs);

	zval *json;
	MAKE_STD_ZVAL(json);
 	php_json_decode(json, content, strlen(content), 1, 512 TSRMLS_CC);

	zval **data;
	zend_hash_find(Z_ARRVAL_P(json), "code", strlen("code") + 1, (void **) &data);
	if (0 != Z_LVAL_PP(data))
	{
		zend_hash_find(Z_ARRVAL_P(json), "msg", strlen("msg") + 1, (void **) &data);
		zend_throw_exception_ex(NULL, 1 TSRMLS_CC, Z_STRVAL_PP(data));
	}

	zend_hash_find(Z_ARRVAL_P(json), "data", strlen("data") + 1, (void **) &data);
	RETVAL_ZVAL(*data, 0, 1);
	if (content) free(content);
}

ZEND_METHOD(ifengidc_app, __construct)
{
	char *api_url= INI_STR("ifengidc.app_api");
	zend_update_property_string(ifengidc_app_ce, getThis(), "api_url", strlen("api_url"), api_url TSRMLS_CC);
	/*
	char *api_id = INI_STR("ifengidc.app_id");
	char *api_key = INI_STR("ifengidc.app_key");
	zend_update_property_string(ifengidc_app_ce, getThis(), "api_id", strlen("api_id"), api_id TSRMLS_CC);
	zend_update_property_string(ifengidc_app_ce, getThis(), "api_key", strlen("api_key"), api_key TSRMLS_CC);
	*/
}

ZEND_METHOD(ifengidc_app, setAppId)
{
	long appid;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,"l", &appid) == FAILURE)
		RETURN_NULL();

	zend_update_property_long(ifengidc_app_ce, getThis(), "api_id", strlen("api_id"), appid TSRMLS_CC);
	RETURN_TRUE;
}

ZEND_METHOD(ifengidc_app, setKey)
{
	char *key;
	int key_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &key_len) == FAILURE)
		RETURN_NULL();

	zend_update_property_string(ifengidc_app_ce, getThis(), "api_key", strlen("api_key"), key TSRMLS_CC);
	RETURN_TRUE;
}

static zend_function_entry ifengidc_app_method[] = {
	ZEND_ME(ifengidc_app, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	ZEND_ME(ifengidc_app, productList, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(ifengidc_app, productListauth, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(ifengidc_app, productGet, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(ifengidc_app, serverList, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(ifengidc_app, setAppId, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	ZEND_ME(ifengidc_app, setKey, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	{ NULL, NULL, NULL }
};

ZEND_MINIT_FUNCTION(ifeng)
{
	REGISTER_INI_ENTRIES();

	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "IfengidcApp", ifengidc_app_method);
	ifengidc_app_ce = zend_register_internal_class(&ce TSRMLS_CC);
	zend_declare_property_string(ifengidc_app_ce, "api_url", strlen("api_url"), "", ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_long(ifengidc_app_ce, "api_id", strlen("api_id"), 0, ZEND_ACC_PUBLIC TSRMLS_CC);
	zend_declare_property_string(ifengidc_app_ce, "api_key", strlen("api_key"), "", ZEND_ACC_PUBLIC TSRMLS_CC);
	return SUCCESS;
}

//module entry
zend_module_entry ifeng_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"ifeng", //这个地方是扩展名称，往往我们会在这个地方使用一个宏。
	NULL, /* Functions */
	ZEND_MINIT(ifeng), /* MINIT */
	NULL, /* MSHUTDOWN */
	NULL, /* RINIT */
	NULL, /* RSHUTDOWN */
	NULL, /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", //这个地方是我们扩展的版本
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_IFENG
ZEND_GET_MODULE(ifeng)
#endif
