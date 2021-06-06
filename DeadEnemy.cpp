#include <string>

#include "DeadEnemy.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include "Collider.hpp"
#include "AudioHelper.hpp"
#include "Enemy.hpp"
#include "EnemyBullet.hpp"

DeadEnemy::DeadEnemy(int x, int y) : Enemy("play/enemy-8.png", x, y, 60, 80, 5, 10, "DeadEnemy") {
    // TODO 2 (6/8): You can imitate the 2 files: 'NormalEnemy.hpp', 'NormalEnemy.cpp' to create a new enemy.
}
