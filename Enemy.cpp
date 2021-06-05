#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"
#include "Collider.hpp"
#include "EnemyFireBullet.hpp"
#include "Killer.hpp"

PlayScene* Enemy::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money, std::string name):
	Engine::Sprite(img, x, y), speed(speed), hp(hp), money(money),name(name),StopEnemyFlag(false) {
	CollisionRadius = radius;
	reachEndTime = 0;
	Velocity = Engine::Point(speed , 0);
	target = Engine::Point(PlayScene::EndGridPointx , static_cast<int>(floor(Position.y / PlayScene::BlockSize))) * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
}
void Enemy::Hit(float damage) {
	hp -= damage;
	if (name == "HomebodyEnemy") {
		Velocity.x += 2000;
	}

	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
}
void Enemy::Update(float deltaTime) {
	float remainSpeed = speed * deltaTime;
	Position.x -= Velocity.x * deltaTime;
	if (name == "HomebodyEnemy" && !StopEnemyFlag) {
		Position.y += cos(Position.x / 20) * deltaTime *80;
	}else Position.y += Velocity.y * deltaTime;
	/*Engine::Point Size = PlayScene::GetClientSize();
	if (Position.y <= PlayScene::BlockSize/2 ) {
		Velocity.y = 0-Velocity.y;
	}
	else if (Position.y >= Size.y- PlayScene::BlockSize / 2) {
		Velocity.y = 0 - Velocity.y;
	}*/
	//stop enemy
	PlayScene* scene = getPlayScene();
	for (auto& it : scene->TowerGroup->GetObjects()) {
		Turret* turret = dynamic_cast<Turret*>(it);
		if (!turret->Visible)
			continue;
		if(Engine::Collider::IsDirectOverlap(Position, turret->CollisionRadius+80, turret->Position)){
			StopEnemyFlag = true;
			Position.x += Velocity.x * deltaTime;
			Position.y -= Velocity.y * deltaTime;
			reload -= deltaTime;
			if (reload <= 0) {
				// shoot.
				reload = 0.3;
				CreateBullet();

			}
		}
	}
	if (Target) {
		if (Target->Position.x > Position.x && Target->Position.y >= Position.y && Target->Position.y < Position.y + scene->BlockSize) {
			Target->lockedEnemys.erase(lockedEnemyIterator);
			Target = nullptr;
			lockedEnemyIterator = std::list<Enemy*>::iterator();
		}
	}
	if (!Target) {
		// Lock first seen target.
		// Can be improved by Spatial Hash, Quad Tree, ...
		// However simply loop through all enemies is enough for this program.
		for (auto& it : scene->TowerGroup->GetObjects()) {
			if (it->Position.x < Position.x && it->Position.y <= Position.y && it->Position.y > Position.y - scene->BlockSize) {
				Target = dynamic_cast<Turret*>(it);
				Target->lockedEnemys.push_back(this);
				lockedEnemyIterator = std::prev(Target->lockedEnemys.end());
				break;
			}
		}
	}
	//TODO by andrea:for killer 
	if (Position.x <  PlayScene::BlockSize) {
		if (!getPlayScene()->islaneKiller.at((int)Position.y / PlayScene::BlockSize)) {
			getPlayScene()->islaneKiller.at((int)Position.y / PlayScene::BlockSize) = true;
			getPlayScene()->EffectGroup->AddNewObject(new Killer(0, PlayScene::BlockSize* ((int)Position.y / PlayScene::BlockSize)));
			return;
		}
	}
	if(Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
		Hit(hp);
		getPlayScene()->Hit();
		reachEndTime = 0;
		return;
	}
	Engine::Point vec = target - Position;
	reachEndTime = (vec.Magnitude() - remainSpeed) / speed;

	if (name == "HomebodyEnemy" && Velocity.x != 80) {
		Velocity.x = 80;
	}
}
void Enemy::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}
void Enemy::CreateBullet() {
	Engine::Point diff = Engine::Point(1, 0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->EnemyBulletGroup->AddNewObject(new EnemyFireBullet(Position, diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
