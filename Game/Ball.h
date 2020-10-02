#pragma once

class Ball
{
private:
	int x100, y100;
	unsigned int direction; // range(0,3600,225) degrees*10
public:
	Ball(int posX, int posY, unsigned int initDirection);
	void changeDirection(unsigned int newDirection);
	inline int getX();
	inline int getY();
	inline int getDirection();
	void move();
};

