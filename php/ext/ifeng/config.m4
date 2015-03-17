PHP_ARG_ENABLE(ifeng,
    [Whether to enable the "ifeng" extension],
    [  enable-ifeng        Enable "ifeng" extension support])

if test $PHP_IFENG != "no"; then
    PHP_SUBST(IFENG_SHARED_LIBADD)
    PHP_NEW_EXTENSION(ifeng, ifeng.c, $ext_shared)
fi
