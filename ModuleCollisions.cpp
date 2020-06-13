#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"

#include "Game/SDL/include/SDL.h"
#pragma comment( lib, "Game/SDL/libx86/SDL2.lib")
#pragma comment( lib, "Game/SDL/libx86/SDL2main.lib")
#include "Game/SDL/include/SDL_Scancode.h"


ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::GROUND][Collider::Type::GROUND] = false;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::GROUND][Collider::Type::WALL] = false; //true
	matrix[Collider::Type::GROUND][Collider::Type::LADDER] = false;
	matrix[Collider::Type::GROUND][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::GROUND][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::GROUND][Collider::Type::FIREBARREL] = false;
	matrix[Collider::Type::GROUND][Collider::Type::LOWERGROUND] = false;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::GROUND][Collider::Type::CONVEYORGROUND] = false;

	matrix[Collider::Type::LOWERGROUND][Collider::Type::LOWERGROUND] = false;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::GROUND] = false;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::WALL] = true;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::LADDER] = false;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::FIREBARREL] = false;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::LOWERGROUND][Collider::Type::CONVEYORGROUND] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::LOWERGROUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::LADDER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::Item_Type] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::FIREBARREL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::CONVEYORGROUND] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::LOWERGROUND] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::GROUND] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::LADDER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::HAMMER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::FIREBARREL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMYWALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::CONVEYORGROUND] = false;

	
	matrix[Collider::Type::ENEMYWALL][Collider::Type::LOWERGROUND] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::GROUND] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::LADDER] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::FIREBARREL] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::CONVEYORGROUND] = false;

	matrix[Collider::Type::WALL][Collider::Type::GROUND] = false; 
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true	;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::LADDER] = false;
	matrix[Collider::Type::WALL][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::WALL][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::WALL][Collider::Type::FIREBARREL] = false;
	matrix[Collider::Type::WALL][Collider::Type::LOWERGROUND] = false;	
	matrix[Collider::Type::WALL][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::CONVEYORGROUND] = false;

	matrix[Collider::Type::LADDER][Collider::Type::GROUND] = false;
	matrix[Collider::Type::LADDER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LADDER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LADDER][Collider::Type::WALL] = false;
	matrix[Collider::Type::LADDER][Collider::Type::LADDER] = false;
	matrix[Collider::Type::LADDER][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::LADDER][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::LADDER][Collider::Type::FIREBARREL] = false;
	matrix[Collider::Type::LADDER][Collider::Type::LOWERGROUND] = false;
	matrix[Collider::Type::LADDER][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::LADDER][Collider::Type::CONVEYORGROUND] = false;

	matrix[Collider::Type::HAMMER][Collider::Type::GROUND] = false;
	matrix[Collider::Type::HAMMER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::HAMMER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::HAMMER][Collider::Type::WALL] = false;
	matrix[Collider::Type::HAMMER][Collider::Type::LADDER] = false;
	matrix[Collider::Type::HAMMER][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::HAMMER][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::HAMMER][Collider::Type::FIREBARREL] = false;
	matrix[Collider::Type::HAMMER][Collider::Type::LOWERGROUND] = false;
	matrix[Collider::Type::HAMMER][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::HAMMER][Collider::Type::CONVEYORGROUND] = false;

	matrix[Collider::Type::Item_Type][Collider::Type::GROUND] = false;
	matrix[Collider::Type::Item_Type][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::Item_Type][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::Item_Type][Collider::Type::WALL] = false;
	matrix[Collider::Type::Item_Type][Collider::Type::LADDER] = false;
	matrix[Collider::Type::Item_Type][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::Item_Type][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::Item_Type][Collider::Type::FIREBARREL] = false;
	matrix[Collider::Type::Item_Type][Collider::Type::LOWERGROUND] = false;
	matrix[Collider::Type::Item_Type][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::Item_Type][Collider::Type::CONVEYORGROUND] = false;

	matrix[Collider::Type::FIREBARREL][Collider::Type::GROUND] = false;
	matrix[Collider::Type::FIREBARREL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FIREBARREL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::FIREBARREL][Collider::Type::WALL] = false;
	matrix[Collider::Type::FIREBARREL][Collider::Type::LADDER] = false;
	matrix[Collider::Type::FIREBARREL][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::FIREBARREL][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::FIREBARREL][Collider::Type::LOWERGROUND] = false;
	matrix[Collider::Type::FIREBARREL][Collider::Type::FIREBARREL] = false;
	matrix[Collider::Type::FIREBARREL][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::FIREBARREL][Collider::Type::CONVEYORGROUND] = false;

	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::GROUND] = false;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::WALL] = false;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::LADDER] = false;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::HAMMER] = false;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::Item_Type] = false;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::LOWERGROUND] = false;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::FIREBARREL] = false;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::CONVEYORGROUND][Collider::Type::CONVEYORGROUND] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

update_status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			--colliderCount;
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->Intersects(c2->rect))
			{
				if(matrix[c1->type][c2->type] && c1->listener) 
					c1->listener->OnCollision(c1, c2); //efecto de la colisión
				
				if(matrix[c2->type][c1->type] && c2->listener) 
					c2->listener->OnCollision(c2, c1);
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return update_status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{

	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::GROUND: // blue
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::WALL: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::LADDER: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::HAMMER: // dark orange
			App->render->DrawQuad(colliders[i]->rect, 255, 140, 0, alpha);
			break;
			case Collider::Type::Item_Type: // pink
			App->render->DrawQuad(colliders[i]->rect, 255, 20, 147, alpha);
			break;
			case Collider::Type::FIREBARREL: // purple
			App->render->DrawQuad(colliders[i]->rect, 128, 0, 128, alpha);
			break;
			case Collider::Type::ENEMYWALL: // purple
			App->render->DrawQuad(colliders[i]->rect, 128, 0, 128, alpha);
			break;
			case Collider::Type::LOWERGROUND: 
			App->render->DrawQuad(colliders[i]->rect, 255, 20, 147, alpha);
			break;
			case Collider::Type::CONVEYORGROUND: // purple
			App->render->DrawQuad(colliders[i]->rect, 128, 0, 128, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			--colliderCount;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener, Collider::Items Item )
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener, Item);
			++colliderCount;
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			--colliderCount;
		}
	}
}