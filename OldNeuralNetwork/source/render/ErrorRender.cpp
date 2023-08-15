#include "../../include/render/ErrorRender.hpp"
#include "../../include/training/TrainingStrategy.hpp"
#include "../../include/render/NetworkVisualization.hpp"

#include <cmath>

ErrorRender::ErrorRender(VisualizationSettings *settings, TrainingStrategy *strategy) {
	font_.loadFromFile(settings->fontFile);
	text_.setFont(font_);
	text_.setPosition({ 0, 0 });
	text_.setCharacterSize(20);
	text_.setFillColor(sf::Color::White);
	text_.setStyle(sf::Text::Bold);
	strategy->setRender(this);
}

void ErrorRender::update(float value) {
	text_.setString("Total error: " + std::to_string(std::abs(value)));
}

void ErrorRender::draw(sf::RenderWindow &window) const {
	window.draw(text_);
}
