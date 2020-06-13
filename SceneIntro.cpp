#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleHud.h"
#include "Game/SDL/include/SDL_scancode.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	monkeyScreen = { 8,352,224,256 };
	introScreen = { 8,88,224,256 };
	
	bool ret = true;

	bgTexture = App->textures->Load("Assets/Hud2.png");
	++activeTextures; ++totalTextures;

	precoin = App->textures->Load("Assets/Precoin.png");
	++activeTextures; ++totalTextures;

	names = App->textures->Load("Assets/Names.png");
	++activeTextures; ++totalTextures;


	FX_Monkey = App->audio->LoadFx("Assets/Music/SFX_MonkeyHeight.wav");
	++activeFx; ++totalFx;

	FX_InsertCoin = App->audio->LoadFx("Assets/Music/SFX_InsertCoin.wav");
	++activeFx; ++totalFx;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	spaceCounter = 0;

	App->audio->PlayFx(FX_InsertCoin);

	App->hud->drawScore = false;
	return ret;
}

update_status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		++spaceCounter;
		if (spaceCounter == 2) App->audio->PlayFx(FX_Monkey);
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && spaceCounter == 4)
	{
		App->fade->FadeToBlack(this, (Module*)App->level3);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	if (spaceCounter == 0) App->render->Blit(names, 0, 0);

	if (spaceCounter == 1) App->render->Blit(precoin, 0, 0);

	if (spaceCounter == 2) App->render->Blit(bgTexture, 0, 0, &introScreen);

	if (spaceCounter == 3) App->render->Blit(bgTexture, 0, 0, &monkeyScreen);
	

	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	App->textures->Unload(bgTexture);
	--totalTextures;
	App->textures->Unload(precoin);
	--totalTextures;
	App->textures->Unload(names);
	--totalTextures;

	App->audio->UnloadFx(FX_Monkey);
	--totalFx;
	App->audio->UnloadFx(FX_InsertCoin);
	--totalFx;

	return true;
}