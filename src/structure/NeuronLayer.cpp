#include "NeuronLayer.hpp"

#include <string>
#include <iostream>

NeuronLayer::NeuronLayer(int layerSize, int nextLayerSize)
	: values_(layerSize, 1), errors_(layerSize, 0), weights_(layerSize * nextLayerSize, 0), nextLayerSize_(nextLayerSize) {}

std::vector<double> & NeuronLayer::values() {
	return values_;
}

std::vector<double> & NeuronLayer::errors() {
	return errors_;
}

std::vector<double> & NeuronLayer::weights() {
	return weights_;
}

void NeuronLayer::print() {
	std::string values = "", errors = "", weights = "";
	for (int valueIndex = 0; valueIndex < values_.size(); ++valueIndex) {
		if (valueIndex > 0)
			values += ", ", errors += ", ";
		values += std::to_string(values_[valueIndex]), errors += std::to_string(errors_[valueIndex]);
		weights += "{ ";
		for (int weightIndex = 0; weightIndex < nextLayerSize_; ++weightIndex) {
			if (weightIndex > 0)
				weights += ", ";
			weights += std::to_string(weights_[valueIndex * nextLayerSize_ + weightIndex]);
		}
		weights += " }\n";
	}
	std::cout << "Values: { " << values << " }\n\nErrors: { " << errors << " }\n\nWeights:\n" << weights << "\n";
}

