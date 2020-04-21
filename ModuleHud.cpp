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

	char lookupTableNumbers[] = { "0123456789" };
	char lookupTableTextAndLives[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ.-," }; // "," is LIVES SPRITE!!!!!!!!!
	whiteFont = App->fonts->Load("Assets/Fonts/Fonts_WHITE.png", lookupTableNumbers, 1);
	lightBlueFont = App->fonts->Load("Assets/Fonts/Fonts_LIGHTBLUE.png", lookupTableTextAndLives, 1);
	darkBlueFont = App->fonts->Load("Assets/Fonts/Fonts_DARKBLUE.png", lookupTableNumbers, 1);
	return ret;
}

update_status ModuleHud::Update()
{

	
	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleHud::PostUpdate()
{
	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%6d", score);
	sprintf_s(highScoreText, 10, "%6d", highscore);
	sprintf_s(loopScore, 10, "%6d", loop);
	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(8	, 8, whiteFont, scoreText);

	App->fonts->BlitText(88, 8, whiteFont, highScoreText);

	App->fonts->BlitText(8, 24, lightBlueFont, livesText);

	App->fonts->BlitText(184, 24, darkBlueFont, livesText);

	return update_status::UPDATE_CONTINUE;
}


bool ModuleHud::CleanUp()
{
	return true;
}