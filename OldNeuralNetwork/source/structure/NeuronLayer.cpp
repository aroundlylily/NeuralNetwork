#include "../../include/structure/Neuron.hpp"
#include "../../include/structure/NeuronLayer.hpp"

#include <iostream>
#include <string>

NeuronLayer::NeuronLayer(int count)
{
        for (int i = 0; i < count; i++) {
                neurons_.push_back(new Neuron);
        }
}

NeuronLayer::~NeuronLayer() {
        for (auto const &neuron : neurons_)
                delete neuron;
	neurons_.clear();
}

void NeuronLayer::addBias() {
        Neuron *biasNeuron = new Neuron();
        biasNeuron->setValue(1);
	biasNeuron->setError(-1);
	neurons_.push_back(biasNeuron);
}

std::vector<Neuron *> NeuronLayer::getNeurons() {
	return neurons_;
}

void NeuronLayer::addNeuron(Neuron *neuron) {
        neurons_.push_back(neuron);
}

void NeuronLayer::setValues(std::vector<float> values) {
	for (int valueIndex = 0; valueIndex < values.size(); valueIndex++) {
		neurons_[valueIndex]->setValue(values[valueIndex]);
	}
}

//void NeuronLayer::setPreviousNeuronLayer(NeuronLayer *previousNeuronLayer) {
//	previousNeuronLayer_ = previousNeuronLayer;
//}
//
//NeuronLayer * NeuronLayer::getPreviousNeuronLayer() {
//	return previousNeuronLayer_;
//}
//
//void NeuronLayer::setNextNeuronLayer(NeuronLayer *nextNeuronLayer) {
//	nextNeuronLayer_ = nextNeuronLayer;
//}
//
//NeuronLayer * NeuronLayer::getNextNeuronLayer() {
//	return nextNeuronLayer_;
//}
