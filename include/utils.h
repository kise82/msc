#ifndef MSC_UTILS_H
#define MSC_UTILS_H

#define OFFSET_OF(st, fld) \
((size_t) &(((st *) 0)->fld))

char *utils_strdup(const char *restrict original);

#endif
