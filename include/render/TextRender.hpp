#ifndef TEXTRENDER_HPP
#define TEXTRENDER_HPP

#include <string>
#include <SFML/Graphics.hpp>

class TrainingStrategy;
struct VisualizationSettings;

class TextRender {
private:
	sf::Font font_;
	sf::Text text_;
	std::string label_;

public:
	TextRender(const VisualizationSettings &settings, const std::string &text, sf::Vector2f position);
	void update(const std::string &text);
	void draw(sf::RenderWindow &window) const;
};

#endif
