#include "Zombie.h"
#include <math.h>
#include <iostream>
#include "TextureHolder.h"
static String pathBase = "/Users/colinwang/Downloads/media_zombieShooter/";
Zombie::Zombie(){

}
void Zombie::spawn(float startX, float startY, int type, int seed)
{
    // spawn a zombie
    switch (type)
    {
        case 0:
            // bloater
            m_Sprite = Sprite(TextureHolder::GetTexture(pathBase+"bloater.png"));
            m_Speed = BLOATER_SPEED;
            m_Health = BLOATER_HEALTH;
            break;
        case 1:
            // chaser
            m_Sprite = Sprite(TextureHolder::GetTexture(pathBase+"chaser.png"));
            m_Speed = CHASER_SPEED;
            m_Health = CHASER_HEALTH;
            break;
        case 2:
            // crawler
            m_Sprite = Sprite(TextureHolder::GetTexture(pathBase+"crawler.png"));
            m_Speed = CRAWLER_SPEED;
            m_Health = CRAWLER_HEALTH;
            break;
    }

    // modify speed to make the zombie unique
    srand((int)time(0) * seed);
    // somewhere between 80 and 100
    float modifier = (rand() % MAX_VARIANCE + OFFSET);
    // as fraction of 1, now equals between .7 and 1
    modifier /= 100;
    m_Speed *= modifier;

    // initialize its location
    m_Position.x = startX;
    m_Position.y = startY;
    // set its origin to the center
    m_Sprite.setOrigin(25, 25);
    // set position
    m_Sprite.setPosition(m_Position);

}
/*
void Zombie::spawn(float startX, float startY, int type, int seed) {
    srand(time(NULL));
    switch (type) {
        case 1:
            m_Speed = BLOATER_SPEED;
            m_Health = BLOATER_HEALTH;
            m_Texture = (TextureHolder::GetTexture("/Users/colinwang/Downloads/graphics_zombiearena/bloater.png"));
            break;
        case 2:
            m_Speed = CHASER_SPEED;
            m_Health = CHASER_HEALTH;
            m_Texture = (TextureHolder::GetTexture("/Users/colinwang/Downloads/graphics_zombiearena/chaser.png"));
            break;
        case 3:
            m_Speed = CRAWLER_SPEED;
            m_Health = CRAWLER_HEALTH;
            m_Texture = (TextureHolder::GetTexture("/Users/colinwang/Downloads/graphics_zombiearena/crawler.png"));
            break;
    }
    m_type=type;


    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin(25, 25);
    m_Position = Vector2f(startX, startY);
    cout<<startX<<" "<<startY<<endl;
}
 */
bool Zombie::hit(){
    m_Health--;
    if(m_Health<=0){
        m_Alive=false;
    }
}
bool Zombie::isAlive(){
    return m_Alive;
}
FloatRect Zombie::getPosition(){
   // FloatRect a = new FloatRect(m_Sprite.get)
}
Vector2f Zombie::getCenter(){
    return m_Position;
}
float Zombie::getRotation(){
    return m_Sprite.getRotation();
}
int Zombie::getType(){
    return m_type;
}
Sprite Zombie::getSprite(){
    return m_Sprite;
}
void Zombie::update(float elapsedTime, Vector2f playerLocation){
//    // update zombie every frame
//    float playerX = playerLocation.x;
//    float playerY = playerLocation.y;
//
//    // update zombie position variables
//    if (playerX > m_Position.x)
//    {
//        m_Position.x += m_Speed * elapsedTime;
//    }
//    if (playerY > m_Position.y)
//    {
//        m_Position.y += m_Speed * elapsedTime;
//    }
//    if (playerX < m_Position.x)
//    {
//        m_Position.x -= m_Speed * elapsedTime;
//    }
//    if (playerY < m_Position.y)
//    {
//        m_Position.y -= m_Speed * elapsedTime;
//    }
//
//    // move the zombie sprite
//    m_Sprite.setPosition(m_Position);
//
//    // face sprite to correct direction
//    float angle = (atan2(playerY - m_Position.y,
//                         playerX - m_Position.x) * 180) / 3.141;
//
//    m_Sprite.setRotation(angle);
    int player_x =playerLocation.x;
    int player_y = playerLocation.y;
    int zombie_x = m_Position.x;
    int zombie_y = m_Position.y;

    float y = player_y-zombie_y;
    float x = player_x-zombie_x;
    float theta = atan2(y,x);
    theta=theta*180/M_PI;
    m_Sprite.setRotation(theta);

    float distancetraveled = m_Speed*elapsedTime;



    float travelx = distancetraveled;
    float travely = distancetraveled;
    if(x<0){
        travelx=-travelx;
    }
    if(y<0){
        travely=-travely;
    }


    /* ratio = y/x (similar triangles serve same ratio)

       travelx^2 + (travelx*ratio)^2=distancetraveled^2;
       x^2(1+(y/x)^2)=distancetraveled^2;

       x^2=distancetraveled^2/(1+y/x)

       xdistance=√(distancetraveled^2/(1+y/x))

     ydistance = xdistance*y/x
*/
    if(x!=0||y!=0) {
        if(y==0) {
            m_Position.x = m_Position.x + travelx;
        }
        else if(x==0) {
            m_Position.y = m_Position.y + travely;
        }
        else{
            int xneg = 1;
            int yneg = 1;
            if(y<0){
                yneg=-1;
                y=-y;
            }
            if(x<0){
                xneg=-1;
                x=-x;
            }
            float ratio = y/x;
            travelx= sqrt(pow(distancetraveled,2)/pow(1+ratio,2));
            travely=travelx*ratio;
            travelx*=xneg;
            travely*=yneg;
            m_Position.x = m_Position.x + travelx;
            m_Position.y = m_Position.y + travely;
         //   cout<<travelx<<" "<<travely<<" "<<m_Position.x<<" "<<m_Position.y<<endl;
        }
    }
    m_Sprite.setPosition(m_Position);
//    std::cout<<m_Position.x<<" "<<m_Position.y<<std::endl;
}
