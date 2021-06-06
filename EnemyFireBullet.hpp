#ifndef ENEMYFIREBULLET_HPP
#define ENEMYFIREBULLET_HPP
#include "EnemyBullet.hpp"

class Enemy;
class Turret;
namespace Engine {
	struct Point;
}  // namespace Engine

class EnemyFireBullet : public EnemyBullet {
public:
	explicit EnemyFireBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
	void OnExplode(Turret* turret) override;
};
#endif // ENEMYFIREBULLET_HPP

