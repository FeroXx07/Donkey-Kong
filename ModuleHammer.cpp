#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleHammer.h"
#include "ModulePlayer.h"

#include <stdio.h>
#include "Game/SDL/include/SDL_scancode.h"

// Constructor
ModuleHammer::ModuleHammer()
{

}


// Destructor
ModuleHammer::~ModuleHammer()
{

}

// Called when the module is activated
// Loads the necessary textures for the hammer
bool ModuleHammer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Background.png"); // arcade version

	//Starting position of the Mario
	position.x = 0;
	position.y = 232;

	//hammerCollider = App->collisions->AddCollider({ position.x,position.y,12,16 }, Collider::Type::PLAYER, App->player);


	return ret;
}

// Called at the middle of the application loop
// Processes new input and handles hammer movement
update_status ModuleHammer::Update()
{

	return update_status::UPDATE_CONTINUE;
}

// Called at the end of the application loop
update_status ModuleHammer::PostUpdate()
{

	return update_status::UPDATE_CONTINUE;
}

// Collision callback, called when the player intersects with another collider
void ModuleHammer::OnCollision(Collider* c1, Collider* c2)
{

}