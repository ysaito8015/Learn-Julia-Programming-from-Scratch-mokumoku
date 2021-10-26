// libpoint.c
#include <math.h>

typedef struct {
	double x;
	double y;
} point2d_t;

double distance(point2d_t p) {
	return sqrt(p.x * p.x + p.y * p.y);
}

void move(point2d_t *p, double dx, double dy) {
	p->x += dx;
	p->y += dy;
}
