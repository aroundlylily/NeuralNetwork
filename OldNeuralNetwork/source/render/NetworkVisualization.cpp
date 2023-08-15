#include "../../include/NetworkStructure.hpp"

#include "../../include/render/NetworkVisualization.hpp"
#include "../../include/render/WeightRender.hpp"
#include "../../include/render/NeuronRender.hpp"
#include "../../include/render/ErrorRender.hpp"
#include "../../include/render/NeuronRender.hpp"

#include <iostream>

VisualizationSettings::VisualizationSettings(int windowWidth, int windowHeight, float neuronRadius, const std::string &fontFile, int characterSize)
	: windowWidth(windowWidth), windowHeight(windowHeight), neuronRadius(neuronRadius), fontFile(fontFile), characterSize(characterSize) {}

NetworkVisualization::NetworkVisualization(VisualizationSettings *settings)
	: settings_(settings), window_(sf::VideoMode(settings->windowWidth, settings->windowHeight), "NeuralNetwork", sf::Style::Close) {}

NetworkVisualization::~NetworkVisualization() {
        for (const auto &neuron : neurons_)
                delete neuron;
        for (const auto &weight : weights_)
                delete weight;
}

void NetworkVisualization::renderNeuron(Neuron *neuron, sf::Vector2f position) {
        sf::Color color;
        if (neuron->getOutputs().empty())
                color = sf::Color::Red;
        else if (neuron->getInputs().empty() && neuron->getError() == -1)
                color = sf::Color::Yellow;
        else if (neuron->getInputs().empty())
                color = sf::Color::Blue;
        else
                color = sf::Color::Green;
        NeuronRender *shape = new NeuronRender(settings_, neuron, position, color);
        neurons_.push_back(shape);
}

void NetworkVisualization::renderNeuronLayer(NeuronLayer *layer, float x) {
        std::vector<sf::Vector2f> positions;
        std::vector<Neuron *> neurons = layer->getNeurons();
        int neuronSize = neurons.size();
        float distance = (settings_->windowHeight - 2 * neuronSize * settings_->neuronRadius) / (1 + neuronSize);
        for (int neuronIndex = 0; neuronIndex < neuronSize; neuronIndex++) {
                float y = (1 + neuronIndex) * distance + settings_->neuronRadius * (1 + 2 * neuronIndex);
                renderNeuron(neurons[neuronIndex], { x, y });
                positions.push_back({ x, y });
        }
}

void NetworkVisualization::renderWeight(Weight *weight, sf::Vector2f start, sf::Vector2f end) {
        WeightRender *shape = new WeightRender(settings_, weight, start, end);
        weights_.push_back(shape);
}

void NetworkVisualization::renderError(TrainingStrategy *strategy) {
	ErrorRender *shape = new ErrorRender(settings_, strategy);
	errors_.push_back(shape);
}

void NetworkVisualization::renderNeuralNetwork(NeuralNetwork *network) {
        std::vector<NeuronLayer *> layers = network->getNeuronLayers();
        int layerSize = layers.size();
        float distance = (settings_->windowWidth - 2 * layerSize * settings_->neuronRadius) / (1 + layerSize);
        for (int layerIndex = 0; layerIndex < layerSize; layerIndex++) {
                float x = (1 + layerIndex) * distance + settings_->neuronRadius * (1 + 2 * layerIndex);
                renderNeuronLayer(layers[layerIndex], x);
        }
        for (const auto &weight : network->getWeights()) {
                Neuron *start = weight->getPreviousNeuron();
                Neuron *end = weight->getNextNeuron();
                renderWeight(weight, start->getPosition(), end->getPosition());
        }
}

bool NetworkVisualization::isOpen() {
	return window_.isOpen();
}

void NetworkVisualization::update() {
	while (window_.pollEvent(event_)) {
		if (event_.type == sf::Event::Closed) {
			window_.close();
		}
	}
}

void NetworkVisualization::draw() {
	window_.clear();
	update();
        for (const auto &weight : weights_)
                weight->draw(window_);
        for (const auto &neuron : neurons_)
                neuron->draw(window_);
	for (const auto &error : errors_)
		error->draw(window_);
	window_.display();
}
