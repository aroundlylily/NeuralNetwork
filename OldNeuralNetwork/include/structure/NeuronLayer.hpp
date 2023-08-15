#ifndef NEURONLAYER_HPP
#define NEURONLAYER_HPP

#include <vector>

class Neuron;
class NeuronWeight;
class PropagationStrategy;

class NeuronLayer {
private:
	std::vector<Neuron *> neurons_;

public:
	NeuronLayer(int count);
	virtual ~NeuronLayer();
        void connectNeuronLayer(NeuronLayer *nextNeuronLayer);
        void addBias();
	std::vector<Neuron *> getNeurons();
        void addNeuron(Neuron *neuron);
	void setValues(std::vector<float> values);
};

#endif
