#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"


struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp();

public:
	// Position of the player in the map
	iPoint position;
	
	bool isHurting;

	int score;
	int highscore;

	// The speed in which we move the player (pixels per frame)
	iPoint speed = { 1,1 };
	iPoint hammerTemp = { 0,0 };
	int temp = 0;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// Player's collider
	Collider* playerCollider = nullptr;

	// A set of animations
	Animation leftIdleAnim;
	Animation rightIdleAnim;
	Animation hammerLeftIdleAnim;
	Animation hammerRightIdleAnim;

	Animation leftAnim;
	Animation rightAnim;
	Animation jumpAnim;

	Animation hammerLeftAnim;
	Animation hammerRightAnim;

	Animation climbingAnim;
	Animation climbedAnim;
	Animation idleClimbedAnim;
	Animation climbingIdle;

	Animation sprite1Climbed;
	Animation sprite2Climbed;
	

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// A flag to detect when the player is in the ladder
	bool isLadder = false;
	bool isGround = true;
	bool isJumping = false;
	bool isGod = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

	// The scene fx sounds
	int FX_Walking = 0;

	int frameCountWalking = 0;
	bool walkingFX = false;

	int conveyorCounter = 0;
	bool conveyorSenseLeft = true;
};

#endif //!__MODULE_PLAYER_H__