#include <string>

#include "HomebodyEnemy.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"

HomebodyEnemy::HomebodyEnemy(int x, int y) : Enemy("play/enemy-5.png", x, y, 60, 80, 5, 10,"HomebodyEnemy") {
}
