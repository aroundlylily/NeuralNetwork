#include "../../include/NetworkStructure.hpp"
#include "../../include/training/TrainingStrategy.hpp"

NeuralNetwork::NeuralNetwork(const std::vector<int> &dimensions) 
	: dimensions_(dimensions), trainingStrategy_(nullptr), iterations_(0), error_(0.f)
{
	int layerSize, nextLayerSize;
	NeuronLayer *layer;
	bool hasBiasNeuron = true;
	for (int currentLayerIndex = 0; currentLayerIndex < dimensions.size(); ++currentLayerIndex) {
		layerSize = dimensions[currentLayerIndex], nextLayerSize = 0;
		if (currentLayerIndex + 1 < dimensions.size())
			nextLayerSize = dimensions[currentLayerIndex + 1];
		if (currentLayerIndex == dimensions.size() - 1) {
			hasBiasNeuron = false;
		}
		layer = new NeuronLayer(layerSize + hasBiasNeuron, nextLayerSize);
		layers_.push_back(layer);
	}
}

NeuralNetwork::~NeuralNetwork() {
	for (const auto &layer : layers_)
		delete layer;
}

const std::vector<int> & NeuralNetwork::dimensions() const {
	return dimensions_;
}

std::vector<NeuronLayer *> NeuralNetwork::layers() const {
	return layers_;
}

void NeuralNetwork::setTrainingStrategy(TrainingStrategy *trainingStrategy) {
        trainingStrategy_ = trainingStrategy;
}

bool NeuralNetwork::hasCompletedTraining() const {
        if (!trainingStrategy_)
                return false;
        return trainingStrategy_->hasCompleted(iterations_);
}

void NeuralNetwork::train(const std::vector<std::vector<double>> &inputs, const std::vector<std::vector<double>> &outputs) {
        if (!trainingStrategy_)
                return;
        error_ = trainingStrategy_->train(this, iterations_++, inputs, outputs);
}

double NeuralNetwork::error() const {
        return error_;
}

void NeuralNetwork::print() const {
	int layerIndex = 0;
	for (const auto &layer : layers_) {
		if (layer == layers_.front())
			std::cout << "\nInputLayer:\n\n";
		else if (layer == layers_.back())
			std::cout << "\nOutputLayer:\n\n";
		else {
			std::cout << "\nLayer" << layerIndex << ":\n\n";
			++layerIndex;
		}
		layer->print();
	}
}
