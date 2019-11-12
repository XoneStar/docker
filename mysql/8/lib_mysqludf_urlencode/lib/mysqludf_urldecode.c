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

#define x2c(c1, c2) _x2c(tolower((unsigned char) (c1)), tolower((unsigned char ) (c2)))
static inline char _x2c(unsigned char c1, unsigned char c2)
{
	return ((c1 >= '0' && c1 <= '9' ? c1 - '0' : c1 - 'a' + 10) * 16) + (c2 >= '0' && c2 <= '9' ? c2 - '0' : c2 - 'a' + 10);
}

my_bool urldecode_init(UDF_INIT *init, UDF_ARGS *args, char *message)
{
	if (args->arg_count != 1 || args->arg_type[0] != STRING_RESULT) {
		strncpy(message, "URLDECODE() accepts exactly 1 string parameter", MYSQL_ERRMSG_SIZE);
		return 1;
	}
	
	init->maybe_null = 1;
	init->ptr = NULL;
	return 0;
}

void urldecode_deinit(UDF_INIT *init)
{
	if (init->ptr) {
		free(init->ptr);
	}
}

char *urldecode(UDF_INIT *init, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error)
{
	unsigned char c;
	char *input;
	
	if (!args->args[0]) {
		*is_null = (char) 1;
		return NULL;
	}
	
	if (args->lengths[0] > 255) {
		if ((init->ptr = malloc(args->lengths[0] + 1))) {
			result = init->ptr;
		} else {
			*error = (char) 1;
			return NULL;
		}
	}
	*length = 0;
	for (input = args->args[0], c = *input++; input <= args->args[0]+args->lengths[0]; c = *input++) {
		if (c == '+') {
			result[(*length)++] = ' ';
		} else if (c == '%' && input - args->args[0] + args->lengths[0] >= 2 && isxdigit(input[0]) && isxdigit(input[1])) {
			result[(*length)++] = x2c(input[0], input[1]);
			input += 2;
		} else {
			result[(*length)++] = c;
		}
	}
	
	return result;
}
