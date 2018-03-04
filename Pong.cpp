#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <stdio.h>


int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    // Define some variables
    const float pi          = 3.14159f;
    const int gameWidth     = 800;
    const int gameHeight    = 600;
    const float ballRadius  = 10.f;

    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 0), "Pong",
                            sf::Style::Titlebar | sf::Style::Close);

    // I don't really know how else to start the generation without a 'while' statement check.
    int sizeThrowawayVar = rand()%550;
    while(sizeThrowawayVar<200){
        sizeThrowawayVar = rand()%550;
    }
                            
    // Create the ball
    sf::CircleShape ball;
    ball.setRadius(ballRadius - 3);
    ball.setOutlineThickness(3);
    ball.setOutlineColor(sf::Color::Black);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);

    // Create the obstacle
    sf::RectangleShape obstacle;
    obstacle.setSize(sf::Vector2f(10,sizeThrowawayVar) - sf::Vector2f(3, 3));
    obstacle.setOrigin(sf::Vector2f(10,50) / 2.f);
    obstacle.setOutlineThickness(3);
    obstacle.setOutlineColor(sf::Color::Black);
    obstacle.setFillColor(sf::Color::White);

    // Load the text font
    sf::Font font;
    if (!font.loadFromFile("resources/unifont.ttf"))
        return EXIT_FAILURE;

    // Initialize the pause message
    sf::Text pauseMessage;
    pauseMessage.setFont(font);
    pauseMessage.setCharacterSize(40);
    pauseMessage.setPosition(170.f, 150.f);
    pauseMessage.setString("Welcome to Flappy Ball!\nPress space to start the game");
    pauseMessage.setColor(sf::Color(0, 0, 0));

    // Define the general properties used in-game.
    float obstSpeed=0.10f;
    bool ballSuspended=false;
    sf::Clock jumpTimer;
    sf::Clock clock;
    bool isPlaying  = false;
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (isPlaying && (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::BackSpace))
            {
                clock.restart();

                // Reset the positions
                ball.setPosition(gameWidth / 2, gameHeight/12);
                obstacle.setPosition(gameWidth-12, gameHeight);
            }
            if (isPlaying && (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return))
            {
                pauseMessage.setString("Press Space to start");
                isPlaying=false;
            }
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }

            // Space key pressed: play
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {
                if (!isPlaying)
                {
                    // (re)start the game
                    isPlaying = true;
                    clock.restart();

                    // Reset the positions
                    ball.setPosition(gameWidth / 2, gameHeight/2);
                    obstacle.setPosition(gameWidth-12, gameHeight);
                }
            }
        }

        if (isPlaying)
        {
            float deltaTime = clock.restart().asSeconds();

            // Move the ball
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::U)) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
            (ball.getPosition().y>12)) /* &&
            !(ballSuspended)) I don't really think this works as it's supposed to but whatever. */
            {
                ball.move(0.f, -300 * deltaTime); // Move the ball up 300 px if it isn't already suspended.
                // ballSuspended=true; ====> See comment on line 118
            }
            if(ball.getPosition().y<gameHeight-12){
                ball.move(0.f, 100 * deltaTime);
            }
            else{
                // ballSuspended=false; ====> See comment on line 118
            }
            if(ball.getPosition().y>12) // I don't know why this doesn't error but it works.
            if(obstacle.getPosition().x<=0){
                sizeThrowawayVar = rand()%550;
                while(sizeThrowawayVar<150){
                    sizeThrowawayVar = rand()%550;
                }
                obstacle.setSize(sf::Vector2f(10,sizeThrowawayVar) - sf::Vector2f(3, 3));
                obstacle.setOrigin(sf::Vector2f(10,sizeThrowawayVar) / 2.f);
                obstacle.setPosition(gameWidth,gameHeight-12);
            }

            obstacle.move(-obstSpeed,0.f);
            obstSpeed+=0.000001f;
            /*
            // Check collisions between the ball and the obstacle
            if (ball.getPosition().x-5<obstacle.getPosition().x &&
            ball.getPosition().x+5>obstacle.getPosition().x &&
            ball.getPosition().y<=)
            {
                isPlaying = false;
                pauseMessage.setString("You lost!\nPress space to restart or\nescape to exit");
            }
            */ // This is broken and I don't understand how to fix it. 
        }

        // Clear the window
        window.clear(sf::Color(7, 255, 189));

        if (isPlaying)
        {
            // Draw the obstacle and the ball
            window.draw(ball);
            window.draw(obstacle);
        }
        else
        {
            // Draw the pause message
            window.draw(pauseMessage);
            // Reset ball speed
            obstSpeed=0.5f;
        }

        // Display things on screen
        window.display();
    }

    return EXIT_SUCCESS;
}
