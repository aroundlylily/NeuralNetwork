#include "../../include/structure/Neuron.hpp"
#include "../../include/structure/Weight.hpp"

#include "../../include/render/NeuronRender.hpp"

#include <iostream>
#include <cmath>
#include <vector>

Neuron::Neuron()
	: value_(0.f), error_(0.f),  shape_(nullptr) {}

void Neuron::setShape(NeuronRender *shape) {
        shape_ = shape;
	shape->update(value_);
}

void Neuron::setValue(float value) {
        if (shape_)
	        shape_->update(value);
	value_ = value;
}

float Neuron::getValue() {
	return value_;
}

void Neuron::setError(float error) {
	error_ = error;
}

float Neuron::getError() {
	return error_;
}

void Neuron::addWeight(float weight) {
	weights_.push_back(weight);
}

std::vector<float> Neuron::getWeights() {
	return weights_;
}

void Neuron::addInput(Weight *weight) {
	inputs_.push_back(weight);
}

std::vector<Weight *> Neuron::getInputs() {
	return inputs_;
}

void Neuron::addOutput(Weight *weight) {
	outputs_.push_back(weight);
}

std::vector<Weight *> Neuron::getOutputs() {
	return outputs_;
}

sf::Vector2f Neuron::getPosition() {
        if (!shape_)
                return { -1, -1 };
        return shape_->getPosition();
}
