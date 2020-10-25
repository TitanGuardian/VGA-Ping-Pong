#pragma once

#include "Neural.h"
#include <string>

struct Generation {
	int size;
	int epoch;
	std::vector<NeuralNetwork_info> agents;
	std::vector<int> scores;

	void evalAsP1(const NeuralNetwork_info player2);
	void evalAsP2(const NeuralNetwork_info player1);

	Generation(int size);
	Generation(const Generation&);
	Generation& operator=(const Generation&);

	void save(std::string fileName);
	void load(std::string fileName);
};
