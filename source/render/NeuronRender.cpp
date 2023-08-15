#include "../../include/render/NeuronRender.hpp"
#include "../../include/render/NetworkVisualization.hpp"

NeuronRender::NeuronRender(const VisualizationSettings &settings, sf::Vector2f position, sf::Color color) {
        font_.loadFromFile(settings.fontFile);
        text_.setFont(font_);
        text_.setCharacterSize(settings.characterSize);
        text_.setFillColor(sf::Color::Black);
        text_.setStyle(sf::Text::Bold);
        float radius = settings.neuronRadius;
        circle_.setRadius(radius);
        circle_.setFillColor(color);
        circle_.setOrigin(radius, radius);
        circle_.setPosition(position);
}

void NeuronRender::positionText() {
        sf::FloatRect shapeBounds = circle_.getGlobalBounds();
        sf::FloatRect textBounds = text_.getLocalBounds();
        text_.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
        text_.setPosition(shapeBounds.left + shapeBounds.width / 2.f, shapeBounds.top + shapeBounds.height / 2.f);
}

void NeuronRender::update(float value) {
        stringStream_.str(""); 
        stringStream_ << std::fixed << std::setprecision(2) << value;
        text_.setString(stringStream_.str());
        positionText();
}

void NeuronRender::draw(sf::RenderWindow &window) const {
        window.draw(circle_);
        window.draw(text_);
}
