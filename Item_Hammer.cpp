#include "Item_Hammer.h"

#include "Application.h"
#include "ModuleCollisions.h"

Item_Hammer::Item_Hammer(int x, int y) : Enemy(x, y)
{
	hammerAnim.PushBack({ 364,110,9,10 });
	collider = App->collisions->AddCollider({ 0, 0, 9, 10 }, Collider::Type::Item_Type, (Module*)App->enemies, Collider::Items::POWERITEMS);

	hammerAnim.loop = false;
	currentAnim = &hammerAnim;
}

void Item_Hammer::Update()
{

	Enemy::Update();
}