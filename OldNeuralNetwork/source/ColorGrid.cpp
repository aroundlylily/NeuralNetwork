#include "../include/ColorGrid.hpp"

ColorGrid::ColorGrid(float width, float height, float scaleFactor)  // sf::Style::Close
        : window_(sf::VideoMode(width * scaleFactor, height * scaleFactor), "ColorGrid", sf::Style::Close), width_(width), height_(height), scaleFactor_(scaleFactor)
{
        image_.create(width, height);
        for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                        image_.setPixel(x, y, sf::Color::Black);
                }
        }
        sprite_.setScale(scaleFactor, scaleFactor);
}

std::vector<std::vector<float>> ColorGrid::getInputs() {
	return inputs_;
}

std::vector<std::vector<float>> ColorGrid::getOutputs() {
	return outputs_;
}

sf::RenderWindow & ColorGrid::getWindow() {
        return window_;
}

void ColorGrid::setPixelColor(int x, int y, float color) {
        image_.setPixel(x, y, sf::Color(color * 255, color * 255, color * 255));
}

void ColorGrid::addMarker() {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window_);

	sf::CircleShape border(6.f);
	border.setOrigin(6.f, 6.f);
	border.setPosition(mousePosition.x, mousePosition.y);

	sf::CircleShape marker(5.f);
	marker.setOrigin(5.f, 5.f);
	marker.setPosition(mousePosition.x, mousePosition.y);

	inputs_.push_back({ mousePosition.x / width_ / scaleFactor_, mousePosition.y / height_ / scaleFactor_ });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		marker.setFillColor(sf::Color::Black);
	        border.setFillColor(sf::Color::White);
		outputs_.push_back({ 0.f });
	}

	else {
		marker.setFillColor(sf::Color::White);
	        border.setFillColor(sf::Color::Black);
		outputs_.push_back({ 1.f });
	}

	markers_.push_back(border);
	markers_.push_back(marker);
}

void ColorGrid::getUserInput() {
	while (window_.pollEvent(event_)) {
		if (takingUserInput_ && event_.type == sf::Event::MouseButtonPressed)
			addMarker();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
			takingUserInput_ = false;
	}
}

void ColorGrid::update() {
	while (window_.pollEvent(event_)) {
		if (event_.type == sf::Event::Closed)
			window_.close();
	}
}

bool ColorGrid::isOpen() {
	return window_.isOpen();
}

bool ColorGrid::isTakingUserInput() {
	return takingUserInput_;
}

void ColorGrid::draw() {
	update();
        window_.clear();
        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);
        window_.draw(sprite_);
	for (const auto &marker : markers_)
		window_.draw(marker);
        window_.display();
}
