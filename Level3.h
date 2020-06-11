#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
struct SDL_Texture;

class ModuleScene3 : public Module
{
public:
	//Constructor
	ModuleScene3(bool startEnabled);

	//Destructor
	~ModuleScene3();

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
	SDL_Texture* dKTexture = nullptr;

	// Level 2 Sprite
	SDL_Rect level_3;

	// Left Elevator Collider
	SDL_Rect elevatorLadderSprite;
	Collider* elevatingLadder[2];

	Animation conveyorBeltLeft;
	Animation conveyorBeltRight;
	Path conveyorPathLeft;
	Path conveyorPathRight;

	Animation oilBarrelAnim;


	// Sound Effect of Winning
	int FX_Win = 0;
	int FX_Lose = 0;

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

	// Princess animations
	Animation prAnimRightIdle;
	Animation prAnimRight;
	Animation* currentAnimPrincess;
	Path princessPathRight;

	// Help sign
	SDL_Rect helpRight;
	int helpCounter = 0;
};
