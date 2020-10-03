#include "Game.h"
#include "common.h"
#include <ctime>
#include <cstdlib>

Game::Game() {
	std::srand(time(0));
	reset();
}

void Game::update() {
	int r1,r2,r3;
	paddleLeft.do_move();
	paddleRight.do_move();
	r1 = ball.leftUpdate(paddleLeft);
	r2 = ball.rightUpdate(paddleRight);
	ball.upDownUpdate();
	
	if (r1) {
		scoreP1 += 1;
		reset();
		return;
	}
	if (r2) {
		scoreP2 += 1;
		reset();
		return;
	}
	ball.move();
}

void Game::reset() {
	int direction;
	int i;
	i = rand() % 14;

	if (i < 7) {
		direction = 225 * (i + 1);
	}
	else {
		direction = 225 * (i + 2);
	}
	direction = 900;
	ball.reset(RESOLUTION_X / 2, RESOLUTION_Y / 2, direction);
	paddleLeft.reset(30, RESOLUTION_Y / 2);
	paddleRight.reset(RESOLUTION_X-31, RESOLUTION_Y / 2);
}


void Game::onInputP1(int direction) {
	switch (direction) {
	case -1:
		paddleLeft.move(-moveSpeed);
		break;
	case 0:
		paddleLeft.move(0);
		break;
	case +1:
		paddleLeft.move(moveSpeed);
		break;
	}
}

void Game::onInputP2(int direction) {
	switch (direction) {
	case -1:
		paddleRight.move(-moveSpeed);
		break;
	case 0:
		paddleRight.move(0);
		break;
	case +1:
		paddleRight.move(moveSpeed);
		break;
	}
}


Ball Game::getBall() const { return ball; }
Paddle Game::getPaddleP1() const { return paddleLeft; }
Paddle Game::getPaddleP2() const { return paddleRight; }
int Game::getScoreP1() const { return scoreP1; }
int Game::getScoreP2() const { return scoreP2; }
