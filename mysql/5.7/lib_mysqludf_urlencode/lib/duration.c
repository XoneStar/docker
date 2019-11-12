#ifdef HAVE_CONFIG_H
#include "mysqludf_config.h"
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
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_TIME_H
#include <time.h>
#endif
#ifdef _DEBUG
#include <stdio.h>
#endif

#include "duration.h"

sll duration(struct tm *t1, struct tm *t2, duration_precision_t w)
{
	switch (w) {
		case DURATION_PRECISION_Y:
			return calc_mon(t1, t2) / SLL(12);
		case DURATION_PRECISION_M:
			return calc_mon(t1, t2);
		case DURATION_PRECISION_D:
			return calc_day(t1, t2);
		case DURATION_PRECISION_H:
			return calc_day(t1, t2) * SLL(24) + calc_sec(t1, t2) / SLL(3600);
		case DURATION_PRECISION_I:
			return calc_day(t1, t2) * SLL(24) * SLL(60) + calc_sec(t1, t2) / SLL(60);
		case DURATION_PRECISION_S:
			return calc_day(t1, t2) * SLL(24) * SLL(60) * SLL(60) + calc_sec(t1, t2);
	}
}

sll duration_y(struct tm *t1, struct tm *t2)
{
	return calc_mon(t1, t2) / SLL(12);
}

sll duration_m(struct tm *t1, struct tm *t2)
{
	return calc_mon(t1, t2);
}

sll duration_d(struct tm *t1, struct tm *t2)
{
	return calc_day(t1, t2);
}

sll duration_h(struct tm *t1, struct tm *t2)
{
	return calc_day(t1, t2) * SLL(24) + calc_sec(t1, t2) / SLL(3600);
}

sll duration_i(struct tm *t1, struct tm *t2)
{
	return calc_day(t1, t2) * SLL(24) * SLL(60) + calc_sec(t1, t2) / SLL(60);
}

sll duration_s(struct tm *t1, struct tm *t2)
{
	return calc_day(t1, t2) * SLL(24) * SLL(60) * SLL(60) + calc_sec(t1, t2);
}

#ifdef _DEBUG
int main(int argc, char *argv[])
{
	struct tm t1, t2;
	duration_precision_t p = DURATION_PRECISION_S;
	
	switch (argc) {
		case 4:
			p = atoi(argv[3]);
		case 3:
			sll_2tm(&t1, sll_pad(atoll(argv[1])));
			sll_2tm(&t2, sll_pad(atoll(argv[2])));
			printf(SLL_FMT "\n", duration(&t1, &t2, p));
			return 0;
		default:
			return 1;
	}
}
#endif
