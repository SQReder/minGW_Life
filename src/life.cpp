#include "life.h"
#include "matrix_templ.cpp"
#include <stdlib.h>
#include <time.h>

tlife::tlife(int w, int h) {
	this->w = w;
	this->h = h;
	grid = allocate_matrix <lType> (w, h);
	buff = allocate_matrix <lType> (w, h);

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			grid[y][x] = 0;
			buff[y][x] = 0;
		}
	}
}

void tlife::seed(int count) {
	srand((int)time(NULL));

	// while (count--) {
		// int x = rand() % w;
		// int y = rand() % h;
		// grid[y][x] = rand() % 2;
	// }

	for (int y = 0; y < h; ++y) {
		// grid[y][w-1] = true;
		// grid[y][w-2] = true;
		// grid[y][w-1] = true;
		// grid[y][0] = true;
	}

	// grid[11][0] = true;
	// grid[10][0] = true;
	// grid[10][1] = true;
	// grid[10][2] = true;
	// grid[10][3] = true;
	// grid[10][4] = true;
	// grid[11][4] = true;

	// grid[11][20] = true;
	// grid[10][20] = true;
	// grid[10][21] = true;
	// grid[10][22] = true;
	// grid[10][23] = true;
	// grid[10][24] = true;
	// grid[11][24] = true;

	// grid[30][20] = true;
	// grid[30][21] = true;
	// grid[30][22] = true;
	// grid[31][20] = true;
	// grid[32][21] = true;
	
	//planergun
	grid[60][50] = true;
	grid[61][50] = true;
	grid[61][49] = true;
	grid[60][49] = true;
	
	grid[62][58] = true;
	grid[63][58] = true;
	grid[58][58] = true;
	grid[57][58] = true;

	grid[58][59] = true;
	grid[59][59] = true;
	grid[60][59] = true;
	grid[61][59] = true;
	grid[62][59] = true;
	
	grid[59][60] = true;
	grid[60][60] = true;
	grid[61][60] = true;
	
	grid[60][61] = true;
	
	//2
	grid[60][75] = true;
	grid[61][75] = true;
	grid[56][75] = true;
	grid[55][75] = true;

	grid[59][76] = true;
	grid[58][76] = true;
	grid[57][76] = true;

	grid[56][77] = true;
	grid[60][77] = true;

	grid[57][78] = true;
	grid[59][78] = true;

	grid[58][79] = true;

	grid[58][84] = true;
	grid[59][84] = true;
	grid[58][83] = true;
	grid[59][83] = true;

	// end planergun

	
	int cx = w / 2;
	int cy = h / 2;

	grid[cx-1][cy-1] = true;
	grid[cx][cy-1] = true;
	grid[cx+1][cy-1] = true;
	grid[cx-1][cy] = true;
	grid[cx+1][cy] = true;
	grid[cx-1][cy+1] = true;
	grid[cx][cy+1] = true;
	grid[cx+1][cy+1] = true;

	// grid[30][0] = true;
	// grid[31][0] = true;
	// grid[32][0] = true;
}

int tlife::neighbour(int x, int y) {
	int ret = 0;

#define range 1

	for (int dx = -range; dx <= range; ++dx) {
		for (int dy = -range; dy <= range; ++dy) {
			if (dx != 0 || dy != 0) {
				int xx, yy;

				if (x + dx < 0) {
					xx = w - 1;
				} else if (x + dx >= w) {
					xx = dx - 1;
				} else {
					xx = x + dx;
				}

				if (y + dy < 0) {
					yy = h - 1;
				} else if (y + dy >= h) {
					yy = dy - 1;
				} else {
					yy = y + dy;
				}

				if (grid[yy][xx]) {
					++ret;
				}
			}
		}
	}
	return ret;
}

void tlife::step() {
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int n = neighbour(x, y);

			bool g = (grid[y][x]);
			bool less = (n < 2);
			bool more = (n > 3);
			bool eq = (n == 3);

			buff[y][x] = (g || eq) && !(less || more);
		}
	}

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			grid[y][x] = buff[y][x];
		}
	}
}

const lType **tlife::get_grid() const { return (const lType * *)grid; }

tlife::~tlife() {
	delete_matrix <lType> (grid, h);
	delete_matrix <lType> (buff, h);
}
