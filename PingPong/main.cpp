#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "simple2d.h"
#include "Fract_N_bit.h"
#include "Neural.h"

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



NeuralNetwork random_NN() {
	srand(time(NULL));
	// input 5, dense 8, dense 3

	int l1_is, l2_is, out_size;
	l1_is = 5;
	l2_is = 8;
	out_size = 3;
	Layer_info l1, l2;
	NeuralNetwork_info nn;

	// l1
	for (int i = 0; i < l2_is; i++) {
		Neuron_info ni;
		ni.bias = ((int)rand() % 256) - 128;
		for (int j = 0; j < l1_is; ++j) {
			ni.weights.push_back(Data_t(((int)rand() % 256) - 128));
		}
		l1.push_back(ni);
	}

	//l2
	for (int i = 0; i < out_size; i++) {
		Neuron_info ni;
		ni.bias = ((int)rand() % 256) - 128;
		for (int j = 0; j < l2_is; ++j) {
			ni.weights.push_back(Data_t(((int)rand() % 256) - 128));
		}
		l2.push_back(ni);
	}
	nn.push_back(l1);
	nn.push_back(l2);

	return NeuralNetwork(nn, l1_is);
}



int main(int argc, char**argv) {
	Game game;
	srand(time(0));
	renderingGame = &game;
	std::thread thread(window_thread);
	
	while (true) {
		NeuralNetwork nn = random_NN();
		Input nn_in(5,0);
		int nn_out;
		nn_in[0] = Data_t(game.getBall().getDirection() * 256 / 3600 - 128);
		nn_in[1] = Data_t(game.getBall().getX() * 640 / 256 - 128);
		nn_in[2] = Data_t(game.getBall().getY() * 480 / 256 - 128);
		nn_in[3] = Data_t(game.getPaddleP1().getY() * 480 / 256 - 128);
		nn_in[4] = Data_t(game.getPaddleP2().getY() * 480 / 256 - 128);

		nn_out = nn.compute(nn_in);
		switch (nn_out)
		{
		case 0: game.onInputP1(-1); break;
		case 1: game.onInputP1(0); break;
		case 2: game.onInputP1(1); break;
		default: throw;
		}

		game.update();
		//LOG_SCORE(game);
		//LOG(game.getBall().getDirection());
		Sleep(10);
	}

	thread.join();
	return 0;
}