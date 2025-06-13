#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RemakeTimber");

    // ���ҽ�
    sf::Texture background;
    background.loadFromFile("graphics/background.png");

    // ���ҽ� ���ఴü
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(background);

    while (window.isOpen())
    {
        sf::Event event;
        // �̺�Ʈ �ݺ�
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ������Ʈ


        // �׸���
        window.clear();

        window.draw(spriteBackground);

        window.display();
    }

    return 0;
}