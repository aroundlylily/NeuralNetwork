#include "../../include/render/ColorGrid.hpp"
#include "../../include/NetworkStructure.hpp"
#include "../../include/training/TrainingStrategy.hpp"

ColorGrid::ColorGrid(int width, int height, float scaleFactor)  // sf::Style::Close
        : window_(sf::VideoMode(width * scaleFactor, height * scaleFactor), "ColorGrid", sf::Style::Close), width_(width), height_(height), scaleFactor_(scaleFactor), takingUserInput_(true)
{
        image_.create(width, height);
        for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                        image_.setPixel(x, y, sf::Color::Black);
                }
        }
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

void ColorGrid::addBinaryClassification() {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window_);
	float output = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		output = 1;
        markers_.push_back(createCircle(mousePosition, 6.f, sf::Color(255 * !output, 255 * !output, 255 * !output)));
        markers_.push_back(createCircle(mousePosition, 5.f, sf::Color(255 * output, 255 * output, 255 * output)));
        inputs_.push_back({ mousePosition.x / width_ / scaleFactor_, mousePosition.y / height_ / scaleFactor_ });
        outputs_.push_back({ output });
}

void ColorGrid::getUserInput() {
        while (window_.pollEvent(event_)) {
                if (takingUserInput_ && event_.type == sf::Event::MouseButtonPressed)
                        addBinaryClassification();
                if (event_.type == sf::Event::Closed)
                        window_.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
                        takingUserInput_ = false;
        }
}

void ColorGrid::updateWindow() {
        while (window_.pollEvent(event_)) {
                if (event_.type == sf::Event::Closed)
                        window_.close();
        }
}

bool ColorGrid::isOpen() {
        return window_.isOpen();
}

void ColorGrid::initialize() {
	while (takingUserInput_ && window_.isOpen()) {
		draw();
		getUserInput();
	}
}

void ColorGrid::applyNetwork(TrainingStrategy &strategy, NeuralNetwork *network) {
	for (int horizontalIndex = 0; horizontalIndex < width_; ++horizontalIndex) {
		float horizontalRatio = 1.f * horizontalIndex / width_;
		for (int verticalIndex = 0; verticalIndex < height_; ++verticalIndex) {
			float verticalRatio = 1.f * verticalIndex / height_;
			float value = strategy.run(network, { horizontalRatio, verticalRatio })[0];
			setPixelColor(horizontalIndex, verticalIndex, strategy.run(network, { horizontalRatio, verticalRatio })[0]);
		}
	}
}

void ColorGrid::draw() {
        updateWindow();
        window_.clear();
        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);
        window_.draw(sprite_);
        for (const auto &marker : markers_)
                window_.draw(marker);
        window_.display();
}
