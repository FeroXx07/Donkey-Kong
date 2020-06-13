#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_FireMinion.h"
#include "Item_Nut.h"
#include "Item_Iron.h"
#include "Item_Umbrella.h"
#include "Item_Bag.h"
#include "Item_Hammer.h"
#include "Enemy_Minecart.h"


#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/Background2.png");
	++activeTextures;  ++totalTextures;
	enemyDestroyedFx = App->audio->LoadFx("Assets/Music/SFX_Kill.wav");
	++activeFx; ++totalFx;
	itemPickedFx = App->audio->LoadFx("Assets/Music/SFX_Bonus.wav");
	++activeFx; ++totalFx;

	return true;
}


update_status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	App->audio->UnloadFx(enemyDestroyedFx);
	--totalFx;
	App->audio->UnloadFx(itemPickedFx);
	--totalFx;
	App->textures->Unload(texture);
	--totalTextures;

	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			SpawnEnemy(spawnQueue[i]);
			spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::ENEMY_FIREMINION:
				{
					enemies[i] = new Enemy_FireMinion(info.x, info.y);
					enemies[i]->destroyedFx = enemyDestroyedFx;
					break;
				}
				case Enemy_Type::ITEM_NUT:
				{
					enemies[i] = new Item_Nut(info.x, info.y);
					enemies[i]->texture = texture;
					enemies[i]->destroyedFx = itemPickedFx;;
					break;
				}
				case Enemy_Type::ITEM_IRON:
				{
					enemies[i] = new Item_Iron(info.x, info.y);
					enemies[i]->texture = texture;
					enemies[i]->destroyedFx = itemPickedFx;
					break;
				}
				case Enemy_Type::ITEM_UMBRELLA:
				{
					enemies[i] = new Item_Umbrella(info.x, info.y);
					enemies[i]->texture = texture;
					enemies[i]->destroyedFx = itemPickedFx;
					break;
				}

				case Enemy_Type::ITEM_BAG:
				{
					enemies[i] = new Item_Bag(info.x, info.y);
					enemies[i]->texture = texture;
					enemies[i]->destroyedFx = itemPickedFx;
					break;
				}
				case Enemy_Type::ITEM_HAMMER:
				{
					enemies[i] = new Item_Hammer(info.x, info.y);
					enemies[i]->texture = texture;
					enemies[i]->destroyedFx = itemPickedFx;
					break;
				}
				case Enemy_Type::ENEMY_MINECART:
				{
					enemies[i] = new Enemy_Minecart(info.x, info.y);
					enemies[i]->texture = texture;
					enemies[i]->destroyedFx = itemPickedFx;
					break;
				}
			}
			enemies[i]->texture = texture;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
}