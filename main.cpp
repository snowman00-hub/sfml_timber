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

    sf::Sprite spriteCloud1;
    spriteCloud1.setTexture(textureCloud);
    sf::Sprite spriteCloud2;
    spriteCloud2.setTexture(textureCloud);
    spriteCloud2.setPosition(0, textureCloud.getSize().y);
    sf::Sprite spriteCloud3;
    spriteCloud3.setTexture(textureCloud);
    spriteCloud3.setPosition(0, textureCloud.getSize().y * 2);

    sf::Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    sf::Sprite spriteBee2;
    spriteBee2.setTexture(textureBee);
    spriteBee2.setPosition(900, 800);
    spriteBee2.setOrigin(textureBee.getSize().x * 0.5f, textureBee.getSize().y * 0.5f);

    srand((int)time(0));
    sf::Clock clock;

    float bee_speed = 250.f;
    float bee2_speed = 2500.f;
    float cloud1_speed = 300.f;
    float cloud2_speed = 450.f;
    float cloud3_speed = 600.f;
    sf::Vector2f bee_dir = { 1.0f,-1.f };
    sf::Vector2f bee2_dir = { 1.0f,-1.f };
    sf::Vector2f cloud1_dir = { 1.0f,0.f };
    sf::Vector2f cloud2_dir = { 1.0f,0.f };
    sf::Vector2f cloud3_dir = { 1.0f,0.f };

    float bee_random = (float)rand() / RAND_MAX;
    float cloud1_random = (float)rand() / RAND_MAX;
    float cloud2_random = (float)rand() / RAND_MAX;
    float cloud3_random = (float)rand() / RAND_MAX;

    if (bee_random <= 0.5f)
    {
        bee_dir = { 1.0f,-1.f };
        spriteBee.setScale(-1.0f, 1.0f);
    }
    else
    {
        bee_dir = { -1.0f,-1.f };
        spriteBee.setScale(1.0f, 1.0f);
    }
    if (cloud1_random <= 0.5f)
    {
        cloud1_dir = { 1.0f,0.f };
        spriteCloud1.setScale(-1.0f, 1.0f);
    }
    else
    {
        cloud1_dir = { -1.0f,0.f };
        spriteCloud1.setScale(1.0f, 1.0f);
    }
    if (cloud2_random <= 0.5f)
    {
        cloud2_dir = { 1.0f,0.f };
        spriteCloud2.setScale(-1.0f, 1.0f);
    }
    else
    {
        cloud2_dir = { -1.0f,0.f };
        spriteCloud2.setScale(1.0f, 1.0f);
    }
    if (cloud3_random <= 0.5f)
    {
        cloud3_dir = { 1.0f,0.f };
        spriteCloud3.setScale(-1.0f, 1.0f);
    }
    else
    {
        cloud3_dir = { -1.0f,0.f };
        spriteCloud3.setScale(1.0f, 1.0f);
    }

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
        sf::Vector2f pos_Bee = spriteBee.getPosition();
        sf::Vector2f pos_Bee2 = spriteBee2.getPosition();
        sf::Vector2f pos_Cloud1 = spriteCloud1.getPosition();
        sf::Vector2f pos_Cloud2 = spriteCloud2.getPosition();
        sf::Vector2f pos_Cloud3 = spriteCloud3.getPosition();

        pos_Bee += bee_dir * bee_speed * deltaTime;
        pos_Bee2 += bee2_dir * bee2_speed * deltaTime;
        pos_Cloud1 += cloud1_dir * cloud1_speed * deltaTime;
        pos_Cloud2 += cloud2_dir * cloud2_speed * deltaTime;
        pos_Cloud3 += cloud3_dir * cloud3_speed * deltaTime;

        spriteBee.setPosition(pos_Bee);
        spriteBee2.setPosition(pos_Bee2);
        spriteCloud1.setPosition(pos_Cloud1);
        spriteCloud2.setPosition(pos_Cloud2);
        spriteCloud3.setPosition(pos_Cloud3);

        bee2_dir.x = (float)(rand() % 3 - 1) * 3;
        if (bee2_dir.x > 0) spriteBee2.setScale(-1.0f, 1.0f);
        else spriteBee2.setScale(1.0f, 1.0f);
        bee2_dir.y = (float)(rand() % 3 - 1);

        if (pos_Bee.x < -100 || pos_Bee.x > 1920 + 100)
        {
            bee_random = (float)rand() / RAND_MAX;
            if (bee_random <= 0.5f)
            {
                bee_dir = { 1.0f,-1.f };
                spriteBee.setPosition(0, 800);
                spriteBee.setScale(-1.0f, 1.0f);
            }
            else
            {
                bee_dir = { -1.0f,-1.f };
                spriteBee.setPosition(1920, 800);
                spriteBee.setScale(1.0f, 1.0f);
            }
        }
        if (pos_Bee2.x < -100 || pos_Bee2.x > 1920 + 100)
        {
            bee_random = (float)rand() / RAND_MAX;
            if (bee_random <= 0.5f)
            {
                bee2_dir = { 1.0f,-1.f };
                spriteBee2.setPosition(0, 800);
                spriteBee2.setScale(-1.0f, 1.0f);
            }
            else
            {
                bee2_dir = { -1.0f,-1.f };
                spriteBee2.setPosition(1920, 800);
                spriteBee2.setScale(1.0f, 1.0f);
            }
        }
        if (pos_Cloud1.x < -100 || pos_Cloud1.x > 1920 + 100)
        {
            cloud1_random = (float)rand() / RAND_MAX;
            if (cloud1_random <= 0.5f)
            {
                cloud1_dir = { 1.0f,0.f };
                spriteCloud1.setPosition(0, 0);
                spriteCloud1.setScale(-1.0f, 1.0f);
            }
            else
            {
                cloud1_dir = { -1.0f,0.f };
                spriteCloud1.setPosition(1920, 0);
                spriteCloud1.setScale(1.0f, 1.0f);
            }
        }
        if (pos_Cloud2.x < -100 || pos_Cloud2.x > 1920 + 100)
        {
            cloud2_random = (float)rand() / RAND_MAX;
            if (cloud2_random <= 0.5f)
            {
                cloud2_dir = { 1.0f,0.f };
                spriteCloud2.setPosition(0, textureCloud.getSize().y);
                spriteCloud2.setScale(-1.0f, 1.0f);
            }
            else
            {
                cloud2_dir = { -1.0f,0.f };
                spriteCloud2.setPosition(1920, textureCloud.getSize().y);
                spriteCloud2.setScale(1.0f, 1.0f);
            }
        }
        if (pos_Cloud3.x < -100 || pos_Cloud3.x > 1920 + 100)
        {
            cloud3_random = (float)rand() / RAND_MAX;
            if (cloud3_random <= 0.5f)
            {
                cloud3_dir = { 1.0f,0.f };
                spriteCloud3.setPosition(0, textureCloud.getSize().y * 2);
                spriteCloud3.setScale(-1.0f, 1.0f);
            }
            else
            {
                cloud3_dir = { -1.0f,0.f };
                spriteCloud3.setPosition(1920, textureCloud.getSize().y * 2);
                spriteCloud3.setScale(1.0f, 1.0f);
            }
        }
        if (pos_Bee.y < 550 || pos_Bee.y > 810)
        {
            bee_dir.y *= -1;
        }
        if (pos_Bee2.y < 200) bee2_dir.y = 1.f;
        if (pos_Bee2.y > 900) bee2_dir.y = -1.f;
                
        // 그리기
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(spriteBee2);
        window.display();
    }

    return 0;
}