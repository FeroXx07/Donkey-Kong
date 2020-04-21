#include "Enemy_FireMinion.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_FireMinion::Enemy_FireMinion(int x, int y) : Enemy(x, y)
{
	enemySpeed.x = -1;

	enemy_FireMinionLeftAnim.PushBack({ 561,140,15,12 });
	enemy_FireMinionLeftAnim.PushBack({ 584,140,16,12 });
	enemy_FireMinionLeftAnim.speed = 0.1f;
	enemy_FireMinionLeftAnim.loop = true;

	enemy_FireMinionRightAnim.PushBack({ 561,128,15,12 });
	enemy_FireMinionRightAnim.PushBack({ 584,128,16,12 });
	enemy_FireMinionRightAnim.speed = 0.1f;
	enemy_FireMinionRightAnim.loop = true;

	collider = App->collisions->AddCollider({0, 0, 15, 12}, Collider::Type::ENEMY, (Module*) App->enemies);
}

void Enemy_FireMinion::Update()
{
	// It will update the collider depending on the position
	position.x += enemySpeed.x;
	/*if (position.x <= 0) {
		currentAnim = &enemy_FireMinionRightAnim;
		enemyFireMinionSpeed = -enemyFireMinionSpeed;
	}
	else if (position.x >= (224 - 16)) {
		currentAnim = &enemy_FireMinionLeftAnim;
		enemyFireMinionSpeed = -enemyFireMinionSpeed;
	}*/

	if (goingLeft) currentAnim = &enemy_FireMinionLeftAnim;
	else currentAnim = &enemy_FireMinionRightAnim;

	Enemy::Update();
}
