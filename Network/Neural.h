#pragma once
#include "Fract_N_bit.h"
#include <vector>

struct Neuron_info;

using Data_t = Fract_N_bit<8>;
using NeuronWeights = std::vector<Data_t>;
using Layer_info = std::vector<Neuron_info>;
using NeuralNetwork_info = std::vector<Layer_info>; // NN configuration weights, and bias by layers
using Input = std::vector<Data_t>;
using Output = Input;

struct Neuron_info {
	NeuronWeights weights;
	Data_t bias;
	Neuron_info();
};

struct Neuron {
	Neuron_info values;
	Neuron(const Neuron_info& info);
	Data_t compute(const Input& input);
};

struct Layer {
	std::vector<Neuron> neurons;
	Layer(const Layer_info& info);
	Output compute(const Input& input);
};

//ARGMAX at end
struct NeuralNetwork {
	std::vector<Layer> layers;
	unsigned int input_size;
	NeuralNetwork_info info;
	NeuralNetwork(const NeuralNetwork_info& info, unsigned int input_size);
	NeuralNetwork();
	int compute(const Input& input);
};

NeuralNetwork_info random_NN();
