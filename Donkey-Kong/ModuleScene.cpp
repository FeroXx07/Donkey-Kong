#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"


ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	bgRect.x = 8;
	bgRect.y = 176;
	bgRect.w = 224;
	bgRect.h = 256;
	bgTexture = App->textures->Load("Assets/Background.png");
	//App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);



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
	App->render->Blit(bgTexture, 0, 0, &bgRect);

	return update_status::UPDATE_CONTINUE;
}