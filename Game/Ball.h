#pragma once

#include "Paddle.h"

class Ball
{
private:
	int x100, y100;
	int size = 10; 
	unsigned int direction; // range(0,3600,225) degrees*10
public:
	Ball();
	Ball(int posX, int posY, unsigned int initDirection);
	void changeDirection(unsigned int newDirection);
	inline int getX() const;
	inline int getY() const;
	inline int getDirection() const;
	inline int getSize() const;
	void move();
	void reset(int posX, int posY, unsigned int initDirection);
	int leftUpdate(Paddle &pad);
	int rightUpdate(Paddle &pad);
	void upDownUpdate();
};

