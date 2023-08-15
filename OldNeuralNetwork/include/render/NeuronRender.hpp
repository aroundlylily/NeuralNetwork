#ifndef NEURONRENDER_HPP
#define NEURONRENDER_HPP

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

class Neuron;
struct VisualizationSettings;

class NeuronRender {
private:
        sf::CircleShape circle_;
        sf::Font font_;
        sf::Text text_;
	std::ostringstream stringStream_;

public:
        NeuronRender(VisualizationSettings *settings, Neuron *neuron, sf::Vector2f position, sf::Color color);
	sf::Vector2f getPosition();
        void positionText();
        void update(float value);
        void draw(sf::RenderWindow &window) const;
};

#endif
