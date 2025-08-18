#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.h"
#include "loader.h"
#include "map.h"
#include "entity.h"
#include "player.h"
#include "game.h"

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Momo Rush");

    loadAllTextures();

    Txt startGame("./Assets/play.png");
    Sprt startBtn(startGame);
    startBtn.setPosition({ 7 * tilesize, 5 * tilesize });
    startBtn.scale({ .5f, .5f });

    Txt newMap("./Assets/newmapgen.png");
    Sprt nMap(newMap);
    nMap.setPosition({ 7 * tilesize, 6 * tilesize });
    nMap.scale({ .5f, .5f });

    Background b1(0), b2(1), b3(2), b4(3);
    Map m1("./Assets/newmap.txt");
    Player p(0, 0, 0, 56, 56);
    game g(p);
    p.move({ static_cast<float>(tilesize * 12) , 0.f }, m1);

    s4.play();

    static bool num2WasPressed = false;

    while (window.isOpen())
    {
        while (std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color(0, 0, 0));

        int state = g.onGoing();

        if (state)
        {
            if (s4.getStatus() == sf::SoundSource::Status::Playing) s4.stop();
            if (s5.getStatus() != sf::SoundSource::Status::Playing) s5.play();
            if (state == 1)
            {
                p.update(m1, g);
            }
            b1.draw(window);
            b2.draw(window);
            b3.draw(window);
            m1.draw(window, static_cast<int>(p.getHitBox().position.x));
            p.draw(window);
        }
        else {
            if (s5.getStatus() == sf::SoundSource::Status::Playing) s5.stop();
            if (s4.getStatus() != sf::SoundSource::Status::Playing) s4.play();

            b4.draw(window);
            window.draw(startBtn);
            window.draw(nMap);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
        {
            if (!g.onGoing())
            {
                p.move({ static_cast<float>(tilesize * 12) , 0.f }, m1);
                g.restart();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
        {
            if (!num2WasPressed && !g.onGoing())
            {
                Map m1(Map::generate(10000));
                g.drawText("New map generated successfully!", 3);
            }
            num2WasPressed = true;
        }
        else
        {
            num2WasPressed = false;
        }

        g.draw(window);

        window.display();
    }
    return 0;
}
