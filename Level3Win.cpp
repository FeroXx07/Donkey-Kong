#include "Level3Win.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleHud.h"

#include "Game/SDL/include/SDL_scancode.h"
#include <stdio.h>

#include "Game/SDL/include/SDL.h"
#include "Game/SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "Game/SDL_mixer/libx86/SDL2_mixer.lib" )


Level3Win::Level3Win(bool startEnabled) : Module(startEnabled)
{
	level3win.x = 704;
	level3win.y = 176;
	level3win.w = SCREEN_WIDTH;
	level3win.h = SCREEN_HEIGHT;

	princessSprite = { 144, 103, 16, 22 };
	marioSprite = { 66, 24, 12, 16 };

	heartSprite.PushBack({ 313, 106,15,13 });
	brokenHeartSprite.PushBack({ 336,106,16,13 });
	heart.PushBack({ 0,0 }, 90, &heartSprite);
	heart.PushBack({ 0,0 }, 30, &brokenHeartSprite);
	heart.loop = false;

	idleDonkey.PushBack({ 256,56,40,32 });

	climbDonkey.PushBack({ 412,52,33,36 });
	climbDonkey.PushBack({ 453,52,33,36 });
	climbDonkey.speed = 0.1f;
	climbDonkey.loop = true;

	climbPrincessDonkey.PushBack({ 591,52,38,36 });
	climbPrincessDonkey.PushBack({ 637,56,43,32 });
	climbPrincessDonkey.speed = 0.1f;
	climbPrincessDonkey.loop = true;

	donkeyPath.PushBack({ 1,0 }, 35, &idleDonkey);
	donkeyPath.PushBack({ 0,-1 }, 10, &climbDonkey);
	donkeyPath.PushBack({ 0,-1 }, 10, &climbPrincessDonkey);
	donkeyPath.loop = false;

	monkeyScreen = { 8,352,224,256 };
}

Level3Win::~Level3Win()
{

}

// Load assets
bool Level3Win::Start()
{
	App->hud->drawScore = true;

	App->player->Disable();

	Mix_HaltMusic();

	LOG("Loading background assets of the WinScene");

	bool ret = true;

	bgTextureScene = App->textures->Load("Assets/Level3Win.png");
	++activeTextures; ++totalTextures;

	bgTexture = App->textures->Load("Assets/Level2Win.png");
	++activeTextures; ++totalTextures;

	monkeyTexture = App->textures->Load("Assets/Hud2.png");
	++activeTextures; ++totalTextures;

	FX_DK_Defeated = App->audio->LoadFx("Assets/Music/Stage_Clear_2.wav");
	++activeFx; ++totalFx;

	FX_DK_BrokenHeart = App->audio->LoadFx("Assets/Music/SFX_BrokenHeart.wav");
	++activeFx; ++totalFx;

	FX_Monkey = App->audio->LoadFx("Assets/Music/SFX_MonkeyHeight.wav");
	++activeFx; ++totalFx;

	spawnPosition.x = 24;
	spawnPosition.y = 56;
	donkeyPosition = { 0,0 };
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	heart.Reset();
	currentAnimHeart = heart.GetCurrentAnimation();

	donkeyPath.Reset();
	donkeyPath.ResetrelativePosition();
	currentAnim = donkeyPath.GetCurrentAnimation();
	frameCount = 0;
	spaceCounter = 0;
	return ret;
}

update_status Level3Win::Update()
{

	LOG("Updating background assets of the WinScene");
	heart.Update();
	donkeyPath.Update();

	donkeyPosition = spawnPosition + donkeyPath.GetRelativePosition();
	printf("DK.Y= %d\n\n", donkeyPosition.y);

	currentAnim = donkeyPath.GetCurrentAnimation();
	currentAnim->Update();

	currentAnimHeart = heart.GetCurrentAnimation();
	currentAnimHeart->Update();

	if (frameCount >= 240) {

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			++spaceCounter;
			if (spaceCounter == 1) App->audio->PlayFx(FX_Monkey);
		}
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && spaceCounter >= 2)
	{
		App->textures->Unload(bgTexture);
		App->fade->FadeToBlack(this, (Module*)App->level4);
	}

	LOG("Updated background assets of the WinScene");
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status Level3Win::PostUpdate()
{
	LOG("Drawing background assets of the WinScene");
	if (frameCount <= 240)
	{
		App->render->Blit(bgTextureScene, 0, 0, &level3win);
		if (frameCount > 0 && frameCount < 60)
		{
			App->render->Blit(bgTexture, 87, 34, &princessSprite);
			App->render->Blit(bgTexture, 126, 40, &marioSprite);
			if (frameCount == 1) App->audio->PlayFx(FX_DK_Defeated);
		}
		if (frameCount >= 60) {
			if (frameCount == 61) App->audio->PlayFx(FX_DK_BrokenHeart);
			App->render->Blit(bgTexture, 126, 40, &marioSprite);
		}

		if (currentAnim != nullptr || currentAnimHeart != nullptr)
		{
			LOG("Drawing DONKEY KONG of the WinScene");
			App->render->Blit(bgTexture, donkeyPosition.x, donkeyPosition.y, &(currentAnim->GetCurrentFrame()));
			App->render->Blit(bgTexture, 108, 27, &(currentAnimHeart->GetCurrentFrame()));
		}
		App->render->DrawQuad(black, 0, 0, 0, 255, 1);
	}
	else if (frameCount > 240)
	{
		App->render->Blit(monkeyTexture, 0, 0, &monkeyScreen);
	}
	++frameCount;
	return update_status::UPDATE_CONTINUE;
}

bool Level3Win::CleanUp()
{
	//App->audio->FreeAll();
	App->collisions->Disable();
	App->player->Disable();

	activeTextures = activeColliders = activeFonts = activeFx = 0;

	// TODO 1: Remove ALL remaining resources. Update resource count properly

	App->textures->Unload(bgTexture);
	--totalTextures;
	App->textures->Unload(bgTextureScene);
	--totalTextures;
	App->textures->Unload(monkeyTexture);
	--totalTextures;

	App->audio->UnloadFx(FX_DK_Defeated);
	--totalFx;
	App->audio->UnloadFx(FX_DK_BrokenHeart);
	--totalFx;
	App->audio->UnloadFx(FX_Monkey);
	--totalFx;

	return true;
}