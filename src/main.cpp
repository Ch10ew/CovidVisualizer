#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <csv.h>
#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;

    io::CSVReader<3> in("../test.csv");
    int a{0};
    int b{0};
    int c{0};
    while (in.read_row(a, b, c))
    {
        std::cout << "a=" << a << ", b=" << b << ", c=" << c << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}