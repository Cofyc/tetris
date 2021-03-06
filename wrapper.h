#ifndef WRAPPER_H
#define WRAPPER_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "usage.h"

extern void *xmalloc(size_t size);
extern void *xrealloc(void *ptr, size_t size);
extern void *xcalloc(size_t nmemb, size_t size);
extern char *xstrndup(const char *str, size_t len);

#endif
