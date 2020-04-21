#include "Item_Bag.h"

#include "Application.h"
#include "ModuleCollisions.h"

Item_Bag::Item_Bag(int x, int y) : Enemy(x, y)
{
	bagAnim.PushBack({ 411,110,9,9 });
	collider = App->collisions->AddCollider({ 0, 0, 9, 9 }, Collider::Type::Item_Type, (Module*)App->enemies, Collider::Items::SCOREITEMS);

	bagAnim.loop = false;
	currentAnim = &bagAnim;
}

void Item_Bag::Update()
{
	/*waveRatio += waveRatioSpeed;
	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));*/
	//position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}