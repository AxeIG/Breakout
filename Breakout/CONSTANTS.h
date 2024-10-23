#pragma once

// implemented powerups
enum POWERUPS
{
    bigPaddle,
    smallPaddle,
    fastBall,
    slowBall,
    fireBall,
    none
};

// Window settings
constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;
constexpr const char* WINDOW_TITLE = "Game";


// Paddle settings
constexpr float PADDLE_WIDTH = 150.0f;
constexpr float PADDLE_HEIGHT = 20.0f;
constexpr float PADDLE_SPEED = 300.0f;

// Ball settings
constexpr float BALL_RADIUS = 10.0f;
constexpr float BALL_SPEED = 400.0f;

// Brick settings
constexpr float BRICK_WIDTH = 75.0f;
constexpr float BRICK_HEIGHT = 20.0f;
constexpr float BRICK_PADDING = 5.0f;
constexpr int BRICK_ROWS = 5;
constexpr int BRICK_COLUMNS = 10;

// Particle setting
constexpr float PARTICLE_SIZE = 15.0f;
constexpr float TRAIL_SIZE = 6.0f;
constexpr float PARTICLE_OFFSET = 15.0f;
constexpr float PARTICLE_SPEED = 40.0f;
constexpr float PARTICLE_TIME_SPAN = 0.5f;
constexpr float NUMBER_OF_PARTICLES = 5.0f;

//Trail Settings


// Power-up settings
constexpr float POWERUP_RADIUS = 15.0f;
constexpr float POWERUP_SPEED = 150.0f;

// UI settings
constexpr float UI_LIFE_RADIUS = 15.0f;
constexpr float UI_LIFE_PADDING = 20.0f;

// Other game settings
constexpr float PAUSE_TIME_BUFFER = 0.5f;
constexpr float POWERUP_FREQUENCY = 7.5f;
constexpr int INITIAL_LIVES = 3;

// Colour Palette
const sf::Color paddleEffectsColour = sf::Color(100, 100, 200); // blue-ish?
const sf::Color speedEffectColour = sf::Color(255, 250, 205); // lemon chiffon -- very fancy.
const sf::Color fireballEffectColour = sf::Color(212, 94, 56); // fier-like red


