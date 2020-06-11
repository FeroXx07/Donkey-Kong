#include "Level3.h"

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
#include <stdio.h>

#include "Game/SDL_mixer/include/SDL_mixer.h"
#include "Game/SDL/include/SDL_scancode.h"


#include "Game/SDL/include/SDL.h"
#include "Game/SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "Game/SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleScene3::ModuleScene3(bool startEnabled) : Module(startEnabled)
{
	// Level 2 scene sprite
	level_3.x = 472;
	level_3.y = 176;
	level_3.w = SCREEN_WIDTH;
	level_3.h = SCREEN_HEIGHT;

	conveyorBeltLeft.PushBack({850,155,11,10});
	conveyorBeltLeft.PushBack({ 874,155,11,10 });
	conveyorBeltLeft.PushBack({ 898,155,11,10 });
	conveyorBeltLeft.loop =false;
	conveyorBeltLeft.pingpong = true;
	conveyorBeltLeft.speed = 0.1f;

	conveyorBeltRight.PushBack({ 850,145,11,10 });
	conveyorBeltRight.PushBack({ 874,145,11,10 });
	conveyorBeltRight.PushBack({ 898,145,11,10 });
	conveyorBeltRight.loop = true;
	conveyorBeltRight.pingpong = true;
	conveyorBeltRight.speed = 0.1f;

	conveyorPathLeft.PushBack({ 0,0 }, 540, &conveyorBeltLeft);


	elevatorLadderSprite = {827,152,10,16};

	oilBarrelAnim.PushBack({416,136,16,32});
	oilBarrelAnim.PushBack({440,136,16,32});
	oilBarrelAnim.PushBack({464,136,16,32});
	oilBarrelAnim.PushBack({488,136,16,32});
	oilBarrelAnim.speed = 0.1f;

	dkAnimIdle.PushBack({ 256, 56, 40, 32 });
	dkRightHand.PushBack({ 357, 56, 46, 32 });
	dkLeftHand.PushBack({ 304, 56, 46, 32 });
	dkAnimIdle.speed = 0.1f;
	dkRightHand.speed = 0.1f;
	dkLeftHand.speed = 0.1f;

	donkeyPath.PushBack({ 0,0, }, 120, &dkAnimIdle);
	donkeyPath.PushBack({ 0,0, }, 30, &dkRightHand);
	donkeyPath.PushBack({ 0,0, }, 30, &dkLeftHand);
	donkeyPath.PushBack({ 0,0, }, 30, &dkRightHand);
	donkeyPath.loop = true;


	prAnimRight.PushBack({ 96,103,15,22 });
	prAnimRight.PushBack({ 121,103,15,22 });
	prAnimRight.speed = 0.1f;
	prAnimRight.loop = true;
	prAnimRightIdle.PushBack({ 143,103,16,22 });

	princessPathRight.PushBack({ 0,0 }, 150, &prAnimRightIdle);
	princessPathRight.PushBack({ 0,0 }, 60, &prAnimRight);
	princessPathRight.loop = true;

	helpRight = { 280,117,24,8 };
}

ModuleScene3::~ModuleScene3()
{

}

