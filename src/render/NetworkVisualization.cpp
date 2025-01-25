#include "NetworkVisualization.hpp"

#include "NeuronRender.hpp"
#include "TextRender.hpp"
#include "WeightRender.hpp"

#include "structure/NeuronLayer.hpp"
#include "structure/NeuralNetwork.hpp"

VisualizationSettings::VisualizationSettings(int windowWidth, int windowHeight, float neuronRadius, const std::string &fontFile, int characterSize)
	: windowWidth(windowWidth), windowHeight(windowHeight), neuronRadius(neuronRadius), fontFile(fontFile), characterSize(characterSize) {}

LayerStructure::LayerStructure(int size, float position, bool hasBiasNeuron)
	: size(size + hasBiasNeuron), position(position), hasBiasNeuron(hasBiasNeuron) {}

NetworkVisualization::NetworkVisualization(const VisualizationSettings &settings)
	: settings_(settings), network_(nullptr), windowActive_(false) {}

NetworkVisualization::~NetworkVisualization() {
	clear();
}

void NetworkVisualization::renderNeuron(sf::Vector2f position, sf::Color color) {
	if (network_)
		return;
        NeuronRender *neuronRender = new NeuronRender(settings_, position, color);
        neurons_.push_back(neuronRender);
}

void NetworkVisualization::renderWeight(sf::Vector2f start, sf::Vector2f end) {
	if (network_)
		return;
        WeightRender *weightRender = new WeightRender(settings_, start, end);
        weights_.push_back(weightRender);
}

void NetworkVisualization::renderText(const std::string &label, sf::Vector2f position) {
	if (network_)
		return;
	TextRender *textRender = new TextRender(settings_, label, position);
	text_.push_back(textRender);
}

void NetworkVisualization::renderLayer(const LayerStructure &layer, const LayerStructure &nextLayer, sf::Color color) {
	float verticalDistance = calculateDistance(layer.size, settings_.windowHeight), nextVerticalDistance = calculateDistance(nextLayer.size, settings_.windowHeight);
        for (int neuronIndex = 0; neuronIndex < layer.size; ++neuronIndex) {
                float verticalPosition = calculatePosition(neuronIndex, verticalDistance);
		for (int nextNeuronIndex = 0; nextNeuronIndex < nextLayer.size - nextLayer.hasBiasNeuron; ++nextNeuronIndex) {
                	float nextVerticalPosition = calculatePosition(nextNeuronIndex, nextVerticalDistance);
			renderWeight({ layer.position, verticalPosition }, { nextLayer.position, nextVerticalPosition });
		}
		if (neuronIndex == layer.size - 1 && layer.hasBiasNeuron)
			color = sf::Color::Yellow;
		renderNeuron({ layer.position, verticalPosition }, color);
        }
}

void NetworkVisualization::renderNetwork(const std::vector<int> &networkDimensions) {
	int networkSize = networkDimensions.size();
	float horizontalDistance = calculateDistance(networkSize, settings_.windowWidth);
	for (int layerIndex = 0; layerIndex < networkSize; ++layerIndex) {
		int nextLayerSize = 0;
		const LayerStructure layer(networkDimensions[layerIndex], calculatePosition(layerIndex, horizontalDistance), layerIndex < networkSize - 1);
		if (layer.hasBiasNeuron)
			nextLayerSize = networkDimensions[layerIndex + 1];
		const LayerStructure nextLayer(nextLayerSize, layer.position + horizontalDistance + 2 * settings_.neuronRadius, layerIndex < networkSize - 2);
		renderLayer(layer, nextLayer, getLayerColor(networkSize, layerIndex));
	}
}

void NetworkVisualization::visualize(NeuralNetwork *network) {
        if (!windowActive_) {
                windowActive_ = true;
                window_.create(sf::VideoMode(settings_.windowWidth, settings_.windowHeight), "NeuralNetwork", sf::Style::Close);
        }
	clear();
	renderNetwork(network->dimensions());
	renderText("Total Error: ", { 0, 0 });
	network_ = network;
}

float NetworkVisualization::calculateDistance(int structureSize, float screenDimension) {
	return (screenDimension - 2 * structureSize * settings_.neuronRadius) / (1 + structureSize);
}

float NetworkVisualization::calculatePosition(int structureIndex, float distance) {
	return (1 + structureIndex) * distance + settings_.neuronRadius * (1 + 2 * structureIndex);
}

sf::Color NetworkVisualization::getLayerColor(int networkSize, int layerIndex) {
	if (layerIndex == 0)
		return sf::Color::Blue;
	else if (layerIndex == networkSize - 1)
		return sf::Color::Red;
	return sf::Color::Green;
}

void NetworkVisualization::updateValues(NeuronLayer *layer, int neuronVisualizationIndex) {
	const std::vector<double> &values = layer->values();
	if (values.empty())
		return;
	for (int valueIndex = 0; valueIndex < values.size(); ++valueIndex) {
		neurons_[neuronVisualizationIndex++]->update(values[valueIndex]);
	}
}

void NetworkVisualization::updateWeights(NeuronLayer *layer, int weightVisualizationIndex) {
	const std::vector<double> &weights = layer->weights();
	if (weights.empty())
		return;
	double layerMaximum = 0.f;
	for (int weightIndex = 0; weightIndex < weights.size(); ++weightIndex) {
		if (weights[weightIndex] > layerMaximum)
			layerMaximum = weights[weightIndex];
	}
	for (int weightIndex = 0; weightIndex < weights.size(); ++weightIndex)
		weights_[weightVisualizationIndex++]->update(weights[weightIndex], layerMaximum);
}

void NetworkVisualization::update() {
	if (!network_)
		return;
	const std::vector<NeuronLayer *> layers = network_->layers();
	int neuronVisualizationIndex = 0;
	int weightVisualizationIndex = 0;
	for (const auto &layer : layers) {
		updateValues(layer, neuronVisualizationIndex);
		updateWeights(layer, weightVisualizationIndex);
		neuronVisualizationIndex += layer->values().size();
		weightVisualizationIndex += layer->weights().size();
	}
	text_.front()->update(std::to_string(network_->error()));
}

void NetworkVisualization::clear() {
	network_ = nullptr;
	for (const auto &neuron : neurons_)
		delete neuron;
	for (const auto &weight : weights_)
		delete weight;
	for (const auto &text : text_)
		delete text;
	neurons_.clear();
	weights_.clear();
	text_.clear();
}

bool NetworkVisualization::isOpen() {
	return window_.isOpen();
}

void NetworkVisualization::draw() {
	while (window_.pollEvent(event_)) {
		if (event_.type == sf::Event::Closed)
			window_.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && network_)
                        network_->reset();
        }
	window_.clear();
	for (const auto &weight : weights_)
		weight->draw(window_);
	for (const auto &neuron : neurons_)
		neuron->draw(window_);
	for (const auto &text : text_)
		text->draw(window_);
	window_.display();
}
