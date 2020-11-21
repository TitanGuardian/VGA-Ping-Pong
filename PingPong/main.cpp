#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "simple2d.h"
#include "Fract_N_bit.h"
#include "Neural.h"
#include "Generation.h"

/*delete comment to run specific test*/
//extern "C" int test_triangle();
//extern "C" int test_triangleIOS();
//extern "C" int test_testcard();
//extern "C" int test_audio();
//extern "C" int test_auto();
//extern "C" int test_controller();

#include <thread>
#include <string>
Game* volatile renderingGame;

const char* font = "media/bitstream_vera/vera.ttf";
int font_size = 20;
S2D_Text* txt_P1;
S2D_Text* txt_P2;
char txt[50];

static void render_main() {

	Ball bl = renderingGame->getBall();
	
	S2D_DrawQuad(
		bl.getX() + bl.getSize(), bl.getY() - bl.getSize(), 1, 1, 1, 1,
		bl.getX() + bl.getSize(), bl.getY() + bl.getSize(), 1, 1, 1, 1,
		bl.getX() - bl.getSize(), bl.getY() + bl.getSize(), 1, 1, 1, 1,
		bl.getX() - bl.getSize(), bl.getY() - bl.getSize(), 1, 1, 1, 1
	);

	Paddle pd1 = renderingGame->getPaddleP1();


	S2D_DrawQuad(
		pd1.getX() + pd1.getWidth(), pd1.getY() - pd1.getSize(), 1, 1, 1, 1,
		pd1.getX() + pd1.getWidth(), pd1.getY() + pd1.getSize(), 1, 1, 1, 1,
		pd1.getX() - pd1.getWidth(), pd1.getY() + pd1.getSize(), 1, 1, 1, 1,
		pd1.getX() - pd1.getWidth(), pd1.getY() - pd1.getSize(), 1, 1, 1, 1
	);


	Paddle pd2 = renderingGame->getPaddleP2();

	S2D_DrawQuad(
		pd2.getX() + pd2.getWidth(), pd2.getY() - pd2.getSize(), 1, 1, 1, 1,
		pd2.getX() + pd2.getWidth(), pd2.getY() + pd2.getSize(), 1, 1, 1, 1,
		pd2.getX() - pd2.getWidth(), pd2.getY() + pd2.getSize(), 1, 1, 1, 1,
		pd2.getX() - pd2.getWidth(), pd2.getY() - pd2.getSize(), 1, 1, 1, 1
	);

	S2D_SetText(txt_P1, "%d", renderingGame->getScoreP1());
	S2D_DrawText(txt_P1);

	S2D_SetText(txt_P2, "%d", renderingGame->getScoreP2());
	S2D_DrawText(txt_P2);

}

static void on_key(S2D_Event e) {
	switch (e.type) {
	case S2D_KEY_DOWN:
		if (strcmp(e.key, "W") == 0) renderingGame->onInputP1(-1);
		if (strcmp(e.key, "S") == 0) renderingGame->onInputP1(1);
		if (strcmp(e.key, "Up") == 0) renderingGame->onInputP2(-1);
		if (strcmp(e.key, "Down") == 0) renderingGame->onInputP2(1);
		if (strcmp(e.key, "R") == 0) renderingGame->reset();
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

	txt_P1 = S2D_CreateText(font, "", font_size);
	txt_P1->x = 50;
	txt_P1->y = 100;
	txt_P1->color.r = 1.0;
	txt_P1->color.g = 0.0;
	txt_P1->color.b = 0.0;
	txt_P1->color.a = 1.0;

	txt_P2 = S2D_CreateText(font, "", font_size);
	txt_P2->x = RESOLUTION_X - 75;
	txt_P2->y = 100;
	txt_P2->color.r = 1.0;
	txt_P2->color.g = 0.0;
	txt_P2->color.b = 0.0;
	txt_P2->color.a = 1.0;

	S2D_Show(window);

	S2D_FreeWindow(window);
	return 0;
}


int main(int argc, char** argv) {

	Generation genP1(100), genP2(100);
	std::cout << "Write command:\n";
	std::string inp;
	int train_size;
	std::cin >> inp;
	if (inp[0] == 'l') {
		genP1.load("genP1.txt");
		genP2.load("genP2.txt");
	}

	if (inp == "t" || inp == "lt") {
		std::cin >> train_size;
		genP2.evalAsP2(genP1);
		genP1.evalAsP1(genP2);

		genP1.sort();
		genP2.sort();
		for (int i = 0; i < train_size; ++i) {
			std::cout << "Generation " << i << "\n";

			genP1.printScores();
			genP2.printScores();

			genP1.nextEpoch();
			genP2.nextEpoch();

			genP2.evalAsP2(genP1);
			genP1.evalAsP1(genP2);

			genP1.sort();
			genP2.sort();
			
			std::cout << "Saving!!!" << "\n";
			genP1.save("genP1.txt");
			genP2.save("genP2.txt");
		}

	}
	std::cout << "Current scores " << "\n";
	genP1.printScores();
	genP2.printScores();

	NeuralNetwork nnP1(genP1.agents[0].info,5), nnP2(genP2.agents[0].info, 5);

	std::thread thread(window_thread);
	while (true)
	{
		Game game;
		renderingGame = &game;

		while (true) {
			Input nn_in(5, 0);
			int nn_outP1, nn_outP2;
			nn_in[0] = Data_t(game.getBall().getDirection() * 256 / 3600 - 128);
			nn_in[1] = Data_t(game.getBall().getX() * 256 / 640 - 128);
			nn_in[2] = Data_t(game.getBall().getY() * 256 / 480 - 128);
			nn_in[3] = Data_t(game.getPaddleP1().getY() * 256 / 480 - 128);
			nn_in[4] = Data_t(game.getPaddleP2().getY() * 256 / 480 - 128);

			nn_outP1 = nnP1.compute(nn_in);
			nn_outP2 = nnP2.compute(nn_in);

			switch (nn_outP1)
			{
			case 0: game.onInputP1(-1); break;
			case 1: game.onInputP1(0); break;
			case 2: game.onInputP1(1); break;
			default: throw;
			}

			switch (nn_outP2)
			{
			case 0: game.onInputP2(-1); break;
			case 1: game.onInputP2(0); break;
			case 2: game.onInputP2(1); break;
			default: throw;
			}

			game.update();
			//LOG_SCORE(game);
			//LOG(game.getBall().getDirection());
			if (game.getStatus()) break;
			Sleep(10);
		}
	}

	thread.join();
	return 0;
}