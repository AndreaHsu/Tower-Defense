#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "FrenchfriesBullet.hpp"
#include "Group.hpp"
#include "AcidCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int AcidCellTurret::Price = 30;
AcidCellTurret::AcidCellTurret(float x, float y) :
	// TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("AcidCellTurret", "play/turret-5.png", x, y, 60, Price, 2, 15) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void AcidCellTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(1, 0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new FrenchfriesBullet(Position, diff, rotation, this));
	AudioHelper::PlayAudio("missile.wav");
}
