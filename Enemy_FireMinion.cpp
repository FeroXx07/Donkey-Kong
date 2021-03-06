#include "Enemy_FireMinion.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleHammer.h"

Enemy_FireMinion::Enemy_FireMinion(int x, int y) : Enemy(x, y)
{
	spawnDelay = 0;
	
	if ((rand() % 100) < 50)
	{
		enemySpeed.x = -1;
	}
	else
		enemySpeed.x = 1;

	enemy_FireMinionLeftAnim.PushBack({ 561,140,15,12 });
	enemy_FireMinionLeftAnim.PushBack({ 584,140,16,12 });
	enemy_FireMinionLeftAnim.speed = 0.1f;
	enemy_FireMinionLeftAnim.loop = true;

	enemy_FireMinionRightAnim.PushBack({ 561,128,15,12 });
	enemy_FireMinionRightAnim.PushBack({ 584,128,16,12 });
	enemy_FireMinionRightAnim.speed = 0.1f;
	enemy_FireMinionRightAnim.loop = true;

	enemy_FireMinionLeftAnimHammer.PushBack({ 609,140,15,12 });
	enemy_FireMinionLeftAnimHammer.PushBack({ 632,140,16,12 });
	enemy_FireMinionLeftAnimHammer.speed = 0.1f;
	enemy_FireMinionLeftAnimHammer.loop = true;

	enemy_FireMinionRightAnimHammer.PushBack({ 609,128,15,12 });
	enemy_FireMinionRightAnimHammer.PushBack({ 632,128,16,12 });
	enemy_FireMinionRightAnimHammer.speed = 0.1f;
	enemy_FireMinionRightAnimHammer.loop = true;

	collider = App->collisions->AddCollider({0, 0, 15, 12}, Collider::Type::ENEMY, (Module*) App->enemies);
}

void Enemy_FireMinion::Update()
{
	// Fire Minion position update
	if (spawnDelay >  60) {
		position.x += enemySpeed.x;
	}
	spawnDelay++;

	// Fire Minion animations
	if (App->hammer->hammerExist)
	{
		if (enemySpeed.x < 0)
			currentAnim = &enemy_FireMinionLeftAnimHammer;
		else if (enemySpeed.x > 0) currentAnim = &enemy_FireMinionRightAnimHammer;
	}
	else
	{
		if (enemySpeed.x < 0) 
			currentAnim = &enemy_FireMinionLeftAnim;
		else if (enemySpeed.x > 0) currentAnim = &enemy_FireMinionRightAnim;
	}
	if (/*			!isGround			*//*			climbingUP || climbingDOWN			*/0) {
		collider->rect.w = 5;
		tempx = 4;
	}
	else {
		collider->rect.w = 15;
		tempx = 0;
	}
	collider->SetPos(position.x + tempx, position.y);
	Enemy::Update();
}
