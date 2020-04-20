#include "Level4.h"

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

#include "Game/SDL_mixer/include/SDL_mixer.h"
#include "Game/SDL/include/SDL_scancode.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{
	// Level 4 scene sprite
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
	// Scene sprites
	bgTexture = App->textures->Load("Assets/Background2.png");
	bgTextureTransparent = App->textures->Load("Assets/Background2Transparent.png");
	level_4BGM = App->audio->PlayMusic("Assets/Music/Stage4BGM.ogg");
	FX_Win = App->audio->LoadFx("Assets/Music/Stage_Clear_2.wav");
	App->collisions->Enable();
	App->player->Enable();
	App->hammer->Enable();
	App->enemies->Enable();

	Nuts = 8;
	frameCount = 0;

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
	
	// Wall collisions
	App->collisions->AddCollider({ 0, 177, 4, 31 }, Collider::Type::WALL); // Floor 1 Left
	App->collisions->AddCollider({ 220, 177, 4, 31 }, Collider::Type::WALL); // Floor 1 Right
	App->collisions->AddCollider({ 0, 137, 12, 31 }, Collider::Type::WALL); // Floor 2 Left
	App->collisions->AddCollider({ 212, 137, 12, 31 }, Collider::Type::WALL); // Floor 2 Right
	App->collisions->AddCollider({ 0, 97, 20, 32 }, Collider::Type::WALL); // Floor 3 Left
	App->collisions->AddCollider({ 204, 97, 20, 32 }, Collider::Type::WALL); // Floor 3 Right
	App->collisions->AddCollider({ 0, 60, 28, 28 }, Collider::Type::WALL); // Floor 4 Left
	App->collisions->AddCollider({ 196, 60, 28, 28 }, Collider::Type::WALL); // Floor 4 Right

	// Adding enemy
	App->enemies->AddEnemy(Enemy_Type::ENEMY_FIREMINION, 162, 248 - 12);
	App->enemies->AddEnemy(Enemy_Type::ITEM_NUT, 56, 207);
	App->enemies->AddEnemy(Enemy_Type::ITEM_NUT, 160, 207);
	App->enemies->AddEnemy(Enemy_Type::ITEM_NUT, 56, 167);
	App->enemies->AddEnemy(Enemy_Type::ITEM_NUT, 160, 167);
	App->enemies->AddEnemy(Enemy_Type::ITEM_NUT, 56, 127);
	App->enemies->AddEnemy(Enemy_Type::ITEM_NUT, 160, 127);
	App->enemies->AddEnemy(Enemy_Type::ITEM_NUT, 56, 87);
	App->enemies->AddEnemy(Enemy_Type::ITEM_NUT, 160, 87);
	return ret;
}

update_status ModuleScene::Update()
{
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN )
	{
		Nuts = 0;
	}

	if (Nuts == 0)
	{
		
		App->audio->PlayFx(FX_Win);
		App->fade->FadeToBlack(this, (Module*)App->sceneWin, 10);
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &level_4);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	// TODO 2: Enable (and properly disable) the player module
	App->enemies->Disable();
	App->textures->Unload(bgTexture);
	App->textures->Unload(bgTextureTransparent);
	// TODO 5: Remove All Memory Leaks - no solution here guys ;)
	return true;
}