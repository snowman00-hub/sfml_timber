#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>

enum class Side { LEFT, RIGHT, NONE };

void updateBranches(Side* branches, int size)
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
	srand((int)time(0));

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timber!");

	// 리소스
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
	sf::Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");

	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	sf::SoundBuffer bufferChop;
	bufferChop.loadFromFile("sound/chop.wav");
	sf::SoundBuffer bufferDeath;
	bufferChop.loadFromFile("sound/death.wav");
	sf::SoundBuffer bufferOutOfTime;
	bufferChop.loadFromFile("sound/out_of_time.wav");

	// 그리기 객체

	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);

	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	sf::Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(1920 * 0.5f, 815.f);
	spriteAxe.setOrigin(texturePlayer.getSize().x * -0.61f, 0.0f);

	/// 0, 1, 2 : 구름   3 : 포물선 벌   4 : 랜덤 움직임 벌
	sf::Sprite spriteCloudBee[5];
	sf::Vector2f dirCloudBee[5];
	sf::Vector2f posCloudBee[5];
	float speedCloudBee[5];
	float random, t = 0, beeStopTime = 0;

	for (int i = 0; i < 5; i++)
	{
		random = (float)rand() / RAND_MAX;
		// 구름
		if (i < 3) 
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
			// 포물선 벌
			if (i == 3) 
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
			// 랜덤움직임 벌
			else 
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

	sf::Sprite testLog;
	testLog.setTexture(textureLog);
	testLog.setOrigin(textureLog.getSize().x * 0.5f, textureLog.getSize().y);
	sf::Vector2f logInitPosition = spriteTree.getPosition();
	logInitPosition.x += textureTree.getSize().x * 0.5f;
	logInitPosition.y = textureTree.getSize().y;
	testLog.setPosition(logInitPosition);

	bool isActiveTestLog = false;
	sf::Vector2f testLogDirection = { 1.f,-1.f };
	float testLogSpeed = 2000.f;	

	sf::Vector2f gravity = { 0.f,6000.f };
	sf::Vector2f testLogVelocity = testLogDirection * testLogSpeed;

	/// UI
	sf::Text textScore;
	textScore.setFont(font);
	textScore.setString("SCORE: 0");
	textScore.setCharacterSize(100);
	textScore.setFillColor(sf::Color::White);
	textScore.setPosition(20, 20);

	sf::Text textMessage;
	textMessage.setFont(font);
	textMessage.setString("Press Enter to start!");
	textMessage.setCharacterSize(70);
	textMessage.setFillColor(sf::Color::White);
	textMessage.setPosition(1920.f * 0.5f, 1080 * 0.3f);
	sf::Vector2f messageOrigin;
	messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
	messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
	textMessage.setOrigin(messageOrigin);

	sf::RectangleShape timeBar;
	float timeBarWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize({ timeBarWidth, timeBarHeight });
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition(1920.f * 0.5f - timeBarWidth * 0.5f, 1080.f - 125.f);

	/// 소리 객체
	sf::Sound soundChop;
	soundChop.setBuffer(bufferChop);
	sf::Sound soundDeath;
	soundDeath.setBuffer(bufferDeath);
	sf::Sound soundOutOfTime;
	soundOutOfTime.setBuffer(bufferOutOfTime);

	/// 게임 데이터
	bool isPlaying = false;
	bool isStarted = false;
	int score = 0;
	float remainTime = 5.f;
	float timeBarSpeed = timeBarWidth / 5.f;

	//

	sf::Clock clock;

	bool isLeft = false;
	bool isRight = false;

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
						case sf::Keyboard::Return:
							isPlaying = !isPlaying;
							// 플레이에서 정지로
							if (!isPlaying)
							{
								textMessage.setString("Press Enter to resume!");
								messageOrigin.x = textMessage.getLocalBounds().width * 0.5f;
								messageOrigin.y = textMessage.getLocalBounds().height * 0.5f;
								textMessage.setOrigin(messageOrigin);
							}
							// 정지에서 플레이로, 재시작
							else
							{
								if (remainTime == 0.f || sidePlayer == sideBranch[NUM_BRANCHES - 1])
								{
									score = 0;
									textScore.setString("SCORE: " + std::to_string(score));
									textMessage.setString("Press Enter to restart!");
									remainTime = 5.f;
									sideBranch[NUM_BRANCHES - 1] = Side::NONE;
									isStarted = false;
								}
							}

							if (!isStarted)
							{
								isStarted = true;
							}
							break;
					}
					break;
				default:
					break;
			}
		}

		// 업데이트		
		if (isPlaying)
		{
			/// 타임바 갱신
			remainTime -= deltaTime;
			if (remainTime < 0.f)
			{
				remainTime = 0.f;
				isPlaying = false;
				textMessage.setString("Press Enter to Restart!");
				soundOutOfTime.play();
			}
			timeBar.setSize({ timeBarSpeed * remainTime, timeBarHeight });
 
			/// Left, Right 키 입력시 실행
			if (isLeftDown || isRightDown)
			{
				isActiveTestLog = true;
				testLog.setPosition(logInitPosition);
				testLogVelocity = testLogDirection * testLogSpeed;

				if (isLeftDown)
				{
					sidePlayer = Side::LEFT;
				}
				if (isRightDown)
				{
					sidePlayer = Side::RIGHT;
				}
				updateBranches(sideBranch, NUM_BRANCHES);
				soundChop.play();

				if (sidePlayer == sideBranch[NUM_BRANCHES - 1])
				{
					isPlaying = false;
					textScore.setString("SCORE: " + std::to_string(score));
					textMessage.setString("Press Enter to Restart!");
					soundDeath.play();
				}
				else
				{
					score += 10;
					textScore.setString("SCORE: " + std::to_string(score));
				}
			}

			/// 위치 설정들
			for (int i = 0; i < 5; i++)
			{
				posCloudBee[i] = spriteCloudBee[i].getPosition();
				random = (float)rand() / RAND_MAX;
				// 구름 
				if (i < 3)
				{
					if (posCloudBee[i].x < -400 || posCloudBee[i].x > 1920 + 400)
					{
						if (random < 0.5f)
						{
							dirCloudBee[i] = { 1.0f,0.0f };
							spriteCloudBee[i].setPosition(0, textureCloud.getSize().y * i);
							posCloudBee[i] = spriteCloudBee[i].getPosition();
							spriteCloudBee[i].setScale(-1.0f, 1.0f);
						}
						else
						{
							dirCloudBee[i] = { -1.0f,0.0f };
							spriteCloudBee[i].setPosition(1920, textureCloud.getSize().y * i);
							posCloudBee[i] = spriteCloudBee[i].getPosition();
							spriteCloudBee[i].setScale(1.0f, 1.0f);
						}
					}

					posCloudBee[i] += dirCloudBee[i] * speedCloudBee[i] * deltaTime;
				}
				else
				{
					// 포물선 벌
					if (i == 3)
					{
						if (posCloudBee[i].x < -100 || posCloudBee[i].x > 1920 + 100)
						{
							if (random < 0.5f)
							{
								dirCloudBee[i] = { 1.0f,-1.0f };
								spriteCloudBee[i].setPosition(0, 800);
								posCloudBee[i] = spriteCloudBee[i].getPosition();
								spriteCloudBee[i].setScale(-1.0f, 1.0f);
								t = 0;
							}
							else
							{
								dirCloudBee[i] = { -1.0f,-1.0f };
								spriteCloudBee[i].setPosition(1920, 800);
								posCloudBee[i] = spriteCloudBee[i].getPosition();
								spriteCloudBee[i].setScale(1.0f, 1.0f);
								t = 0;
							}
						}

						posCloudBee[i].x += dirCloudBee[i].x * speedCloudBee[i] * deltaTime;
						posCloudBee[i].y += dirCloudBee[i].y * speedCloudBee[i] * sinf(t) * deltaTime;
						t += 2 * deltaTime;
					}
					// 랜덤움직임 벌
					else
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
									posCloudBee[i] = spriteCloudBee[i].getPosition();
									spriteCloudBee[i].setScale(-1.0f, 1.0f);
								}
								else
								{
									dirCloudBee[i] = { -1.0f,-1.0f };
									spriteCloudBee[i].setPosition(1920, 800);
									posCloudBee[i] = spriteCloudBee[i].getPosition();
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

						posCloudBee[i] += dirCloudBee[i] * speedCloudBee[i] * deltaTime;
					}
				}
				spriteCloudBee[i].setPosition(posCloudBee[i]);
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
		
			if (isActiveTestLog)
			{
				testLogVelocity += gravity * deltaTime;

				sf::Vector2f position = testLog.getPosition();
				position += testLogVelocity * deltaTime;
				testLog.setPosition(position);
			}
		}

		// 그리기
		window.clear();

		/// WORLD
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
		window.draw(testLog);
		window.draw(spritePlayer);
		if ((isLeft || isRight) && isPlaying)
		{
			window.draw(spriteAxe);
		}

		/// UI
		window.draw(textScore);
		if (!isPlaying)
		{
			window.draw(textMessage);
		}
		window.draw(timeBar);
		
		window.display();
	}

	return 0;
}