#include "../../include/training/NetworkTraining.hpp"
#include "../../include/NetworkStructure.hpp"

#include "../../include/render/ErrorRender.hpp"

#include <cmath>
#include <iostream>

NetworkTraining::NetworkTraining(float learningRate, int epochs)
	: learningRate_(learningRate), epochs_(epochs), cycleNumber_(0), render_(nullptr) {}

void NetworkTraining::setRender(ErrorRender *render) {
	render_ = render;
}

void NetworkTraining::setInputs(const std::vector<std::vector<float>> &inputs) {
	inputs_ = inputs;
}

void NetworkTraining::setOutputs(const std::vector<std::vector<float>> &outputs) {
	outputs_ = outputs;
}

float NetworkTraining::applySigmoid(float x) {
	return 1.f / (1.f + std::exp(-x));
}

float NetworkTraining::calculateValue(Neuron *neuron) {
	if (neuron->getInputs().empty())
		return neuron->getValue();
	float valueSum = 0;
	for (const auto &input : neuron->getInputs())
		valueSum += input->getPreviousNeuron()->getValue() * input->getWeight();
	return applySigmoid(valueSum);
}

float NetworkTraining::calculateError(Neuron *neuron) {
	if (neuron->getOutputs().empty()) {
		return calculateValue(neuron) - neuron->getValue();
	}
	float errorSum = 0;
	for (const auto output : neuron->getOutputs())
		errorSum += output->getNextNeuron()->getError() * output->getWeight();
	return errorSum;
}

void NetworkTraining::forwardPropagate(LayerIterator *iterator) {
	if (!iterator->viewNextLayer()) {
		return;
	}
	for (const auto &neuron : iterator->viewCurrentLayer()->getNeurons()) {
		float value = calculateValue(neuron);
		neuron->setValue(value);
	}
	forwardPropagate(iterator->next());
}

void NetworkTraining::backPropagate(LayerIterator *iterator) {
	if (!iterator->viewPreviousLayer())
		return;
	for (const auto &neuron : iterator->viewCurrentLayer()->getNeurons()) {
		float error = calculateError(neuron);
                if (!iterator->viewNextLayer())
                        totalError_ += std::abs(error);
		neuron->setError(error);
		adjustWeights(neuron);
	}
	backPropagate(iterator->previous());
}

void NetworkTraining::adjustWeights(Neuron *neuron) {
	float activationValue = neuron->getOutputs().empty() ? calculateValue(neuron) : neuron->getValue();
	float derivative = activationValue * (1 - activationValue);
	for (const auto &input : neuron->getInputs()) {
		float adjustment = learningRate_ * neuron->getError() * derivative * input->getPreviousNeuron()->getValue();
		//std::cout << "ConnectedNeuron: " << input->getPreviousNeuron()->getValue() << " " << "CurrentNeuron: " << neuron->getValue() << " " << adjustment << std::endl;
		input->setWeight(input->getWeight() - adjustment);
	}
}

bool NetworkTraining::isTraining() {
	return (cycleNumber_ < epochs_);
}

void NetworkTraining::train(LayerIterator *iterator) {
        totalError_ = 0.f;
	cycleNumber_++;
	for (int outputIndex = 0; outputIndex < outputs_.size(); outputIndex++) {
		iterator->viewInputLayer()->setValues(inputs_[outputIndex]);
		forwardPropagate(iterator->startAtInputLayer());
		iterator->viewOutputLayer()->setValues(outputs_[outputIndex]);
		backPropagate(iterator->startAtOutputLayer());
	}
	if (render_)
		render_->update(totalError_);
}

std::vector<float> NetworkTraining::test(LayerIterator *iterator, const std::vector<float> &inputs) {
        std::vector<float> output;
	iterator->viewInputLayer()->setValues(inputs);
	forwardPropagate(iterator->startAtInputLayer());
	for (const auto &neuron : iterator->viewOutputLayer()->getNeurons()) {
                float result = calculateValue(neuron);
                output.push_back(result);
		neuron->setValue(result);
	}
        return output;
}
