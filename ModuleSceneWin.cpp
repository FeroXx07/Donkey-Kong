#include "ModuleSceneWin.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Game/SDL/include/SDL_scancode.h"

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

	angry.PushBack({ 8,588,40,32 });
	angry.PushBack({ 56,588,46,32 });
	angry.PushBack({ 110,588,46,32 });
	angry.speed = 0.1f;
	path.PushBack({ 0.0f,0.0f }, 180, &angry);
}

ModuleSceneWin::~ModuleSceneWin()
{

}

// Load assets
bool ModuleSceneWin::Start()
{
	LOG("Loading background assets of the WinScene");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/WinTexture.png");

	spawnPosition.x = 105;
	spawnPosition.y = 716 - 32;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	spaceCounter = 0;
	return ret;
}

update_status ModuleSceneWin::Update()
{
	LOG("Updating background assets of the WinScene");
	path.Update();
	donkeyPosition = spawnPosition + path.GetRelativePosition();
	//currentAnim = path.GetCurrentAnimation();
	LOG("Updated background assets of the WinScene");
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleSceneWin::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, &fallingScene);
	App->render->Blit(bgTexture, donkeyPosition.x, donkeyPosition.y, &(path.GetCurrentAnimation()->GetCurrentFrame()));
	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneWin::CleanUp()
{
	App->textures->Unload(bgTexture);

	return true;
}