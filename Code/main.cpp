#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 700;
const float PLAYER_SPEED = 3.0f;
const float ENEMY_SPEED = 1.5f;
const float BULLET_SPEED = 7.0f;
const float SAFE_ZONE_SHRINK_RATE = 0.1f;

class Entity {
protected:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;
    int health;

public:
    Entity(float x, float y, float radius, sf::Color color, float speed, int health) : speed(speed), health(health) {
        shape.setPosition(x, y);
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setOrigin(radius, radius);
    }

    void move() {
        shape.move(velocity);
    }

    bool isAlive() const { 
        return health > 0; }

    void takeDamage(int amount) {
         health -= amount; }
    
    sf::Vector2f getPosition() const {
         return shape.getPosition(); }

    float getRadius() const { 
        return shape.getRadius(); }

    sf::CircleShape& getShape() { 
        return shape; }
};

class Player : public Entity {
public:
    Player() : Entity(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 15, sf::Color::Green, PLAYER_SPEED, 100) {}

    void handleInput(sf::RenderWindow& window) {
        velocity = {0, 0};
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity.y -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity.y += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x += speed;
    }
};

class Enemy : public Entity {
public:
    Enemy(float x, float y) : Entity(x, y, 12, sf::Color::Red, ENEMY_SPEED, 50) {}

    void update(const sf::Vector2f& playerPos) {
        sf::Vector2f direction = playerPos - shape.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        
        if (length > 0) {
            direction /= length;
            velocity = direction * speed;
        }
    }
};

class Bullet : public Entity {
public:
    Bullet(float x, float y, float dirX, float dirY) : Entity(x, y, 5, sf::Color::Yellow, BULLET_SPEED, 1) {
        float length = std::sqrt(dirX * dirX + dirY * dirY);
        if (length > 0) {
            velocity.x = (dirX / length) * speed;
            velocity.y = (dirY / length) * speed;
        }
    }
};

class SafeZone {
private:
    sf::CircleShape shape;
    float shrinkRate;
    float minRadius;

public:
    SafeZone() : shrinkRate(SAFE_ZONE_SHRINK_RATE), minRadius(50.0f) {
        shape.setRadius(std::min(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
        shape.setPosition(WINDOW_WIDTH / 2 - shape.getRadius(), WINDOW_HEIGHT / 2 - shape.getRadius());
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(2.0f);
        shape.setOutlineColor(sf::Color::Blue);
    }

    void update() {
        float currentRadius = shape.getRadius();
        if (currentRadius > minRadius) {
            currentRadius -= shrinkRate;
            shape.setRadius(currentRadius);
            shape.setPosition(WINDOW_WIDTH / 2 - currentRadius, WINDOW_HEIGHT / 2 - currentRadius);
        }
    }

    bool isInside(const sf::Vector2f& position) const {
        sf::Vector2f center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        float distance = std::sqrt(
            std::pow(position.x - center.x, 2) + std::pow(position.y - center.y, 2)
        );
        return distance < shape.getRadius();
    }

    sf::CircleShape& getShape() { 
        return shape; }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "The Last Helldiver");
    window.setFramerateLimit(60);
    
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    SafeZone safeZone;
    
    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error loading font!\n";
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    
    for (int i = 0; i < 5; i++) {
        float x = std::rand() % WINDOW_WIDTH;
        float y = std::rand() % WINDOW_HEIGHT;
        enemies.emplace_back(x, y);
    }
    
    sf::Clock clock;
    float timeSinceLastSpawn = 0.0f;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f playerPos = player.getPosition();
                float dirX = mousePos.x - playerPos.x;
                float dirY = mousePos.y - playerPos.y;
                bullets.emplace_back(playerPos.x, playerPos.y, dirX, dirY);
            }
        }
        
        float deltaTime = clock.restart().asSeconds();
        timeSinceLastSpawn += deltaTime;
        
        player.handleInput(window);
        player.move();
        
        for (auto it = bullets.begin(); it != bullets.end(); ) {
            it->move();
            
            sf::Vector2f pos = it->getPosition();
            if (pos.x < 0 || pos.x > WINDOW_WIDTH || pos.y < 0 || pos.y > WINDOW_HEIGHT) {
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }
        
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            enemyIt->update(player.getPosition());
            enemyIt->move();
            
            bool enemyHit = false;
            for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
                float dx = bulletIt->getPosition().x - enemyIt->getPosition().x;
                float dy = bulletIt->getPosition().y - enemyIt->getPosition().y;
                float distance = std::sqrt(dx * dx + dy * dy);
                
                if (distance < (bulletIt->getRadius() + enemyIt->getRadius())) {
                    enemyIt->takeDamage(25);
                    bulletIt = bullets.erase(bulletIt);
                    if (!enemyIt->isAlive()) {
                        score += 10;
                        enemyHit = true;
                    }
                    break;
                } else {
                    ++bulletIt;
                }
            }
            
            if (enemyHit) {
                enemyIt = enemies.erase(enemyIt);
            } else {
                float dx = player.getPosition().x - enemyIt->getPosition().x;
                float dy = player.getPosition().y - enemyIt->getPosition().y;
                float distance = std::sqrt(dx * dx + dy * dy);
                
                if (distance < (player.getRadius() + enemyIt->getRadius())) {
                    player.takeDamage(1);
                }
                
                ++enemyIt;
            }
        }
        
        safeZone.update();
        
        if (!safeZone.isInside(player.getPosition())) {
            player.takeDamage(1);
        }
        
        if (timeSinceLastSpawn > 3.0f && enemies.size() < 10) {
            float x = std::rand() % WINDOW_WIDTH;
            float y = std::rand() % WINDOW_HEIGHT;
            enemies.emplace_back(x, y);
            timeSinceLastSpawn = 0.0f;
        }
        
        scoreText.setString("Score: " + std::to_string(score) + " | Health: " + std::to_string(player.isAlive() ? 100 : 0));
        
        window.clear(sf::Color(50, 50, 50));
        
        window.draw(safeZone.getShape());
        
        for (auto& bullet : bullets) {
            window.draw(bullet.getShape());
        }
        
        for (auto& enemy : enemies) {
            window.draw(enemy.getShape());
        }
        
        window.draw(player.getShape());
        
        window.draw(scoreText);
        
        window.display();
        
        if (!player.isAlive()) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("Game Over! Final Score: " + std::to_string(score));
            gameOverText.setCharacterSize(32);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setPosition(
                WINDOW_WIDTH / 2 - gameOverText.getLocalBounds().width / 2,
                WINDOW_HEIGHT / 2 - gameOverText.getLocalBounds().height / 2
            );
            
            window.clear(sf::Color(50, 50, 50));
            window.draw(gameOverText);
            window.display();
            
            sf::sleep(sf::seconds(3));
            window.close();
        }
    }
    
    return 0;
}