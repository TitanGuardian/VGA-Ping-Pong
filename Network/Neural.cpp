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
	return sum>0?Data_t::MIN:Data_t::MAX;
}

Neuron_info::Neuron_info() : bias(0) {}
