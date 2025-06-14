#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>

enum class Side { LEFT, RIGHT, NONE };

void InitCloud(Side* side, sf::Sprite* sprite, sf::Vector2f* dir, sf::Texture* texture, int random);
void InitBee(Side* side, sf::Sprite* sprite, sf::Vector2f* dir);
void InitBranch(Side* side, sf::Sprite* sprite, int index);

void UpdateCloud(Side sideCloud[], sf::Sprite spriteCloud[], sf::Vector2f dirCloud[], float speedCloud[], sf::Texture* textureCloud, float deltatime);
void UpdateBee(Side* sideBee, sf::Sprite* spriteBee, sf::Vector2f* dirBee, float speedBee, float* timeBee, float deltatime);
void UpdateBranch(Side* sideBranch, sf::Sprite* spriteBranch);
void UpdateLogs(bool isActiveLog[], sf::Vector2f velocityLog[], sf::Sprite spriteLog[], float gravity, float deltatime, int COUNT_LOG);
void UpdateTimer(sf::RectangleShape* timer, float* remainTime, float deltatime, bool* isPlaying, bool* isGameOver, sf::Text* textMessage, float INITAL_TIME, sf::Sound* soundOutOfTime);

int main()
{
    srand((int)time(0));
    sf::Clock clock;
    sf::Time time;
    int random;    
    int score = 0;
    const float INITIAL_TIME = 15.0f;
    float remainTime = INITIAL_TIME;

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
    sf::Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    sf::Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    sf::Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");

    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    sf::SoundBuffer sbChop;
    sbChop.loadFromFile("sound/chop.wav");
    sf::SoundBuffer sbDeath;
    sbDeath.loadFromFile("sound/death.wav");
    sf::SoundBuffer sbOutOfTime;
    sbOutOfTime.loadFromFile("sound/out_of_time.wav");
    
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
    Side sideBee;
    sf::Vector2f dirBee;
    float speedBee = 150.f;
    float timeBee = 0;
    InitBee(&sideBee, &spriteBee, &dirBee);

    sf::Sprite spriteBranch[6];
    Side sideBranch[6];
    for (int i = 0; i < 6; i++)
    {
        spriteBranch[i].setTexture(textureBranch);
        spriteBranch[i].setOrigin(-150.f, 0);
        spriteBranch[i].setPosition(1920 * 0.5f, 150.f * i);
        InitBranch(sideBranch, spriteBranch, i);
    }
    sideBranch[5] = Side::NONE;

    const int COUNT_LOG = 10;
    sf::Sprite spriteLog[COUNT_LOG];
    sf::Vector2f dirLog;
    sf::Vector2f velocityLog[COUNT_LOG];
    bool isActiveLog[COUNT_LOG];
    int indexLog = 0;
    float speedLog = 2000.f;
    float gravity = 7000.f;
    for (int i = 0; i < COUNT_LOG; i++)
    {
        spriteLog[i].setTexture(textureLog);
        spriteLog[i].setOrigin(textureLog.getSize().x * 0.5f, textureLog.getSize().y);
        spriteLog[i].setPosition(1920 * 0.5f, textureTree.getSize().y);
        velocityLog[i] = { 0,0 };
        isActiveLog[i] = false;
    }

    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setOrigin(texturePlayer.getSize().x * 0.5f - textureTree.getSize().x, texturePlayer.getSize().y);
    spritePlayer.setPosition(1920 * 0.5f, 910);
    Side sidePlayer = Side::RIGHT;

    sf::Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setOrigin(-90, textureAxe.getSize().y);
    spriteAxe.setPosition(1920 * 0.5f, 850);

    // UI
    sf::RectangleShape timer;
    timer.setFillColor(sf::Color::Red);
    timer.setSize({ 1720, 100 });
    timer.setPosition(100, 925);
    
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(70);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score : " + std::to_string(score));
    sf::Text textMessage;
    textMessage.setFont(font);
    textMessage.setCharacterSize(70);
    textMessage.setFillColor(sf::Color::White);
    textMessage.setPosition(1920 * 0.5f, 400);
    textMessage.setString("Press Enter to Start!");
    textMessage.setOrigin(textMessage.getLocalBounds().width * 0.5f, textMessage.getLocalBounds().height * 0.5f);

    // 사운드
    sf::Sound soundChop;
    soundChop.setBuffer(sbChop);
    sf::Sound soundDeath;
    soundDeath.setBuffer(sbDeath);
    sf::Sound soundOutOfTime;
    soundOutOfTime.setBuffer(sbOutOfTime);

    bool isLeft = false;
    bool isRight = false;
    bool isPlaying = false;
    bool isGameOver = false;

    // 윈도우 실행
    while (window.isOpen())
    {
        time = clock.restart();
        float deltatime = time.asSeconds();

        // 이벤트 반복
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
                            isLeft = false;
                            isLeftUp = true;
                            break;
                        case sf::Keyboard::Right:
                            isRight = false;
                            isRightUp = true;
                            break;
                        case sf::Keyboard::Return:
                            isPlaying = !isPlaying;
                            // 정지에서 플레이로 바뀔 때
                            if (isPlaying)
                            {
                                if (isGameOver)
                                {
                                    sideBranch[5] = Side::NONE;
                                    score = 0;
                                    remainTime = INITIAL_TIME;
                                    scoreText.setString("Score : " + std::to_string(score));
                                    isGameOver = false;
                                    timer.setSize({ 1720, 100 });
                                }
                            }
                            // 플레이에서 정지로 바뀔 때
                            else
                            {
                                textMessage.setString("Press Enter to Resume!");
                                textMessage.setOrigin(textMessage.getLocalBounds().width * 0.5f, textMessage.getLocalBounds().height * 0.5f);
                            }
                            break;
                    }
                    break;                
            }
        }

        // 업데이트
        if (isPlaying)
        {
            UpdateCloud(sideCloud, spriteCloud, dirCloud, speedCloud, &textureCloud, deltatime);
            UpdateBee(&sideBee, &spriteBee, &dirBee, speedBee, &timeBee, deltatime);
            if (isLeftDown || isRightDown)
            {
                if (isLeftDown)
                {
                    spritePlayer.setScale(-1.f, 1.f);
                    spriteAxe.setScale(-1.f, 1.f);
                    sidePlayer = Side::LEFT;

                    dirLog = {1.0f,-1.0f};
                }

                if (isRightDown)
                {
                    spritePlayer.setScale(1.f, 1.f);
                    spriteAxe.setScale(1.f, 1.f);
                    sidePlayer = Side::RIGHT;

                    dirLog = {-1.0f,-1.0f};
                }

                velocityLog[indexLog] = dirLog * speedLog;
                isActiveLog[indexLog] = true;

                indexLog = (indexLog + 1) % COUNT_LOG;
                spriteLog[indexLog].setPosition(1920 * 0.5f, textureTree.getSize().y);
                velocityLog[indexLog] = { 0,0 };
                isActiveLog[indexLog] = false;
                soundChop.play();

                score += 1000;
                scoreText.setString("Score : " + std::to_string(score));

                UpdateBranch(sideBranch, spriteBranch);

                if (sidePlayer == sideBranch[5])
                {
                    isPlaying = false;
                    isGameOver = true;
                    textMessage.setString("Press Enter to Restart!");
                    textMessage.setOrigin(textMessage.getLocalBounds().width * 0.5f, textMessage.getLocalBounds().height * 0.5f);
                    soundDeath.play();
                }
            }
            UpdateTimer(&timer, &remainTime, deltatime, &isPlaying, &isGameOver, &textMessage, INITIAL_TIME,&soundOutOfTime);
            UpdateLogs(isActiveLog, velocityLog, spriteLog, gravity, deltatime, COUNT_LOG);            
        }

        // 그리기
        window.clear();
        #pragma region Draw
        window.draw(spriteBackground);
        for (int i = 0; i < 3; i++)
        {
            window.draw(spriteCloud[i]);
        }
        window.draw(spriteTree);
        for (int i = 0; i < 6; i++)
        {
            if (sideBranch[i] != Side::NONE)
            {
                window.draw(spriteBranch[i]);
            }
        }
        window.draw(spriteBee);
        for (int i = 0; i < COUNT_LOG; i++)
        {
            window.draw(spriteLog[i]);
        }
        window.draw(spritePlayer);
        if (isPlaying && (isLeft || isRight))
        {
            window.draw(spriteAxe);
        }
        window.draw(scoreText);
        if (!isPlaying)
        {
            window.draw(textMessage);
        }
        window.draw(timer);
