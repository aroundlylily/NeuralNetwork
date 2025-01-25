#ifndef TRAININGSTRATEGY_HPP
#define TRAININGSTRATEGY_HPP

#include <vector>
#include <cmath>
#include <random>

class NeuronLayer;
class NeuralNetwork;
class ActivationFunction;

class TrainingStrategy {
private:
	double learningRate_;
	const ActivationFunction &activationFunction_;
	ActivationFunction *outputScalingFunction_;
	int epochs_;
	double restartThreshold_;
	std::random_device device_;
	std::uniform_real_distribution<double> distribution_;
	std::mt19937 generator_;
	double previousTotalError_;

public:
	TrainingStrategy(double learningRate, const ActivationFunction &function, int epochs, double restartThreshold);
	void setInputs(NeuronLayer *inputLayer, const std::vector<double> &inputs);
	void setScalingFunction(ActivationFunction *scalingFunction);
	double calculateOutputError(NeuronLayer *outputLayer, const std::vector<double> &outputs);
	void initializeWeights(const std::vector<NeuronLayer *> &layers);

private:
	void applyScalingFunction(NeuronLayer *outputLayer);
	void calculateValues(NeuronLayer *currentLayer, NeuronLayer *nextLayer, bool hasBiasNeuron);
	void calculateErrors(NeuronLayer *previousLayer, NeuronLayer *currentLayer, bool hasBiasNeuron);
        void adjustWeights(NeuronLayer *previousLayer, NeuronLayer *currentLayer, bool hasBiasNeuron);
	void resetStructure(std::vector<double> &structure, bool hasBiasNeuron);
	void applyActivationFunction(std::vector<double> &values, bool hasBiasNeuron);

public:
	void forwardPropagate(const std::vector<NeuronLayer *> &layers, int layerIndex);
	void backPropagate(const std::vector<NeuronLayer *> &layers, int layerIndex);
	bool hasCompleted(int iteration);
	double train(const NeuralNetwork *network, int iteration, const std::vector<std::vector<double>> &inputs, const std::vector<std::vector<double>> &outputs);
	std::vector<double> apply(const NeuralNetwork *network, const std::vector<double> inputs);
};

#endif
