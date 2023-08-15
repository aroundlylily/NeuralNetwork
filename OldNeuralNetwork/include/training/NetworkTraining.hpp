#ifndef NETWORKTRAINING_HPP
#define NETWORKTRAINING_HPP

#include <vector>

#include "TrainingStrategy.hpp"

class Neuron;
class NeuronLayer;
class NeuralNetwork;
class LayerIterator;
class ErrorRender;

class NetworkTraining : public TrainingStrategy {
private:
	float learningRate_;
        float totalError_;
	int epochs_;
	int cycleNumber_;
	std::vector<std::vector<float>> inputs_;
	std::vector<std::vector<float>> outputs_;
	ErrorRender *render_;

public:
	NetworkTraining(float learningRate, int epochs);
	void setRender(ErrorRender *render) override;
	void setInputs(const std::vector<std::vector<float>> &inputs);
	void setOutputs(const std::vector<std::vector<float>> &outputs);
	float applySigmoid(float x);
	float calculateValue(Neuron *neuron);
	float calculateError(Neuron *neuron);
	void forwardPropagate(LayerIterator *iterator);
	void backPropagate(LayerIterator *iterator);
	void adjustWeights(Neuron *neuron);
	bool isTraining();
	void train(LayerIterator *iterator);
        std::vector<float> test(LayerIterator *iterator, const std::vector<float> &inputs);
};

#endif
