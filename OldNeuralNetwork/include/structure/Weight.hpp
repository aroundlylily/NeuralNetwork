#ifndef WEIGHT_HPP
#define WEIGHT_HPP

#include <vector>

class Neuron;
class WeightRender;
class NetworkVisualization;

class Weight {
private:
	Neuron *previousNeuron_;
	Neuron *nextNeuron_;
	float weight_;
	WeightRender *shape_;

public:
	Weight(Neuron *previousNeuron, Neuron *nextNeuron);
	virtual ~Weight();
	Neuron *getPreviousNeuron();
	Neuron *getNextNeuron();
	float getWeight();
	void setWeight(float weight);
};

#endif
