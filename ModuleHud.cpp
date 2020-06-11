#include "ModuleHud.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
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
	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%6d", score);
	sprintf_s(highScoreText, 10, "%6d", highscore);
	sprintf_s(loopScore, 10, "%2d", loop);
	
	if (lives == 3)
	{
		for (int i = 0; i < 3; ++i)
		{
			livesText[i] = ',';
		}
		livesText[3] = '\0';
	}
	else if (lives == 2)
	{
		for (int i = 0; i < 2; ++i)
		{
			livesText[i] = ',';
		}
		for (int i = 2; i <= 3; ++i)
		{
			livesText[i] = '\0';
		}
	}
	else if (lives == 1)
	{
		for (int i = 0; i < 1; ++i)
		{
			livesText[i] = ',';
		}
		for (int i = 1; i <= 3; ++i)
		{
			livesText[i] = '\0';
		}
	}
	else
	{
		for (int i = 1; i <= 3; ++i)
		{
			livesText[i] = '\0';
		}
	}
	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleHud::PostUpdate()
{
	// TODO 3: Blit the text of the score in at the bottom of the screen
	if (drawScore)
	{
		App->fonts->BlitText(8, 8, whiteFont, scoreText);

		App->fonts->BlitText(88, 8, whiteFont, highScoreText);

		App->fonts->BlitText(8, 24, lightBlueFont, livesText);

		App->fonts->BlitText(184, 24, darkBlueFont, loopScore);

		if (App->player->destroyed && App->hud->lives == 0 && App->intro->IsEnabled() == false)
		{
			App->fonts->BlitText(78, 185, lightBlueFont, "GAME");
			App->fonts->BlitText(120, 185, lightBlueFont, "OVER");
		}
	}


	return update_status::UPDATE_CONTINUE;
}


bool ModuleHud::CleanUp()
{
	return true;
}