// Load assets
bool ModuleScene3::Start()
{
	App->hud->drawScore = true;

	LOG("Loading background assets");

	bool ret = true;
	// Scene sprites
	bgTexture = App->textures->Load("Assets/Background.png");
	++activeTextures; ++totalTextures;

	dKTexture = App->textures->Load("Assets/Background2.png");
	++activeTextures; ++totalTextures;


	FX_Win = App->audio->LoadFx("Assets/Music/Stage_Clear_2.wav");
	++activeFx; ++totalFx;

	FX_Lose = App->audio->LoadFx("Assets/Music/SFX_Death.wav");
	++activeFx; ++totalFx;

	FX_Stomp = App->audio->LoadFx("Assets/Music/SFX_Stomp.wav");
	++activeFx; ++totalFx;

	App->particles->Enable();
	App->collisions->Enable();
	App->player->Enable();
	App->hammer->Enable();
	if (App->hud->lives != 3) App->hammer->Start();
	App->enemies->Enable();

	resetCounter = 0;
	donkeyCounterFX = 0;
	helpCounter = 0;

	App->player->destroyed = false;

	// Level 2 colliders:
	//App->collisions->AddCollider({ 0, 500, SCREEN_WIDTH, 8 }, Collider::Type::ENEMY);

	App->collisions->AddCollider({ 0, 248, 224, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 8, 208, 16, 8 }, Collider::Type::GROUND);// Conveyor
	App->collisions->AddCollider({ 24 + 3, 208, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 32, 208, 48, 8 }, Collider::Type::GROUND);// Conveyor
	App->collisions->AddCollider({ 80 + 3, 208, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 88, 208, 48, 8 }, Collider::Type::GROUND);// Conveyor
	App->collisions->AddCollider({ 136 + 3, 208, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 144, 208, 48, 8 }, Collider::Type::GROUND);// Conveyor
	App->collisions->AddCollider({ 192 + 3, 208, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 200, 208, 22, 8 }, Collider::Type::GROUND);// Conveyor
	activeColliders += 10; totalColliders += 10;

	App->collisions->AddCollider({ 8, 168, 40, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 63, 168, 1, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 64 + 3, 168, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 72, 168, 72, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 144 + 3, 168, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 152, 168, 1, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 168, 168, 48, 8 }, Collider::Type::GROUND);
	activeColliders += 6; totalColliders += 6;

	App->collisions->AddCollider({ 0, 128, 24, 8 }, Collider::Type::GROUND);// Conveyor
	App->collisions->AddCollider({ 24 + 3, 128, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 32, 128, 48, 8 }, Collider::Type::GROUND);// Conveyor
	App->collisions->AddCollider({ 80 + 3, 128, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 88, 128, 8, 8 }, Collider::Type::GROUND);// Conveyor

	App->collisions->AddCollider({ 128, 128, 8, 8 }, Collider::Type::GROUND);// Conveyor
	App->collisions->AddCollider({ 136 + 3, 128, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 144, 128, 48, 8 }, Collider::Type::GROUND);// Conveyor
	App->collisions->AddCollider({ 192 + 3, 128, 8 - 6, 40 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 200, 128, 24, 8 }, Collider::Type::GROUND);// Conveyor
	activeColliders += 10; totalColliders += 10;

	


	// Elevators
	//elevatingLadder[1] = App->collisions->AddCollider({ 32, 197, 16, 6 }, Collider::Type::GROUND);
	//elevatingLadder[1]->rect.x = 32;
	//elevatingLadder[1]->rect.y = 197;//192

	//elevatingLadder[0] = App->collisions->AddCollider({ 32, 248, 16, 6 }, Collider::Type::GROUND);
	//elevatingLadder[0]->rect.x = 32;
	//elevatingLadder[0]->rect.y = 248;

	
	activeColliders += 3; totalColliders += 3;

	// Items
	App->enemies->AddEnemy(Enemy_Type::ITEM_IRON, 61, 159);
	App->enemies->AddEnemy(Enemy_Type::ITEM_UMBRELLA, 196, 152);
	App->enemies->AddEnemy(Enemy_Type::ITEM_BAG, 119, 238);
	donkeyCollider = App->collisions->AddCollider({ 24, 56, 40, 32 }, Collider::Type::ENEMY);
	activeColliders += 4; totalColliders += 4;



	// Walls
	/*App->collisions->AddCollider({ 54 - 5, 128, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 88 + 5, 128, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 60 - 5, 200, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 90 + 5, 200, 2, 8 }, Collider::Type::ENEMYWALL);

	App->collisions->AddCollider({ 206 - 5, 92, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 224 + 5, 92, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 182 - 5, 132, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 224 + 5, 132, 2, 8 }, Collider::Type::ENEMYWALL);

	App->collisions->AddCollider({ 181 - 5, 168, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 200 + 5, 168, 2, 8 }, Collider::Type::ENEMYWALL);
	activeColliders += 10; totalColliders += 10;*/

	//Starting position of the Mario
	App->player->position.x = 48;
	App->player->position.y = 232 - App->player->playerCollider->rect.h;
	App->player->speed.y = 0;

	return ret;
}

update_status ModuleScene3::Update()
{
	// Resets elevator positions
	/*for (int i = 0; i < 2; ++i)
	{
		elevatingLadder[i]->SetPos(elevatingLadder[i]->rect.x, --elevatingLadder[i]->rect.y);
		if (elevatingLadder[i]->rect.y <= 104)
		{
			elevatingLadder[i]->rect.y = 248;
		}
	}*/

	// Resets level when dies
	if (App->player->destroyed && App->hud->lives > 0) {

		if (resetCounter >= 180)
		{
			resetCounter = -60;
			App->fade->FadeToBlack(this, (Module*)App->level3);
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
		if (resetCounter >= 500)
		{
			resetCounter = -60;
			App->fade->FadeToBlack(this, (Module*)App->intro);
		}

		if (resetCounter == 1)
		{
			Mix_HaltMusic();
			App->audio->PlayFx(FX_Lose);
			App->particles->AddParticle(App->particles->marioDeath, App->player->playerCollider->rect.x, App->player->playerCollider->rect.y);
		}
		++resetCounter;
	}

	++donkeyCounterFX;
	if (donkeyCounterFX == 150 || donkeyCounterFX == 180 || donkeyCounterFX == 210)
	{
		App->audio->PlayFx(FX_Stomp);
	}
	else if (donkeyCounterFX > 210)
	{
		donkeyCounterFX = 0;
	}


	princessPathRight.Update();
	currentAnimPrincess = princessPathRight.GetCurrentAnimation();
	currentAnimPrincess->Update();

	donkeyPath.Update();
	currentAnimDonkey = donkeyPath.GetCurrentAnimation();

	// counter for Help signal
	++helpCounter;
	if (helpCounter >= 210)
	{
		helpCounter = 0;
	}

	oilBarrelAnim.Update();
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene3::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &level_3);
	
	for (int i = 0; i < 2; ++i)
	{
		//App->render->Blit(bgTexture, elevatingLadder[i]->rect.x, elevatingLadder[i]->rect.y, &elevatorLadderSprite);
	}

	App->render->Blit(bgTexture, 104, 113, &oilBarrelAnim.GetCurrentFrame());

	if (currentAnimDonkey != nullptr)
	{
		LOG("Drawing DONKEY KONG of the WinScene");
		App->render->Blit(dKTexture, 24, 56, &(currentAnimDonkey->GetCurrentFrame()));
	}

	if (currentAnimPrincess != nullptr)
	{
		LOG("Drawing the Princess ");
		App->render->Blit(dKTexture, 88, 34, &(currentAnimPrincess->GetCurrentFrame()));
		if (helpCounter >= 150)
		{
			if (currentAnimPrincess == &prAnimRight)
				App->render->Blit(dKTexture, 107, 34, &helpRight);
		}
	}

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene3::CleanUp()
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

	App->audio->UnloadFx(FX_Stomp);
	--totalFx;

	App->textures->Unload(bgTexture);
	--totalTextures;

	App->textures->Unload(dKTexture);
	--totalTextures;
	return true;
}