#include "Item_Nut.h"

#include "Application.h"
#include "ModuleCollisions.h"

Item_Nut::Item_Nut(int x, int y) : Enemy(x, y)
{
	item_NutAnimation.PushBack({ 656,143,8,9 });
	item_NutAnimation.speed = 0.1f;
	item_NutAnimation.loop = false;

	currentAnim = &item_NutAnimation;
	collider = App->collisions->AddCollider({ 0+2, 0, 8-4, 9 }, Collider::Type::Item_Type, (Module*)App->enemies, Collider::Items::IMPORTANTITEMS);

}

void Item_Nut::Update()
{
	collider->SetPos(position.x + 2, position.y);
	Enemy::Update();
	collider->SetPos(position.x + 2, position.y);
}