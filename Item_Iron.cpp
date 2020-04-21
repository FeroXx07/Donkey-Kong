#include "Item_Iron.h"

#include "Application.h"
#include "ModuleCollisions.h"

Item_Iron::Item_Iron(int x, int y) : Enemy(x, y)
{
	ironAnim.PushBack({ 385,111,15,8 });
	collider = App->collisions->AddCollider({ 0, 0, 15, 8 }, Collider::Type::Item_Type, (Module*)App->enemies, Collider::Items::SCOREITEMS);

	ironAnim.loop = false;
	currentAnim = &ironAnim;
}

void Item_Iron::Update()
{
	/*waveRatio += waveRatioSpeed;
	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));*/
	//position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}