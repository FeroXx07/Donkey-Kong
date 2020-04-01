#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
//#include "ModuleCollisions.h"

ModuleScene::ModuleScene()
{
	level_2.x = 472;
	level_2.y = 176;
	level_2.w = SCREEN_WIDTH;
	level_2.h = SCREEN_HEIGHT;
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/BackgroundTRANSPERENT.png");
	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);


	return ret;
}

update_status ModuleScene::Update()
{
	

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &level_2);

	return update_status::UPDATE_CONTINUE;
}