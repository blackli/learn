#ifndef WALU_H
#define WALU_H

//加载config.h，如果配置了的话
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//加载php头文件
#include "php.h"
#define phpext_ifeng_ptr &ifeng_module_entry
extern zend_module_entry ifeng_module_entry;
extern zend_module_entry *myclass_ce;

#endif
