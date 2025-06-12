#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

enum class Side { LEFT, RIGHT, NONE };

void updateBranches(Side* branches,int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        branches[i] = branches[i - 1];
    }
    
    int r = rand() % 3;
    switch (r)
    {
        case 0:
            branches[0] = Side::LEFT;
            break;
        case 1:
            branches[0] = Side::RIGHT;
            break;
        case 2:
            branches[0] = Side::NONE;
            break;
    }
}

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
    sf::Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");

    // 

    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);

    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    sf::Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(1920 * 0.5f, 815.f);
    spriteAxe.setOrigin(texturePlayer.getSize().x * -0.61f, 0.0f);

    // 0, 1, 2 : 구름   3 : 포물선 벌   4 : 랜덤 움직임 벌
    sf::Sprite spriteCloudBee[5];
    sf::Vector2f dirCloudBee[5];
    sf::Vector2f posCloudBee[5];
    float speedCloudBee[5];
    float random, beeStopTime = 0;

    for (int i = 0; i < 5; i++)
    {
        random = (float)rand() / RAND_MAX;

        if (i < 3) // 구름
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
            if (i == 3) // 포물선 벌
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
            else // 랜덤움직임 벌
            {
                spriteCloudBee[i].setPosition(900, 800);
                spriteCloudBee[i].setOrigin(textureBee.getSize().x * 0.5f, textureBee.getSize().y * 0.5f);
                speedCloudBee[i] = 8000.f;
                dirCloudBee[i] = { 1.0f,-1.0f };
            }
        }
    }
        
    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setOrigin(texturePlayer.getSize().x * 0.5f - textureTree.getSize().x, texturePlayer.getSize().y);
    spritePlayer.setPosition(1920 * 0.5f, textureTree.getSize().y);
    Side sidePlayer = Side::LEFT;

    const int NUM_BRANCHES = 6;
    sf::Sprite spriteBranch[NUM_BRANCHES];
    Side sideBranch[NUM_BRANCHES];
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        spriteBranch[i].setTexture(textureBranch);
        spriteBranch[i].setOrigin(textureTree.getSize().x * -0.5f, 0.f);
        spriteBranch[i].setPosition(1920.f * 0.5, i * 150.f);

        int r = rand() % 3;
        switch (r)
        {
            case 0:
                sideBranch[i] = Side::LEFT;
                break;
            case 1:
                sideBranch[i] = Side::RIGHT;
                break;
            case 2:
                sideBranch[i] = Side::NONE;
                break;
        }
    }
    sideBranch[NUM_BRANCHES - 1] = Side::NONE;

    srand((int)time(0));
    sf::Clock clock;

    bool isLeft = false;
    bool isRight = false;
    bool isPause = false;

    while (window.isOpen())
    {
        sf::Time time = clock.restart();
        float deltaTime = time.asSeconds();

        // 이벤트 루프
        sf::Event event;
        bool isLeftDown = false;
        bool isLeftUp = false;
        bool isRightDown = false;
        bool isRightUp = false;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Left:
                            if (!isLeft)
                            {
                                isLeftDown = true;
                            }
                            isLeft = true;
                            break;
                        case sf::Keyboard::Right:
                            if (!isRight)
                            {
                                isRightDown = true;
                            }
                            isRight = true;
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Left:
                            isLeftUp = true;
                            isLeft = false;
                            break;
                        case sf::Keyboard::Right:
                            isRightUp = true;
                            isRight = false;
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        // 업데이트
        if (isLeftDown || isRightDown)
        {
            if (isLeftDown)
            {
                sidePlayer = Side::LEFT;
            }
            if (isRightDown)
            {
                sidePlayer = Side::RIGHT;
            }
            updateBranches(sideBranch, NUM_BRANCHES);

            if (sidePlayer == sideBranch[NUM_BRANCHES - 1])
            {
                printf("충돌했습니다!\n");
            }
        }

        for (int i = 0; i < 5; i++)
        {
            posCloudBee[i] = spriteCloudBee[i].getPosition();
            posCloudBee[i] += dirCloudBee[i] * speedCloudBee[i] * deltaTime;
            spriteCloudBee[i].setPosition(posCloudBee[i]);
            random = (float)rand() / RAND_MAX;

            if (i < 3) // 구름
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
                if (i == 3) // 포물선 벌
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
                else // 랜덤움직임 벌
                {
                    beeStopTime += deltaTime;

                    if (beeStopTime > 0.2f)
                    {
                        beeStopTime = 0;
                        dirCloudBee[i].x = (float)(rand() % 3 - 1) * 3;
                        dirCloudBee[i].y = (float)(rand() % 3 - 1) * 2;
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

                        if (posCloudBee[i].y < 400) dirCloudBee[i].y = 1.0f;
                        if (posCloudBee[i].y > 900) dirCloudBee[i].y = -1.0f;

                    }
                    else
                    {
                        dirCloudBee[i].x = 0;
                        dirCloudBee[i].y = 0;
                    }
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
                spriteAxe.setScale(-1.f, 1.f);
                break;
            case Side::RIGHT:
                spritePlayer.setScale(1.f, 1.f);
                spriteAxe.setScale(1.f, 1.f);
                break;
        }

        // 그리기
        window.clear();

        window.draw(spriteBackground); // 배경
        for (int i = 0; i < 3; i++) // 구름들
        {
            window.draw(spriteCloudBee[i]); 
        }
        window.draw(spriteTree); // 나무
        for (int i = 0; i < NUM_BRANCHES; i++) // 나뭇가지들
        {
            if (sideBranch[i] != Side::NONE)
            {
                window.draw(spriteBranch[i]); 
            }
        }
        for (int i = 3; i < 5; i++) // 벌들
        {
            window.draw(spriteCloudBee[i]); 
        }        
        window.draw(spritePlayer); // 플레이어
        if (isLeft || isRight) // 도끼
        {
            window.draw(spriteAxe); 
        }

        window.display();
    }

    // isleft일때 axe 보이게
    // 충돌시 게임 정지 그 상태에서 enter키 누를시 이어서 시작

    return 0;
}