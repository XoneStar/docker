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

#include "duration.h"

#ifndef local
#define local static inline
#endif

local longlong now(struct tm *act_time)
{
	if (!act_time) {
		time_t now = time(NULL);
#if defined(HAVE_LOCALTIME_R) && defined(_REENTRANT)
		struct tm tmp_time;
	
		localtime_r(&now, &tmp_time);
		act_time = &tmp_time;
#else
		act_time = localtime(&now);
#endif
	}
	return 
			((longlong) act_time->tm_year + SLL(1900)) * SLL(10000000000) +
			((longlong) act_time->tm_mon  + SLL(   1)) * SLL(100000000) +
			((longlong) act_time->tm_mday)             * SLL(1000000) +
			((longlong) act_time->tm_hour)             * SLL(10000) +
			((longlong) act_time->tm_min)              * SLL(100) +
			((longlong) act_time->tm_sec);
}

my_bool humanage_init(UDF_INIT *init, UDF_ARGS *args, char *message)
{
	switch (args->arg_count) {
		case 3:
			args->arg_type[2] = INT_RESULT;
		case 2:
			args->arg_type[1] = INT_RESULT;
		case 1:
			args->arg_type[0] = INT_RESULT;
			break;
		default:
			strncpy(message, "HUMANAGE() accepts 1, 2 or 3 parameters", MYSQL_ERRMSG_SIZE);
			return 1;
	}
	
	init->maybe_null = 1;
	
	return 0;
}

void humanage_deinit(UDF_INIT *init)
{
}

longlong humanage(UDF_INIT *init, UDF_ARGS *args, char *is_null, char *error)
{
	int w = 4;
	longlong arg1, arg2;
	struct tm t1, t2;
	
	switch (args->arg_count) {
		case 3:
			if (args->args[2]) {
				w = (int) *(longlong *) args->args[2];
			}
		case 2:
			if (args->args[1]) {
				break;
			}
		case 1:
			if (args->args[0]) {
				break;
			}
			*is_null = (char) 1;
			return 0;
	}
	
	if (args->args[0]) {
		arg1 = sll_pad(*((longlong *) args->args[0]));
		if (args->arg_count >= 2 && args->args[1]) {
			arg2 = sll_pad(*((longlong *) args->args[1]));
		} else {
			arg2 = now(NULL);
		}
	} else {
		arg1 = now(NULL);
		arg2 = sll_pad(*((longlong *) args->args[1]));
	}
	
	if (w < 4) {
		w = 4;
	} else if (w > 14) {
		w = 14;
	} else {
		w += w % 2;
	}
	
	/* t1 > t2 */
	if (arg1 > arg2 && arg2 > SLL(0)) {
		sll_2tm(&t1, arg1);
		sll_2tm(&t2, arg2);
	} else {
		sll_2tm(&t1, arg2);
		sll_2tm(&t2, arg1);
	}
	
	return duration(&t1, &t2, w);
}
