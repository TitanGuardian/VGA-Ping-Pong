#include "Generation.h"
#include "Game.h"
#include <iostream>
#include <fstream>

void Generation::evalAsP1(const NeuralNetwork_info player2) {
	for (int i = 0; i < size; ++i) {
		NeuralNetwork nn(agents[i], 5), nn_opposite(player2, 5);
		scores[i] = 0;
		Game game;
		while (game.getTurns() <= 1000) {
			Input nn_in(5, 0);
			int nn_out, nn_opposite_out;
			nn_in[0] = Data_t(game.getBall().getDirection() * 256 / 3600);
			nn_in[1] = Data_t(game.getBall().getX() * 640 / 256);
			nn_in[2] = Data_t(game.getBall().getY() * 480 / 256);
			nn_in[3] = Data_t(game.getPaddleP1().getY() * 480 / 256);
			nn_in[4] = Data_t(game.getPaddleP2().getY() * 480 / 256);

			nn_out = nn.compute(nn_in);
			nn_opposite_out = nn_opposite.compute(nn_in);
			switch (nn_out)
			{
			case 0: game.onInputP1(-1); break;
			case 1: game.onInputP1(0); break;
			case 2: game.onInputP1(1); break;
			default: throw;
			}

			switch (nn_opposite_out)
			{
			case 0: game.onInputP2(-1); break;
			case 1: game.onInputP2(0); break;
			case 2: game.onInputP2(1); break;
			default: throw;
			}

			game.update();


			if (game.getStatus()) {
				scores[i] = game.getScoreP1() - game.getScoreP2();
				break;
			}
		}
	}
}

void Generation::evalAsP2(const NeuralNetwork_info player1) {
	for (int i = 0; i < size; ++i) {
		NeuralNetwork nn(agents[i], 5), nn_opposite(player1, 5);
		scores[i] = 0;
		Game game;
		while (game.getTurns() <= 1000) {
			Input nn_in(5, 0);
			int nn_out, nn_opposite_out;
			nn_in[0] = Data_t(game.getBall().getDirection() * 256 / 3600);
			nn_in[1] = Data_t(game.getBall().getX() * 640 / 256);
			nn_in[2] = Data_t(game.getBall().getY() * 480 / 256);
			nn_in[3] = Data_t(game.getPaddleP1().getY() * 480 / 256);
			nn_in[4] = Data_t(game.getPaddleP2().getY() * 480 / 256);

			nn_out = nn.compute(nn_in);
			nn_opposite_out = nn_opposite.compute(nn_in);
			switch (nn_out)
			{
			case 0: game.onInputP2(-1); break;
			case 1: game.onInputP2(0); break;
			case 2: game.onInputP2(1); break;
			default: throw;
			}

			switch (nn_opposite_out)
			{
			case 0: game.onInputP1(-1); break;
			case 1: game.onInputP1(0); break;
			case 2: game.onInputP1(1); break;
			default: throw;
			}

			game.update();

			if (game.getStatus()) {
				scores[i] = game.getScoreP2() - game.getScoreP1();
				break;
			}
		}
	}
}

Generation::Generation(int size) : agents(size), size(size), epoch(0) {
	srand(286);
	for (int i = 0; i < size; ++i) {
		agents[i] = random_NN();
	}
}
Generation::Generation(const Generation&) = default;
Generation& Generation::operator=(const Generation&) = default;

void Generation::save(std::string fileName) {
	std::ofstream file;
	file.open(fileName.c_str());
	file << epoch << " " << size << "\n";
	for (auto& agent : agents) {
		for (auto& layer : agent) {
			for (auto& neuron : layer) {
				for (auto& weight : neuron.weights) {
					file << weight << " ";
				}
				file <<	neuron.bias << " ";
			}
		}
		file << "\n";
	}

	file.close();
}

void Generation::load(std::string fileName) {
	std::ifstream file;
	file.open(fileName.c_str());
	file >> epoch >> size;
	int tmp;
	for (auto& agent : agents) {
		for (auto& layer : agent) {
			for (auto& neuron : layer) {
				for (auto& weight : neuron.weights) {
					file >> tmp;
					weight = tmp;
				}
				file >> tmp;
				neuron.bias = tmp;
			}
		}
	}
	file.close();
}
