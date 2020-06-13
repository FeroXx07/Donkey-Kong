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
#include <stdio.h>

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

	elevatorSprite = {536,140,16,8};
	elevatorComplementSpriteDOWN = { 512, 136,16,16 };
	elevatorComplementSpriteUP = { 512, 118,16,16 };


	jumperAnim.PushBack({ 466,137,12,15 });
	jumperAnim.PushBack({ 488,141,16,11 });
	jumperAnim.loop = true;
	jumperAnim.speed = 0.1f;


	pathJumper.loop = true;
	pathJumper.PushBack({ 1.5, 1 }, 20, &jumperAnim);
	pathJumper.PushBack({ 1.5, -1 }, 20, &jumperAnim);
	pathJumper.PushBack({ 1.5, 1 }, 20, &jumperAnim);
	pathJumper.PushBack({ 1.5, -1 }, 20, &jumperAnim);
	pathJumper.PushBack({ 1.5, 1 }, 20, &jumperAnim);
	pathJumper.PushBack({ 1.5, -1 }, 20, &jumperAnim);
	pathJumper.PushBack({ 0, 2 }, 120, &jumperAnim);
	currentAnimJumper = pathJumper.GetCurrentAnimation();

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

	FX_Jumps = App->audio->LoadFx("Assets/Music/SFX_EnemyJumper.wav");
	++activeFx; ++totalFx;

	FX_Fall = App->audio->LoadFx("Assets/Music/SFX_Fall.wav");
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
	App->collisions->AddCollider({ 0, 500, SCREEN_WIDTH, 8 }, Collider::Type::ENEMY);

	App->collisions->AddCollider({ 0, 232, 24, 8 }, Collider::Type::GROUND); 
	App->collisions->AddCollider({ 0, 192, 7, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 8 + 3, 192, 8 - 6, 40 }, Collider::Type::LADDER); 
	App->collisions->AddCollider({ 16, 192, 9, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 16, 198, 9, 2 }, Collider::Type::LOWERGROUND);

	App->collisions->AddCollider({ 0, 136, 15, 6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 0, 142, 15, 2 }, Collider::Type::LOWERGROUND);
	App->collisions->AddCollider({ 16 + 3, 136, 8 - 6, 56 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 24, 136, 1, 6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 24, 142, 1, 2 }, Collider::Type::LOWERGROUND);

	
	App->collisions->AddCollider({ 64, 208, 24, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 56, 136, 7, 6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 56, 142, 7, 2 }, Collider::Type::LOWERGROUND);
	App->collisions->AddCollider({ 64 + 3, 136, 8 - 6, 72 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 72, 136, 7, 6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 72, 142, 7, 2 }, Collider::Type::LOWERGROUND);
	App->collisions->AddCollider({ 80 + 3, 136, 8 - 6, 72 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 88, 136, 1, 6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 88, 142, 1, 2 }, Collider::Type::LOWERGROUND);


	App->collisions->AddCollider({ 120, 232, 24, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 152+1, 224, 16-1, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 176, 216, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 200, 208, 24, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 207, 184, 1, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 207, 190, 1, 2 }, Collider::Type::LOWERGROUND);
	App->collisions->AddCollider({ 208 + 3, 184, 8 - 6, 24 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 216, 184, 8, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 216, 190, 8, 2 }, Collider::Type::LOWERGROUND);

	App->collisions->AddCollider({ 184, 176, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 183, 144, 1, 8-6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 183, 150, 1, 8 - 6 }, Collider::Type::LOWERGROUND);
	App->collisions->AddCollider({ 183 + 4, 144, 8 - 6, 32 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 192, 144, 32, 8-6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 192, 150, 32, 2 }, Collider::Type::LOWERGROUND);

	App->collisions->AddCollider({ 160, 168, 15, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 136, 160, 16, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 128, 128, 8, 5 }, Collider::Type::GROUND); //Modified
	App->collisions->AddCollider({ 128, 134, 8, 2 }, Collider::Type::LOWERGROUND);
	App->collisions->AddCollider({ 136 + 3, 128, 8 - 6, 32 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 144, 128, 8, 5 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 144, 134, 8, 2 }, Collider::Type::LOWERGROUND);


	App->collisions->AddCollider({ 160, 120, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 184, 112, 16, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 207, 104, 1, 6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 207, 110, 1, 2 }, Collider::Type::LOWERGROUND);
	App->collisions->AddCollider({ 208 + 3, 104, 8 - 6, 41 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 216, 104, 8, 6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 216, 110, 8, 2 }, Collider::Type::LOWERGROUND);

	App->collisions->AddCollider({ 0, 88, 160, 8-6 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 0, 94, 140, 2  }, Collider::Type::ENEMY);
	App->collisions->AddCollider({ 160 + 3, 88, 8 - 6, 32 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 168, 88, 1, 8-6 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 88, 56, 40, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 88, 60, 40, 2 }, Collider::Type::LOWERGROUND);
	App->collisions->AddCollider({ 128 + 3, 56, 8 - 6, 32 }, Collider::Type::LADDER);
	App->collisions->AddCollider({ 136, 56, 1, 2 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 136, 60, 1, 2 }, Collider::Type::LOWERGROUND);

	activeColliders += 58; totalColliders += 58;

	// Walls
	App->collisions->AddCollider({ 151, 229, 2, 3 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 175, 221, 2, 3 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 199, 212, 2, 3 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 199, 180, 3, 4 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 175, 173, 3, 4 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 151, 164, 3, 4 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 158, 124, 3, 4 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 183, 116, 2, 3 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 206, 108, 2, 3 }, Collider::Type::WALL);

	activeColliders += 9; totalColliders += 9;

	// Elevators
	elevator[2] = App->collisions->AddCollider({ 32, 146, 16, 6 }, Collider::Type::GROUND);
	elevator[2]->rect.x = 32;
	elevator[2]->rect.y = 146; //140

	elevator[1] = App->collisions->AddCollider({ 32, 197, 16, 6 }, Collider::Type::GROUND);
	elevator[1]->rect.x = 32;
	elevator[1]->rect.y = 197;//192

	elevator[0] = App->collisions->AddCollider({ 32, 248, 16, 6 }, Collider::Type::GROUND);
	elevator[0]->rect.x = 32;
	elevator[0]->rect.y = 248;

	elevator[5] = App->collisions->AddCollider({ 96, 146, 16, 8 }, Collider::Type::GROUND);
	elevator[5]->rect.x = 96;
	elevator[5]->rect.y = 146; //140

	elevator[4] = App->collisions->AddCollider({ 96, 197, 16, 8 }, Collider::Type::GROUND);
	elevator[4]->rect.x = 96;
	elevator[4]->rect.y = 197;//192

	elevator[3] = App->collisions->AddCollider({ 96, 248, 16, 8 }, Collider::Type::GROUND);
	elevator[3]->rect.x = 96;
	elevator[3]->rect.y = 248;
	
	activeColliders += 6; totalColliders += 6;

	// Items
	App->enemies->AddEnemy(Enemy_Type::ITEM_IRON, 69, 199);
	App->enemies->AddEnemy(Enemy_Type::ITEM_UMBRELLA, 4, 120);
	App->enemies->AddEnemy(Enemy_Type::ITEM_BAG, 207, 94);
	donkeyCollider = App->collisions->AddCollider({ 24, 56, 40, 32 }, Collider::Type::ENEMY);
	activeColliders += 4; totalColliders += 4;

	App->enemies->AddEnemy(Enemy_Type::ENEMY_FIREMINION, 70, 124);
	App->enemies->AddEnemy(Enemy_Type::ENEMY_FIREMINION, 211, 92);
	activeColliders += 2; totalColliders += 2;

	// Walls
	App->collisions->AddCollider({ 54-5, 128, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 88+5, 128, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 60-5, 200, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 90+5, 200, 2, 8 }, Collider::Type::ENEMYWALL);

	App->collisions->AddCollider({ 206 - 5, 92, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 224 + 5, 92, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 182 - 5, 132, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 224 + 5, 132, 2, 8 }, Collider::Type::ENEMYWALL);

	App->collisions->AddCollider({ 181 - 5, 168, 2, 8 }, Collider::Type::ENEMYWALL);
	App->collisions->AddCollider({ 200 + 5, 168, 2, 8 }, Collider::Type::ENEMYWALL);
	activeColliders += 10; totalColliders += 10;

	//Starting position of the Mario
	App->player->position.x = 2;
	App->player->position.y = 232 - App->player->playerCollider->rect.h;
	App->player->speed.y = 0;

	jumperPosition.x = 0;
	jumperPosition.y = 0;
	spawnPosition = { 0,57 };
	jumperCollider = App->collisions->AddCollider({ jumperPosition.x+1 ,jumperPosition.y+1,2,2 }, Collider::Type::ENEMY);
	activeColliders += 6; totalColliders += 6;
	return ret;
}

