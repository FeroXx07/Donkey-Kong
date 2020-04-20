#include "Module.h"
#include "Animation.h"
#include "p2Point.h"


struct SDL_Texture;
struct Collider;

class ModuleHammer : public Module
{
public:
	// Constructor
	ModuleHammer(bool startEnabled);

	// Destructor
	~ModuleHammer();

	// Called when the module is activated
	// Loads the necessary textures for the hammer
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles hammer movement
	update_status Update() override;

	// Called at the end of the application loop
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp();

public:
	// Position of the hammer in the map
	iPoint hammerPosition;

	int temp = 0;

	// A flag to detect when the hammer has been destroyed
	bool hammerExist = true;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// Player's collider
	Collider* hammerCollider = nullptr;

	int FX_Hammer = 0;
	int frameCountHammer = 0;

};