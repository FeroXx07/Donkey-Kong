#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene(bool startEnabled);

	//Destructor
	~ModuleScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	bool CleanUp();
public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	// The scene background music
	int level_4BGM = 0;

	// Counter to know how many nuts are left
	int Nuts = 0;

	// Level Sprite
	SDL_Rect level_4;

	// Sound Effect of Winning
	int FX_Win = 0;
	int FX_Lose = 0;

	int frameCount = 0;

	// Counter to reset lever after dying
	int resetCounter = 0;


	// Donkey 
	Path donkeyPath;
	Collider* donkeyCollider;

	// Donkey FX
	int FX_Stomp = 0;
	int donkeyCounterFX = 0;
	// Enemy animations
	Animation dkAnimIdle, dkRightHand, dkLeftHand;
	Animation* currentAnimDonkey;
};

#endif