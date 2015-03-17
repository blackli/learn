#include "php_ifeng.h"

ZEND_FUNCTION(ifeng_hello)
{
	php_printf("i am ifeng");
}

ZEND_FUNCTION(ifeng_sample_long) 
{
	if (return_value_used) {
		ZVAL_LONG(return_value, 42);
		return;
	} else {
		php_error_docref(NULL TSRMLS_CC, E_NOTICE,"jeje");
		RETURN_NULL();
	}
}

ZEND_FUNCTION(ifeng_sample_getlong)
{
	long foo;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &foo) == FAILURE)
	{
		RETURN_NULL();
	}
	php_printf("%ld\n", foo);
	RETURN_TRUE;
}

ZEND_FUNCTION(ifeng_array)
{
	array_init(return_value);
	add_assoc_long(return_value, "life", 43);
}

static zend_function_entry ifeng_functions[] = {
	ZEND_FE(ifeng_hello,        NULL)
	ZEND_FALIAS(ifeng_hi, ifeng_hello, NULL)
	ZEND_FE(ifeng_sample_long,        NULL)
	ZEND_FE(ifeng_sample_getlong,        NULL)
	ZEND_FE(ifeng_array,        NULL)
	{ NULL, NULL, NULL }
};

//module entry
zend_module_entry ifeng_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"ifeng", 
	ifeng_functions, /* Functions */
	NULL, /* MINIT */
	NULL, /* MSHUTDOWN */
	NULL, /* RINIT */
	NULL, /* RSHUTDOWN */
	NULL, /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* version */
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_IFENG
ZEND_GET_MODULE(ifeng)
#endif
