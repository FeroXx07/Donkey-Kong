#include "Enemy_FireMinion.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_FireMinion::Enemy_FireMinion(int x, int y) : Enemy(x, y)
{
	enemy_FireMinionAnim.PushBack({ 561,140,15,12 });
	enemy_FireMinionAnim.speed = 0.1f;
	enemy_FireMinionAnim.loop = false;

	currentAnim = &enemy_FireMinionAnim;
	collider = App->collisions->AddCollider({0, 0, 15, 12}, Collider::Type::ENEMY, (Module*) App->enemies);
}

void Enemy_FireMinion::Update()
{
	/*waveRatio += waveRatioSpeed;
	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));*/
	//position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
