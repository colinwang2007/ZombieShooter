#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
private:
    const float BLOATER_SPEED = 100;
    const float CHASER_SPEED = 400;
    const float CRAWLER_SPEED = 200;
    const float BLOATER_HEALTH = 3;
    const float CHASER_HEALTH = 1;
    const float CRAWLER_HEALTH = 5;
    const int MAX_VARIANCE = 30;
    const int OFFSET= 101-MAX_VARIANCE;
    Vector2f m_Position;
    Sprite m_Sprite;
    float m_Speed;
    float m_Health;
    bool m_Alive;
    Texture m_Texture;

    int m_type;



public:
    Zombie();
    void spawn(float startX, float startY, int type, int seed);
    bool hit();
    int getType();
    bool isAlive();
    FloatRect getPosition();
    Vector2f getCenter();
    float getRotation();
    Sprite getSprite();
    void update(float elapsedTime, Vector2f playerLocation);

};

