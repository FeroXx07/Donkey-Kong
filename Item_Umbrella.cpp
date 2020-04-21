#include "Item_Umbrella.h"

#include "Application.h"
#include "ModuleCollisions.h"

Item_Umbrella::Item_Umbrella(int x, int y) : Enemy(x, y)
{
	umbrellaAnim.PushBack({ 432,104,16,15 });
	collider = App->collisions->AddCollider({ 0, 0, 16, 15 }, Collider::Type::Item_Type, (Module*)App->enemies, Collider::Items::SCOREITEMS);

	umbrellaAnim.loop = false;
	currentAnim = &umbrellaAnim;
}

void Item_Umbrella::Update()
{
	/*waveRatio += waveRatioSpeed;
	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));*/
	//position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}