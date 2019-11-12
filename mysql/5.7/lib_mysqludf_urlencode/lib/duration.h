
#ifdef _MSVC
typedef __int64 sll;
#define SLL(x) x##I64
#define SLL_FMT "%i64"
#else
#if SIZOF_LONG == 8
typedef long sll;
#define SLL(x) x##L
#define SLL_FMT "%ld"
#else
typedef long long sll;
#define SLL(x) x##LL
#define SLL_FMT "%lld"
#endif
#endif

typedef enum {
	DURATION_PRECISION_Y = 4,
	DURATION_PRECISION_M = 6,
	DURATION_PRECISION_D = 8,
	DURATION_PRECISION_H = 10,
	DURATION_PRECISION_I = 12,
	DURATION_PRECISION_S = 14
} duration_precision_t;

#ifdef _DEBUG
#define local
#define DBG2(m,_1,_2) fprintf(stderr,m,_1,_2)
#define DBG3(m,_1,_2,_3) fprintf(stderr,m,_1,_2,_3)
#else
#define local static inline
#define DBG2
#define DBG3
#endif

#define adj_gen(inc, val, nxt) \
	DBG3("> adj_gen(%d,%d,%d)\n",inc,val,nxt); \
	if (val < 0 || val > inc) { \
		nxt += val / inc ? val / inc : val > 0 ? 1 : -1; \
		val = inc - (val > 0 ? 1 : -1 * (val % inc)); \
	} \
	DBG3("< adj_gen(%d,%d,%d)\n",inc,val,nxt);

#define adj_mon(m, y) \
	DBG2("> adj_mon(%d,%d)\n",m,y); \
	while (m >= 12) { \
		m -= 12; \
		y += 1; \
	} \
	while (m < 0) { \
		m += 12; \
		y -= 1; \
	} \
	DBG2("< adj_mon(%d,%d)\n",m,y);

local int calc_dim(int m, int y)
{
	adj_mon(m, y);
	
	switch (m) {
		case 1:
			return ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0)) ? 29 : 28;
		case 3:
		case 5:
		case 8:
		case 10:
			return 30;
		default:
			return 31;
	}
}

local sll calc_sec(struct tm *t1, struct tm *t2)
{
	return t1->tm_hour * 60 * 60 + t1->tm_min * 60 + t1->tm_sec + 24 * 60 * 60 - t2->tm_hour * 60 * 60 - t2->tm_min * 60 - t2->tm_sec;
}

local sll calc_day(struct tm *t1, struct tm *t2)
{
	int y, m, d;
	
	if (t1->tm_year == t2->tm_year && t1->tm_mon == t2->tm_mon) {
		d = t1->tm_mday - t2->tm_mday;
	} else {
		d = t1->tm_mday + calc_dim(t2->tm_mon, t2->tm_year + 1900) - t2->tm_mday;
		for (y = t2->tm_year; y <= t1->tm_year; ++y) {
			DBG2("while (%d < %d)\n", y + 1900, t1->tm_year + 1900);
			for (m = (y == t2->tm_year) ? t2->tm_mon + 1 : 0; (y == t2->tm_year || y != t1->tm_year) ? m < 12 : m < t1->tm_mon; ++m) {
				d += calc_dim(m, y + 1900);
				DBG2("d += calc_dim(%d, %d)\n", m, y + 1900);
			}
		}
	}
	
	if (d && calc_sec(t1, t2) < 24 * 60 * 60) {
		d -= 1;
	}
	
	return d;
}

local sll calc_mon(struct tm *t1, struct tm *t2)
{
	if (t1->tm_year == t2->tm_year) {
		return t1->tm_mon - t2->tm_mon;
	} else {
		return (t1->tm_year - t2->tm_year - 1) * 12 + t1->tm_mon + 12 - t2->tm_mon;
	}
}

local struct tm *sll_2tm(struct tm *t, sll date)
{
#define _calc(_tvar, _date, _f) \
	_tvar = _date % _f; \
	_date = (_date - _tvar) / _f;
	_calc(t->tm_sec, date, 100);
	_calc(t->tm_min, date, 100);
	_calc(t->tm_hour, date, 100);
	_calc(t->tm_mday, date, 100);
	_calc(t->tm_mon, date, 100);
	_calc(t->tm_year, date, 10000);
#undef _calc
	t->tm_mon  -= 1;
	t->tm_year -= 1900;
	
	adj_gen(60, t->tm_sec, t->tm_min);
	adj_gen(60, t->tm_min, t->tm_hour);
	adj_gen(24, t->tm_hour, t->tm_mday);
	
	while (t->tm_mday > calc_dim(t->tm_mon, t->tm_year)) {
		t->tm_mday -= calc_dim(t->tm_mon, t->tm_year);
		t->tm_mon  += 1;
		adj_mon(t->tm_mon, t->tm_year);
	}
	while (t->tm_mday < 1) {
		t->tm_mon  -= 1;
		adj_mon(t->tm_mon, t->tm_year);
		t->tm_mday += calc_dim(t->tm_mon, t->tm_year);
	}
	adj_mon(t->tm_mon, t->tm_year);
	
	return t;
}

local sll sll_pad(sll arg)
{
	if (arg <= SLL(9999)) {
		arg *= SLL(10000000000);
	} else if (arg <= SLL(999999)) {
		arg *= SLL(100000000);
	} else if (arg <= SLL(99999999)) {
		arg *= SLL(1000000);
	} else if (arg <= SLL(9999999999)) {
		arg *= SLL(10000);
	} else if (arg <= SLL(999999999999)) {
		arg *= SLL(100);
	}
	return arg;
}

sll duration(struct tm *t1, struct tm *t2, duration_precision_t w);
sll duration_y(struct tm *t1, struct tm *t2);
sll duration_m(struct tm *t1, struct tm *t2);
sll duration_d(struct tm *t1, struct tm *t2);
sll duration_h(struct tm *t1, struct tm *t2);
sll duration_i(struct tm *t1, struct tm *t2);
sll duration_s(struct tm *t1, struct tm *t2);
