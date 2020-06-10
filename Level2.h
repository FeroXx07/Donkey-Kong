#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
struct SDL_Texture;

class ModuleScene2 : public Module
{
public:
	//Constructor
	ModuleScene2(bool startEnabled);

	//Destructor
	~ModuleScene2();

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

	// Level 2 Sprite
	SDL_Rect level_2;

	// Left Elevator Collider
	Collider *elevator[6];

	SDL_Rect elevatorSprite;
	SDL_Rect elevatorComplementSpriteUP;
	SDL_Rect elevatorComplementSpriteDOWN;


	// Sound Effect of Winning
	int FX_Win = 0;
	int FX_Lose = 0;

	// Sound Effect of Enemy Jumper
	int FX_Jumps = 0;
	int FX_Fall = 0;

	// Counter to reset lever after dying
	int resetCounter = 0;

	// The path that will define the position in the world
	Animation* currentAnimJumper = nullptr;
	Path pathJumper;

	Animation jumperAnim;
	iPoint jumperPosition, spawnPosition;
	Collider* jumperCollider;

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
