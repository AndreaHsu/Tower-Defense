#include <allegro5/base.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "TCellTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include "Collider.hpp"
#include "EnemyBullet.hpp"

const int TCellTurret::Price = 30;
TCellTurret::TCellTurret(float x, float y) :
	// TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
	Turret("TCellTurret","play/turret-4.png", x, y,200, Price, 0.5,1) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}

void TCellTurret::Draw() const {
	/*if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}*/
	Sprite::Draw();
	al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
}
void TCellTurret::Hit(float damage) {
	hp -= damage;

	if (hp <= 0) {
		PlayScene* scene = getPlayScene();
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it : lockedEnemys)
			it->Target = nullptr;
		for (auto& it : lockedEnemyBullets)
			it->Target = nullptr;
		if (!isboon) {
			for (auto& it : scene->EnemyGroup->GetObjects()) {
				Enemy* enemy = dynamic_cast<Enemy*>(it);
				if (!enemy->Visible)
					continue;
				if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
					enemy->OnExplode();
					enemy->Hit(100);
				}
			}
		}
		getPlayScene()->ChangemapState(Position.x, Position.y);
		getPlayScene()->TowerGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}

void TCellTurret::CreateBullet() {
	return;
}
