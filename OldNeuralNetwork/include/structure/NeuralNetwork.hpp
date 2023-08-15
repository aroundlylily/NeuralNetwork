#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>

class NeuronLayer;
class Weight;
class PropagationStrategy;

class NeuralNetwork {
private:
        std::vector<Weight *> weights_;
        std::vector<NeuronLayer *> layers_;

public:
        virtual ~NeuralNetwork();
        void addNeuronLayer(int count);
        std::vector<Weight *> getWeights();
        std::vector<NeuronLayer *> getNeuronLayers();
};

#endif
