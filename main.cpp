#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");

    //

    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    sf::Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    sf::Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    // 

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    sf::Sprite sprite_CloudBee[5];
    sf::Vector2f dir_CloudBee[5];
    float speed_CloudBee[5];
    float random_CloudBee[5];

    for (int i = 0; i < 5; i++)
    {
        random_CloudBee[i] = (float)rand() / RAND_MAX;

        if (i < 3)
        {
            sprite_CloudBee[i].setTexture(textureCloud);
            sprite_CloudBee[i].setPosition(0, textureCloud.getSize().y * i);
            speed_CloudBee[i] = 300 + 150 * i;
            if (random_CloudBee[i] < 0.5f)
            {
                dir_CloudBee[i] = { 1.0f,0.0f };
                sprite_CloudBee[i].setScale(-1.0f, 1.0f);
            }
            else
            {
                dir_CloudBee[i] = { -1.0f,0.0f };
                sprite_CloudBee[i].setScale(1.0f, 1.0f);
            }
        }
        else
        {
            sprite_CloudBee[i].setTexture(textureBee);
            if (i == 3)
            {
                sprite_CloudBee[i].setPosition(0, 800);
                speed_CloudBee[i] = 250.f;
                if (random_CloudBee[i] < 0.5f)
                {
                    dir_CloudBee[i] = { 1.0f,-1.0f };
                    sprite_CloudBee[i].setScale(-1.0f, 1.0f);
                }
                else
                {
                    dir_CloudBee[i] = { -1.0f,-1.0f };
                    sprite_CloudBee[i].setScale(1.0f, 1.0f);
                }
            }
            else
            {
                sprite_CloudBee[i].setPosition(900, 800);
                sprite_CloudBee[i].setOrigin(textureBee.getSize().x * 0.5f, textureBee.getSize().y * 0.5f);
                speed_CloudBee[i] = 2500.f;
                dir_CloudBee[i] = { 1.0f,-1.0f };
            }
        }
    }

    srand((int)time(0));
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time time = clock.restart();
        float deltaTime = time.asSeconds();

        // 이벤트 루프
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // 업데이트
        sf::Vector2f pos_CloudBee[5];
        for (int i = 0; i < 5; i++)
        {
            pos_CloudBee[i] = sprite_CloudBee[i].getPosition();
            pos_CloudBee[i] += dir_CloudBee[i] * speed_CloudBee[i] * deltaTime;
            sprite_CloudBee[i].setPosition(pos_CloudBee[i]);
            random_CloudBee[i] = (float)rand() / RAND_MAX;

            if (i < 3)
            {
                if (pos_CloudBee[i].x < -100 || pos_CloudBee[i].x > 1920 + 100)
                {
                    if (random_CloudBee[i] < 0.5f)
                    {
                        dir_CloudBee[i] = { 1.0f,0.0f };
                        sprite_CloudBee[i].setPosition(0, textureCloud.getSize().y * i);
                        sprite_CloudBee[i].setScale(-1.0f, 1.0f);
                    }
                    else
                    {
                        dir_CloudBee[i] = { -1.0f,0.0f };
                        sprite_CloudBee[i].setPosition(1920, textureCloud.getSize().y * i);
                        sprite_CloudBee[i].setScale(1.0f, 1.0f);
                    }
                }
            }
            else
            {
                if (i == 3) // 포물선 벌
                {
                    if (pos_CloudBee[i].x < -100 || pos_CloudBee[i].x > 1920 + 100)
                    {
                        if (random_CloudBee[i] < 0.5f)
                        {
                            dir_CloudBee[i] = { 1.0f,-1.0f };
                            sprite_CloudBee[i].setPosition(0, 800);
                            sprite_CloudBee[i].setScale(1.0f, 1.0f);
                        }
                        else
                        {
                            dir_CloudBee[i] = { -1.0f,-1.0f };
                            sprite_CloudBee[i].setPosition(1920, 800);
                            sprite_CloudBee[i].setScale(1.0f, 1.0f);
                        }
                    }
                    if (pos_CloudBee[i].y < 550 || pos_CloudBee[i].y >810)
                    {
                        dir_CloudBee[i].y *= -1;
                    }
                }
                else // 랜덤움직임 벌
                {
                    dir_CloudBee[i].x = (float)(rand() % 3 - 1) * 3;
                    if (dir_CloudBee[i].x > 0) sprite_CloudBee[i].setScale(-1.0f, 1.0f);
                    else sprite_CloudBee[i].setScale(1.0f, 1.0f);
                    dir_CloudBee[i].y = (float)(rand() % 3 - 1);

                    if (pos_CloudBee[i].x < -100 || pos_CloudBee[i].x > 1920 + 100)
                    {
                        if (random_CloudBee[i] < 0.5f)
                        {
                            dir_CloudBee[i] = { 1.0f,-1.0f };
                            sprite_CloudBee[i].setPosition(0, 800);
                            sprite_CloudBee[i].setScale(-1.0f, 1.0f);
                        }
                        else
                        {
                            dir_CloudBee[i] = { -1.0f,-1.0f };
                            sprite_CloudBee[i].setPosition(1920, 800);
                            sprite_CloudBee[i].setScale(1.0f, 1.0f);
                        }
                    }
                    if (pos_CloudBee[i].y < 200) dir_CloudBee[i].y = 1.0f;
                    if (pos_CloudBee[i].y > 900) dir_CloudBee[i].y = -1.0f;
                }
            }
        }
                
        // 그리기
        window.clear();
        window.draw(spriteBackground);
        window.draw(sprite_CloudBee[0]);
        window.draw(sprite_CloudBee[1]);
        window.draw(sprite_CloudBee[2]);
        window.draw(spriteTree);
        window.draw(sprite_CloudBee[3]);
        window.draw(sprite_CloudBee[4]);
        window.display();
    }

    return 0;
}