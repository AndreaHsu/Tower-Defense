#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "IceCreamBullet.hpp"
#include "Group.hpp"
#include "TCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include "Collider.hpp"

const int TCellTurret::Price = 30;
TCellTurret::TCellTurret(float x, float y) :
	// TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("play/turret-4.png", x, y,200, Price, 0.5) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void TCellTurret::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;
	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		if (!enemy->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
			flag = 1;
			enemy->OnExplode();
			enemy->Hit(100);
			return;
		}
	}
	if(flag) getPlayScene()->TowerGroup->RemoveObject(objectIterator);
}

void TCellTurret::CreateBullet() {
	AudioHelper::PlayAudio("gun.wav");
}
