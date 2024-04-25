#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;

const float SCALE = 30.0f; 

int main()
{
    RenderWindow window(VideoMode(800, 600), "Caja deslizante con Box2D");

    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, window.getSize().y / SCALE); 
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(window.getSize().x / SCALE, 0.1f); 
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.position.Set(window.getSize().x / 2.0f / SCALE, (window.getSize().y - 100.0f) / SCALE); 
    b2Body* boxBody = world.CreateBody(&boxBodyDef);
    b2PolygonShape boxShape;
    boxShape.SetAsBox(50.0f / SCALE, 50.0f / SCALE); 
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1.0f; 
    boxFixtureDef.friction = 0.3f; 
    boxBody->CreateFixture(&boxFixtureDef);

    float force = 28.0f;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        float forceX = 0.0f;
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            forceX -= force;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            forceX += force;
        }
        boxBody->ApplyForceToCenter(b2Vec2(forceX, 0.0f), true);

        world.Step(1.0f / 60.0f, 8, 3);

        window.clear(Color::Black);

        RectangleShape box(Vector2f(100.0f, 100.0f));
        box.setOrigin(50.0f, 50.0f); 
        box.setPosition(boxBody->GetPosition().x * SCALE, boxBody->GetPosition().y * SCALE);
        box.setRotation(boxBody->GetAngle() * 180.0f / b2_pi); 
        box.setFillColor(Color::Red);
        window.draw(box);

        window.display();
    }

    return 0;
}