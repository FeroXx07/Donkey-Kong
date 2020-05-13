#include "ModuleSceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Game/SDL/include/SDL_scancode.h"
#include <stdio.h>

#include "Game/SDL/include/SDL.h"
#include "Game/SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "Game/SDL_mixer/libx86/SDL2_mixer.lib" )


ModuleSceneWin::ModuleSceneWin(bool startEnabled) : Module(startEnabled)
{
	normalScene.x = 8;
	normalScene.y = 628;
	normalScene.w = SCREEN_WIDTH;
	normalScene.h = SCREEN_HEIGHT;

	fallingScene.x = 240;
	fallingScene.y = 628;
	fallingScene.w = SCREEN_WIDTH;
	fallingScene.h = SCREEN_HEIGHT;

	celebrationScene.x = 472;
	celebrationScene.y = 628;
	celebrationScene.w = SCREEN_WIDTH;
	celebrationScene.h = SCREEN_HEIGHT;

	angryAnim.PushBack({ 8,588,40,32 });
	angryAnim.PushBack({ 56,588,46,32 });
	angryAnim.PushBack({ 110,588,46,32 });
	angryAnim.loop = true;
	angryAnim.speed = 0.1f;

	fallAnim.PushBack({ 164	,588,40,32 });
	fallAnim.loop = true;
	fallAnim.speed = 0.1f;

	hurtAnim.PushBack({ 212,580,40,40 });
	hurtAnim.PushBack({ 260,580,40,40 });
	hurtAnim.PushBack({ 308,580,40,40 });
	hurtAnim.PushBack({ 356,580,40,40 });
	hurtAnim.PushBack({ 404,580,40,40 });
	hurtAnim.PushBack({ 452,580,40,40 });
	hurtAnim.loop = true;
	hurtAnim.speed = 0.1f;

	
	path.loop = false;
	path.PushBack({ 0,0 }, 180, &angryAnim);
	path.PushBack({ 0,+1.0f }, 127, &fallAnim);
	path.PushBack({ 0,0 }, 240, &hurtAnim);
	currentAnim = path.GetCurrentAnimation();
	
	princessSprite = {504, 598, 16, 22};
	marioSprite = { 530, 604, 12, 16 };
	heartSprite = { 553, 598,15,13 };
}

ModuleSceneWin::~ModuleSceneWin()
{

}

// Load assets
bool ModuleSceneWin::Start()
{
	Mix_HaltMusic();

	LOG("Loading background assets of the WinScene");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/WinTexture.png");
	++activeTextures; ++totalTextures;

	FX_DK_Defeated = App->audio->LoadFx("Assets/Music/SFX_DK Defeated.wav");
	++activeFx; ++totalFx;
	FX_DK_Falling= App->audio->LoadFx("Assets/Music/SFX_Fall.wav");
	++activeFx; ++totalFx;
	FX_DK_Stomp = App->audio->LoadFx("Assets/Music/SFX_Stomp.wav");
	++activeFx; ++totalFx;
	FX_WinMusic = App->audio->LoadFx("Assets/Music/SFX_Ending.wav");
	++activeFx; ++totalFx;

	spawnPosition.x = 90;
	spawnPosition.y = 88 - 32;
	donkeyPosition = { 0,0 };
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	currentAnim = path.GetCurrentAnimation();
	frameCount = 0;
	return ret;
}

update_status ModuleSceneWin::Update()
{

	LOG("Updating background assets of the WinScene");
	path.Update();
	
	donkeyPosition = spawnPosition + path.GetRelativePosition();
	printf("DK.Y= %d\n\n", donkeyPosition.y);
	currentAnim = path.GetCurrentAnimation();
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (frameCount >= 307) {
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			App->textures->Unload(bgTexture);
			App->fade->FadeToBlack(this, (Module*)App->intro);
		}
	}
	

	LOG("Updated background assets of the WinScene");
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneWin::PostUpdate()
{
	LOG("Drawing background assets of the WinScene");
	if (frameCount < 15) 
	{
		App->render->Blit(bgTexture, 0, 0, &normalScene);
		App->render->Blit(bgTexture, spawnPosition.x + 40/2 - princessSprite.w/2, 48 - princessSprite.h, &princessSprite);

		if (frameCount == 14) App->audio->PlayFx(FX_DK_Defeated);
		
	}
	if (frameCount >= 15 && frameCount < 307) {
		if (frameCount == 200) App->audio->PlayFx(FX_DK_Falling);

		App->render->Blit(bgTexture, 0, 0, &fallingScene);
		App->render->Blit(bgTexture, spawnPosition.x + 40 / 2 - princessSprite.w / 2, 48 - princessSprite.h, &princessSprite);
		
	}
	if (frameCount >= 307) {
		if (frameCount == 307) App->audio->PlayFx(FX_DK_Stomp);
		App->collisions->Disable();
		App->player->Disable();

		App->render->Blit(bgTexture, 0, 0, &celebrationScene);
		App->render->Blit(bgTexture, spawnPosition.x + 40 / 2 - princessSprite.w / 2, 88 - princessSprite.h, &princessSprite);
		App->render->Blit(bgTexture, spawnPosition.x + 40 / 2 - marioSprite.w / 2 + 40, 88 - marioSprite.h, &marioSprite);
		App->render->Blit(bgTexture, spawnPosition.x + 40 / 2  - heartSprite.w / 2 + 20, 88 - heartSprite.h - 14, &heartSprite);
		if (frameCount == 367) App->audio->PlayFx(FX_WinMusic);
	}

	if (currentAnim != nullptr)
	{
		LOG("Drawing DONKEY KONG of the WinScene");
		App->render->Blit(bgTexture, donkeyPosition.x, donkeyPosition.y, &(currentAnim->GetCurrentFrame()));
	}
	++frameCount;
	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneWin::CleanUp()
{
	//App->audio->FreeAll();
	App->collisions->Disable();
	App->player->Disable();

	activeTextures = activeColliders = activeFonts = activeFx = 0;

	// TODO 1: Remove ALL remaining resources. Update resource count properly

	App->textures->Unload(bgTexture);
	--totalTextures;

	App->audio->UnloadFx(FX_DK_Defeated);
	--totalFx;
	App->audio->UnloadFx(FX_DK_Falling);
	--totalFx;
	App->audio->UnloadFx(FX_DK_Stomp);
	--totalFx;
	App->audio->UnloadFx(FX_WinMusic);
	--totalFx;
	return true;
	return true;
}