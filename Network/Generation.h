#pragma once

#include "Neural.h"
#include <string>

struct Agent {
	NeuralNetwork_info info;
	int score;
};

struct Generation {
	int size;
	int epoch;
	std::vector<Agent> agents;
	int mutationRate = 25; // range 0-999
	void evalAsP1(const NeuralNetwork_info player2);
	void evalAsP2(const NeuralNetwork_info player1);

	Generation(int size);
	Generation(const Generation&);
	Generation& operator=(const Generation&);

	void save(std::string fileName);
	void load(std::string fileName);

	void nextEpoch(); // eval before next epoch step

	void sort();

	void printScores();
};
