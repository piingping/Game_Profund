#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <fstream>

sf::Vector2f getRandomEnemyPosition(sf::RenderWindow& window)
{
    float x = static_cast<float>(std::rand() % window.getSize().x);
    float y = static_cast<float>(std::rand() % (window.getSize().y / 2)); 
}
struct ScoreEntry {
    std::string name;
    int score;
};

void saveScore(const ScoreEntry& entry, const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << entry.name << " " << entry.score << "\n";
        file.close();
    }
    else {
        std::cerr << "Failed to open the file for saving the score." << std::endl;
    }
}

std::vector<ScoreEntry> getTopFiveScores(const std::string& filename) {
    std::vector<ScoreEntry> scores;
    std::ifstream file(filename);
    if (file.is_open()) {
        ScoreEntry entry;
        while (file >> entry.name >> entry.score) {
            scores.push_back(entry);
        }
        file.close();
    }
    else {
        std::cerr << "Failed to open the file for reading high scores." << std::endl;
    }

 
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
        });

    
    if (scores.size() > 5) {
        scores.resize(5);
    }

    return scores;
}


class Bullet {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;


    Bullet(sf::Vector2f position, sf::Texture& bossBulletTex) 
        : velocity(sf::Vector2f(0.f, 1.f)), shape(sf::Vector2f(100.f, 100.f)) {
        shape.setPosition(position.x - 120.f, position.y);   
        shape.setTexture(&bossBulletTex); 
    }

    void update() {
        shape.move(velocity);
    }
};