update_status ModuleScene2::Update()
{
	// Resets elevator positions
	for (int i = 0; i < 3; ++i)
	{
		elevator[i]->SetPos(elevator[i]->rect.x, --elevator[i]->rect.y);
		if (elevator[i]->rect.y <= 104)
		{
			elevator[i]->rect.y = 248;
		}
	}

	for (int i = 3; i < 6; ++i)
	{
		elevator[i]->SetPos(elevator[i]->rect.x, ++elevator[i]->rect.y);
		if (elevator[i]->rect.y >= 248)
		{
			elevator[i]->rect.y = 104;
		}
	}

	// Resets level when dies
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

	if (jumperPosition.x == 31 || jumperPosition.x == 94 || jumperPosition.x == 159)
	{
		App->audio->PlayFx(FX_Jumps);
	}
	if (jumperPosition.x == 187 && jumperPosition.y == 72)
	{
		App->audio->PlayFx(FX_Fall);
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

	// Update path of the jumper
	pathJumper.Update();

	// Limit the jumper to a certain position to make it reset
	if (jumperPosition.y >= 248)
	{
		pathJumper.ResetrelativePosition();
		pathJumper.Reset();
		jumperPosition.y = spawnPosition.y;
		jumperPosition.x = spawnPosition.x;
	}

	// Update pos, coll and anim of the jumper
	jumperPosition = spawnPosition + pathJumper.GetRelativePosition();
	printf("DK.Y= %d\n\n", jumperPosition.y);
	printf("DK.X= %d\n\n", jumperPosition.x);
	jumperCollider->SetPos(jumperPosition.x+1, jumperPosition.y+3);
	currentAnimJumper->Update();

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

	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN)
	{
		App->player->position.x = 126;
		App->player->position.y = 40;
	}

	if (App->player->position.y <= 41)
	{
		App->hud->LevelWins += 25;
		App->fade->FadeToBlack(this, (Module*)App->level2win);

	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &level_2);
	App->render->Blit(bgTexture, 32, 88, &elevatorComplementSpriteDOWN);
	App->render->Blit(bgTexture, 96, 88, &elevatorComplementSpriteDOWN);

	for (int i = 0; i < 6; ++i)
	{
		App->render->Blit(bgTexture, elevator[i]->rect.x, elevator[i]->rect.y, &elevatorSprite);
	}
	App->render->Blit(bgTexture, 32, 239, &elevatorComplementSpriteUP);
	App->render->Blit(bgTexture, 96, 239, &elevatorComplementSpriteUP);

	if (currentAnimDonkey != nullptr)
	{
		LOG("Drawing DONKEY KONG of the WinScene");
		App->render->Blit(bgTexture, 24, 56, &(currentAnimDonkey->GetCurrentFrame()));
	}

	if (currentAnimJumper != nullptr)
	{
		LOG("Drawing DONKEY KONG of the WinScene");
		App->render->Blit(bgTexture, jumperPosition.x, jumperPosition.y, &(currentAnimJumper->GetCurrentFrame()));
	}

	if (currentAnimPrincess != nullptr)
	{
		LOG("Drawing the Princess ");
		App->render->Blit(bgTexture, 88, 34, &(currentAnimPrincess->GetCurrentFrame()));
		if (helpCounter >= 150)
		{
			if (currentAnimPrincess == &prAnimRight)
				App->render->Blit(bgTexture, 107, 34, &helpRight);
		}
	}

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

	App->audio->UnloadFx(FX_Jumps);
	--totalFx;

	App->audio->UnloadFx(FX_Fall);
	--totalFx;

	App->audio->UnloadFx(FX_Stomp);
	--totalFx;

	App->textures->Unload(bgTexture);
	--totalTextures;
	return true;
}