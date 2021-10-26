// libsum.c
#include <stddef.h>

double sum(const double xs[], size_t n) {
	double s = 0;
	for (size_t i = 0; i < n; i++)
		s += xs[i];
	return s;
}
