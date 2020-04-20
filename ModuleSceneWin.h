#include "Module.h"
#include "Animation.h"
#include "Path.h"


struct SDL_Texture;

class ModuleSceneWin : public Module
{
public:
	//Constructor
	ModuleSceneWin(bool startEnabled);

	//Destructor
	~ModuleSceneWin();

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
	
	// The path that will define the position in the world
	Animation* currentAnim = nullptr;
	Path path;

	// The three stages of this scene
	SDL_Rect normalScene, fallingScene, celebrationScene;
	SDL_Rect princessSprite, marioSprite, heartSprite;
	// Enemy animations
	iPoint spawnPosition,donkeyPosition;

	// The three animations of donkey
	Animation angryAnim, fallAnim, hurtAnim;

	int frameCount = 0;

	// Sound efects pointers
	int FX_DK_Defeated = 0;
	int FX_DK_Falling = 0;
	int FX_DK_Stomp = 0;
	int FX_WinMusic = 0;
	
	int spaceCounter = 0;
};

