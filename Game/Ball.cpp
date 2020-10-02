#include "Ball.h"

Ball::Ball(int posX, int posY, unsigned int initDirection) : x100(posX * 100), y100(posY * 100), direction(initDirection) {}

void Ball::changeDirection(unsigned int newDirection) {
	direction = newDirection;
	if (newDirection == 0 || newDirection == 1800) throw;
}

inline int Ball::getX() { 
	return x100 / 100; 
}

inline int Ball::getY() { 
	return y100 / 100; 
}
inline int Ball::getDirection() { 
	return direction; 
}

void Ball::move() {
	switch (direction) {
	case  225: y100 += 75; x100 +=  25; break;
	case  450: y100 += 50; x100 +=  50; break;
	case  675: y100 += 25; x100 +=  75; break;
	case  900: y100 +=  0; x100 += 100; break;
	case 1125: y100 -= 25; x100 +=  75; break;
	case 1350: y100 -= 50; x100 +=  50; break;
	case 1575: y100 -= 75; x100 +=  25; break;
	case 2025: y100 -= 75; x100 -=  25; break;
	case 2250: y100 -= 50; x100 -=  50; break;
	case 2475: y100 -= 25; x100 -=  75; break;
	case 2700: y100 +=  0; x100 -= 100; break;
	case 2925: y100 += 25; x100 -=  75; break;
	case 3150: y100 += 50; x100 -=  50; break;
	case 3375: y100 += 75; x100 -=  25; break;
	default: throw;
	}
}
