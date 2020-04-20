#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

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
	SDL_Texture* bgTextureTransparent = nullptr;

	// The scene background music
	int level_4BGM = 0;

	// Counter to know how many nuts are left
	int Nuts = 0;
	// Level Sprite
	SDL_Rect level_4;

	// Sound Effect of Winning
	int FX_Win = 0;
	int frameCount = 0;
	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;
};

#endif