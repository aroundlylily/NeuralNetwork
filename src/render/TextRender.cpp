#include "TextRender.hpp"
#include "render/NetworkVisualization.hpp"

TextRender::TextRender(const VisualizationSettings &settings, const std::string &label, sf::Vector2f position)
: label_(label) 
{
	font_.loadFromFile(settings.fontFile);
	text_.setFont(font_);
	text_.setPosition(position);
	text_.setCharacterSize(20);
	text_.setFillColor(sf::Color::White);
	text_.setStyle(sf::Text::Bold);
}

void TextRender::update(const std::string &text) {
	text_.setString(label_ + text);
}

void TextRender::draw(sf::RenderWindow &window) const {
	window.draw(text_);
}
