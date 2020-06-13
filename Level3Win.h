#include "Module.h"
#include "Animation.h"
#include "Path.h"
struct SDL_Texture;

class Level3Win : public Module
{
public:
	//Constructor
	Level3Win(bool startEnabled);

	//Destructor
	~Level3Win();

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
	SDL_Texture* bgTextureScene = nullptr;
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* monkeyTexture = nullptr;

	SDL_Rect level3win;

	// The path that will define the position in the world
	Animation* currentAnim = nullptr;
	Path donkeyPath;
	Path heart;

	// The three stages of this scene
	SDL_Rect princessSprite, marioSprite;
	Animation heartSprite, brokenHeartSprite;
	Animation* currentAnimHeart = nullptr;

	SDL_Rect black = { 0,0,SCREEN_WIDTH,24 };
	SDL_Rect monkeyScreen;

	// Enemy animations
	iPoint spawnPosition, donkeyPosition;

	// Donkey Animations
	Animation idleDonkey, climbDonkey, climbPrincessDonkey;

	int frameCount = 0;

	// Sound efects pointers
	int FX_DK_Defeated = 0;
	int FX_DK_BrokenHeart = 0;
	int FX_Monkey = 0;
	int spaceCounter = 0;
};