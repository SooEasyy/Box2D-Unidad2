#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf; 

const float SCALE = 30.f;
const float DEG_TO_RAD = 0.017453f;

int main() {
    RenderWindow window(VideoMode(800, 600), "SFML + Box2D");
    window.setFramerateLimit(60);

    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(400.0f, 0.5f, b2Vec2(400.0f / SCALE, 600.0f / SCALE), 35 * DEG_TO_RAD);
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 10.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        world.Step(1 / 60.f, 8, 3);

        window.clear(Color::Black);

        ConvexShape ground;
        ground.setPointCount(4);
        ground.setPoint(0, Vector2f(0.0f, 0.0f));
        ground.setPoint(1, Vector2f(800.0f, 0.0f));
        ground.setPoint(2, Vector2f(800.0f, 600.0f));
        ground.setPoint(3, Vector2f(0.0f, 600.0f));
        ground.setFillColor(Color::Green);
        ground.setRotation(35.0f);
        window.draw(ground);

        RectangleShape box(Vector2f(2.0f * SCALE, 2.0f * SCALE));
        box.setFillColor(Color::Red);
        box.setOrigin(SCALE, SCALE);
        box.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
        box.setRotation(body->GetAngle() * (180 / b2_pi));
        window.draw(box);

        window.display();
    }

    return 0;
}
