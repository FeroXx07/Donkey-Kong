#include "ModuleHud.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleFonts.h"
#include <stdio.h>
ModuleHud::ModuleHud(bool startEnabled) : Module(startEnabled)
{

}


// Destructor
ModuleHud::~ModuleHud()
{
	this->CleanUp();
}


bool ModuleHud::Start()
{
	LOG("Loading hud");

	bool ret = true;

	char lookupTable[] = { "0123456789" };
	whiteFont = App->fonts->Load("Assets/Fonts/Fonts_WHITE.png", lookupTable, 1);
	return ret;
}

update_status ModuleHud::Update()
{

	
	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleHud::PostUpdate()
{
	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(0, 0, whiteFont, scoreText);

	App->fonts->BlitText(100, 100, whiteFont, "1");
	++score;
	return update_status::UPDATE_CONTINUE;
}


bool ModuleHud::CleanUp()
{
	return true;
}