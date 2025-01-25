#include "TrainingStrategy.hpp"
#include "ActivationFunction.hpp"

#include "structure/NeuronLayer.hpp"
#include "structure/NeuralNetwork.hpp"

TrainingStrategy::TrainingStrategy(double learningRate, const ActivationFunction &activationFunction, int epochs, double restartThreshold)
        : learningRate_(learningRate), activationFunction_(activationFunction), outputScalingFunction_(nullptr), epochs_(epochs), restartThreshold_(restartThreshold), distribution_(-1.f, 1.f), generator_(device_()) {}

void TrainingStrategy::setInputs(NeuronLayer *inputLayer, const std::vector<double> &inputs) {
	std::vector<double> &inputValues = inputLayer->values();
	for (int inputIndex = 0; inputIndex < inputs.size(); ++inputIndex)
		inputValues[inputIndex] = inputs[inputIndex];
}

void TrainingStrategy::setScalingFunction(ActivationFunction *scalingFunction) {
	outputScalingFunction_ = scalingFunction;
}

void TrainingStrategy::applyScalingFunction(NeuronLayer *outputLayer) {
	if (!outputLayer || !outputScalingFunction_)
		return;
	std::vector<double> &outputValues = outputLayer->values();
	for (int outputIndex = 0; outputIndex < outputValues.size(); ++outputIndex) {
		outputValues[outputIndex] = outputScalingFunction_->apply(outputValues[outputIndex]);
	}
}

double TrainingStrategy::calculateOutputError(NeuronLayer *outputLayer, const std::vector<double> &outputs) {
	const std::vector <double> &outputValues = outputLayer->values();
	std::vector<double> &outputErrors = outputLayer->errors();
        double error = 0;
	for (int outputIndex = 0; outputIndex < outputs.size(); ++outputIndex) {
		double outputNeuronError = outputValues[outputIndex] - outputs[outputIndex];
		error += std::abs(outputNeuronError);
		outputErrors[outputIndex] = outputNeuronError;
	}
        return error;
}

void TrainingStrategy::initializeWeights(const std::vector<NeuronLayer *> &layers) {
	for (const auto &layer : layers) {
		for (auto &weight : layer->weights())
			weight = distribution_(generator_);
	}
}

void TrainingStrategy::resetStructure(std::vector<double> &structure, bool hasBiasNeuron) {
	for (int structureIndex = 0; structureIndex < structure.size() - hasBiasNeuron; ++structureIndex)
		structure[structureIndex] = 0;
}

void TrainingStrategy::applyActivationFunction(std::vector<double> &values, bool hasBiasNeuron) {
	for (int valueIndex = 0; valueIndex < values.size() - hasBiasNeuron; ++valueIndex)
		values[valueIndex] = activationFunction_.apply(values[valueIndex]);
}

void TrainingStrategy::forwardPropagate(const std::vector<NeuronLayer *> &layers, int layerIndex) {
	NeuronLayer *currentLayer = layers[layerIndex], *nextLayer = layers[layerIndex + 1];
	bool hasBiasNeuron = true;
	if (nextLayer == layers.back())
		hasBiasNeuron = false;
	resetStructure(nextLayer->values(), hasBiasNeuron);
	calculateValues(currentLayer, nextLayer, hasBiasNeuron);
	if (nextLayer == layers.back()) {
		applyScalingFunction(nextLayer);
		return;
	}
	applyActivationFunction(nextLayer->values(), hasBiasNeuron);
	forwardPropagate(layers, layerIndex + 1);
}

void TrainingStrategy::calculateValues(NeuronLayer *currentLayer, NeuronLayer *nextLayer, bool hasBiasNeuron) {
	const std::vector<double> &currentValues = currentLayer->values(), &weights = currentLayer->weights();
	std::vector<double> &nextValues = nextLayer->values();
	size_t nextLayerSize = nextValues.size() - hasBiasNeuron;
	for (int nextWeightIndex = 0; nextWeightIndex < weights.size(); ++nextWeightIndex) {
		int nextValueIndex = nextWeightIndex % nextLayerSize, currentValueIndex = nextWeightIndex / nextLayerSize;
		nextValues[nextValueIndex] += currentValues[currentValueIndex] * weights[nextWeightIndex];
	}
}

void TrainingStrategy::backPropagate(const std::vector<NeuronLayer *> &layers, int layerIndex) {
	if (layerIndex <= 0)
		return;
	NeuronLayer *previousLayer = layers[layerIndex - 1], *currentLayer = layers[layerIndex];
        bool hasBiasNeuron = true;
        if (currentLayer == layers.back())
                hasBiasNeuron = false;
        resetStructure(previousLayer->errors(), hasBiasNeuron);
        calculateErrors(previousLayer, currentLayer, hasBiasNeuron);
        adjustWeights(previousLayer, currentLayer, hasBiasNeuron);
	backPropagate(layers, layerIndex - 1);
}

void TrainingStrategy::calculateErrors(NeuronLayer *previousLayer, NeuronLayer *currentLayer, bool hasBiasNeuron) {
        const std::vector<double> &currentErrors = currentLayer->errors(), &weights = previousLayer->weights();
        std::vector<double> &previousErrors = previousLayer->errors();
        size_t currentLayerSize = currentErrors.size() - hasBiasNeuron;
        for (int previousWeightIndex = 0; previousWeightIndex < weights.size(); ++previousWeightIndex) {
                int previousErrorIndex = previousWeightIndex / currentLayerSize, currentErrorIndex = previousWeightIndex % currentLayerSize;
                previousErrors[previousErrorIndex] += currentErrors[currentErrorIndex] * weights[previousWeightIndex];
        }
}

void TrainingStrategy::adjustWeights(NeuronLayer *previousLayer, NeuronLayer *currentLayer, bool hasBiasNeuron) {
        const std::vector<double> &currentErrors = currentLayer->errors(), &previousValues = previousLayer->values(), &currentValues = currentLayer->values();
        std::vector<double> &weights = previousLayer->weights();
        size_t currentLayerSize = currentErrors.size() - hasBiasNeuron;
        for (int previousWeightIndex = 0; previousWeightIndex < weights.size(); ++previousWeightIndex) {
                int currentValueIndex = previousWeightIndex % currentLayerSize, previousValueIndex = previousWeightIndex / currentLayerSize;
                weights[previousWeightIndex] -= learningRate_ * currentErrors[currentValueIndex] * activationFunction_.applyDerivative(currentValues[currentValueIndex]) * previousValues[previousValueIndex];
        }
}

bool TrainingStrategy::hasCompleted(int iteration) {
	return (iteration > epochs_);
}

double TrainingStrategy::train(const NeuralNetwork *network, int iteration, const std::vector<std::vector<double>> &inputs, const std::vector<std::vector<double>> &outputs) {
	const std::vector<NeuronLayer *> &layers = network->layers();
	if (iteration == 0) {
		initializeWeights(layers);
	}
	double error = 0.f;
	for (int setIndex = 0; setIndex < inputs.size(); ++setIndex) {
		setInputs(layers.front(), inputs[setIndex]);
		forwardPropagate(layers, 0);
		error += calculateOutputError(layers.back(), outputs[setIndex]);
		backPropagate(layers, layers.size() - 1);
	}
        return error;
}

std::vector<double> TrainingStrategy::apply(const NeuralNetwork *network, const std::vector<double> inputs) {
	const std::vector<NeuronLayer *> &layers = network->layers();
	setInputs(layers.front(), inputs);
	forwardPropagate(layers, 0);
	return layers.back()->values();
}
