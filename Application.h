#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 21

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModuleScene;
class ModuleScene2;
class ModuleCollisions;
class ModuleRender;
class ModuleHammer;
class ModuleEnemies;
class ModuleFadeToBlack;
class SceneIntro;
class Level4Win;
class ModuleParticles;
class ModuleFonts;
class ModuleHud;
class ModuleDebugInfo;
class ModuleScene3;
class Level2Win;
class Level3Win;


class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;
	ModuleHammer* hammer = nullptr;
	Level4Win* level4win = nullptr;
	ModuleScene* level4 = nullptr;
	ModuleScene2* level2 = nullptr;
	Level2Win* level2win = nullptr;
	ModuleScene3* level3 = nullptr;
	Level3Win* level3win = nullptr;
	SceneIntro* intro = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleRender* render = nullptr;
	ModuleFonts* fonts = nullptr;
	ModuleHud* hud = nullptr;
	ModuleDebugInfo* debugInfo = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__