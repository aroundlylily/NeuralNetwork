#ifndef NEURONLAYER_HPP
#define NEURONLAYER_HPP

#include <vector>

class NeuronLayer {
private:
	std::vector<double> values_;
	std::vector<double> errors_;
	std::vector<double> weights_;
	int layerSize_;
	int nextLayerSize_;

public:
	NeuronLayer(int layerSize, int nextLayerSize);
	std::vector<double> & values();
	std::vector<double> & errors();
	std::vector<double> & weights();
	void print();
};

#endif
