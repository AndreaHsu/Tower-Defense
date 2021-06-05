#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "IceCreamBullet.hpp"
#include "Group.hpp"
#include "Boon.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include "Collider.hpp"
#include "Resources.hpp"

const int Boon::Price = 15;
Boon::Boon(float x, float y) :
	// TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("Boon","play/bomb.png", x, y,100, Price, 0.5,0) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void Boon::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;

	for (auto& it : scene->TowerGroup->GetObjects()) {
		Turret* turret = dynamic_cast<Turret*>(it);
		if (!turret->Visible || turret == this)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, 0)) {
			turret->OnExplode();
			if (turret->name == "TCellTurret")
				turret->isboon = true;
			turret->Hit(100);
			//return;
		}
	}
	getPlayScene()->TowerGroup->RemoveObject(objectIterator);
	AudioHelper::PlayAudio("shockwave.ogg");
}

void Boon::CreateBullet() {
	return;
}

void Boon::Draw() const {
	Sprite::Draw();
	return;
}
