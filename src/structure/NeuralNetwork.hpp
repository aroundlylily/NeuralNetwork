#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>

class NeuronLayer;
class TrainingStrategy;

class NeuralNetwork {
private:
	const std::vector<int> dimensions_;
	std::vector<NeuronLayer *> layers_;
        TrainingStrategy *trainingStrategy_;
        int iterations_;
        double error_;

public:
	NeuralNetwork(const std::vector<int> &dimensions);
	virtual ~NeuralNetwork();
	const std::vector<int> & dimensions() const;
	std::vector<NeuronLayer *> layers() const;
        void setTrainingStrategy(TrainingStrategy *trainingStrategy);
        bool hasCompletedTraining() const;
        void train(const std::vector<std::vector<double>> &inputs, const std::vector<std::vector<double>> &outputs);
        void reset();
        double error() const;
	void print() const;
};

#endif
