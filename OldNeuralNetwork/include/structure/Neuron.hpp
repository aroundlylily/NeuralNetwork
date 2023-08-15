#ifndef NEURON_HPP
#define NEURON_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class NeuronRender;
class Weight;

class Neuron {
private:
	float value_;
	float error_;
	std::vector<Weight *> inputs_;
	std::vector<Weight *> outputs_;
        NeuronRender *shape_;
	std::vector<float> weights_;

public:	
        Neuron();
        void setShape(NeuronRender *shape);
	void setValue(float value);
	float getValue();
	void setError(float error);
	float getError();
	void addWeight(float weight);
	std::vector<float> getWeights();
	void addInput(Weight *weight);
	std::vector<Weight *> getInputs();
	void addOutput(Weight *weight);
	std::vector<Weight *> getOutputs();
        sf::Vector2f getPosition();
};

#endif
