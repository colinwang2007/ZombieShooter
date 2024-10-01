#include <SFML/Graphics.hpp>
using namespace sf;
class Player{
private:
    const float START_SPEED = 500;
    const float START_HEALTH = 100;
    Vector2f m_position;
    Sprite m_Sprite;
    Texture m_Texture;
    Vector2f m_Resolution;
    IntRect m_Arena;
    int m_TileSize;
    bool m_UpPressed=false;
    bool m_DownPressed=false;
    bool m_LeftPressed=false;
    bool m_RightPressed=false;
    float m_Health;
    int m_maxHealth;
    Time m_LastHit;
    float m_Speed;


public:
    Player();

    void spawn(IntRect arena, Vector2f resolution, int tileSize);
    void resetPlayerStats();
    bool hit(Time timeHit);
    Time getLastHitTime();
    FloatRect getPosition();
    Vector2f getCenter();
    float getRotation();
    Sprite getSprite();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopLeft();
    void stopRight();
    void stopDown();
    void stopUp();
    void update(float elapsedTime, Vector2i mousePosition);
    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);
    int getHealth();


};
