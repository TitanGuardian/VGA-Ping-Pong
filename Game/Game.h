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
	int moveSpeed = 5;
	int status = 0;
	int turns = 0;
	bool scoreChange = false;
public:
	Game();
	void reset();
	void update();
	void onInputP1(int direction = 0);
	void onInputP2(int direction = 0);
	Ball getBall() const;
	Paddle getPaddleP1() const;
	Paddle getPaddleP2() const;
	int getScoreP1() const;
	int getScoreP2() const;
	int getStatus() const;
	int getTurns() const;
	int getScoreChange();
};

