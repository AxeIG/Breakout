#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "CONSTANTS.h"

class Paddle 
{
public:
    Paddle(sf::RenderWindow* window);
    ~Paddle();

    void moveLeft(float dt);
    void moveRight(float dt);
    void mouseDrag(int mouseX);
    void update(float dt);
    void render();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);
    void setFillColour(sf::Color colour) { _sprite.setFillColor(colour); }

    void calculateMouseOffset(int x);
    bool isDragged() { return _isDragged; }
    void setDragged(bool val) { _isDragged = val; }
    sf::Color getColour() { return _colour; };

private:


    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
    int _offset;
    sf::Color _colour;

    bool _isDragged;
};
