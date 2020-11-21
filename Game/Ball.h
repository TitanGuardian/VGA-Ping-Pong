#pragma once

#include "Paddle.h"

class Ball
{
private:
	int x100, y100;
	int size = 5; 
	int direction; // range(0,3600,225) degrees*10
	const int moveSpeed = 7;
public:
	Ball();
	Ball(int posX, int posY, int initDirection);
	void changeDirection(int newDirection);
	int getX() const;
	int getY() const;
	int getDirection() const;
	int getSize() const;
	void move();
	void reset(int posX, int posY, unsigned int initDirection);
	int leftUpdate(Paddle &pad);
	int rightUpdate(Paddle &pad);
	void upDownUpdate();
};

