#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "common.h"

class Game
{
private:
	Ball ball;
	Paddle paddleLeft;
	Paddle paddleRight;
	int scoreP1 = 0;
	int scoreP2 = 0;
	int moveSpeed = 10;
public:
	Game();
	void reset();
	void update();
	void onInputP1(int direction = 0);
	void onInputP2(int direction = 0);
	inline Ball getBall() const;
	inline Paddle getPaddleP1() const;
	inline Paddle getPaddleP2() const;
	inline int getScoreP1() const;
	inline int getScoreP2() const;
};

