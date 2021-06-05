#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"
#include "TCellTurret.hpp"

class Bullet;
class PlayScene;
class Turret;

class Enemy : public Engine::Sprite {
protected:
	Engine::Point target;
	float speed;
	float hp;
	int money;
	PlayScene* getPlayScene();
	virtual void OnExplode();
	std::list<Enemy*>::iterator lockedEnemyIterator;
	float reload = 0;
	//std::string name;
public:
	float reachEndTime;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money , std::string name);
 	void Hit(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
	friend  class TCellTurret;
	virtual void CreateBullet() ;
	Turret* Target = nullptr;
	bool StopEnemyFlag;
	std::string name;
};
#endif // ENEMY_HPP
