#include "Player.h"
#include <math.h>
#include <iostream>
static String pathBase = "/Users/colinwang/Downloads/media_zombieShooter/";
Player::Player() {
    m_Speed=START_SPEED;
    m_Health=START_HEALTH;
    m_maxHealth=START_HEALTH;
    m_Texture.loadFromFile(pathBase+"player.png");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin(25,25);
}
void Player::spawn(IntRect arena, Vector2f resolution, int tileSize){
    m_position.x=arena.width/2;
    m_position.y=arena.height/2;
    m_Arena.left = arena.left;
    m_Arena.width=arena.width;
    m_Arena.top=arena.top;
    m_Arena.height=arena.height;
    m_TileSize = tileSize;
    m_Resolution.x = resolution.x;
    m_Resolution.y = resolution.y;
}
void Player::resetPlayerStats(){
    m_Speed=START_SPEED;
    m_Health=START_HEALTH;
    m_maxHealth=START_HEALTH;
}
bool Player::hit(Time timeHit){
    if(timeHit.asMilliseconds()-m_LastHit.asMilliseconds()>200){
        m_Health-=10;
        m_LastHit = timeHit;
        return true;
    }
    return false;
}
Time Player::getLastHitTime(){
    return m_LastHit;
}
FloatRect Player::getPosition(){
    return m_Sprite.getGlobalBounds();
}
Vector2f Player::getCenter(){
    return m_position;
}
float Player::getRotation(){
    return m_Sprite.getRotation();
}
Sprite Player::getSprite(){
    return m_Sprite;
}
int Player::getHealth(){
    return m_Health;
}

void Player::moveLeft(){
    m_LeftPressed=true;
}
void Player::moveRight(){
    m_RightPressed=true;
}
void Player::moveUp(){
    m_UpPressed=true;
}
void Player::moveDown(){
    m_DownPressed=true;
}
void Player::stopLeft(){
    m_LeftPressed=false;
}
void Player::stopRight(){
    m_RightPressed=false;
}
void Player::stopUp(){
    m_UpPressed=false;
}
void Player::stopDown(){
    m_DownPressed= false;
}
void Player::update(float elapsedTime, Vector2i mousePosition) {
    //std::cout<<mousePosition.x<<" "<<mousePosition.y<<"\n";
    if (m_RightPressed) {
        m_position.x += m_Speed * elapsedTime;
    }
    if (m_LeftPressed) {
        m_position.x -= m_Speed * elapsedTime;
    }
    if (m_UpPressed) {
        m_position.y -= m_Speed * elapsedTime;
    }
    if (m_DownPressed) {
        m_position.y += m_Speed * elapsedTime;
    }
//    std::cout<<m_position.x<<" "<<m_position.y<<"\n";
    m_Sprite.setPosition(m_position);
    if (m_position.x > m_Arena.width - m_TileSize-42){
        m_position.x = m_Arena.width - m_TileSize-42;
    }
    if (m_position.x < m_Arena.left+m_TileSize){
        m_position.x = m_Arena.left+m_TileSize;
    }
    if (m_position.y > m_Arena.height - m_TileSize-12){
        m_position.y = m_Arena.height - m_TileSize-12;
    }
    if (m_position.y < m_Arena.top+m_TileSize){
        m_position.y = m_Arena.top+m_TileSize;
    }

    int midx= m_Resolution.x/2;
    int midy= m_Resolution.y/2;

    int mousex = mousePosition.x;
    int mousey = mousePosition.y;

    int y = mousey-midy;
    int x = mousex-midx;

    float theta = atan2(y,x);
    theta=theta*180/M_PI;
    m_Sprite.setRotation(theta);
}
void Player::upgradeSpeed() {
    m_Speed+=START_SPEED*1.2;
}
void Player::upgradeHealth() {
    m_Health+=START_HEALTH*1.2;
}
void Player::increaseHealthLevel(int amount) {
    m_Health=std::min(m_Health+amount,START_HEALTH);
}


