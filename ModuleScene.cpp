#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

ModuleScene::ModuleScene()
{
	//Level 2 scene sprite
	level_2.x = 472;
	level_2.y = 176;
	level_2.w = SCREEN_WIDTH;
	level_2.h = SCREEN_HEIGHT;


	//Level 4 scene sprite
	level_4.x = 472;
	level_4.y = 160;
	level_4.w = SCREEN_WIDTH;
	level_4.h = SCREEN_HEIGHT;
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
	bgTexture = App->textures->Load("Assets/Background2.png");
	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);


	// Level 2 colliders:
	/*
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
	App->collisions->AddCollider({ 96, 144, 32, 24 }, Collider::Type::WALL);*/

	// Level 4 colliders:
	App->collisions->AddCollider({ 0, 248, 224, 8 }, Collider::Type::GROUND); // Base

	App->collisions->AddCollider({ 7, 208, 1, 8 }, Collider::Type::GROUND); // Floor 1
	// LEFT LADDER
	App->collisions->AddCollider({ 17, 208, 39, 8 }, Collider::Type::GROUND); // Floor 1
	App->collisions->AddCollider({ 64, 208, 48-2-7, 8}, Collider::Type::GROUND); // Floor 1 
	// MID LADDER
	App->collisions->AddCollider({ 64+49, 208, 48-1, 8 }, Collider::Type::GROUND); // Floor 1
	App->collisions->AddCollider({ 168, 208, 39, 8 }, Collider::Type::GROUND); // Floor 1
	// RIGHT LADDER
	App->collisions->AddCollider({ 217, 208, 1, 8 }, Collider::Type::GROUND); // Floor 1

	App->collisions->AddCollider({ 15, 168, 1, 8 }, Collider::Type::GROUND); // Floor 2
	// LEFT LADDER
	App->collisions->AddCollider({ 25, 168, 31, 8 }, Collider::Type::GROUND); // Floor 2
	App->collisions->AddCollider({ 64, 168, 7, 8 }, Collider::Type::GROUND); // Floor 2
	// MID LADDER
	App->collisions->AddCollider({ 81, 168, 62, 8 }, Collider::Type::GROUND); // Floor 2
	// MID LADDER
	App->collisions->AddCollider({ 153, 168, 7, 8 }, Collider::Type::GROUND); // Floor 2
	App->collisions->AddCollider({ 168, 168, 31, 8 }, Collider::Type::GROUND); // Floor 2
	// RIGHT LADDER
	App->collisions->AddCollider({ 209, 168, 1, 8 }, Collider::Type::GROUND); // Floor 2

	App->collisions->AddCollider({ 23, 128, 1, 8 }, Collider::Type::GROUND); // Floor 3
	// LEFT LADDER
	App->collisions->AddCollider({ 33, 128, 23, 8  }, Collider::Type::GROUND); // Floor 3
	App->collisions->AddCollider({ 64, 128, 39, 8 }, Collider::Type::GROUND); // Floor 3
	// MID LADDER
	App->collisions->AddCollider({ 113, 128, 47, 8  }, Collider::Type::GROUND); // Floor 3
	App->collisions->AddCollider({ 168, 128, 23, 8 }, Collider::Type::GROUND); // Floor 3
	// RIGHT LADDER
	App->collisions->AddCollider({ 201, 128, 1, 8 }, Collider::Type::GROUND); // Floor 3

	App->collisions->AddCollider({ 31, 88, 1, 8 }, Collider::Type::GROUND); // Floor 4
	// LEFT LADDER
	App->collisions->AddCollider({ 41, 88, 15, 8  }, Collider::Type::GROUND); // Floor 4
	App->collisions->AddCollider({ 63, 88, 1, 8 }, Collider::Type::GROUND); // Floor 4
	//MID LADDER
	App->collisions->AddCollider({ 73, 88, 78, 8  }, Collider::Type::GROUND); // Floor 4
	//MID LADDER
	App->collisions->AddCollider({ 160, 88, 1, 8 }, Collider::Type::GROUND); // Floor 4
	App->collisions->AddCollider({ 168, 88, 15, 8  }, Collider::Type::GROUND); // Floor 4
	// RIGHT LADDER
	App->collisions->AddCollider({ 193, 88, 1, 8 }, Collider::Type::GROUND); // Floor 4

	App->collisions->AddCollider({ 8+3, 216-7, 8-6, 32 + 7 }, Collider::Type::LADDER); // Base
	App->collisions->AddCollider({ 104+3, 216-6, 8-6, 32 + 6 }, Collider::Type::LADDER); // Base
	App->collisions->AddCollider({ 208+3, 216-7, 8-6, 32 + 7 }, Collider::Type::LADDER); // Base

	App->collisions->AddCollider({ 16 + 3, 176, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 1
	App->collisions->AddCollider({ 72 + 3, 176, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 1
	App->collisions->AddCollider({ 144 + 3, 176, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 1
	App->collisions->AddCollider({ 200 + 3, 176, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 1

	App->collisions->AddCollider({ 24 + 3, 136, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 2
	App->collisions->AddCollider({ 104 + 3, 136, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 2
	App->collisions->AddCollider({ 192 + 3, 136, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 2

	App->collisions->AddCollider({ 32 + 3, 96, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 3
	App->collisions->AddCollider({ 64 + 3, 96, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 3
	App->collisions->AddCollider({ 152 + 3, 96, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 3
	App->collisions->AddCollider({ 184 + 3, 96, 8 - 6, 32 }, Collider::Type::LADDER); // Floor 3



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
	//App->render->Blit(bgTexture, 0, 0, &level_2);
	App->render->Blit(bgTexture, 0, 0, &level_4);

	return update_status::UPDATE_CONTINUE;
}