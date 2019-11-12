#ifdef HAVE_CONFIG_H
#include "mysqludf_config.h"
#undef PACKAGE
#undef PACKAGE_NAME
#undef PACKAGE_TARNAME
#undef PACKAGE_STRING
#undef PACKAGE_VERSION
#undef PACKAGE_BUGREPORT
#undef VERSION
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

static const unsigned char hexits[] = "0123456789ABCDEF";

my_bool urlencode_init(UDF_INIT *init, UDF_ARGS *args, char *message)
{
	if (args->arg_count != 1 || args->arg_type[0] != STRING_RESULT) {
		strncpy(message, "URLENCODE() accepts exactly 1 string parameter", MYSQL_ERRMSG_SIZE);
		return 1;
	}
	
	init->maybe_null = 1;
	init->max_length *= 3;
	init->ptr = NULL;
	return 0;
}

void urlencode_deinit(UDF_INIT *init)
{
	if (init->ptr) {
		free(init->ptr);
	}
}

char *urlencode(UDF_INIT *init, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
	unsigned char c;
	char *input;
	
	if (!args->args[0]) {
		*is_null = (char) 1;
		return NULL;
	}
	
	*length = args->lengths[0] * 3;
	if (*length > 255) {
		if ((init->ptr = malloc(*length + 1))) {
			result = init->ptr;
		} else {
			*error = (char) 1;
			return NULL;
		}
	}
	*length = 0;
	for (input = args->args[0], c = *input++; input <= args->args[0]+args->lengths[0]; c = *input++) {
		if (c == '.' || c == '-' || c == '_' || isalnum(c)) {
			result[(*length)++] = c;
		} else {
			result[(*length)++] = '%';
			result[(*length)++] = hexits[c >> 4];
			result[(*length)++] = hexits[c & 15];
		}
	}
	
	return result;
}
