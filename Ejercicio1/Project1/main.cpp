#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf; 

int main()
{
    RenderWindow window(VideoMode(800, 600), "SFML + Box2D");

    b2Vec2 gravity(0.0f, 0.1f); 
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.0f, 500.0f); 
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(400.0f, 10.0f); 
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef blockBodyDef;
    blockBodyDef.type = b2_dynamicBody;
    blockBodyDef.position.Set(400.0f, 100.0f); 
    b2Body* blockBody = world.CreateBody(&blockBodyDef);
    b2PolygonShape blockShape;
    blockShape.SetAsBox(50.0f, 50.0f); 
    b2FixtureDef blockFixtureDef;
    blockFixtureDef.shape = &blockShape;
    blockFixtureDef.density = 1.0f; 
    blockFixtureDef.friction = 0.3f; 
    blockBody->CreateFixture(&blockFixtureDef);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        world.Step(1.0f / 60.0f, 8, 3);

        window.clear(Color::Black);

        RectangleShape ground(Vector2f(800.0f, 20.0f));
        ground.setPosition(0.0f, 500.0f);
        ground.setFillColor(Color::Green);
        window.draw(ground);

        RectangleShape block(Vector2f(100.0f, 100.0f));
        block.setOrigin(50.0f, 50.0f);
        block.setPosition(blockBody->GetPosition().x, blockBody->GetPosition().y);
        block.setRotation(blockBody->GetAngle() * 180 / b2_pi); 
        block.setFillColor(Color::Red);
        window.draw(block);

        window.display();
    }

    return 0;
}