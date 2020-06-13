#include "Enemy_Minecart.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleHammer.h"
#include "ModulePlayer.h"

Enemy_Minecart::Enemy_Minecart(int x, int y) : Enemy(x, y)
{
	spawnDelay = 0;

	enemySpeed.x = 1;

	mineCartAnim.PushBack({672,144,16,8});
	mineCartAnim.speed = 0.1f;
	mineCartAnim.loop = true;
	currentAnim = &mineCartAnim;
	collider = App->collisions->AddCollider({ 0, y+4, 12, 4 }, Collider::Type::ENEMY, (Module*)App->enemies, Collider::Items::MINECART);
}

void Enemy_Minecart::Update()
{
	// Fire Minion position update
	if (App->player->conveyorSenseLeft == true)
	{
		if (spawnDelay > 120) {
			position.x -= enemySpeed.x;
		}
		spawnDelay++;
	}
	else if (App->player->conveyorSenseLeft == false)
	{
		if (spawnDelay > 120) {
			position.x += enemySpeed.x;
		}
		spawnDelay++;
	}

	collider->SetPos(position.x+2 , position.y+4);
	Enemy::Update();
}
