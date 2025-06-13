#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RemakeTimber");

    // 리소스
    sf::Texture background;
    background.loadFromFile("graphics/background.png");

    // 리소스 실행객체
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(background);

    while (window.isOpen())
    {
        sf::Event event;
        // 이벤트 반복
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 업데이트


        // 그리기
        window.clear();

        window.draw(spriteBackground);

        window.display();
    }

    return 0;
}