#ifndef ERRORRENDER_HPP
#define ERRORRENDER_HPP

#include <SFML/Graphics.hpp>

class TrainingStrategy;
struct VisualizationSettings;

class ErrorRender {
private:
	sf::Font font_;
	sf::Text text_;

public:
	ErrorRender(VisualizationSettings *settings, TrainingStrategy *strategy);
	void update(float value);
	void draw(sf::RenderWindow &window) const;
};

#endif
