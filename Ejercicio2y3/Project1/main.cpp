#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;

const float SCALE = 30.0f; 

int main()
{
    RenderWindow window(VideoMode(800, 600), "Pelota rebotante con Box2D");

    b2Vec2 gravity(0.0f, 0.0f); 
    b2World world(gravity);

    b2BodyDef edgeBodyDef;
    b2Body* edgeBody = world.CreateBody(&edgeBodyDef);
    b2EdgeShape edgeShape;

    edgeShape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(window.getSize().x / SCALE, 0.0f)); 
    edgeBody->CreateFixture(&edgeShape, 0.0f);

    edgeShape.SetTwoSided(b2Vec2(0.0f, window.getSize().y / SCALE), b2Vec2(window.getSize().x / SCALE, window.getSize().y / SCALE)); 
    edgeBody->CreateFixture(&edgeShape, 0.0f);

    edgeShape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, window.getSize().y / SCALE)); 
    edgeBody->CreateFixture(&edgeShape, 0.0f);

    edgeShape.SetTwoSided(b2Vec2(window.getSize().x / SCALE, 0.0f), b2Vec2(window.getSize().x / SCALE, window.getSize().y / SCALE));
    edgeBody->CreateFixture(&edgeShape, 0.0f);

    for (int i = 0; i < 3; ++i) {
        b2BodyDef obstacleBodyDef;
        obstacleBodyDef.type = b2_staticBody;
        obstacleBodyDef.position.Set((i + 1) * 200.0f / SCALE, 300.0f / SCALE);
        b2Body* obstacleBody = world.CreateBody(&obstacleBodyDef);
        b2PolygonShape obstacleShape;
        obstacleShape.SetAsBox(50.0f / SCALE, 50.0f / SCALE); 
        obstacleBody->CreateFixture(&obstacleShape, 0.0f);
    }

    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(window.getSize().x / 2.0f / SCALE, window.getSize().y / 2.0f / SCALE); 
    b2Body* ballBody = world.CreateBody(&ballBodyDef);
    b2CircleShape ballShape;
    ballShape.m_radius = 20.0f / SCALE; 
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = 1.0f; 
    ballFixtureDef.friction = 0.3f; 
    ballFixtureDef.restitution = 1.0f; 
    ballBody->CreateFixture(&ballFixtureDef);

    b2Vec2 initialVelocity(1.5f, 1.5f); 
    ballBody->SetLinearVelocity(initialVelocity);

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

        RectangleShape top(Vector2f(window.getSize().x, 10.0f));
        top.setPosition(0.0f, 0.0f);
        top.setFillColor(Color::Green);
        window.draw(top);

        RectangleShape bottom(Vector2f(window.getSize().x, 10.0f));
        bottom.setPosition(0.0f, window.getSize().y - 10.0f);
        bottom.setFillColor(Color::Green);
        window.draw(bottom);

        RectangleShape left(Vector2f(10.0f, window.getSize().y));
        left.setPosition(0.0f, 0.0f);
        left.setFillColor(Color::Green);
        window.draw(left);

        RectangleShape right(Vector2f(10.0f, window.getSize().y));
        right.setPosition(window.getSize().x - 10.0f, 0.0f);
        right.setFillColor(Color::Green);
        window.draw(right);

        for (b2Body* b = world.GetBodyList(); b; b = b->GetNext()) {
            if (b->GetType() == b2_staticBody) {
                b2Vec2 position = b->GetPosition();
                RectangleShape obstacle(Vector2f(100.0f, 100.0f));
                obstacle.setOrigin(50.0f, 50.0f);
                obstacle.setPosition(position.x * SCALE, position.y * SCALE);
                obstacle.setFillColor(Color::Red);
                window.draw(obstacle);
            }
        }

        CircleShape ball(20.0f);
        ball.setOrigin(20.0f, 20.0f); 
        ball.setPosition(ballBody->GetPosition().x * SCALE, ballBody->GetPosition().y * SCALE);
        ball.setFillColor(Color::Blue);
        window.draw(ball);

        window.display();
    }

    return 0;
}
