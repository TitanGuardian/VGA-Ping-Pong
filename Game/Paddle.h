#pragma once

class Paddle
{
private:
	/*position of center*/
	int x;
	int y;
	int size = 49; // must be multiple of 7
	int width = 3; 
	int step;
public:
	Paddle(int _x, int _y);
	Paddle();

	void reset(int _x, int _y);

	void move(int new_step);
	void do_move();

	int getX() const;
	int getY() const;
	int getSize() const;
	int getWidth() const;
};

