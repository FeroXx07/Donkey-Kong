#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleHammer.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"

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
	hammerPosition.x = App->player->position.x;
	hammerPosition.y = App->player->position.y;

	hammerCollider = App->collisions->AddCollider({ hammerPosition.x,hammerPosition.y, 10,10 }, Collider::Type::HAMMER, App->player);
	return ret;
}

// Called at the middle of the application loop
// Processes new input and handles hammer movement
update_status ModuleHammer::Update()
{
	if (hammerExist == true && App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN )
	{
		hammerExist = false;
		hammerPosition = { 0, 0 };
		hammerCollider->SetPos(hammerPosition.x, hammerPosition.y);
	}

	if (hammerExist == false && App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN) {
		
		hammerExist = true;
		hammerPosition = { App->player->position.x, App->player->position.y };
	}

	if (hammerExist == true)
	{
		if (App->player->currentAnimation->GetCurrentFps() % 2 == 0)
		{
			if (App->player->currentAnimation == &App->player->hammerLeftAnim) {
				hammerPosition.x = App->player->position.x - 16;
				hammerPosition.y = App->player->position.y + 4;
			}
			else if (App->player->currentAnimation == &App->player->hammerRightAnim) {
				hammerPosition.x = App->player->position.x + 8 + App->player->playerCollider->rect.w;
				hammerPosition.y = App->player->position.y + 4;
			}
		}

		else
		{
			if (App->player->currentAnimation == &App->player->hammerLeftAnim) {
				hammerPosition.x = App->player->position.x - 16;
				hammerPosition.y = App->player->position.y + 4;
			}
			else if (App->player->currentAnimation == &App->player->hammerRightAnim) {
				hammerPosition.x = App->player->position.x + 8 + App->player->playerCollider->rect.w;
				hammerPosition.y = App->player->position.y + 4;
			}
			if (hammerExist) hammerCollider->SetPos(hammerPosition.x, hammerPosition.y);
		}
		
	}
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