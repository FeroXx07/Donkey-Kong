#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
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

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	spaceCounter = 0;
	return ret;
}

update_status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		++spaceCounter;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && spaceCounter == 2)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	if (spaceCounter == 0) App->render->Blit(bgTexture, 0, 0, &introScreen);

	if (spaceCounter == 1) App->render->Blit(bgTexture, 0, 0, &monkeyScreen);


	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->textures->Unload(bgTexture);

	return true;
}