int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "StarStrike");
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //SCORE TEXT

    sf::Font font;
    if (!font.loadFromFile("font/CursedTimerUlil-Aznm.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    sf::Font Namefont; 
    if (!Namefont.loadFromFile("font/Chronosferdemo-0WGDo.ttf")) 
    {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }
 
    //MENU TEXT

    sf::Font menufont;
    if (!menufont.loadFromFile("font/rock.TTF"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    sf::Texture bossBulletTex; 

    if (!bossBulletTex.loadFromFile("strite/boss1bullet.png")) {
        std::cerr << "Failed to load texture." << std::endl;
        return 1;
    }

  
    std::vector<Bullet> bossBullets; 

    //HIGHSCORE

    sf::Font playerhighscore;
    if (!playerhighscore.loadFromFile("font/Neon.TTF"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }


    //sound effect
    sf::SoundBuffer shootBuffer;
    if (!shootBuffer.loadFromFile("sound/jiwjiw.wav")) {
        std::cerr << "Failed to load sound effect." << std::endl;
        return 1;
    }

  sf::Sound shootSound; 
    shootSound.setBuffer(shootBuffer); 
    shootSound.setVolume(30);

   
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("sound/bg_sound.ogg")) {
        std::cerr << "Failed to load background music." << std::endl;
        return 1; 
    }

 
    backgroundMusic.setVolume(50); 
    backgroundMusic.setLoop(true); 
    backgroundMusic.play(); 

    // gain item effect
    sf::SoundBuffer itemGainBuffer;
    if (!itemGainBuffer.loadFromFile("sound/gainitem_effect.mp3")) {
        std::cerr << "Failed to load item gain sound effect." << std::endl;
        return 1; 
    }

   
    sf::Sound itemGainSound; 
    itemGainSound.setBuffer(itemGainBuffer); 
    itemGainSound.setVolume(70);

     // Texture

    sf::Texture playerTex;
    if (!playerTex.loadFromFile("strite/spaceship2.png"))
    {
        std::cerr << "Failed to load player texture!" << std::endl;
        return 1; 
    }

    sf::Texture bulletTex;
    if (!bulletTex.loadFromFile("strite/bullet5.png"))
    {
        std::cerr << "Failed to load bullet texture!" << std::endl;
        return 1;
    }

    sf::Texture enemyTex;
    if (!enemyTex.loadFromFile("strite/enemy2.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return 1;
    }

    sf::Texture enemyTex2;
    if (!enemyTex2.loadFromFile("strite/comet.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return 1;
    }

    sf::Texture bossTex;
    if (!bossTex.loadFromFile("strite/boss1.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return 1;
    }
    sf::Texture bossTex2;
    if (!bossTex2.loadFromFile("strite/boss2.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return 1;
    }
    sf::Texture bossTex3;
    if (!bossTex3.loadFromFile("strite/boss3.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return 1;
    }
    sf::Texture itemSpeedUpTex;
    if (!itemSpeedUpTex.loadFromFile("strite/fire.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return 1;
    }

    sf::Texture itemHPTex;
    if (!itemHPTex.loadFromFile("strite/heart.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return 1;
    }
    sf::Texture backgroundMenuTexture;
    if (!backgroundMenuTexture.loadFromFile("wallpaper/city/menu.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1;
    }
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("wallpaper/city/bg1.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1; 
    }
    sf::Texture backgroundTexture2;
    if (!backgroundTexture2.loadFromFile("wallpaper/city/bg2.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1;
    }
    sf::Texture backgroundTexture3;
    if (!backgroundTexture3.loadFromFile("wallpaper/city/bg3.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1;
    }
    sf::Texture backgroundTexture4;
    if (!backgroundTexture4.loadFromFile("wallpaper/city/bg4.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1;
    }

    sf::Texture ScoreBoardTexture;
    if (!backgroundTexture4.loadFromFile("wallpaper/city/ScoreBoard.jpg"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1; 
    }

   
    Bullet bullet(sf::Vector2f(100.f, 100.f), bossBulletTex);

    const std::string filename = "text/highscores.txt";
    std::vector<ScoreEntry> highScores = getTopFiveScores(filename);

    playerTex.setSmooth(true);
    bulletTex.setSmooth(true);
    enemyTex.setSmooth(true);
    enemyTex2.setSmooth(true);
    bossTex.setSmooth(true);
    bossTex2.setSmooth(true);
    bossTex3.setSmooth(true);
    itemSpeedUpTex.setSmooth(true);
    itemHPTex.setSmooth(true);
    bossBulletTex.setSmooth(true);
    backgroundTexture.setSmooth(true);
    backgroundTexture2.setSmooth(true);
    backgroundTexture3.setSmooth(true);
    backgroundTexture4.setSmooth(true);


    sf::Vector2f mousePos;
    std::vector<sf::RectangleShape> bullets; 
    std::vector<sf::Vector2f> bulletVelocities; 
    std::vector<sf::RectangleShape> enemies;
    std::vector<sf::RectangleShape> enemies2;
    std::vector<sf::RectangleShape> itemSpeedUps;
    std::vector<sf::RectangleShape> itemHPUps;
    std::vector<sf::RectangleShape> bossEnemies;
    sf::RectangleShape itemHPUp(sf::Vector2f(45.f, 45.f));
    sf::RectangleShape itemSpeedUp(sf::Vector2f(45.f, 45.f));
    std::string inputName;

    // speed up
    itemSpeedUp.setFillColor(sf::Color::White);
    itemSpeedUp.setTexture(&itemSpeedUpTex);
    //HP
    itemHPUp.setFillColor(sf::Color::White);
    itemHPUp.setTexture(&itemHPTex);

    sf::RectangleShape pinkSquare(sf::Vector2f(200.f, 200.f));
    pinkSquare.setOrigin(pinkSquare.getSize() / 2.f);
    pinkSquare.setPosition(window.getSize().x / 2.f, window.getSize().y - 100.f);
    pinkSquare.setTexture(&playerTex);


    sf::Sprite backgroundSprite4;
    backgroundSprite4.setTexture(backgroundTexture4);
    backgroundSprite4.setPosition(0, 0); 
    sf::Sprite backgroundSprite3;
    backgroundSprite3.setTexture(backgroundTexture3);
    backgroundSprite3.setPosition(0, 0); 
    sf::Sprite backgroundSprite2;
    backgroundSprite2.setTexture(backgroundTexture2);
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0); 
    sf::Sprite backgroundSpriteMenu;
    backgroundSpriteMenu.setTexture(backgroundMenuTexture);
    backgroundSpriteMenu.setPosition(0, 0); 


    //TEXT

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setString("Score: 0");
    scoreText.setPosition(20.f / 2, 30.f);

    sf::Text HPtext;
    HPtext.setFont(menufont);
    HPtext.setCharacterSize(45);
    HPtext.setFillColor(sf::Color::White);
    HPtext.setString("HP: 100");
    HPtext.setPosition(20.f, 100.f);


    // play button
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setPosition(900.f, 500.f);
    playButton.setFillColor(sf::Color::White);

    sf::Text playText("Play", menufont, 24);
    playText.setPosition(975.f, 510.f);
    playText.setFillColor(sf::Color::Black);

    //scoreboard button
    sf::RectangleShape  ScoreBoardButton(sf::Vector2f(200, 50));
    ScoreBoardButton.setPosition(900.f, 600.f);
    ScoreBoardButton.setFillColor(sf::Color::White);

    sf::Text  ScoreBoardText("ScoreBoard", menufont, 24);
    ScoreBoardText.setPosition(940.f, 610.f);
    ScoreBoardText.setFillColor(sf::Color::Black);

    //  exit button
    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setPosition(900.f, 700.f);
    exitButton.setFillColor(sf::Color::White);


    sf::Text exitText("Exit", menufont, 24);
    exitText.setPosition(975.f, 710.f);
    exitText.setFillColor(sf::Color::Black);

    sf::Text playerName;
    playerName.setFont(Namefont);
    playerName.setCharacterSize(100);
    playerName.setFillColor(sf::Color::Yellow);
    playerName.setPosition(1000, 300);
    playerName.setString("Enter your name:");

    sf::Text nameText;
    nameText.setFont(Namefont);
    nameText.setCharacterSize(70);
    nameText.setFillColor(sf::Color::White);
    nameText.setPosition(1000, 400);


    sf::Text highScoretext;
    highScoretext.setFont(playerhighscore);
    highScoretext.setCharacterSize(60);
    highScoretext.setFillColor(sf::Color::Yellow);

    sf::Text playerhighScoretext;
    playerhighScoretext.setFont(menufont);
    playerhighScoretext.setCharacterSize(24);
    playerhighScoretext.setFillColor(sf::Color::White);


  

    sf::Clock bulletCooldown; 
    sf::Clock delayTimer;
    sf::Clock speedUpTimer;
    sf::Clock bossShootTimer;

    

    float bulletSpeed = 0.3f;
    int bossHp = 100;
    float movementSpeed = 0.3f;
    bool isSpeedUpActive = false;
    bool canMove = true;
    float speedUpDuration = 5.0f;
    float bulletDelay = 0.2f; 

    bool bossDefeated = false;
    bool bossDefeated2 = false;
    bool bossDefeated3 = false;

    //item
    int score = 0;
    bool canDropIt = false;
    bool canDropSpIt = false;
    bool canDropHpIt = false;

    int firstTime = 0;
    int firstTime2 = 0;
    int firstTime3 = 0;

    const int numEnemies = 4;
    const int numEnemies2 = 6;
    const int numitemHPUps = 1;
    const int numitemSpeedUps = 1;
    const int numBossEnemies = 1; 

    int hp = 100;
    int stage = 0;
    bool showPassStagePopup = false;
    int reset = 0;

    enemies.clear();
    enemies2.clear();
    itemHPUps.clear();
    itemSpeedUps.clear();
    bossEnemies.clear();
    inputName.clear();
    for (int i = 0; i < numEnemies; ++i)
    {
        sf::RectangleShape enemy(sf::Vector2f(60.f, 60.f));
        enemy.setPosition(getRandomEnemyPosition(window));
        enemy.setTexture(&enemyTex);
      
        enemies.push_back(enemy);
    }

    for (int i = 0; i < numEnemies2; ++i)
    {
        sf::RectangleShape enemy2(sf::Vector2f(100.f, 100.f));
        enemy2.setPosition(getRandomEnemyPosition(window));
        enemy2.setTexture(&enemyTex2);
       
        enemies2.push_back(enemy2);
    }
   

    for (int i = 0; i < numitemSpeedUps; ++i)
    {
        sf::RectangleShape itemSpeedUp(sf::Vector2f(30.f, 30.f));

        itemSpeedUp.setTexture(&itemSpeedUpTex);
      
        itemSpeedUps.push_back(itemSpeedUp);
    }

    for (int i = 0; i < numitemHPUps; ++i)
    {
        sf::RectangleShape itemHPup(sf::Vector2f(30.f, 30.f));

        itemHPUp.setTexture(&itemHPTex);
        
        itemHPUps.push_back(itemHPUp);
    }

for (int i = 0; i < numBossEnemies; ++i)
{
    sf::RectangleShape bossEnemy(sf::Vector2f(300.f, 300.f));
    bossEnemy.setOrigin(bossEnemy.getSize());
    bossEnemy.setPosition(5000.f, 5000.f); 
    bossEnemy.setTexture(&bossTex);
    bossEnemies.push_back(bossEnemy);
}
   


    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            if (stage == 1) {
               
              


                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 13) { 

                            nameText.setString(inputName);
                            stage = 2;
                        }
                        else if (event.text.unicode == 8 && !inputName.empty()) { 
                            inputName.pop_back();
                        }
                        else {
                            std::cout << inputName << std::endl;
                            inputName += static_cast<char>(event.text.unicode);

                        }
                        nameText.setString(inputName);
                    }
                }
            }
        }
        if (stage == 0) {

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

           
            if (playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                playButton.setFillColor(sf::Color::Yellow);
            }
            else {
                playButton.setFillColor(sf::Color::White);  
            }

           
            if (ScoreBoardButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                ScoreBoardButton.setFillColor(sf::Color::Yellow);  
            }
            else {
                ScoreBoardButton.setFillColor(sf::Color::White); 
            }

           
            if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                exitButton.setFillColor(sf::Color::Yellow); 
            }
            else {
                exitButton.setFillColor(sf::Color::White); 
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                   
                    if (playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                      
                        std::cout << reset << std::endl;
                        if (reset == 1) {
                            bulletCooldown.restart();
                            delayTimer.restart();
                            speedUpTimer.restart();
                            bossShootTimer.restart();

                            score = 0;

                            bulletSpeed = 0.3f;
                            bossHp = 100;
                            movementSpeed = 0.3f;
                            isSpeedUpActive = false;
                            canMove = true;
                            speedUpDuration = 5.0f;

                            bossDefeated = false;
                            bossDefeated2 = false;
                            bossDefeated3 = false;

                            //item
                            canDropIt = false;
                            canDropSpIt = false;
                            canDropHpIt = false;

                            firstTime = 0;
                            firstTime2 = 0;
                            firstTime3 = 0;



                            hp = 100;
                            showPassStagePopup = false;

                            enemies.clear();
                            enemies2.clear();
                            itemHPUps.clear();
                            itemSpeedUps.clear();
                            bossEnemies.clear();
                            inputName.clear();
                            scoreText.setString("Score: 0");
                            HPtext.setString("HP: 100");
                            for (int i = 0; i < numEnemies; ++i)
                            {
                                sf::RectangleShape enemy(sf::Vector2f(60.f, 60.f));
                                enemy.setPosition(getRandomEnemyPosition(window));
                                enemy.setTexture(&enemyTex);
                             
                                enemies.push_back(enemy);
                            }

                            for (int i = 0; i < numEnemies2; ++i)
                            {
                                sf::RectangleShape enemy2(sf::Vector2f(100.f, 100.f));
                                enemy2.setPosition(getRandomEnemyPosition(window));
                                enemy2.setTexture(&enemyTex2);
                          
                                enemies2.push_back(enemy2);
                            }


                            for (int i = 0; i < numitemSpeedUps; ++i)
                            {
                                sf::RectangleShape itemSpeedUp(sf::Vector2f(30.f, 30.f));

                                itemSpeedUp.setTexture(&itemSpeedUpTex);
                               
                                itemSpeedUps.push_back(itemSpeedUp);
                            }


                            for (int i = 0; i < numitemHPUps; ++i)
                            {
                                sf::RectangleShape itemHPup(sf::Vector2f(30.f, 30.f));

                                itemHPUp.setTexture(&itemHPTex);
                              
                                itemHPUps.push_back(itemHPUp);
                            }

                            for (int i = 0; i < numBossEnemies; ++i)
                            {
                                sf::RectangleShape bossEnemy(sf::Vector2f(300.f, 300.f));
                                bossEnemy.setOrigin(bossEnemy.getSize());
                                bossEnemy.setPosition(5000.f, 5000.f);
                                bossEnemy.setTexture(&bossTex);
                                bossEnemies.push_back(bossEnemy);
                            }
         
                            reset = 0;
                      

                        }
                        stage = 1;
                       
                        std::cout << "Play button clicked" << std::endl;
                    }
                    if (ScoreBoardButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        stage = 4;
                      
                    }
                    if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        window.close();
                    }
                }
            }
        }


        if (stage == 4) {

            if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                stage = 0;
            }

        }



        if (stage == 2) {



            if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                stage = 0;
            }

            if ((bossHp <= 0 && !bossDefeated && !bossDefeated2) && firstTime2 == 0) {
                bossDefeated = true;
                backgroundSprite = backgroundSprite2;
                showPassStagePopup = true;
            }
            if (bossHp <= 0 && !bossDefeated2 && firstTime2 == 1 && firstTime3 == 0) {
                bossDefeated2 = true;
                backgroundSprite = backgroundSprite3;
                showPassStagePopup = true;
            }
            if (bossHp <= 0 && !bossDefeated3 && firstTime2 == 1 && firstTime3 == 1) {
                bossDefeated3 = true;
                backgroundSprite = backgroundSprite4;
                showPassStagePopup = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletCooldown.getElapsedTime().asSeconds() >= bulletDelay)
            {
                sf::RectangleShape bullet(sf::Vector2f(100.f, 100.f));
                bullet.setFillColor(sf::Color::White);
                bullet.setTexture(&bulletTex);

                bullet.setPosition(pinkSquare.getPosition().x - bullet.getSize().x / 2,
                    pinkSquare.getPosition().y - pinkSquare.getSize().y / 2 - bullet.getSize().y);

                sf::Vector2f bulletVelocity(0, -bulletSpeed);

                //sound effect
                Bullet playerBullet(pinkSquare.getPosition(), bossBulletTex);
                
                // Play the shoot sound effect
                shootSound.play();

                bullets.push_back(bullet);
                bulletCooldown.restart();
            }
            for (size_t i = 0; i < bullets.size(); ++i)
            {
                bullets[i].move(0, -bulletSpeed);
                if (bullets[i].getPosition().y < 0)
                {
                    bullets.erase(bullets.begin() + i);
                }
                else
                {
                    for (size_t j = 0; j < enemies.size(); ++j)
                    {
                        if (bullets[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
                        {
                            if (rand() % 3 == 0 && canDropIt == 0) {
                                if (rand() % 2 == 0) {
                                    if (canDropSpIt == 0 && canDropHpIt == 0) {
                                        for (size_t k = 0; k < itemSpeedUps.size(); ++k) {

                                            itemSpeedUps[k].setPosition(enemies[j].getPosition().x, enemies[j].getPosition().y + 20);
                                            canDropIt = 1;
                                            canDropSpIt = 1;
                                        }
                                    }

                                }
                                else {
                                    if (canDropHpIt == 0 && canDropSpIt == 0) {
                                        for (size_t k = 0; k < itemHPUps.size(); ++k)
                                        {

                                            itemHPUps[k].setPosition(enemies[j].getPosition().x, enemies[j].getPosition().y + 20);
                                            canDropIt = 1;
                                            canDropHpIt = 1;
                                        }
                                    }

                                }
                            }

                            enemies[j].setPosition(getRandomEnemyPosition(window));
                            bullets.erase(bullets.begin() + i);
                            score = score + 3; 

                            scoreText.setString("Score: " + std::to_string(score)); 
                            scoreText.setPosition(20.f / 2, 30.f);
                            break; 
                        }
                    }
                }
            }
            if (canDropIt == 1) {
                if (canDropSpIt == 1) {

                    for (size_t k = 0; k < itemSpeedUps.size(); ++k) {

                        itemSpeedUps[k].move(0, 0.1f);

                        if (itemSpeedUps[k].getPosition().y > 1080) {
                            canDropIt = 0;
                            canDropSpIt = 0;
                        }

                    }
                }
                if (canDropHpIt == 1) {
                    for (size_t k = 0; k < itemHPUps.size(); ++k) {

                        itemHPUps[k].move(0, 0.1f);

                        if (itemHPUps[k].getPosition().y > 1080) {
                            canDropIt = 0;
                            canDropHpIt = 0;


                        }

                    }
                }


            }

            for (size_t i = 0; i < bullets.size(); ++i)
            {
                bullets[i].move(0, -bulletSpeed);
                if (bullets[i].getPosition().y < 0)
                {
                    bullets.erase(bullets.begin() + i);
                }
                else
                {
                    for (size_t j = 0; j < enemies2.size(); ++j)
                    {
                        if (bullets[i].getGlobalBounds().intersects(enemies2[j].getGlobalBounds()))
                        {
                            enemies2[j].setPosition(getRandomEnemyPosition(window));
                            bullets.erase(bullets.begin() + i);
                            score++; 

                            scoreText.setString("Score: " + std::to_string(score));
                            scoreText.setPosition(20.f / 2, 30.f);
                            break; 
                        }
                    }
                }
            }
            for (size_t i = 0; i < bullets.size(); ++i)
            {
               
                bullets[i].move(0, -bulletSpeed);
                if (bullets[i].getPosition().y < 0)
                {
                    bullets.erase(bullets.begin() + i);
                }
                else
                {
                    for (size_t j = 0; j < bossEnemies.size(); ++j)
                    {
                        if (bullets[i].getGlobalBounds().intersects(bossEnemies[j].getGlobalBounds()))
                        {
                            bullets.erase(bullets.begin() + i);
                            bossHp -= 20;
                            if (bossHp <= 0)
                            {
                               
                                score += 20;
                                bossEnemies[j].setPosition(5000.f, 5000.f);
                                
                            }
                            break;
                        }
                    }

                }
            }

            float enemySpeed = 0.1f;
            
            for (size_t i = 0; i < enemies.size(); ++i)
            {
                sf::Vector2f enemyPos = enemies[i].getPosition();
                sf::Vector2f playerPos = pinkSquare.getPosition();

                sf::Vector2f direction = playerPos - enemyPos;
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                if (length != 0)
                {
                    direction /= length;
                }

              
                enemies[i].move(direction.x * enemySpeed, direction.y * enemySpeed);
            }

            float enemy2Speed = 0.1f;
         
            for (size_t i = 0; i < enemies2.size(); ++i)
            {
                sf::Vector2f enemy2Pos = enemies2[i].getPosition();

                
                enemies2[i].move(enemy2Speed, enemy2Speed);
            }

      
            for (size_t i = 0; i < enemies.size(); ++i)
            {
                if (pinkSquare.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
                {
                   
                    enemies[i].setPosition(getRandomEnemyPosition(window));
                   
                    hp--;

                    HPtext.setString("HP: " + std::to_string(hp)); 
                    HPtext.setPosition(20.f, 100.f);
                    break; 
                }
            }

            for (size_t i = 0; i < enemies2.size(); i++) {
                if (enemies2[i].getPosition().y > 1080 || enemies2[i].getPosition().x > 1920) {
                    enemies2[i].setPosition(getRandomEnemyPosition(window));

                }

                else if (pinkSquare.getGlobalBounds().intersects(enemies2[i].getGlobalBounds())) {
                    enemies2[i].setPosition(getRandomEnemyPosition(window));
                    hp--;

                    HPtext.setString("HP: " + std::to_string(hp)); 
                    HPtext.setPosition(20.f, 100.f);
                    break; 
                }
            }

            for (size_t i = 0; i < itemSpeedUps.size(); ++i)
            {
                if (pinkSquare.getGlobalBounds().intersects(itemSpeedUps[i].getGlobalBounds()))
                {
                  
                    itemSpeedUps[i].setPosition(getRandomEnemyPosition(window));

                    //SpeedUp sound effect
                    itemGainSound.play();

                    
                    if (isSpeedUpActive == false) {
                        canDropIt = 0;
                        canDropSpIt = 0;
                        movementSpeed += 1.0f;
                        speedUpTimer.restart();
                        isSpeedUpActive = true;

                    }
                }
            }
            if (score > 100 && firstTime2 != 1) {
                if (firstTime2 == 0) {
                    for (int i = 0; i < numBossEnemies; ++i)
                    {
                        sf::RectangleShape bossEnemy(sf::Vector2f(300.f, 300.f)); 
                        bossEnemy.setOrigin(bossEnemy.getSize());
                        bossEnemy.setPosition(5000.f, 5000.f); 
                        bossEnemy.setTexture(&bossTex2);
                        bossEnemies.pop_back();
                        bossEnemies.push_back(bossEnemy);
                    }
                    bossEnemies[0].setPosition(window.getSize().x / 2.f, 300.f);

                    firstTime2 = 1;
                    bossHp = 200;
                }

            }
            if (score > 200 && firstTime3 != 1) {
                if (firstTime3 == 0) {
                    for (int i = 0; i < numBossEnemies; ++i)
                    {
                        sf::RectangleShape bossEnemy(sf::Vector2f(300.f, 300.f)); 
                        bossEnemy.setOrigin(bossEnemy.getSize());
                        bossEnemy.setPosition(5000.f, 5000.f); 
                        bossEnemy.setTexture(&bossTex3);
                        bossEnemies.pop_back();
                        bossEnemies.push_back(bossEnemy);
                    }
                    bossEnemies[0].setPosition(window.getSize().x / 2.f, 300.f);

                    firstTime3 = 1;
                    bossHp = 300;
                }

            }
            if (score > 20) {

                for (size_t i = 0; i < bossEnemies.size(); ++i)
                {
                    if (firstTime == 0) {
                        bossEnemies[i].setPosition(window.getSize().x / 2.f, 300.f);
                        firstTime = 1;
                    }
                    float leftLimit = 800.0f;
                    float rightLimit = 1400.0f;

                    float movementSpeed = 0.2f;

                   
                    static bool moveRight = true; 
                    sf::Vector2f currentPosition = bossEnemies[i].getPosition();

                    if (moveRight)
                    {
                        bossEnemies[i].move(movementSpeed, 0.0f); 
                        if (currentPosition.x >= rightLimit)
                        {
                            moveRight = false; 
                        }
                    }

                    else
                    {
                        bossEnemies[i].move(-movementSpeed, 0.0f); 
                        if (currentPosition.x <= leftLimit)
                        {
                            moveRight = true; 
                        }
                    }

                    if (bossShootTimer.getElapsedTime().asSeconds() >= 0.4f) {
                      

                        sf::Vector2f bossBulletPosition = (bossEnemies[0].getPosition()); 
                        Bullet bossBullet(bossBulletPosition, bossBulletTex);
                        bossBullets.push_back(bossBullet);
                        bossShootTimer.restart();
                    }


                    for (size_t i = 0; i < bossBullets.size(); ++i) {
                        bossBullets[i].update();
                        window.draw(bossBullets[i].shape);

                       
                        if (pinkSquare.getGlobalBounds().intersects(bossBullets[i].shape.getGlobalBounds())) {
                          
                            hp -= 5;
                            bossBullets.erase(bossBullets.begin() + i);
                        }
                    }

                }
            }

            if (score > 20) {

                for (size_t i = 0; i < bossEnemies.size(); ++i)
                {
                    if (firstTime == 0) {
                        bossEnemies[i].setPosition(window.getSize().x / 2.f, 300.f);
                        firstTime = 1;
                    }
                    float leftLimit = 800.0f;
                    float rightLimit = 1400.0f;

                    float movementSpeed = 0.2f;

                    
                    static bool moveRight = true;
                    sf::Vector2f currentPosition = bossEnemies[i].getPosition();

                    if (moveRight)
                    {
                        bossEnemies[i].move(movementSpeed, 0.0f); 
                        if (currentPosition.x >= rightLimit)
                        {
                            moveRight = false;
                        }
                    }

                    else
                    {
                        bossEnemies[i].move(-movementSpeed, 0.0f); 
                        if (currentPosition.x <= leftLimit)
                        {
                            moveRight = true;
                        }
                    }

                   
                    if (bossShootTimer.getElapsedTime().asSeconds() >= 0.4f) {
                       

                        sf::Vector2f bossBulletPosition = (bossEnemies[0].getPosition()); 

                       
                        Bullet bossBullet(bossBulletPosition, bossBulletTex);

                        bossBullets.push_back(bossBullet);

                     
                        bossShootTimer.restart();
                    }


                    for (size_t i = 0; i < bossBullets.size(); ++i) {
                        bossBullets[i].update();
                        window.draw(bossBullets[i].shape);

                        if (pinkSquare.getGlobalBounds().intersects(bossBullets[i].shape.getGlobalBounds())) {
                         
                            hp -= 5;
                            bossBullets.erase(bossBullets.begin() + i);
                        }
                    }

                }
            }



            for (size_t i = 0; i < itemHPUps.size(); ++i)
            {
                if (pinkSquare.getGlobalBounds().intersects(itemHPUps[i].getGlobalBounds()))
                {
                    // Collision with player, remove the enemy
                    itemHPUps[i].setPosition(getRandomEnemyPosition(window));
        
                    itemGainSound.play();
                    hp += 5;
                    canDropIt = 0;
                    canDropHpIt = 0;

                }
            }

            if (isSpeedUpActive)
            {

                if (speedUpTimer.getElapsedTime().asSeconds() >= speedUpDuration)
                {
                    

                    isSpeedUpActive = false;
                    movementSpeed -= 1.0f;
                    speedUpTimer.restart();

                }
            }
            if (hp <= 0)
            {

                ScoreEntry entry;
                entry.name = inputName;
                entry.score = score;
                saveScore(entry, filename);
                reset = 1;
                stage = 0;


            }

            if (canMove)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    if (pinkSquare.getPosition().y > 0)
                        pinkSquare.move(0, -movementSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    if (pinkSquare.getPosition().x > 0)
                        pinkSquare.move(-movementSpeed, 0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    if (pinkSquare.getPosition().y + pinkSquare.getSize().y < window.getSize().y)
                        pinkSquare.move(0, movementSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    if (pinkSquare.getPosition().x + pinkSquare.getSize().x < window.getSize().x + 50)
                        pinkSquare.move(movementSpeed, 0);
                }
            }

            window.clear(sf::Color::White);

            if (!bossDefeated) {

                window.draw(backgroundSprite);
            }
            else if (bossDefeated && !bossDefeated2) {



                window.draw(backgroundSprite2);

            }
            else if (bossDefeated && bossDefeated2 && !bossDefeated3) {



                window.draw(backgroundSprite3);

            }
            else if (bossDefeated && bossDefeated2 && bossDefeated3) {

                window.draw(backgroundSprite4);

            }


        }
        if (stage == 0) {

            window.clear();
            window.draw(backgroundSpriteMenu);
       
            window.draw(playButton);
            window.draw(playText);
            window.draw(ScoreBoardButton);
            window.draw(ScoreBoardText);
            window.draw(exitButton);
            window.draw(exitText);

            window.display();
        }
        if (stage == 1) {
            
            window.clear();
            window.draw(backgroundSprite4);
            window.draw(playerName);
            window.draw(nameText);
            window.display();

        }
        if (stage == 2) {

            for (auto& bullet : bullets)
            {
                window.draw(bullet);
            }
            for (auto& bullet : bossBullets) {
                bullet.update();
                window.draw(bullet.shape);
            }

            for (auto& enemy : enemies)
            {
                window.draw(enemy);
            }

            for (auto& enemy2 : enemies2)
            {
                window.draw(enemy2);
            }
            if (canDropIt == 1) {
                if (canDropSpIt == 1) {

                    for (auto& itemSpeedUp : itemSpeedUps)
                    {
                        window.draw(itemSpeedUp);
                    }
                }
                if (canDropHpIt == 1) {


                    for (auto& itemHPUp : itemHPUps)
                    {
                        window.draw(itemHPUp);
                    }
                }
            }

            window.draw(pinkSquare);
            window.draw(scoreText);
            if (score > 20) {
                window.draw(bossEnemies[0]);
            }
            

            window.draw(HPtext);
            window.display();
        }
        if (stage == 4) {

            highScores = getTopFiveScores(filename);
            window.draw(backgroundSprite4);
            highScoretext.setString("HighScore");
            highScoretext.setPosition(900,350);
            window.draw(highScoretext);
            for (size_t i = 0; i < highScores.size(); ++i) {
                playerhighScoretext.setString(highScores[i].name + ": " + std::to_string(highScores[i].score));
                playerhighScoretext.setPosition(900, 450 + i * 40);
                window.draw(playerhighScoretext);
            }
            window.display();
        }
    }

    return 0;
}
