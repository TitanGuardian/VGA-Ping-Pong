#pragma once

class Paddle
{
private:
	/*position of center*/
	int x;
	int y;
	int size = 100; // must be multiple of 7
	int width = 10; 
	int step;
public:
	Paddle(int _x, int _y);
	Paddle();

	void reset(int _x, int _y);

	void move(int new_step);
	void do_move();

	inline int getX() const;
	inline int getY() const;
	inline int getSize() const;
	inline int getWidth() const;
};

