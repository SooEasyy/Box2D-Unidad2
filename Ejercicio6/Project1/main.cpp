#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "Cannon Game");
    window.setFramerateLimit(60);

    Texture cannonTexture;
    if (!cannonTexture.loadFromFile("cannon.png")) {
        return 1;
    }

    cannonTexture.setSmooth(true);

    Sprite cannonSprite(cannonTexture);
    cannonSprite.setScale(0.5f, 0.5f);
    cannonSprite.setOrigin(cannonSprite.getGlobalBounds().width, cannonSprite.getGlobalBounds().height);
    cannonSprite.setPosition(80.0f, window.getSize().y - 500.0f);

    vector<CircleShape> projectiles;
    vector<Vector2f> velocities; 

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f targetPosition(event.mouseButton.x, event.mouseButton.y);
                Vector2f cannonPosition = cannonSprite.getPosition();
                Vector2f direction = targetPosition - cannonPosition;

                float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                direction /= length;

                CircleShape projectile(10);
                projectile.setFillColor(Color::Red);
                projectile.setPosition(cannonPosition);

                float speed = 5.0f; 
                Vector2f velocity = direction * speed;

                projectiles.push_back(projectile);
                velocities.push_back(velocity);
            }
        }

        for (size_t i = 0; i < projectiles.size(); ++i) {
            projectiles[i].move(velocities[i]); 

            if (projectiles[i].getPosition().x > window.getSize().x || projectiles[i].getPosition().y > window.getSize().y ||
                projectiles[i].getPosition().x < 0 || projectiles[i].getPosition().y < 0) {
                projectiles.erase(projectiles.begin() + i);
                velocities.erase(velocities.begin() + i); 
                --i; 
            }
        }

        window.clear(Color::Black);

        window.draw(cannonSprite);

        for (const auto& projectile : projectiles) {
            window.draw(projectile);
        }

        window.display();
    }

    return 0;
}