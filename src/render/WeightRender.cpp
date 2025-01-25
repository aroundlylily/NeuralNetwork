#include "WeightRender.hpp"
#include "render/NetworkVisualization.hpp"

WeightRender::WeightRender(const VisualizationSettings &settings, sf::Vector2f start, sf::Vector2f end)
	: line_(sf::VertexArray(sf::Lines, 2))
{
        line_[0] = start;
        line_[1] = end;
}

void WeightRender::draw(sf::RenderWindow &window) const {
	window.draw(line_);
}

void WeightRender::update(float value, float layerMaximum) {
	int alpha = 255 * value / layerMaximum;
	sf::Color color = sf::Color(0, 255, 0, alpha);
	if (value < 0)
		color = sf::Color(255, 0, 0, alpha);
	line_[0].color = color;
	line_[1].color = color;
}
