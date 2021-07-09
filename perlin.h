#ifndef __PERLIN_H__
#define __PERLIN_H__

#include <cmath>

double lerp(double a0, double a1, double w) {
	return (1.0 - w) * a0 + w * a1;
}

double dotGridGradient(int ix, int iy, double x, double y)
{
	// extern float gradient[IYMAX][IXMAX][2]; // precomputed gradient vectors for each grid node
	// compute the distance vector
	double dx = x - ix;
	double dy = y - iy;
	// compute dot-product

	return (dx * gradient[iy][ix][0] + dy * gradient[iy][ix][1]);

}

double perlin(double x, double y) {
	// determine grid cell coordinates
	int x0 = std::floor(x);
	int x1 = x0 + 1;
	int y0 = std::floor(y);
	int y1 = y0 + 1;

	// determine interpolation weights
	// could also use higher order polynomial/s-curve here
	auto sx = x - x0;
	auto sy = y - y0;

	// interpolate between grid point gradients
	auto n0 = dotGridGradient(x0, y0, x, y);
	auto n1 = dotGridGradient(x1, y0, x, y);
	auto ix0 = lerp(n0, n1, sx);
	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	auto ix1 = lerp(n0, n1, sx);
	auto value = lerp(ix0, ix1, sy);

	return value;
}

#endif //__PERLIN_H__