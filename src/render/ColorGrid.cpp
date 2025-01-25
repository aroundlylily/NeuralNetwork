#include "ColorGrid.hpp"
#include "training/TrainingStrategy.hpp"
#include "structure/NeuralNetwork.hpp"

ColorGrid::ColorGrid(int width, int height, float scaleFactor)  // sf::Style::Close
        : windowActive_(false), width_(width), height_(height), scaleFactor_(scaleFactor)
{
        image_.create(width, height);
        sprite_.setScale(scaleFactor, scaleFactor);
}

std::vector<std::vector<double>> ColorGrid::getInputs() {
        return inputs_;
}

std::vector<std::vector<double>> ColorGrid::getOutputs() {
        return outputs_;
}

void ColorGrid::setPixelColor(int x, int y, float color) {
        image_.setPixel(x, y, sf::Color(color * 255, color * 255, color * 255));
}

sf::CircleShape ColorGrid::createCircle(sf::Vector2i position, float radius, sf::Color color) {
	sf::CircleShape circle(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(position.x, position.y);
	circle.setFillColor(color);
	return circle;
}

void ColorGrid::addBinaryClassification(bool value) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window_);
	float output = value;
        markers_.push_back(createCircle(mousePosition, 6.f, sf::Color(255 * !output, 255 * !output, 255 * !output)));
        markers_.push_back(createCircle(mousePosition, 5.f, sf::Color(255 * output, 255 * output, 255 * output)));
        inputs_.push_back({ mousePosition.x / width_ / scaleFactor_, mousePosition.y / height_ / scaleFactor_ });
        outputs_.push_back({ output });
}

bool ColorGrid::isOpen() {
        return window_.isOpen();
}

void ColorGrid::initialize() {
        freshGrid_ = true;
        if (!windowActive_) {
                window_.create(sf::VideoMode(width_ * scaleFactor_, height_ * scaleFactor_), "ColorGrid", sf::Style::Close);
                windowActive_ = true;
        }

        markers_.clear();
        inputs_.clear();
        outputs_.clear();

        for (int x = 0; x < width_; x++) {
                for (int y = 0; y < height_; y++) {
                        image_.setPixel(x, y, sf::Color::Black);
                }
        }

        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);
}

void ColorGrid::applyNetwork(TrainingStrategy &strategy, NeuralNetwork *network) {
        if (freshGrid_) {
                network->reset();
                freshGrid_ = false;
        }
	for (int horizontalIndex = 0; horizontalIndex < width_; ++horizontalIndex) {
		float horizontalRatio = 1.f * horizontalIndex / width_;
		for (int verticalIndex = 0; verticalIndex < height_; ++verticalIndex) {
			float verticalRatio = 1.f * verticalIndex / height_;
			float value = strategy.apply(network, { horizontalRatio, verticalRatio }).front();
			setPixelColor(horizontalIndex, verticalIndex, value);
		}
	}
        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);
}

void ColorGrid::draw() {
        while (window_.pollEvent(event_)) {
                if (event_.type == sf::Event::MouseButtonPressed && event_.mouseButton.button == sf::Mouse::Left)
                        addBinaryClassification(true);
                if (event_.type == sf::Event::MouseButtonPressed && event_.mouseButton.button == sf::Mouse::Right)
                        addBinaryClassification(false);
                if (event_.type == sf::Event::Closed)
                        window_.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        ColorGrid::initialize();
        }
        window_.clear();
        window_.draw(sprite_);
        for (const auto &marker : markers_)
                window_.draw(marker); window_.display(); }