#pragma endregion
        window.display();
    }

    return 0;
}

void UpdateTimer(sf::RectangleShape* timer, float* remainTime, float deltatime, bool* isPlaying, bool* isGameOver, sf::Text* textMessage, float INITIAL_TIME,sf::Sound* soundOutOfTime)
{
    *remainTime -= deltatime;
    if (*remainTime < 0)
    {
        *remainTime = 0;
        *isPlaying = false;
        *isGameOver = true;
        textMessage->setString("Press Enter to Restart!");
        textMessage->setOrigin(textMessage->getLocalBounds().width * 0.5f, textMessage->getLocalBounds().height * 0.5f);
        soundOutOfTime->play();
    }
    timer->setSize({ 1720.f * (*remainTime / INITIAL_TIME), 100 });
}

void UpdateLogs(bool isActiveLog[], sf::Vector2f velocityLog[], sf::Sprite spriteLog[], float gravity, float deltatime, int COUNT_LOG)
{
    for (int i = 0; i < COUNT_LOG; i++)
    {
        if (isActiveLog[i])
        {
            velocityLog[i].y += gravity * deltatime;
            sf::Vector2f posLog = spriteLog[i].getPosition();
            posLog += velocityLog[i] * deltatime;
            spriteLog[i].setPosition(posLog);
        }
    }
}

