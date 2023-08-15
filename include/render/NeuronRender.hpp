#ifndef NEURONRENDER_HPP
#define NEURONRENDER_HPP

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

struct VisualizationSettings;

class NeuronRender {
private:
        sf::CircleShape circle_;
        sf::Font font_;
        sf::Text text_;
	std::ostringstream stringStream_;

public:
        NeuronRender(const VisualizationSettings &settings, sf::Vector2f position, sf::Color color);

private:
        void positionText();

public:
        void update(float value);
        void draw(sf::RenderWindow &window) const;
};

#endif
