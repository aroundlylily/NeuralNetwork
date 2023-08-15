#include "../../include/structure/NeuralNetwork.hpp"
#include "../../include/structure/Neuron.hpp"
#include "../../include/structure/Weight.hpp"
#include "../../include/structure/NeuronLayer.hpp"

NeuralNetwork::~NeuralNetwork() {
        for (const auto &weight : weights_)
                delete weight;
        for (const auto &layer : layers_)
                delete layer;
}

void NeuralNetwork::addNeuronLayer(int count) {
	NeuronLayer *nextNeuronLayer = new NeuronLayer(count);
        if (layers_.empty()) {
                layers_.push_back(nextNeuronLayer);
                return;
        }
	NeuronLayer *previousNeuronLayer = layers_.back();
	previousNeuronLayer->addBias();
	layers_.push_back(nextNeuronLayer);
	for (const auto &previousNeuron : previousNeuronLayer->getNeurons()) {
		for (const auto &nextNeuron : nextNeuronLayer->getNeurons()) {
			Weight *weight = new Weight(previousNeuron, nextNeuron);
			previousNeuron->addOutput(weight);
			nextNeuron->addInput(weight);
			weights_.push_back(weight);
		}
	}
}

std::vector<Weight *> NeuralNetwork::getWeights() {
        return weights_;
}

std::vector<NeuronLayer *> NeuralNetwork::getNeuronLayers() {
        return layers_;
}
