#include <string>

#include "HeadEnemy.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"

HeadEnemy::HeadEnemy(int x, int y) : Enemy("play/enemy-4.png", x, y, 60, 80, 10, 20, "HeadEnemy") {
}
