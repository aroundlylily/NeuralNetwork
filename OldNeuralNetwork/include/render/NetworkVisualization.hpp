#ifndef NETWORKVISUALIZATION_HPP
#define NETWORKVISUALIZATION_HPP

#include <SFML/Graphics.hpp>
#include <iomanip>

class Neuron;
class NeuronRender;
class Weight;
class WeightRender;
class NeuronLayer;
class NeuralNetwork;
class TrainingStrategy;
class ErrorRender;

struct VisualizationSettings {
	int windowWidth;
	int windowHeight;
	float neuronRadius;
	std::string fontFile;
	int characterSize;
	VisualizationSettings(int windowWidth, int windowHeight, float neuronRadius, const std::string &fontFile, int characterSize);
};

class NetworkVisualization {
private:
	VisualizationSettings *settings_;
	sf::RenderWindow window_;
	sf::Event event_;
        std::vector<NeuronRender *> neurons_;
        std::vector<WeightRender *> weights_;
	std::vector<ErrorRender *> errors_;

public:
        NetworkVisualization(VisualizationSettings *settings);
	virtual ~NetworkVisualization();
        void renderNeuron(Neuron *neuron, sf::Vector2f position);
        void renderNeuronLayer(NeuronLayer *layer, float x);
        void renderNeuralNetwork(NeuralNetwork *network);
        void renderWeight(Weight *weight, sf::Vector2f start, sf::Vector2f end);
	void renderError(TrainingStrategy *strategy);
	bool isOpen();
	void update();
        void draw();
};

#endif
