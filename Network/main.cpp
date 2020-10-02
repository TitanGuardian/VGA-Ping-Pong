#include <iostream>
#include "Fract_N_bit.h"
#include "Neural.h"
#include "time.h"

int main() {
	
	srand(time(NULL));
	// input 32, dense 48, dense 4
	
	int l1_is, l2_is;
	l1_is = 32; 
	l2_is = 48;
	Layer_info l1, l2;
	NeuralNetwork_info nn;

	// l1
	for (int i = 0; i < 48; i++) {
		Neuron_info ni;
		ni.bias = ((int)rand() % 256) - 128;
		for (int j = 0; j < l1_is; ++j) {
			ni.weights.push_back(Data_t(((int)rand() % 256)-128));
		}
		l1.push_back(ni);
	}

	//l2
	for (int i = 0; i < 4; i++) {
		Neuron_info ni;
		ni.bias = ((int)rand() % 256) - 128;
		for (int j = 0; j < l2_is; ++j) {
			ni.weights.push_back(Data_t(((int)rand() % 256) - 128));
		}
		l2.push_back(ni);
	}
	nn.push_back(l1);
	nn.push_back(l2);

	NeuralNetwork my_nn (nn, 32);

	Input in(32, 0);

	//for (auto& el : in) {
	//	el = ((int)rand() % 256) - 128;
	//}

	std::cout << my_nn.compute(in);


	return 0;
}