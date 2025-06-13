#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

enum class Side { LEFT, RIGHT, NONE };

void InitCloud(Side* side, sf::Sprite* sprite, sf::Vector2f* dir, sf::Texture* texture, int random);

int main()
{
    srand((int)time(0));
    sf::Clock clock;
    sf::Time time;
    int random;    
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RemakeTimber");

    // 리소스
    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    sf::Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    sf::Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");

    // 리소스 실행객체
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setOrigin(textureTree.getSize().x * 0.5f, 0);
    spriteTree.setPosition(1920 * 0.5f,0);

    sf::Sprite spriteCloud[3];    
    Side sideCloud[3];
    sf::Vector2f dirCloud[3];
    float speedCloud[3];
    for (int i = 0; i < 3; i++)
    {
        InitCloud(&sideCloud[i], &spriteCloud[i], &dirCloud[i], &textureCloud, i);               
        spriteCloud[i].setTexture(textureCloud);
        speedCloud[i] = 200 + 100 * i;
    }

    sf::Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setOrigin(textureBee.getSize().x * 0.5f, textureBee.getSize().y * 0.5f);
    spriteBee.setPosition(500, 800);
    Side sideBee;
    sf::Vector2f dirBee;
    float speedBee = 300.f;
    if (rand() % 2)
    {
        sideBee = Side::LEFT;
        dirBee = { -1.f,-1.f };
        spriteBee.setScale(1.f, 1.f);
    }
    else
    {
        sideBee = Side::RIGHT;
        dirBee = { 1.f,-1.f };
        spriteBee.setScale(-1.f, 1.f);
    }
    
    // 윈도우 실행
    while (window.isOpen())
    {
        time = clock.restart();
        float deltatime = time.asSeconds();

        sf::Event event;
        // 이벤트 반복
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 업데이트
        for (int i = 0; i < 3; i++)
        {
            sf::Vector2f position = spriteCloud[i].getPosition();
            position += speedCloud[i] * dirCloud[i] * deltatime;
            spriteCloud[i].setPosition(position);

            if (position.x < -200 || position.x > 1920 + 200)
            {
                InitCloud(&sideCloud[i], &spriteCloud[i], &dirCloud[i], &textureCloud, i);
            }
        }
        
        sf::Vector2f posBee = spriteBee.getPosition();
        posBee += speedBee * dirBee * deltatime;
        spriteBee.setPosition(posBee);
        if (posBee.x < 0 - 100 || posBee.y > 1920 + 100)
        {

        }
        if (posBee.y < 600 || posBee.y > 900) dirBee.y *= -1;

        // 그리기
        window.clear();

        window.draw(spriteBackground);
        for (int i = 0; i < 3; i++)
        {
            window.draw(spriteCloud[i]);
        }       
        window.draw(spriteTree);
        window.draw(spriteBee);

        window.display();
    }

    return 0;
}

void InitCloud(Side* side, sf::Sprite* sprite, sf::Vector2f* dir, sf::Texture* texture, int i)
{
    int random = rand() % 2;
    if (random)
    {
        *side = Side::LEFT;
        sprite->setScale(1.f, 1.f);
        *dir = { -1.f,0.f };
        sprite->setPosition(1920 + 200, texture->getSize().y * i);
    }
    else
    {
        *side = Side::RIGHT;
        sprite->setScale(-1.f, 1.f);
        *dir = { 1.f,0.f };
        sprite->setPosition(0 - 200, texture->getSize().y * i);
    }
}