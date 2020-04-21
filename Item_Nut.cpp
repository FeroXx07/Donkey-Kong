#include "Item_Nut.h"

#include "Application.h"
#include "ModuleCollisions.h"

Item_Nut::Item_Nut(int x, int y) : Enemy(x, y)
{
	item_NutAnimation.PushBack({ 656,143,8,9 });
	item_NutAnimation.speed = 0.1f;
	item_NutAnimation.loop = false;

	currentAnim = &item_NutAnimation;
	collider = App->collisions->AddCollider({ 0, 0, 8, 9 }, Collider::Type::Item_Type, (Module*)App->enemies, Collider::Items::IMPORTANTITEMS);

}

void Item_Nut::Update()
{
	/*waveRatio += waveRatioSpeed;
	position.y = spawnPos.y + (waveHeight * sinf(waveRatio));*/
	//position.x -= 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}