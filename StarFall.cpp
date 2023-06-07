#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>


using namespace std;
using namespace sf;

void spawnEnemies(RenderWindow& window , vector< CircleShape>& enemies , CircleShape& enemy) {
    //enemies spawning
    enemy.setRadius(20.0f);

    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window.getSize().x - enemy.getRadius())),
        0.0f
    );
    enemy.setFillColor( Color::Green);
    enemies.push_back(enemy);
    
}
void spawnBullets(RectangleShape player, vector<sf::RectangleShape>& bullets, RectangleShape& bullet) {

    bullet.setSize(Vector2f(20.0f, 40.0f));
    bullet.setPosition(player.getPosition());
    bullet.setFillColor(sf::Color::Red);
    bullets.push_back(bullet);
    
}



void updateStars( RenderWindow& window, vector< CircleShape>& stars,  vector<float>& speeds) {
    for (size_t i = 0; i < stars.size(); ++i) {
        stars[i].move(0, speeds[i]);

        if (stars[i].getPosition().y >window.getSize().y) {
            stars[i].setPosition( rand() % window.getSize().x, 0);
        }
    }
}

void drawStars( RenderWindow& window, const  vector< CircleShape>& stars) {
    for (const auto& star : stars) {
        window.draw(star);
    }
}


int main()
{

    //VARIABLES
    const int STAR_COUNT = 100;
    const float STAR_SPEED = 3.0f;
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    int speed = 5;
    int lives = 3;
    int score = 0;
    float gravity = 5.0f;
    int enemySpawnTimerMax = 75.f;
    int enemySpawnTimer = enemySpawnTimerMax;
    int maxEnemies = 10;
    int reloadTimerMax = 5.0f;
    int reloadTimer = reloadTimerMax;
    int bulletspeed = 30.0f;
    int noBullets = 10;
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text BulletText;
    std::vector<sf::RectangleShape> bullets;
    sf::RectangleShape bullet;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Starfall");

    font.loadFromFile("Fonts/SpaceMono-Bold.ttf");

     scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score");
    scoreText.setPosition(Vector2f(10.0f, 10.0f));

    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setString("Score");
    livesText.setPosition(Vector2f(window.getSize().x - 150, 10.0f));

    BulletText.setFont(font);
    BulletText.setCharacterSize(24);
    BulletText.setFillColor(sf::Color::White);
    if (noBullets = 0)
    {
        BulletText.setFillColor(sf::Color::Red);
    }
    BulletText.setString("Bullets");
    BulletText.setPosition(Vector2f(window.getSize().y - 150, 10.0f));




    
    window.setFramerateLimit(60);

     srand(static_cast<unsigned int>( time(NULL)));
    
     vector< CircleShape> stars;
    stars.reserve(STAR_COUNT);
     vector<float> speeds;
    speeds.reserve(STAR_COUNT);

    for (int i = 0; i < STAR_COUNT; ++i) {
        float x =  rand() % WINDOW_WIDTH;
        float y =  rand() % WINDOW_HEIGHT;
        float speed = STAR_SPEED + ( rand() % 5) / 10.0f;

         CircleShape star(1.0f);
        star.setFillColor( Color(255, 255, 255,  rand() % 128 + 128));
        star.setPosition(x, y);

        stars.push_back(star);
        speeds.push_back(speed);
    }


     vector< CircleShape> enemies;
     CircleShape enemy;

    //defining player
     RectangleShape player;
     player.setSize( Vector2f(75.f, 75.f));
     player.setPosition( Vector2f( window.getSize().x / 2,window.getSize().y / 2));
     player.setFillColor( Color::Blue);
     player.setOrigin(player.getSize().x / 2, player.getSize().y / 2);
     player.setOutlineColor( Color::Red);
     player.setOutlineThickness(10);


    

      

      /* bullet.setSize(Vector2f(20.0f, 40.0f));
       bullet.setPosition( player.getPosition());
       bullet.setFillColor( Color::Red);
       bullets.push_back( bullet);
      cout << "Spawn";*/
   

     



    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type ==  Event::Closed)
                window.close();
        }

        //updating happens here

        //movement
        if ( Keyboard::isKeyPressed( Keyboard::W) ||  Keyboard::isKeyPressed( Keyboard::Up) && player.getPosition().y > 0)
            player.move(0, -speed);
        if ( Keyboard::isKeyPressed( Keyboard::S) ||  Keyboard::isKeyPressed( Keyboard::Down) && player.getPosition().y < window.getSize().y)
            player.move(0, speed);
        if ( Keyboard::isKeyPressed( Keyboard::A) ||  Keyboard::isKeyPressed( Keyboard::Left) && player.getPosition().x > 0)
            player.move(-speed, 0);
        if ( Keyboard::isKeyPressed( Keyboard::D) ||  Keyboard::isKeyPressed( Keyboard::Right) && player.getPosition().x < window.getSize().x)
            player.move(speed, 0);

        if ( enemies.size() <  maxEnemies)
        {
            if ( enemySpawnTimer >=  enemySpawnTimerMax)
            {
                 spawnEnemies(window , enemies , enemy);
                 enemySpawnTimer = 0.f;
            }
            else
            {
                 enemySpawnTimer += 1.f;
            }
        }



        //updating enemies
        for (int i = 0; i <  enemies.size(); i++)
        {
             enemies[i].move(0.0f,  gravity);

             
            if ( enemies[i].getGlobalBounds().intersects( bullet.getGlobalBounds()))
            {
                 enemies.erase( enemies.begin() + i);
                 score++;
            }

            if ( enemies[i].getGlobalBounds().intersects( player.getGlobalBounds())) {
                 enemies.erase( enemies.begin() + i);
                lives--;
            }

            else if ( enemies[i].getPosition().y >  window.getSize().y) {
                 enemies.erase( enemies.begin() + i);
                /* score++;*/
            }

        }

        std::stringstream scr;
        scr << "Score: " << score;
        scoreText.setString(scr.str());

        std::stringstream livesstring;
        livesstring << "Lives: " << lives;
        livesText.setString(livesstring.str());


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (reloadTimer >= reloadTimerMax)
            {

                spawnBullets(player , bullets , bullet);
                reloadTimer = 0.f;
            }
        }
        else
        {
            reloadTimer += 1.f;
        }

        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].move(0.0f, -bulletspeed);

            if (bullets[i].getPosition().y < 0) {
                bullets.erase(bullets.begin() + i);
            }
            else {
                for (int j = 0; j < enemies.size(); j++)
                {
                    if (bullets[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
                    {
                        score++;
                        bullets.erase(bullets.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        break;
                    }
                }
            }


        }

        if (lives <= 0) {
            window.close();
        }

        window.clear();
        for (auto& e : bullets)
        {
            window.draw(e);
        }

        //rendering enemies
        for (auto& e :  enemies)
        {
             window.draw(e);
             
        }
        

        


        updateStars( window,stars, speeds);

        drawStars(window, stars);
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(player);
        window.display();
    }

    return 0;
}