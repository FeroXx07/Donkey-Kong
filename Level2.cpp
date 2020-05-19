#include "Level2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleHammer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleHud.h"
#include "ModuleParticles.h"

#include "Game/SDL_mixer/include/SDL_mixer.h"
#include "Game/SDL/include/SDL_scancode.h"


#include "Game/SDL/include/SDL.h"
#include "Game/SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "Game/SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleScene2::ModuleScene2(bool startEnabled) : Module(startEnabled)
{
	// Level 2 scene sprite
	level_2.x = 8;
	level_2.y = 160;
	level_2.w = SCREEN_WIDTH;
	level_2.h = SCREEN_HEIGHT;
}

ModuleScene2::~ModuleScene2()
{

}

// Load assets
bool ModuleScene2::Start()
{
	App->hud->drawScore = true;

	LOG("Loading background assets");

	bool ret = true;
	// Scene sprites
	bgTexture = App->textures->Load("Assets/Background2.png");
	++activeTextures; ++totalTextures;

	FX_Win = App->audio->LoadFx("Assets/Music/Stage_Clear_2.wav");
	++activeFx; ++totalFx;

	FX_Lose = App->audio->LoadFx("Assets/Music/SFX_Death.wav");
	++activeFx; ++totalFx;

	App->particles->Enable();
	App->collisions->Enable();
	App->player->Enable();
	App->hammer->Enable();
	if (App->hud->lives != 3) App->hammer->Start();
	App->enemies->Enable();

	resetCounter = 0;
	App->player->destroyed = false;

	// Level 2 colliders:
	App->collisions->AddCollider({ 0, 500, SCREEN_WIDTH, 8 }, Collider::Type::ENEMY);


	App->collisions->AddCollider({ 0, 232, 24, 8 }, Collider::Type::GROUND); 
	App->collisions->AddCollider({ 0, 192, 7, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 8 + 3, 192, 8 - 6, 40 }, Collider::Type::LADDER); 
	App->collisions->AddCollider({ 16, 192, 9, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 0, 136, 15, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 16 + 3, 136, 8 - 6, 56 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 24, 136, 1, 8 }, Collider::Type::GROUND);
	
	App->collisions->AddCollider({ 64, 208, 24, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 56, 136, 7, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 64 + 3, 136, 8 - 6, 72 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 72, 136, 7, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 80 + 3, 136, 8 - 6, 72 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 88, 136, 1, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 120, 232, 24, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 152, 224, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 176, 216, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 200, 208, 24, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 207, 184, 1, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 208 + 3, 184, 8 - 6, 24 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 216, 184, 8, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 184, 176, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 183, 144, 1, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 183 + 3, 144, 8 - 6, 32 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 192, 144, 32, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 160, 168, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 136, 160, 16, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 128, 128, 8, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 136 + 3, 128, 8 - 6, 32 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 144, 128, 8, 8 }, Collider::Type::GROUND);


	App->collisions->AddCollider({ 160, 120, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 184, 112, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 207, 104, 1, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 208 + 3, 104, 8 - 6, 41 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 216, 104, 8, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 0, 88, 160, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 160 + 3, 88, 8 - 6, 32 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 168, 88, 1, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 88, 56, 40, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 128 + 3, 56, 8 - 6, 32 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 136, 56, 1, 8 }, Collider::Type::GROUND);

	//Starting position of the Mario
	App->player->position.x = 2;
	App->player->position.y = 232 - App->player->playerCollider->rect.h;
	App->player->speed.y = 0;
	activeColliders += 40; totalColliders += 40;

	return ret;
}

update_status ModuleScene2::Update()
{
	if (App->player->destroyed && App->hud->lives > 0) {

		if (resetCounter >= 180)
		{
			resetCounter = -60;
			App->fade->FadeToBlack(this, (Module*)App->level2);
		}

		if (resetCounter == 1)
		{
			Mix_HaltMusic();
			App->audio->PlayFx(FX_Lose);
			App->particles->AddParticle(App->particles->marioDeath, App->player->playerCollider->rect.x, App->player->playerCollider->rect.y);
		}

		++resetCounter;
	}
	else if (App->player->destroyed && App->hud->lives == 0) {

	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &level_2);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene2::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	App->particles->Disable();
	App->collisions->Disable();
	App->player->Disable();
	App->enemies->Disable();

	App->audio->UnloadFx(FX_Win);
	--totalFx;

	App->audio->UnloadFx(FX_Lose);
	--totalFx;

	App->textures->Unload(bgTexture);
	--totalTextures;
	return true;
}