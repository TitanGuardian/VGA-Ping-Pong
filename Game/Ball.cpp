#include "Ball.h"
#include "common.h"
//#include <iostream>

Ball::Ball(int posX, int posY, int initDirection) : x100(posX * 100), y100(posY * 100), direction(initDirection) {
}

Ball::Ball() {
}

void Ball::changeDirection(int newDirection) {
	direction = newDirection;
	if (newDirection == 0 || newDirection == 1800) throw;
}

int Ball::getX() const {
	return x100 / 100; 
}

int Ball::getY() const {
	return y100 / 100; 
}
int Ball::getDirection() const {
	return direction; 
}

int Ball::getSize() const {
	return size;
}

void Ball::move() {
	switch (direction) {
	case  225: y100 -= 75 * moveSpeed; x100 +=  25 * moveSpeed; break;
	case  450: y100 -= 50 * moveSpeed; x100 += 50  * moveSpeed; break;
	case  675: y100 -= 25 * moveSpeed; x100 += 75  * moveSpeed; break;
	case  900: y100 += 0  * moveSpeed; x100 += 100 * moveSpeed; break;
	case 1125: y100 += 25 * moveSpeed; x100 += 75  * moveSpeed; break;
	case 1350: y100 += 50 * moveSpeed; x100 += 50  * moveSpeed; break;
	case 1575: y100 += 75 * moveSpeed; x100 += 25  * moveSpeed; break;
	case 2025: y100 += 75 * moveSpeed; x100 -= 25  * moveSpeed; break;
	case 2250: y100 += 50 * moveSpeed; x100 -= 50  * moveSpeed; break;
	case 2475: y100 += 25 * moveSpeed; x100 -= 75  * moveSpeed; break;
	case 2700: y100 += 0  * moveSpeed; x100 -= 100 * moveSpeed; break;
	case 2925: y100 -= 25 * moveSpeed; x100 -= 75  * moveSpeed; break;
	case 3150: y100 -= 50 * moveSpeed; x100 -= 50  * moveSpeed; break;
	case 3375: y100 -= 75 * moveSpeed; x100 -= 25  * moveSpeed; break;
	default: throw;
	}
}

static int reverseX(int direction) {
	switch (direction) {
	case  225: direction = 3375; break;
	case  450: direction = 3150; break;
	case  675: direction = 2925; break;
	case  900: direction = 2700; break;
	case 1125: direction = 2475; break;
	case 1350: direction = 2250; break;
	case 1575: direction = 2025; break;
	case 2025: direction = 1575; break;
	case 2250: direction = 1350; break;
	case 2475: direction = 1125; break;
	case 2700: direction = 900;  break;
	case 2925: direction = 675;  break;
	case 3150: direction = 450;  break;
	case 3375: direction = 225;  break;
	}
	return direction;
}

static int reverseY(int direction) {
	switch (direction) {
	case  225: direction = 1575; break;
	case  450: direction = 1350; break;
	case  675: direction = 1125; break;
	case  900: direction = 900;  break;
	case 1125: direction = 675;  break;
	case 1350: direction = 450;  break;
	case 1575: direction = 225;  break;
	case 2025: direction = 3375; break;
	case 2250: direction = 3150; break;
	case 2475: direction = 2925; break;
	case 2700: direction = 2700; break;
	case 2925: direction = 2475; break;
	case 3150: direction = 2250; break;
	case 3375: direction = 2025; break;
	}
	return direction;
}

void Ball::reset(int posX, int posY, unsigned int initDirection) {
	x100 = posX*100; 
	y100 = posY*100;
	direction = initDirection;
}

int Ball::leftUpdate(Paddle& pad) {
	int x, y;
	x = x100 / 100;
	y = y100 / 100;
	if ((x - size <= (pad.getX() + pad.getWidth())) && (direction > 1800 && direction < 3600)) {
		if ((y + size >= (pad.getY() - pad.getSize())) && (y - size <= (pad.getY() + pad.getSize()))) {
			
			if (y < (pad.getY() - pad.getSize())) {
				y = pad.getY() - pad.getSize();
			}
			else if (y > (pad.getY() + pad.getSize())) {
				y = (pad.getY() + pad.getSize());
			}

			int position = y - (pad.getY() - pad.getSize());
			int cl_size = 2 * pad.getSize() / 7;
			int cluster_number=0;

			if (position < cl_size) {
				cluster_number = -3;
			}
			else if (position < 2*cl_size) {
				cluster_number = -2;
			}
			else if (position < 3 * cl_size) {
				cluster_number = -1;
			}
			else if (position < 4 * cl_size+1) {
				cluster_number = 0;
			}
			else if (position < 5 * cl_size + 1) {
				cluster_number = 1;
			}
			else if (position < 6 * cl_size + 1) {
				cluster_number = 2;
			}
			else if (position < 7 * cl_size + 1) {
				cluster_number = 3;
			}

			//std::cout << "Hit P1 " << direction<< " " << reverseX(direction) << " " << cluster_number;
			//std::cout << " " << direction;
			direction = reverseX(direction) + cluster_number * 225;
			if (direction >= 1800) direction = 1575;
			else if (direction <= 0) direction = 225;
			//std::cout << " " << direction << std::endl;
			return 2;
		}
		else {
			return 1;
		}
	}
	return 0;
}

int Ball::rightUpdate(Paddle& pad) {
	int x, y;
	x = x100 / 100;
	y = y100 / 100;
	if ((x + size >= (pad.getX() - pad.getWidth()))&&(direction>0&&direction<1800)) {
		if ((y + size >= (pad.getY() - pad.getSize())) && (y - size <= (pad.getY() + pad.getSize()))) {

			if (y < (pad.getY() - pad.getSize())) {
				y = pad.getY() - pad.getSize();
			}
			else if (y > (pad.getY() + pad.getSize())) {
				y = (pad.getY() + pad.getSize());
			}

			int position = y - (pad.getY() - pad.getSize());
			int cl_size = 2 * pad.getSize() / 7;
			int cluster_number = 0;

			if (position < cl_size) {
				cluster_number = -3;
			}
			else if (position < 2 * cl_size) {
				cluster_number = -2;
			}
			else if (position < 3 * cl_size) {
				cluster_number = -1;
			}
			else if (position < 4 * cl_size + 1) {
				cluster_number = 0;
			}
			else if (position < 5 * cl_size + 1) {
				cluster_number = 1;
			}
			else if (position < 6 * cl_size + 1) {
				cluster_number = 2;
			}
			else if (position < 7 * cl_size + 1) {
				cluster_number = 3;
			}

			//std::cout << "Hit P2 " << direction << " " << reverseX(direction) << " " << cluster_number;
			direction = reverseX(direction) - cluster_number * 225;
			//std::cout << " " << direction;
			if (direction >= 3600) direction = 3375;
			else if (direction <= 1800) direction = 2025;
			//std::cout << " " << direction << std::endl;
			return 2;
		}
		else {
			return 1;
		}
	}
	return 0;
}

void Ball::upDownUpdate() {
	int x, y;
	x = x100 / 100;
	y = y100 / 100;
	if ((y - size <= 0)||(y+size >= RESOLUTION_Y-1)) {
		direction = reverseY(direction);
	}
}