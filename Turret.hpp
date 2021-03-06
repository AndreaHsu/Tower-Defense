#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Sprite.hpp"

class Enemy;
class PlayScene;
class EnemyBullet;

class Turret: public Engine::Sprite {
protected:
    int price;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Turret*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;
    float hp;
public:
    bool Enabled = true;
    bool Preview = false;
    Enemy* Target = nullptr;
    Turret(/*std::string imgBase*/std::string name ,std::string imgTurret, float x, float y,float radius, int price, float coolDown,float hp);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
    virtual void Hit(float damage);
    virtual void OnExplode();
    std::list<Enemy*> lockedEnemys;
    std::list<EnemyBullet*> lockedEnemyBullets;
    std::string name;
    bool isboon = false;
};
#endif // TURRET_HPP
