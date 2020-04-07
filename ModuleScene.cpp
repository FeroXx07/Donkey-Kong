#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

ModuleScene::ModuleScene()
{
	//Level 2 scene
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
	//Scene sprites
	bgTexture = App->textures->Load("Assets/Background.png");
	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	//Add colliders for the ground
	App->collisions->AddCollider({ 0, 248, 224, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 8, 208, 208, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 8, 168, 40, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 64, 168, 88, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 168, 168, 48, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 0, 128, 96, 8 }, Collider::Type::GROUND);
	App->collisions->AddCollider({ 128, 128, 96, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 8, 88, 208, 8 }, Collider::Type::GROUND);

	App->collisions->AddCollider({ 88, 56, 48, 8 }, Collider::Type::GROUND);

	//Add collider for the wall
	App->collisions->AddCollider({ 96, 144, 32, 24 }, Collider::Type::WALL);

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