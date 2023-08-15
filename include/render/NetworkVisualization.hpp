#ifndef NETWORKVISUALIZATION_HPP
#define NETWORKVISUALIZATION_HPP

#include <SFML/Graphics.hpp>
#include <iomanip>

class NeuronLayer;
class NeuralNetwork;
class TrainingStrategy;
class NeuronRender;
class WeightRender;
class TextRender;

struct VisualizationSettings {
	const int windowWidth;
	const int windowHeight;
	const float neuronRadius;
	const std::string fontFile;
	const int characterSize;
	VisualizationSettings(int windowWidth, int windowHeight, float neuronRadius, const std::string &fontFile, int characterSize);
};

struct LayerStructure {
	const int size;
	const float position;
	const bool hasBiasNeuron;
	LayerStructure(int size, float position, bool hasBiasNeuron);
};

class NetworkVisualization {
private:
	const VisualizationSettings settings_;
	NeuralNetwork *network_;
	sf::RenderWindow window_;
	sf::Event event_;
	std::vector<NeuronRender *> neurons_;
	std::vector<WeightRender *> weights_;
	std::vector<TextRender *> text_;

public:
        NetworkVisualization(const VisualizationSettings &settings);
	virtual ~NetworkVisualization();
	void renderNeuron(sf::Vector2f position, sf::Color color);
        void renderWeight(sf::Vector2f start, sf::Vector2f end);
	void renderText(const std::string &label, sf::Vector2f position);
        void renderLayer(const LayerStructure &layer, const LayerStructure &nextLayer, sf::Color color);
        void renderNetwork(const std::vector<int> &networkDimensions);
	void visualize(NeuralNetwork *network);
	void updateValues(NeuronLayer *layer, int neuronVisualizationIndex);
	void updateWeights(NeuronLayer *layer, int weightVisualizationIndex);
	void update();
	void clear();

private:
	float calculateDistance(int structureSize, float screenDimension);
	float calculatePosition(int structureIndex, float distance);
	sf::Color getLayerColor(int networkSize, int layerIndex);

public:
	bool isOpen();
	void updateWindow();
        void draw();
};

#endif
