#ifndef COLORGRID_HPP
#define COLORGRID_HPP

#include <SFML/Graphics.hpp>
#include <functional>

class NeuralNetwork;
class TrainingStrategy;

class ColorGrid {
private:
        sf::RenderWindow window_;
        int width_;
        int height_;
        float scaleFactor_;
        sf::Image image_;
        sf::Texture texture_;
        sf::Sprite sprite_;
        sf::Event event_;
        std::vector<sf::CircleShape> markers_;
        std::vector<std::vector<double>> inputs_;
        std::vector<std::vector<double>> outputs_;
        bool takingUserInput_;

public:
        ColorGrid(int width, int height, float scaleFactor);
        std::vector<std::vector<double>> getInputs();
        std::vector<std::vector<double>> getOutputs();
        sf::Color getPixelColor(int x, int y);
        void setPixelColor(int x, int y, float color);

private:
	sf::CircleShape createCircle(sf::Vector2i position, float radius, sf::Color color);
        void addBinaryClassification();
        void getUserInput();

public:
        void updateWindow();
        bool isOpen();
        void initialize();
	void applyNetwork(TrainingStrategy &strategy, NeuralNetwork *network);
        void draw();
};

#endif
