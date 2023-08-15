#ifndef WEIGHTRENDER_HPP
#define WEIGHTRENDER_HPP

#include <SFML/Graphics.hpp>

class Weight;
struct VisualizationSettings;

class WeightRender {
private:
	sf::VertexArray line_;

public:
	WeightRender(VisualizationSettings *settings, Weight *weight, sf::Vector2f start, sf::Vector2f end);
	void draw(sf::RenderWindow &window) const;
};

#endif