void UpdateBranch(Side* sideBranch, sf::Sprite* spriteBranch)
{
    for (int i = 5; i > 0; i--)
    {
        sideBranch[i] = sideBranch[i - 1];

        if (sideBranch[i] == Side::LEFT)
            spriteBranch[i].setScale(-1.f, 1.f);
        if (sideBranch[i] == Side::RIGHT)
            spriteBranch[i].setScale(1.f, 1.f);
    }
    InitBranch(sideBranch, spriteBranch, 0);
}

void InitBranch(Side* sideBranch, sf::Sprite* spriteBranch, int i)
{
    int random = rand() % 3;
    switch (random)
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

    if (sideBranch[i] == Side::LEFT)
        spriteBranch[i].setScale(-1.f, 1.f);
    if (sideBranch[i] == Side::RIGHT)
        spriteBranch[i].setScale(1.f, 1.f);
}

void UpdateBee(Side* sideBee, sf::Sprite* spriteBee, sf::Vector2f* dirBee, float speedBee, float* timeBee, float deltatime)
{
    sf::Vector2f posBee = spriteBee->getPosition();
    posBee.x += speedBee * dirBee->x * deltatime;
    posBee.y += speedBee * dirBee->y * sinf(*timeBee) * deltatime;
    *timeBee += deltatime;
    spriteBee->setPosition(posBee);
    if (posBee.x < 0 - 100 || posBee.x > 1920 + 100)
    {
        InitBee(sideBee, spriteBee, dirBee);
        timeBee = 0;
    }
}

void UpdateCloud(Side sideCloud[], sf::Sprite spriteCloud[], sf::Vector2f dirCloud[], float speedCloud[], sf::Texture* textureCloud, float deltatime)
{
    for (int i = 0; i < 3; i++)
    {
        sf::Vector2f position = spriteCloud[i].getPosition();
        position += speedCloud[i] * dirCloud[i] * deltatime;
        spriteCloud[i].setPosition(position);

        if (position.x < -200 || position.x > 1920 + 200)
        {
            InitCloud(&sideCloud[i], &spriteCloud[i], &dirCloud[i], textureCloud, i);
        }
    }
}

void InitBee(Side* side, sf::Sprite* sprite, sf::Vector2f* dir)
{
    if (rand() % 2)
    {
        *side = Side::LEFT;
        *dir = { -1.f,-1.f };
        sprite->setScale(1.f, 1.f);
        sprite->setPosition(1920 + 50, 900);
    }
    else
    {
        *side = Side::RIGHT;
        *dir = { 1.f,-1.f };
        sprite->setScale(-1.f, 1.f);
        sprite->setPosition(0 - 50, 900);
    }
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