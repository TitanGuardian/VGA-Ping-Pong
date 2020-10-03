#include "Paddle.h"
#include "common.h"


Paddle::Paddle(int _x, int _y) : x(_x), y(_y), step(0) {}
Paddle::Paddle() {}

void Paddle::move(int new_step) {
	step = new_step;
}

void Paddle::do_move() {
	y += step;

	if (y + size >= RESOLUTION_Y) {
		y = RESOLUTION_Y - 1 - size;
	}
	if (y - size < 0) {
		y = size;
	}
}

void Paddle::reset(int _x, int _y) {
	x = _x;
	y = _y;
	step = 0;
}

int Paddle::getX() const { return x; }
int Paddle::getY() const { return y; }
int Paddle::getSize() const { return size; }
int Paddle::getWidth() const { return width; }
