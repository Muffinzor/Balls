#include <random>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// Convert Box2D meters to SFML pixels
const float PPM = 1;
const int quantity = 45;

double random_double(const double min, const double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}

void create_ball(b2World &world, const b2Vec2 position, const b2Vec2 velocity, const float radius, std::vector<b2Body*>& bodies) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x / PPM, position.y / PPM);
    b2Body *body = world.CreateBody(&bodyDef);
    b2CircleShape shape;
    shape.m_radius = radius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.restitution = 1;
    fixtureDef.friction = 0;
    body->CreateFixture(&fixtureDef);
    body->SetLinearVelocity(velocity);
    bodies.push_back(body);
}

void check_bounds(b2Body *body) {
    const b2Vec2 p = body->GetPosition();
    b2Vec2 v = body->GetLinearVelocity();
    if (p.x < 0 || p.x > 790) {
        v.x = -v.x;
    }
    if (p.y < 0 || p.y > 590) {
        v.y = -v.y;
    }
    body->SetLinearVelocity(b2Vec2(v.x, v.y));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Balls");

    b2Vec2 gravity(0.f, 0.f);
    b2World world(gravity);
    std::vector<b2Body*> bodies;
    std::vector<sf::CircleShape> shapes;

    for (int i = 0; i < quantity; ++i) {
        auto *pos_1 = new b2Vec2(random_double(0,800), random_double(0,600));
        auto *vel_1 = new b2Vec2(random_double(-4,4), random_double(-4,4));
        create_ball(world, *pos_1, *vel_1, 10, bodies);
        delete pos_1;
        delete vel_1;
    }
    for (int i = 0; i < quantity; ++i) {
        sf::CircleShape circle(10);
        circle.setFillColor(sf::Color::Green);
        circle.setOutlineColor(sf::Color::Cyan);
        circle.setOutlineThickness(2.f);
        shapes.push_back(circle);
    }

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        float timeStep = 1.f / 60.f;
        int velocityIterations = 2;
        int positionIterations = 1;
        world.Step(timeStep, velocityIterations, positionIterations);

        for (int i = 0; i < quantity; ++i) {
            check_bounds(bodies[i]);
            shapes[i].setPosition(bodies[i]->GetPosition().x,bodies[i]->GetPosition().y);
        }

        window.clear();
        for (int i = 0; i < quantity; ++i) {
            window.draw(shapes[i]);
        }
        window.display();
    }
    return 0;
}


