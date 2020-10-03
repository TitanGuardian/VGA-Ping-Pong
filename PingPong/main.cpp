#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "simple2d.h"

/*delete comment to run specific test*/
//extern "C" int test_triangle();
//extern "C" int test_triangleIOS();
//extern "C" int test_testcard();
//extern "C" int test_audio();
//extern "C" int test_auto();
//extern "C" int test_controller();

#include <thread>

Game* renderingGame;

static void render_main() {

	Ball bl = renderingGame->getBall();
	
	S2D_DrawQuad(
		bl.getX() + bl.getSize(), bl.getY() - bl.getSize(), 1, 0, 0, 1,
		bl.getX() + bl.getSize(), bl.getY() + bl.getSize(), 1, 0, 0, 1,
		bl.getX() - bl.getSize(), bl.getY() + bl.getSize(), 1, 0, 0, 1,
		bl.getX() - bl.getSize(), bl.getY() - bl.getSize(), 1, 0, 0, 1
	);

	Paddle pd1 = renderingGame->getPaddleP1();


	S2D_DrawQuad(
		pd1.getX() + pd1.getWidth(), pd1.getY() - pd1.getSize(), 1, 0, 0, 1,
		pd1.getX() + pd1.getWidth(), pd1.getY() + pd1.getSize(), 1, 0, 0, 1,
		pd1.getX() - pd1.getWidth(), pd1.getY() + pd1.getSize(), 1, 0, 0, 1,
		pd1.getX() - pd1.getWidth(), pd1.getY() - pd1.getSize(), 1, 0, 0, 1
	);


	Paddle pd2 = renderingGame->getPaddleP2();

	S2D_DrawQuad(
		pd2.getX() + pd2.getWidth(), pd2.getY() - pd2.getSize(), 1, 0, 0, 1,
		pd2.getX() + pd2.getWidth(), pd2.getY() + pd2.getSize(), 1, 0, 0, 1,
		pd2.getX() - pd2.getWidth(), pd2.getY() + pd2.getSize(), 1, 0, 0, 1,
		pd2.getX() - pd2.getWidth(), pd2.getY() - pd2.getSize(), 1, 0, 0, 1
	);

}

static void on_key(S2D_Event e) {
	switch (e.type) {
	case S2D_KEY_DOWN:
		if (strcmp(e.key, "W") == 0) renderingGame->onInputP1(-1);
		if (strcmp(e.key, "S") == 0) renderingGame->onInputP1(1);
		if (strcmp(e.key, "Up") == 0) renderingGame->onInputP2(-1);
		if (strcmp(e.key, "Down") == 0) renderingGame->onInputP2(1);
		break;
	case S2D_KEY_HELD:
		if (strcmp(e.key, "W") == 0) renderingGame->onInputP1(-1);
		if (strcmp(e.key, "S") == 0) renderingGame->onInputP1(1);
		if (strcmp(e.key, "Up") == 0) renderingGame->onInputP2(-1);
		if (strcmp(e.key, "Down") == 0) renderingGame->onInputP2(1);
		break;

	case S2D_KEY_UP:
		if (strcmp(e.key, "W") == 0) renderingGame->onInputP1(0);
		if (strcmp(e.key, "S") == 0) renderingGame->onInputP1(0);
		if (strcmp(e.key, "Up") == 0) renderingGame->onInputP2(0);
		if (strcmp(e.key, "Down") == 0) renderingGame->onInputP2(0);
		break;
	}
}

#define LOG_SCORE(g)  std::cout << g.getScoreP1() << " " << g.getScoreP2() << std::endl;
#define LOG(g)  std::cout << g << std::endl;



int window_thread() {
	S2D_Window* window = S2D_CreateWindow(
		"Hello PingPong", 640, 480, NULL, render_main, 0
	);
	window->on_key = on_key;
	S2D_Show(window);
	return 0;
}

int main(int argc, char**argv) {
	Game game;
	srand(time(0));
	renderingGame = &game;
	std::thread thread(window_thread); // Pass 10 to functor object
	while (true) {
		game.update();
		LOG_SCORE(game);
		LOG(game.getBall().getDirection());
		Sleep(10);
	}

	thread.join();
	return 0;
}