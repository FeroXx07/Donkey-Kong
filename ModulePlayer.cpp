#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleHammer.h"
#include "Level4.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleHud.h"

#include <stdio.h>
#include "Game/SDL/include/SDL_scancode.h"

//Previously was this
//#define JUMPSPEED 50.0f
//const float gravity = 60.0f + 50.0f

//Now temporally is this
#define JUMPSPEED 50.0f
const float gravity = 60.0f + 50.0f;         // pixels / second^2
const float deltaTime = 1.0f / 25.0f; // More or less 60 frames per second



ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	//name = "player";

	climbingIdle.PushBack({ 138, 24, 13, 16 });
	climbingIdle.loop = true;
	climbingIdle.speed = 0.1f;

	// left idle animation
	leftIdleAnim.PushBack({ 66, 24, 12, 16 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = 0.1f;

	// right idle animation
	rightIdleAnim.PushBack({ 66, 41, 12, 16 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = 0.1f;

	hammerLeftIdleAnim.PushBack({ 519,24,31,16 });
	hammerLeftIdleAnim.PushBack({ 498,14,12,26 });
	hammerLeftIdleAnim.loop = true;
	hammerLeftIdleAnim.speed = 0.1f;

	hammerRightIdleAnim.PushBack({ 520 ,55,30,16 });
	hammerRightIdleAnim.PushBack({ 498 ,45 - 1,12 + 1,26 });
	hammerRightIdleAnim.loop = true;
	hammerRightIdleAnim.speed = 0.1f;


	leftAnim.PushBack({ 89, 24, 15, 16 }); // movement left 1
	leftAnim.PushBack({ 66, 24, 12, 16 }); // idle left
	leftAnim.PushBack({ 113, 24, 15, 15 }); // movement left 2
	leftAnim.PushBack({ 66, 24, 12, 16 }); // idle left
	leftAnim.loop = true;
	leftAnim.speed = 0.3f;

	rightAnim.PushBack({ 113, 41, 15, 15 });
	rightAnim.PushBack({ 66, 41, 12, 16 });
	rightAnim.PushBack({ 89, 41, 15, 16 });
	rightAnim.PushBack({ 66, 41, 12, 16 });
	rightAnim.loop = true;
	rightAnim.speed = 0.3f;

	hammerLeftAnim.PushBack({ 648, 25, 32, 15 }); // % 2 == 0, 0 is hammer down
	hammerLeftAnim.PushBack({ 625, 14,15,26 }); // % 2 == 1, 1 is hammer up
	hammerLeftAnim.PushBack({ 584,24,31,16 }); // % 2 == 0
	hammerLeftAnim.PushBack({ 562,14,13,26 }); // % 2 == 1
	hammerLeftAnim.PushBack({ 520,24,31,16 }); // % 2 == 0
	hammerLeftAnim.PushBack({ 498,14,12,26 }); // % 2 == 1
	hammerLeftAnim.loop = true;
	hammerLeftAnim.speed = 0.1f;

	hammerRightAnim.PushBack({ 648 - 3 + 2,56,32 + 3 + 2,15 });
	hammerRightAnim.PushBack({ 625 + 2,45,15 + 2,26 });
	hammerRightAnim.PushBack({ 584 - 5 + 2,55,31 + 5 + 2,16 });
	hammerRightAnim.PushBack({ 562 - 3 + 2,45,13 + 3 + 2,26 });
	hammerRightAnim.PushBack({ 520 - 6 + 2,55,30 + 6 + 2,16 });
	hammerRightAnim.PushBack({ 498 - 3 + 2,45,12 + 3 + 2,26 });
	hammerRightAnim.loop = true;
	hammerRightAnim.speed = 0.1f;


	jumpAnim.PushBack({ 113, 24, 15, 15 });
	jumpAnim.loop = true;
	jumpAnim.speed = 0.1f;

	climbingAnim.PushBack({ 138, 24, 13, 16 }); // climb movement 1
	climbingAnim.PushBack({ 138, 40, 13, 16 }); // climb movement 2
	climbingAnim.loop = true;
	climbingAnim.speed = 0.1f;


	climbedAnim.PushBack({ 161, 25, 14, 15 }); // when already up 1
	climbedAnim.PushBack({ 184, 27, 16, 12 }); // when already up 2
	climbedAnim.loop = false;
	climbingAnim.speed = 0.1f;

	sprite1Climbed.PushBack({ 184, 27 - 3, 16, 12 + 3 });
	sprite1Climbed.loop = false;
	sprite1Climbed.speed = 0.1f;

	sprite2Climbed.PushBack({ 161, 25 - 3, 14, 15 + 3 });
	sprite2Climbed.loop = false;
	sprite2Climbed.speed = 0.1f;


	idleClimbedAnim.PushBack({ 208, 25, 16, 15 }); // idle up
	idleClimbedAnim.loop = false;
	idleClimbedAnim.speed = 0.1f;
	

	
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Background3.png"); // arcade version
	++activeTextures; ++totalTextures;

	//Starting position of the Mario
	position.x = 0;
	position.y = 232;

	playerCollider = App->collisions->AddCollider({position.x,position.y,12,16}, Collider::Type::PLAYER, App->player);
	++activeColliders; ++totalColliders;

	currentAnimation = &rightIdleAnim; 

	FX_Walking = App->audio->LoadFx("Assets/Music/SFX_Walking.wav");
	++activeFx; ++totalFx;

	frameCountWalking = 0;
	conveyorCounter = 0;

	return ret;
}

update_status ModulePlayer::Update()
{
	GamePad& pad = App->input->pads[0];

	if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || pad.l_x) && (isGround == true || isJumping == true))
	{
		position.x -= speed.x;

		if (walkingFX == false) walkingFX = App->audio->PlayFx(FX_Walking);
		if (frameCountWalking == 11) 
		{
			walkingFX = false;
			frameCountWalking = 0;
		}
		++frameCountWalking;

		if (App->hammer->hammerExist)
		{
			App->hammer->hammerPosition -= speed;
		}
		
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			if (App->hammer->hammerExist)
			{
				currentAnimation = &hammerLeftAnim;
			}
			else
			{
				currentAnimation = &leftAnim;
			}
		}
	}

	if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || (pad.l_x > 0.0f)) && (isGround == true || isJumping == true))
	{
		position.x += speed.x;

		if (walkingFX == false) walkingFX = App->audio->PlayFx(FX_Walking);
		if (frameCountWalking == 11) 
		{
			walkingFX = false;
			frameCountWalking = 0;
		}
		++frameCountWalking;

		if (App->hammer->hammerExist) App->hammer->hammerPosition += speed;

		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			if (App->hammer->hammerExist == true)
			{
				currentAnimation = &hammerRightAnim;
			}
			else
			{
				currentAnimation = &rightAnim;
			}
		}
	}

	if (isLadder == true)
	{
		isGround = false;
		if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || (pad.l_y < 0.0f)) && App->hammer->hammerExist == false)
		{
			if (walkingFX == false) walkingFX = App->audio->PlayFx(FX_Walking);
			if (frameCountWalking == 11)
			{
				walkingFX = false;
				frameCountWalking = 0;
			}
			++frameCountWalking;

			position.y -= speed.x;
		}
		if ((App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || (pad.l_y > 0.0f)) && App->hammer->hammerExist == false)
		{
			if (walkingFX == false) walkingFX = App->audio->PlayFx(FX_Walking);
			if (frameCountWalking == 11)
			{
				walkingFX = false;
				frameCountWalking = 0;
			}
			++frameCountWalking;

			position.y += speed.x;
		}
		playerCollider->rect.w = 2;
		temp = 5;
	}
	else
	{
		playerCollider->rect.w = 12;
		playerCollider->rect.h = 16;
		temp = 0;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		playerCollider->rect.h = 18;
		playerCollider->rect.w = 2+2+1;
		temp = 5-1;
	}

	if ((App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true) && isGround == true)
	{
		speed.y -= JUMPSPEED;
		if (currentAnimation != &jumpAnim)
		{
			currentAnimation = &jumpAnim;
		}
		isGround = false;
		isJumping = true;
	}

	// If last movement was left, set the current animation back to left idle
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_UP && App->hammer->hammerExist == false)
	{
		currentAnimation = &leftIdleAnim;
	}
	else if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_UP && App->hammer->hammerExist == true) {
		currentAnimation = &hammerLeftIdleAnim;
	}

	if ((App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_UP || App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_UP) && isLadder)
		currentAnimation = &climbingIdle;

	// If last movement was right, set the current animation back to left idle
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_UP && App->hammer->hammerExist == false)
		currentAnimation = &rightIdleAnim;
	else if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_UP && App->hammer->hammerExist == true)
		currentAnimation = &hammerRightIdleAnim;

	if (pad.enabled)
	{
		if (pad.l_x == 0.0f && pad.l_y == 0.0f)
			currentAnimation = &rightIdleAnim;
	}

	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN && App->hammer->hammerExist == true)
	{
		currentAnimation = &rightIdleAnim;
	}

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN )
	{
		isGod = !isGod;
	}

	//Gravity
	if (isLadder == false && destroyed == false)
	{ 
		
		position.y += speed.y * deltaTime;      // Apply vertical velocity to X position
		speed.y += gravity * deltaTime;

		//printf("Position is: %d\n", position.y);
		//printf("Speed is: %d\n\n", speedY);
	}

	App->hammer->hammerCollider->SetPos(App->hammer->hammerPosition.x, App->hammer->hammerPosition.y);
	playerCollider->SetPos(position.x +temp, position.y);

	currentAnimation->Update();

	//The camera limits for the player
	if (position.x < 0) position.x = 0;
	if (position.x > 211) position.x = 211;
	if (position.y < 0) position.y = 0;


	if (isLadder == true)
	{
		printf("LADDER TRUE\n\n");
	}
	else
		printf("LADDER FALSE\n\n");

	if (isGround == true)
	{
		printf("Ground TRUE\n\n");
	}
	else
		printf("Ground FALSE\n\n");

	printf("Position X: %d\n Position Y: %d\n\n", position.x, position.y);

	if (App->hud->lives == 0) {
		
		printf("GAMEOVER\n\n");
	}

	printf("Lives: %d\n\n", App->hud->lives);

	if (/*	isScoring  */1) { // isScoring is  a variable in which we put it true when we have to score, i.e. jumping over barrels, fires and enemies, grabbing items, killing enemies, etc.
		// TODO implement each type of scoring

	
		if (App->hud->score > App->hud->highscore) {
			App->hud->highscore = App->hud->score;
		}
		//isScoring = false;
	}

	
	if (conveyorCounter >= 600)
	{
		conveyorSenseLeft = !conveyorSenseLeft;
		conveyorCounter = 0;
	}
	++conveyorCounter;

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		//App->render->Blit(texture, position.x, position.y, &rect);
		if (App->hammer->hammerExist == true)
		{
			if (currentAnimation->GetCurrentFps() % 2 == 0) // Hammer down
			{
				if ((currentAnimation == &hammerLeftAnim) || (currentAnimation == &hammerLeftIdleAnim))
					hammerTemp.x = -18;
				if (currentAnimation == &hammerRightAnim)
					hammerTemp.x -= 4;

				App->render->Blit(texture, position.x + hammerTemp.x, position.y, &rect);
			}
			else // Hammer Up
			{
				hammerTemp.y = -11;
				if ((currentAnimation == &hammerLeftAnim) || (currentAnimation == &hammerLeftIdleAnim))
					hammerTemp.y += 1;

				App->render->Blit(texture, position.x, position.y + hammerTemp.y, &rect);
			}
		}
		else
			App->render->Blit(texture, position.x, position.y, &rect);

		hammerTemp = { 0,0 };
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (destroyed == false)
	{
		if (c2->type == Collider::Type::LADDER && isJumping==false)
		{
			if (position.x + 4 < c2->rect.x && position.x + 9 > c2->rect.x + 1) 
				isLadder = true;

			if (position.y < c2->rect.y + c2->rect.h - 16 && (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT))
				currentAnimation = &climbingAnim;


			if (position.y <= c2->rect.y - 15)
			{
				isLadder = false;
				currentAnimation = &idleClimbedAnim;
			}



			if (position.y <= c2->rect.y && position.y+14 >= c2->rect.y)
			{
				currentAnimation = &sprite1Climbed;
			}
			if (position.y <= c2->rect.y && position.y +5 >= c2->rect.y)
			{
				currentAnimation = &sprite2Climbed;
			}

			if (position.y + c1->rect.h >= c2->rect.y + c2->rect.h && !App->hammer->hammerExist)
			{
				currentAnimation = &idleClimbedAnim;
			}
			
		}
		else
			isLadder = false;

		if (c2->type == Collider::Type::GROUND)
		{
			isGround = true;
			isJumping = false;
			if (isLadder == true) 
			{

			}
			else if (isLadder == false)
			{
				//if (position.y + 16 > c2->rect.y ) // Collision to maintain the player to the ground
				//{ 
				//	position.y = c2->rect.y - 15;
				//	speed.y = 0;
				//}
				if (position.y + 15 >= c2->rect.y) // Collision to maintain the player to the ground
				{
					position.y = c2->rect.y - 15;
					speed.y = 0;
				}
				
			}
		}

		if (c2->type == Collider::Type::CONVEYORGROUND)
		{
			isGround = true;
			isJumping = false;
			if (isLadder == true)
			{
			}
			else if (isLadder == false)
			{
				if (position.y + 15 >= c2->rect.y) // Collision to maintain the player to the ground
				{
					position.y = c2->rect.y - 15;
					speed.y = 0;

					if (!(App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && (isGround == true || isJumping == true)))
					{
						if (conveyorSenseLeft)
							--position.x;
						else if (conveyorSenseLeft == false)
							++position.x;
					}

				}

			}
		}

		if (c2->type == Collider::Type::LOWERGROUND)
		{
			if (position.y <= c2->rect.y + c2->rect.h) // Collision to maintain the player to the ground
			{
				position.y = c2->rect.y + c2->rect.h;
			}
		}

		if (c2->type == Collider::Type::WALL)
		{
			if (position.x > c2->rect.x + c2->rect.w / 2)
			{
				position.x = c2->rect.x + c2->rect.w;
			}
			if (position.x < c2->rect.x + c2->rect.w / 2)
			{
				position.x = c2->rect.x - 13;
			}
		}
		

		if (c2->type == Collider::Type::ENEMY || c2->type == Collider::Type::FIREBARREL && isGod == false)
		{
			if (App->hud->lives > 0 && destroyed ==false) {
				--App->hud->lives;
				destroyed = true;
			}
		}
	}
}

bool ModulePlayer::CleanUp()
{
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	// TODO 1: Remove ALL remaining resources. Update resource count properly

	App->textures->Unload(texture);
	--totalTextures;

	App->audio->UnloadFx(FX_Walking);
	--totalFx;

	App->collisions->RemoveCollider(playerCollider);
	--totalColliders;

	App->hammer->CleanUp();
	return true;
}