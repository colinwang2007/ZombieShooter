//imports and namespaces
#include "Player.h"
//#include "Zombie.h"
#include "ZombieArena.h"
//#include "pathBase.h"
#include <sstream>
#include <cstdlib>
#include <SFML/graphics.hpp>
#include <string>
#include <iostream>
#include "TextureHolder.h"
#include "Bullet.h"
using namespace sf;
using namespace std;
const int HEIGHT=1080;
const int WIDTH = 1920;

static String pathBase = "/Users/colinwang/Downloads/media_zombieShooter/";
enum class State {
    PAUSED, LEVELING_UP, GAME_OVER, PLAYING, MENU, OPTIONS, COUNTDOWN
};
int main() {
//    int ZOMBIE_NUM = 5;
//    Zombie zombie[ZOMBIE_NUM];
//    for(int i=0; i<ZOMBIE_NUM; i++) {
//        zombie[i];
//    }
    // enum class


    State state = State::MENU;
    State prevstate = State::MENU;

    VideoMode vm(WIDTH, HEIGHT);
    RenderWindow window(vm, "Zombie Shooter");
    Vector2f resolution = Vector2f(WIDTH, HEIGHT);
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
    IntRect arena;
    arena = IntRect(0, 0, WIDTH*2, HEIGHT*2);

    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;


    //__________________________________________________BACKGROUND AND SPRITER TEXTURES________________________________________________________________________________________

    //background has 4 different type of blocks
    TextureHolder holder;
    Texture textureBackground = TextureHolder::GetTexture(pathBase+"background_sheet.png");
    VertexArray background;
    background.setPrimitiveType(Quads);
    createBackground(background,arena);

    //Background in the menu
    Texture menutexture;
    Sprite menubackground;
    menutexture.loadFromFile(pathBase+"background.png");
    menubackground.setTexture(menutexture);




    //__TEXTS__




    //create a font
    Font font;
    font.loadFromFile(pathBase+"zombiecontrol.ttf");

    //Text in the menu
    Text menuText;
    menuText.setFont(font);
    menuText.setString("ZOMBIE SHOOTER");
    menuText.setCharacterSize(150);
    menuText.setOutlineThickness(3);
    menuText.setFillColor(Color::White);
    menuText.setPosition(500, 200);

    //Score
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score = 0");
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(0, 0);

    //HIGHscore text
    Text HighScore;
    HighScore.setFont(font);
    HighScore.setString("HighScore = 0");
    HighScore.setCharacterSize(50);
    HighScore.setFillColor(Color::White);
    HighScore.setPosition(0, 75);

    //Health Text
    Text healthText;
    healthText.setFont(font);
    healthText.setString("Health = 0");
    healthText.setCharacterSize(50);
    healthText.setFillColor(Color::White);
    healthText.setPosition(0, 150);

    //Text showing how much time passed
    Text timeText;
    timeText.setFont(font);
    timeText.setString("");
    timeText.setCharacterSize(50);
    timeText.setFillColor(Color::White);
    timeText.setPosition(0, 150);

    //The text during countdown
    Text countdowntext;
    countdowntext.setFont(font);
    countdowntext.setString(" ");
    countdowntext.setCharacterSize(100);
    countdowntext.setFillColor(Color::White);
    countdowntext.setPosition(900, 540);

    //CREATE SOME BUTTONS



    //PLAY button
    RectangleShape playbutton;
    playbutton.setSize(Vector2f(360, 240));
    playbutton.setFillColor(Color(255, 255, 0));
    playbutton.setPosition(WIDTH / 2 - 180, HEIGHT / 2 - 120);
    playbutton.setOutlineThickness(3);
    playbutton.setOutlineColor(Color::Black);

    Text playbuttontext;
    playbuttontext.setFont(font);
    playbuttontext.setString("  Play\n(Enter)");
    playbuttontext.setCharacterSize(100);
    playbuttontext.setOutlineThickness(3);
    playbuttontext.setFillColor(Color::White);
    playbuttontext.setPosition(playbutton.getPosition().x + 10, playbutton.getPosition().y + 10);



    //OPTIONS BUTTON
    CircleShape optionsbutton;
    optionsbutton.setRadius(200);
    optionsbutton.setFillColor(Color(0, 255, 255));
    optionsbutton.setPosition(WIDTH - optionsbutton.getRadius() - 50, HEIGHT - optionsbutton.getRadius() - 50);
    optionsbutton.setOutlineThickness(3);

    Text optionsbuttontext;
    optionsbuttontext.setFont(font);
    optionsbuttontext.setCharacterSize(50);
    optionsbuttontext.setOutlineThickness(3);
    optionsbuttontext.setFillColor(Color::White);
    optionsbuttontext.setPosition(optionsbutton.getPosition().x + 50, optionsbutton.getPosition().y + 90);


    //PAUSE BUTTON
    CircleShape pauseButton;
    pauseButton.setRadius(50);
    pauseButton.setFillColor(Color(255, 155, 0));
    pauseButton.setPosition(WIDTH - pauseButton.getRadius() * 2 - 50, 50);
    pauseButton.setOutlineThickness(3);

    Text pauseButtonText;
    pauseButtonText.setFont(font);
    pauseButtonText.setLetterSpacing(0);
    pauseButtonText.setCharacterSize(50);
    pauseButtonText.setFillColor(Color::White);
    pauseButtonText.setPosition(WIDTH - pauseButton.getRadius() * 2 - 15, 74);

    //QUIT BUTTON
    RectangleShape quitbutton;
    quitbutton.setSize(Vector2f(250, 150));
    quitbutton.setFillColor(Color(200, 200, 200));
    quitbutton.setPosition(0, 870);

    Text quitbuttontext;
    quitbuttontext.setFont(font);
    quitbuttontext.setString("Quit (Q)");
    quitbuttontext.setCharacterSize(50);
    quitbuttontext.setFillColor(Color::White);
    quitbuttontext.setPosition(10, 880);


    //GAMEOVER BUTTON
    RectangleShape gameoverbutton;
    gameoverbutton.setSize(Vector2f(400, 200));
    gameoverbutton.setFillColor(Color(255, 0, 0));
    gameoverbutton.setPosition(660, 540);

    Text gameoverbuttontext;
    gameoverbuttontext.setFont(font);
    gameoverbuttontext.setString("Continue");
    gameoverbuttontext.setCharacterSize(100);
    gameoverbuttontext.setFillColor(Color::White);
    gameoverbuttontext.setPosition(680, 560);

    //__________________________________________________LOOP SETUP________________________________________________________________________________________


    //Setup time
    Clock clock;
    Time timepassed;

    //Help close the game
    int close = 0;

    bool mousePressed = false;
    bool canclick = false;

    int countdown = 3;
    int countdownclock = 0;

    //SCORESHEALTH
    int score = 0;
    int highscore = 0;

    //create a player
    Player player;

    //create zombies
    int numZombies;
    int numZombiesAlive;
    Zombie* zombies = nullptr;

    //SETUP bullets
    Bullet bullet;
    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 100000;
    int clipSize = 10000000;
    float fireRate = 1;
    Time lastPressed;//last fired



    // Hide the mouse pointer and replace it with crosshair @TODO
    window.setMouseCursorVisible(true);
    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::GetTexture(pathBase+"crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    spriteCrosshair.setOrigin(25, 25);


    // Create a couple of pickups
//    Pickup healthPickup(1);@TODO
//    Pickup ammoPickup(2);


    //__________________________________________________START THE GAME LOOP________________________________________________________________________________________


    while (window.isOpen()) {
        //CREATE A NEW EVENT
        Event event;
        window.pollEvent(event);

        //Closing game event
        if (event.type == Event::Closed) {
            if (close > 1) {
                window.close();
            }
            close++;
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        //reset a screen
        window.clear();


        //See if mouse is pressed
        if (event.type == Event::MouseButtonPressed) {
            mousePressed = true;
        }
        if (event.type == Event::MouseButtonReleased) {
            mousePressed = false;
        }


        //__________________________________________________MENU STATE________________________________________________________________________________________
        if (state == State::MENU) {

            //change changeables
            optionsbuttontext.setString(" Options\n    (O)");
            menuText.setString("ZOMBIE SHOOTER");
            menuText.setCharacterSize(150);
            menuText.setOutlineThickness(3);
            menuText.setPosition(500, 200);

            //DRAW necessaries
            window.draw(menubackground);
            window.draw(menuText);
            window.draw(playbutton);
            window.draw(playbuttontext);
            window.draw(optionsbutton);
            window.draw(optionsbuttontext);
            window.draw(HighScore);

            //See if the mouse is over the buttons on the screen
            bool playbuttonhover = playbutton.getGlobalBounds().contains(
                    static_cast<float>(Mouse::getPosition(window).x),
                    static_cast<float>(Mouse::getPosition(window).y));

            bool optionsbuttonhover = optionsbutton.getGlobalBounds().contains(
                    static_cast<float>(Mouse::getPosition(window).x),
                    static_cast<float>(Mouse::getPosition(window).y));

            //see if the mouse clicked the button
            if (playbuttonhover) {
                playbutton.setFillColor(Color(155, 155, 0));
                if (mousePressed) {
                    canclick = true;
                }
                if (!mousePressed && canclick) {
                    state = State::COUNTDOWN;
                    canclick = false;
                }
            } else if (optionsbuttonhover) {
                optionsbutton.setFillColor(Color(0, 155, 155));
                if (mousePressed) {
                    canclick = true;
                }
                if (!mousePressed && canclick) {
                    prevstate = State::MENU;
                    state = State::OPTIONS;
                    canclick = false;
                }
            } else {
                canclick = false;
                playbutton.setFillColor(Color(255, 255, 0));
                optionsbutton.setFillColor(Color(0, 255, 255));
            }

            //START GAME event
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                state = State::COUNTDOWN;
            }

            //OPTIONS PAGE event
            if (Keyboard::isKeyPressed(Keyboard::O)) {
                prevstate = State::MENU;
                state = State::OPTIONS;
            }
        }

            //__________________________________________________OPTIONS________________________________________________________________________________________
        else if (state == State::OPTIONS) {

            //changeables
            optionsbuttontext.setString(" Back\n   (B)");
            menuText.setString(
                    "                  OPTIONS:\n\n- SPACE BAR TO SHOOT\n- ASDW TO MOVE\n- WALK ON HEAL PACKS/AMMO PACKS \n  TO COLLECT\n- P TO PAUSE");
            menuText.setCharacterSize(100);
            menuText.setOutlineThickness(3);
            menuText.setPosition(300, 200);

            //draw
            window.draw(menubackground);
            window.draw(optionsbutton);
            window.draw(optionsbuttontext);
            window.draw(menuText);

            //BUTTON LOGIC
            if (optionsbutton.getGlobalBounds().contains(static_cast<float>(Mouse::getPosition(window).x),
                                                         static_cast<float>(Mouse::getPosition(window).y))) {
                optionsbutton.setFillColor(Color(0, 155, 155));
                if (mousePressed) {
                    canclick = true;
                }
                if (!mousePressed && canclick) {
                    state = prevstate;
                    canclick = false;
                }
            } else {
                canclick = false;
                optionsbutton.setFillColor(Color(0, 255, 255));
            }


            //RETURN EVENT
            if (Keyboard::isKeyPressed(Keyboard::B)) {
                state = prevstate;
            }

        }

            //__________________________________________________COUNTFDOWN STATE________________________________________________________________________________________


        else if (state == State::COUNTDOWN) {
            //COUNTDOWN CLOCK
            if (countdown >= 0) {
                countdownclock++;
                countdowntext.setString(to_string(countdown));
                if (countdown == 0) {
                    countdowntext.setString("GO!");
                }
                if (countdownclock >= 400) {
                    countdown--;
                    countdownclock = 0;
                }
            } else {

                //THE GAME IS STARTED!!!

                //reset countdown
                countdown=3;

                //Set Stage to playing
                state = State::PLAYING;
//                player.spawn(arena, resolution, 50);
//                for(int i=0; i<ZOMBIE_NUM; i++) {
//                    zombie[i].spawn(rand() % 3840, rand() % 2160, i%3+1, 0);
//                }
//                arena.width = resolution.x;
//                arena.height = resolution.y;

                //setup
                arena.left = 0;
                arena.top = 0;
                int tileSize = createBackground(background, arena);


                // Spawn the player in the middle of the arena
                player.spawn(arena, resolution, tileSize);


                // create a horde of zombies
                numZombies = 100;  //@TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO @TODO
                delete[] zombies;
                zombies = createHorde(numZombies, arena);
                numZombiesAlive = numZombies;
            }

            //draw
            window.draw(countdowntext);
        }

            //__________________________________________________PLAYING STAGE________________________________________________________________________________________


        else if (state == State::PLAYING) {

            //change the time
            Time dt = clock.restart();
            timepassed+=dt;
            float dtAsSeconds = dt.asSeconds();

            //find the mouse
            mouseScreenPosition = Mouse::getPosition(window);
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);


//            cout<<player.getCenter().x<<" "<<player.getCenter().y<<"\n";
//            cout<<arena.width<<" "<<arena.height<<"\n\n";

            //update the character
            player.update(dt.asSeconds(), mouseScreenPosition);



            //update the zombies
            for(int i=0; i<numZombies; i++) {
                zombies[i].update(dt.asSeconds(), player.getCenter());
            }


            //update the bullets
            for(int i=0; i<100; i++){
                if(bullets[i].isInFlight()){
                    bullets[i].update(dt.asSeconds());
                }
            }


            //update the mainview
            Vector2f playerPosition(player.getCenter());
            mainView.setCenter(player.getCenter());


            //changeables
            HighScore.setString("HighScore = " + to_string(highscore));
            scoreText.setString("Score = " + to_string(score));
            healthText.setString("Health: "+ to_string(player.getHealth()));
            timeText.setString(to_string(timepassed.asSeconds()));
            pauseButtonText.setString("| |");

            highscore = max(score, highscore);
            pauseButton.setPosition(WIDTH - pauseButton.getRadius() * 2 - 50, 50);

            //move the pause button
            float r = pauseButton.getRadius();
            float x = pauseButton.getPosition().x+r-Mouse::getPosition(window).x;
            float y = pauseButton.getPosition().y+r-Mouse::getPosition(window).y;
            if (x*x+y*y<r*r){
                pauseButton.setFillColor(Color(155, 55, 0));
                if (mousePressed) {
                    canclick = true;
                }
                if (!mousePressed && canclick) {
                    state = State::PAUSED;
                    canclick = false;
                }
            } else {
                canclick = false;
                pauseButton.setFillColor(Color(255, 155, 0));
            }


            //change the buttons
            pauseButton.setPosition(player.getCenter().x+ 960 - pauseButton.getRadius() * 2 - 50,player.getCenter().y-540+ 50);
            pauseButtonText.setPosition(player.getCenter().x+ 960 - pauseButton.getRadius() * 2 - 15,player.getCenter().y-540+ 74);
            scoreText.setPosition(player.getCenter().x- 960 +50,player.getCenter().y-540+ 50);
            HighScore.setPosition(player.getCenter().x- 960 +50,player.getCenter().y-540+ 125);
            healthText.setPosition(player.getCenter().x- 960 +50,player.getCenter().y-540+ 200);
            timeText.setPosition(player.getCenter().x,player.getCenter().y-540+50);


            //EVENT: pause game
            if (Keyboard::isKeyPressed(Keyboard::P)) {
                state = State::PAUSED;
            }

            //EVENT go right
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                player.moveRight();
            } else { player.stopRight(); }

            //EVENT go left
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                player.moveLeft();
            } else { player.stopLeft(); }

            //EVENT go up
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                player.moveUp();
            } else { player.stopUp(); }

            //EVENT go down
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                player.moveDown();
            } else { player.stopDown(); }

            //EVENT move
            if (Keyboard::isKeyPressed(Keyboard::Space)) {


                //bullet needs a cooldown
                if (timepassed.asMilliseconds()
                    - lastPressed.asMilliseconds()
                    > 100 / fireRate && bulletsInClip > 0)
                {

                    // Pass the centre of the player and the centre of the crosshair


                    // SHOOT THE BULLET
                    bullets[currentBullet].shoot(
                            player.getCenter().x, player.getCenter().y,
                            player.getCenter().x-(WIDTH/2)+mouseScreenPosition.x, player.getCenter().y-(HEIGHT/2)+mouseScreenPosition.y);


                    //@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO@TODO


                    //change the bullet and delete the one used
                    currentBullet++;
                    if (currentBullet > 99)
                    {
                        currentBullet = 0;
                    }
                    lastPressed = timepassed;
                    //shoot.play();
                    bulletsInClip--;
                }
            }

            //DRAW THINGS
            window.draw(background, &textureBackground);
            window.draw(player.getSprite());

            //draw all the zombies
            for(int i=0; i<numZombies; i++) {
                window.draw(zombies[i].getSprite());
            }

            //draw all the bullets
            for(int i=0; i<100; i++){
                if(bullets[i].isInFlight()){
                    window.draw(bullets[i].getShape());
                }
            }

            //draw other things
            window.draw(pauseButton);
            window.draw(pauseButtonText);
            window.draw(scoreText);
            window.draw(HighScore);
            window.draw(healthText);
            window.draw(timeText);
            window.setView(mainView);
        }

            //__________________________________________________PAUSED STAGE________________________________________________________________________________________

        else if (state == State::PAUSED) {

            //Changeables
            mainView.setCenter(960,540);
            optionsbuttontext.setString(" Options\n    (O)");
            HighScore.setString("HighScore = " + to_string(highscore));
            scoreText.setString("Score = " + to_string(score));
            pauseButtonText.setString("l>");
            pauseButton.setPosition(WIDTH - pauseButton.getRadius() * 2 - 50, 50);
            pauseButtonText.setPosition(WIDTH - pauseButton.getRadius() * 2 - 15, 74);


            //BUTTON LOGIC
            bool optionsbuttonhover = optionsbutton.getGlobalBounds().contains(
                    static_cast<float>(Mouse::getPosition(window).x),
                    static_cast<float>(Mouse::getPosition(window).y));
            if (pauseButton.getGlobalBounds().contains(static_cast<float>(Mouse::getPosition(window).x),
                                                       static_cast<float>(Mouse::getPosition(window).y))) {
                pauseButton.setFillColor(Color(155, 55, 0));
                if (mousePressed) {
                    canclick = true;
                }
                if (!mousePressed && canclick) {
                    state = State::PLAYING;
                    canclick = false;
                }
            } else if (quitbutton.getGlobalBounds().contains(static_cast<float>(Mouse::getPosition(window).x),
                                                             static_cast<float>(Mouse::getPosition(window).y))) {
                quitbutton.setFillColor(Color(100, 100, 100));
                if (mousePressed) {
                    canclick = true;
                }
                if (!mousePressed && canclick) {
                    state = State::GAME_OVER;
                    canclick = false;
                }
            } else if (optionsbuttonhover) {
                optionsbutton.setFillColor(Color(0, 155, 155));
                if (mousePressed) {
                    canclick = true;
                }
                if (!mousePressed && canclick) {
                    prevstate = State::PAUSED;
                    state = State::OPTIONS;
                    canclick = false;
                }
            } else {
                canclick = false;
                pauseButton.setFillColor(Color(255, 155, 0));
                optionsbutton.setFillColor(Color(0, 255, 255));
                quitbutton.setFillColor(Color(200, 200, 200));
            }





            //EVENT: go to options
            if (Keyboard::isKeyPressed(Keyboard::O)) {
                prevstate = State::PAUSED;
                state = State::OPTIONS;
            }

            //EVENT: RETURN TO PLAYING STATE
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
                state = State::PLAYING;
            }

            //EVENT: QUIT THE GAME
            if (Keyboard::isKeyPressed(Keyboard::Q)) {
                state = State::GAME_OVER;
            }

            //DRAW THINGS
            window.draw(player.getSprite());
            window.draw(pauseButton);
            window.draw(pauseButtonText);
            window.draw(optionsbutton);
            window.draw(optionsbuttontext);
            window.draw(quitbutton);
            window.draw(quitbuttontext);
            window.setView(mainView);
        }

            //__________________________________________________GAME OVER STAGE________________________________________________________________________________________

        else if (state == State::GAME_OVER) {

            //changeables
            menuText.setString("GAME   OVER\nPress Space to Continue");
            menuText.setCharacterSize(150);
            menuText.setOutlineThickness(3);
            menuText.setPosition(500, 200);



            //button logic
            if (gameoverbutton.getGlobalBounds().contains(static_cast<float>(Mouse::getPosition(window).x),
                                                          static_cast<float>(Mouse::getPosition(window).y))) {
                gameoverbutton.setFillColor(Color(155, 0, 0));
                if (mousePressed) {
                    canclick = true;
                }
                if (!mousePressed && canclick) {
                    state = State::MENU;
                    canclick = false;
                }
            } else {
                canclick = false;
                gameoverbutton.setFillColor(Color(255, 0, 0));
                score = 0;
                player.resetPlayerStats();
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                state = State::MENU;
            }

            //draw things
            window.draw(menuText);
            window.draw(gameoverbutton);
            window.draw(gameoverbuttontext);
            window.draw(scoreText);
            window.draw(HighScore);

        }
        else if (state == State::LEVELING_UP) {

        }

        //show everything on the screen
        window.display();
    }


    delete[] zombies;
    return 0;
}