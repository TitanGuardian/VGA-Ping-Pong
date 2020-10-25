#include "Generation.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void Generation::evalAsP1(const NeuralNetwork_info player2) {
	for (int i = 0; i < size; ++i) {
		NeuralNetwork nn(agents[i].info, 5), nn_opposite(player2, 5);
		agents[i].score = 1000;
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
				agents[i].score = game.getTurns(); // game.getScoreP1() - game.getScoreP2();
				break;
			}
		}
	}
}

void Generation::evalAsP2(const NeuralNetwork_info player1) {
	for (int i = 0; i < size; ++i) {
		NeuralNetwork nn(agents[i].info, 5), nn_opposite(player1, 5);
		agents[i].score = 1000;
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
				agents[i].score = game.getTurns();  // game.getScoreP2() - game.getScoreP1();
				break;
			}
		}
	}
}

Generation::Generation(int size) : agents(size), size(size), epoch(0) {
	for (int i = 0; i < size; ++i) {
		agents[i].info = random_NN();
	}
}
Generation::Generation(const Generation&) = default;
Generation& Generation::operator=(const Generation&) = default;

void Generation::save(std::string fileName) {
	std::ofstream file;
	file.open(fileName.c_str());
	file << epoch << " " << size << "\n";
	for (auto& agent : agents) {
		for (auto& layer : agent.info) {
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
		for (auto& layer : agent.info) {
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


void Generation::sort() {
	std::sort(agents.begin(), agents.end(), [](Agent const& a, Agent& b) {return a.score > b.score; });
}

void Generation::nextEpoch() {
	sort();
	//top 10 parents
	std::vector<Agent> Parents{ agents.at(0),
								agents.at(1),
								agents.at(2),
								agents.at(3),
								agents.at(4),
								agents.at(5),
								agents.at(6),
								agents.at(7),
								agents.at(8),
								agents.at(9)
								};

	for (int i = 0; i < agents.size(); ++i) {
		for (int j = 0; j < agents[i].info.size(); ++j) {
			for (int k = 0; k < agents[i].info[j].size(); ++k) {
				for (int l = 0; l < agents[i].info[j][k].weights.size(); ++l) {
					int TempSelection = rand() % Parents.size();
					agents[i].info[j][k].weights[l] = Parents.at(TempSelection).info[j][k].weights[l];

					if (rand() % 1000 < mutationRate) { agents[i].info[j][k].weights[l] = Data_t(rand() % 512 - 128); }
				}
				int TempSelection = rand() % Parents.size();
				agents[i].info[j][k].bias = Parents.at(TempSelection).info[j][k].bias;
				if (rand() % 1000 < mutationRate) { agents[i].info[j][k].bias = Data_t(rand() % 512 - 128); }
			}
		}
	}

	++epoch;
}

void Generation::printScores() {
	std::vector<Agent> Parents{ agents.at(0),
							agents.at(1),
							agents.at(2),
							agents.at(3),
							agents.at(4),
							agents.at(5),
							agents.at(6),
							agents.at(7),
							agents.at(8),
							agents.at(9)
	};

	for (auto& el : Parents) {
		std::cout << el.score << " ";
	}
	std::cout << std::endl;
}
