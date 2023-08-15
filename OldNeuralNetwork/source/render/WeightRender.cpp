#include "../../include/render/WeightRender.hpp"
#include "../../include/render/NetworkVisualization.hpp"

#include <iostream>

WeightRender::WeightRender(VisualizationSettings *settings, Weight *weight, sf::Vector2f start, sf::Vector2f end)
	: line_(sf::VertexArray(sf::Lines, 2))
{
        line_[0] = start;
        line_[1] = end;
}

void WeightRender::draw(sf::RenderWindow &window) const {
	window.draw(line_);
}
