#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleHammer.h"
#include "ModulePlayer.h"
#include "Level4.h"
#include "ModuleEnemies.h"

#include <stdio.h>
#include "Game/SDL/include/SDL_scancode.h"

// Constructor
ModuleHammer::ModuleHammer(bool startEnabled) : Module(startEnabled)
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
	++activeTextures; ++totalTextures;

	FX_Hammer = App->audio->LoadFx("Assets/Music/SFX_Hammer.wav");
	++activeFx; ++totalFx;

	//Starting position of the Mario
	hammerPosition.x = App->player->position.x;
	hammerPosition.y = App->player->position.y;

	hammerCollider = App->collisions->AddCollider({ hammerPosition.x,hammerPosition.y, 10,10 }, Collider::Type::HAMMER);
	++activeColliders; ++totalColliders;
	return ret;
}

// Called at the middle of the application loop
// Processes new input and handles hammer movement
update_status ModuleHammer::Update()
{
	if (hammerExist)
	{
		if (frameCountHammer == 0)
			App->audio->PlayFx(FX_Hammer);
		frameCountHammer++;
	}

	if (frameCountHammer == 960)
		frameCountHammer = 0;

	if (hammerExist == true && App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
	{
		hammerExist = false;
		hammerPosition = { 0, 0 };
		hammerCollider->SetPos(hammerPosition.x, hammerPosition.y);
	}

	if (hammerExist == false && App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN) {

		hammerExist = true;
		hammerPosition = { App->player->position.x, App->player->position.y };

		if (frameCountHammer == 0)
			App->audio->PlayFx(FX_Hammer);
	}

	if (hammerExist == true)
	{
		if (App->player->currentAnimation->GetCurrentFps() % 2 == 0) // Hammer down
		{
			if ((App->player->currentAnimation == &App->player->hammerLeftAnim) || (App->player->currentAnimation == &App->player->hammerLeftIdleAnim)) {
				hammerCollider->SetPos(App->player->position.x - 16, App->player->position.y + 4);
			}
			else if ((App->player->currentAnimation == &App->player->hammerRightAnim) || (App->player->currentAnimation == &App->player->hammerRightIdleAnim)) {
				hammerCollider->SetPos(App->player->position.x + 18, App->player->position.y + 4);
			}
		}

		else // Hammer up
		{
			if ((App->player->currentAnimation == &App->player->hammerLeftAnim) || (App->player->currentAnimation == &App->player->hammerLeftIdleAnim)) {
				hammerCollider->SetPos(App->player->position.x + 1, App->player->position.y - 11);
			}
			else if ((App->player->currentAnimation == &App->player->hammerRightAnim) || (App->player->currentAnimation == &App->player->hammerRightIdleAnim)) {
				hammerCollider->SetPos(App->player->position.x + 1, App->player->position.y - 11);
			}
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

bool ModuleHammer::CleanUp()
{
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	App->textures->Unload(texture);
	--totalTextures;

	App->audio->UnloadFx(FX_Hammer);
	--totalFx;

	App->collisions->RemoveCollider(hammerCollider);
	--totalColliders;

	return true;
}