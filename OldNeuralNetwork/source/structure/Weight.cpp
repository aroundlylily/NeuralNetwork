#include "../../include/structure/Weight.hpp"
#include "../../include/structure/Neuron.hpp"

#include "../../include/render/WeightRender.hpp"

#include <random>

Weight::Weight(Neuron *previousNeuron, Neuron *nextNeuron)
	: previousNeuron_(previousNeuron), nextNeuron_(nextNeuron), shape_(nullptr)
{
	std::random_device seed;
	std::uniform_real_distribution<float> distribution(-1.0, 1.0);
	weight_ = distribution(seed);
}

Weight::~Weight() {
        //if (shape_)
	//        delete shape_;
}

Neuron * Weight::getPreviousNeuron() {
	return previousNeuron_;
}

Neuron * Weight::getNextNeuron() {
	return nextNeuron_;
}

float Weight::getWeight() {
	return weight_;
}

void Weight::setWeight(float weight) {
	weight_ = weight;
}
