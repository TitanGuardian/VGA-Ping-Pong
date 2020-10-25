#include "Neural.h"
#include <algorithm>

#define ARGMAX(vec) (static_cast<int>(std::distance(vec.begin(), max_element(vec.begin(), vec.end()))));


Neuron::Neuron(const Neuron_info& info): values(info) {}

Layer::Layer(const Layer_info& info) {
	for (auto& el : info) {
		neurons.push_back(el);
	}
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork_info& info, unsigned int input_size): input_size(input_size), info(info) {
	for (auto& el : info) {
		layers.push_back(el);
	}
}

NeuralNetwork::NeuralNetwork() = default;


int NeuralNetwork::compute(const Input& input) {
	auto current_computation = input;
	for (auto& layer : this->layers) {
		current_computation = layer.compute(current_computation);
	}
	return ARGMAX(current_computation);
}

Input Layer::compute(const Input& input) {
	Input tmp;
	for (auto& neuron : this->neurons) {
		tmp.push_back(neuron.compute(input));
	}
	return tmp;
}

Data_t Neuron::compute(const Input& input) {
	Data_t sum(0);
	for (int i = 0; i < input.size(); ++i) {
		sum.MUL_ADD_ACC(this->values.weights[i], input[i], this->values.bias);
	}
	return sum; 
}

Neuron_info::Neuron_info() : bias(0) {}


NeuralNetwork_info random_NN() {
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
		ni.bias = ((int)rand() % 256);
		for (int j = 0; j < l1_is; ++j) {
			ni.weights.push_back(Data_t(((int)rand() % 256)));
		}
		l1.push_back(ni);
	}

	//l2
	for (int i = 0; i < out_size; i++) {
		Neuron_info ni;
		ni.bias = ((int)rand() % 256);
		for (int j = 0; j < l2_is; ++j) {
			ni.weights.push_back(Data_t(((int)rand() % 256)));
		}
		l2.push_back(ni);
	}
	nn.push_back(l1);
	nn.push_back(l2);

	return nn;
}

