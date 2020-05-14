#include "Globals.h"
#include "Module.h"

#include "p2Point.h"
class ModuleHud: public Module
{
public:

	ModuleHud(bool startEnabled);
	~ModuleHud();
	//By now we will consider all modules to be permanently active
	bool Start();

	//Called at the middle of each application loop
	update_status Update();

	//Called at the end of each application loop
	update_status PostUpdate();

	//Called at the end of the application
	bool CleanUp();

public:
	uint score = 0;
	uint highscore = 0;
	uint loop = 0;
	uint lives = 3;
	int whiteFont = -1;
	int lightBlueFont = -1;
	int darkBlueFont = -1;

	char scoreText[10] = { "\0" };
	char highScoreText[10] = { "\0" };
	char loopScore[10] = { "\0" };
	char livesText[4] = { ",,,"};

	bool drawScore = false;
};