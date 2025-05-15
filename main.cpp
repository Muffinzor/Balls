#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML + Box2D");

    b2Vec2 gravity(0.f, -9.8f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.f, -10.f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.f, 10.f);
    groundBody->CreateFixture(&groundBox, 0.f);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(1.0f / 60.0f, 8, 3);

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}