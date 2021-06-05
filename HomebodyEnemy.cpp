#include <string>

#include "HomebodyEnemy.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"

HomebodyEnemy::HomebodyEnemy(int x, int y) : Enemy("play/enemy-5.png", x, y, 60, 80, 8, 10,"HomebodyEnemy") {
    // TODO 2 (6/8): You can imitate the 2 files: 'NormalEnemy.hpp', 'NormalEnemy.cpp' to create a new enemy.
}
