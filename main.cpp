#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

enum class Side { LEFT, RIGHT, NONE };

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
    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    sf::Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    // 

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // 0, 1, 2 : ����   3 : ������ ��   4 : ���� ������ ��
    sf::Sprite spriteCloudBee[5];
    sf::Vector2f dirCloudBee[5];
    sf::Vector2f posCloudBee[5];
    float speedCloudBee[5];
    float random;

    for (int i = 0; i < 5; i++)
    {
        random = (float)rand() / RAND_MAX;

        if (i < 3) // ����
        {
            spriteCloudBee[i].setTexture(textureCloud);
            spriteCloudBee[i].setPosition(0, textureCloud.getSize().y * i);
            speedCloudBee[i] = 300 + 150 * i;
            if (random < 0.5f)
            {
                dirCloudBee[i] = { 1.0f,0.0f };
                spriteCloudBee[i].setScale(-1.0f, 1.0f);
            }
            else
            {
                dirCloudBee[i] = { -1.0f,0.0f };
                spriteCloudBee[i].setScale(1.0f, 1.0f);
            }
        }
        else
        {
            spriteCloudBee[i].setTexture(textureBee);
            if (i == 3) // ������ ��
            {
                spriteCloudBee[i].setPosition(0, 800);
                speedCloudBee[i] = 250.f;
                if (random < 0.5f)
                {
                    dirCloudBee[i] = { 1.0f,-1.0f };
                    spriteCloudBee[i].setScale(-1.0f, 1.0f);
                }
                else
                {
                    dirCloudBee[i] = { -1.0f,-1.0f };
                    spriteCloudBee[i].setScale(1.0f, 1.0f);
                }
            }
            else // ���������� ��
            {
                spriteCloudBee[i].setPosition(900, 800);
                spriteCloudBee[i].setOrigin(textureBee.getSize().x * 0.5f, textureBee.getSize().y * 0.5f);
                speedCloudBee[i] = 2500.f;
                dirCloudBee[i] = { 1.0f,-1.0f };
            }
        }
    }

    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setOrigin(texturePlayer.getSize().x * 0.5f - textureTree.getSize().x, texturePlayer.getSize().y);
    spritePlayer.setPosition(1920 * 0.5f, 925.f);
    Side sidePlayer = Side::LEFT;

    const int NUM_BRANCHES = 6;
    sf::Sprite spriteBranch[NUM_BRANCHES];
    Side sideBranch[NUM_BRANCHES] = { Side::LEFT,Side::RIGHT, Side::NONE, Side::LEFT, Side::RIGHT, Side::NONE };
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        spriteBranch[i].setTexture(textureBranch);
        spriteBranch[i].setOrigin(textureTree.getSize().x * -0.5f, 0.f);
        spriteBranch[i].setPosition(1920.f * 0.5, i * 150.f);        
    }

    srand((int)time(0));
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time time = clock.restart();
        float deltaTime = time.asSeconds();

        // �̺�Ʈ ����
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // ������Ʈ
        for (int i = 0; i < 5; i++)
        {
            posCloudBee[i] = spriteCloudBee[i].getPosition();
            posCloudBee[i] += dirCloudBee[i] * speedCloudBee[i] * deltaTime;
            spriteCloudBee[i].setPosition(posCloudBee[i]);
            random = (float)rand() / RAND_MAX;

            if (i < 3) // ����
            {
                if (posCloudBee[i].x < -100 || posCloudBee[i].x > 1920 + 100)
                {
                    if (random < 0.5f)
                    {
                        dirCloudBee[i] = { 1.0f,0.0f };
                        spriteCloudBee[i].setPosition(0, textureCloud.getSize().y * i);
                        spriteCloudBee[i].setScale(-1.0f, 1.0f);
                    }
                    else
                    {
                        dirCloudBee[i] = { -1.0f,0.0f };
                        spriteCloudBee[i].setPosition(1920, textureCloud.getSize().y * i);
                        spriteCloudBee[i].setScale(1.0f, 1.0f);
                    }
                }
            }
            else
            {
                if (i == 3) // ������ ��
                {
                    if (posCloudBee[i].x < -100 || posCloudBee[i].x > 1920 + 100)
                    {
                        if (random < 0.5f)
                        {
                            dirCloudBee[i] = { 1.0f,-1.0f };
                            spriteCloudBee[i].setPosition(0, 800);
                            spriteCloudBee[i].setScale(-1.0f, 1.0f);
                        }
                        else
                        {
                            dirCloudBee[i] = { -1.0f,-1.0f };
                            spriteCloudBee[i].setPosition(1920, 800);
                            spriteCloudBee[i].setScale(1.0f, 1.0f);
                        }
                    }

                    if (posCloudBee[i].y < 550 || posCloudBee[i].y > 810)
                    {
                        dirCloudBee[i].y *= -1;
                    }
                }
                else // ���������� ��
                {
                    dirCloudBee[i].x = (float)(rand() % 3 - 1) * 3;
                    dirCloudBee[i].y = (float)(rand() % 3 - 1);
                    if (dirCloudBee[i].x > 0) spriteCloudBee[i].setScale(-1.0f, 1.0f);
                    else spriteCloudBee[i].setScale(1.0f, 1.0f);

                    if (posCloudBee[i].x < -100 || posCloudBee[i].x > 1920 + 100)
                    {
                        if (random < 0.5f)
                        {
                            dirCloudBee[i] = { 1.0f,-1.0f };
                            spriteCloudBee[i].setPosition(0, 800);
                            spriteCloudBee[i].setScale(-1.0f, 1.0f);
                        }
                        else
                        {
                            dirCloudBee[i] = { -1.0f,-1.0f };
                            spriteCloudBee[i].setPosition(1920, 800);
                            spriteCloudBee[i].setScale(1.0f, 1.0f);
                        }
                    }

                    if (posCloudBee[i].y < 200) dirCloudBee[i].y = 1.0f;
                    if (posCloudBee[i].y > 900) dirCloudBee[i].y = -1.0f;
                }
            }
        }
        
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            switch (sideBranch[i])
            {
                case Side::LEFT:
                    spriteBranch[i].setScale(-1.f, 1.f);
                    break;
                case Side::RIGHT:
                    spriteBranch[i].setScale(1.f, 1.f);
                    break;
            }
        }

        switch (sidePlayer)
        {
            case Side::LEFT:
                spritePlayer.setScale(-1.f, 1.f);
                break;
            case Side::RIGHT:
                spritePlayer.setScale(1.f, 1.f);
                break;
        }

        // �׸���
        window.clear();

        window.draw(spriteBackground);
        for (int i = 0; i < 3; i++)
        {
            window.draw(spriteCloudBee[i]);
        }
        window.draw(spriteTree);
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            if (sideBranch[i] != Side::NONE)
            {
                window.draw(spriteBranch[i]);
            }
        }
        for (int i = 3; i < 5; i++)
        {
            window.draw(spriteCloudBee[i]);
        }        
        window.draw(spritePlayer);

        window.display();
    }

    return 0;
}