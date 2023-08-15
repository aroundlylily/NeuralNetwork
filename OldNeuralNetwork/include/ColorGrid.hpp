#ifndef COLORGRID_HPP
#define COLORGRID_HPP

#include <SFML/Graphics.hpp>

class ColorGrid {
private:
        sf::RenderWindow window_;
        const float width_;
        const float height_;
	const float scaleFactor_;
        sf::Image image_;
        sf::Texture texture_;
        sf::Sprite sprite_;
	sf::Event event_;
	std::vector<sf::CircleShape> markers_;
	std::vector<std::vector<float>> inputs_;
	std::vector<std::vector<float>> outputs_;
	bool takingUserInput_;

public:
        ColorGrid(float width, float height, float scaleFactor);
	std::vector<std::vector<float>> getInputs();
	std::vector<std::vector<float>> getOutputs();
        sf::RenderWindow & getWindow();
        sf::Color getPixelColor(int x, int y);
        void setPixelColor(int x, int y, float color);
        std::vector<float> getRelativePosition(int x, int y);
        void setRelativePixelColor(float x, float y, float color);
	void addMarker();
	void getUserInput();
	void update();
	bool isOpen();
	bool isTakingUserInput();
        void draw();
};

#endif
