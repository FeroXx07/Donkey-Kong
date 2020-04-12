#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

#include <stdio.h>
#include "Game/SDL/include/SDL_scancode.h"


const float gravity = 60.0f;         // pixels / second^2
const float deltaTime = 1.0f / 20.0f; // More or less 60 frames per second

ModulePlayer::ModulePlayer()
{
	// left idle animation
	leftIdleAnim.PushBack({ 66, 24, 12, 16 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = 0.1f;

	// right idle animation
	rightIdleAnim.PushBack({ 66, 41, 12, 16 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = 0.1f;

	leftAnim.PushBack({ 89, 24, 15, 16 }); // movement left 1
	leftAnim.PushBack({ 113, 24, 15, 15 }); // movement left 2
	leftAnim.PushBack({ 66, 24, 12, 16 }); // idle left
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	rightAnim.PushBack({ 89, 41, 15, 16 });
	rightAnim.PushBack({ 113, 41, 15, 15 });
	rightAnim.PushBack({ 66, 41, 12, 16 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	jumpAnim.PushBack({ 113, 24, 15, 15 });
	jumpAnim.loop = true;
	jumpAnim.speed = 0.1f;

	climbAnim.PushBack({ 138, 24, 13, 16 }); // climb movement 1
	climbAnim.PushBack({ 138, 40, 13, 16 }); // climb movement 2
	climbAnim.PushBack({ 161, 25, 14, 15 }); // when already up 1
	climbAnim.PushBack({184, 27, 16, 12 }); // when already up 2
	climbAnim.PushBack({ 208, 25, 16, 15 }); // idle up
	climbAnim.loop = true;
	climbAnim.speed = 0.1f;

	
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Background.png"); // arcade version

	//Starting position of the Mario
	position.x = 0;
	position.y = 232;

	playerCollider = App->collisions->AddCollider({position.x,position.y,12,16 }, Collider::Type::PLAYER, App->player);
	currentAnimation = &rightIdleAnim; 

	return ret;
}

update_status ModulePlayer::Update()
{

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && (isGround == true || isJumping ==true))
	{
		position.x -= speed.x;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && (isGround == true || isJumping ==true))
	{
		position.x += speed.x;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	

	if (isLadder == true)
	{
		isGround = false;
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed.x;
			if (currentAnimation != &climbAnim)
			{
				rightAnim.Reset();
				currentAnimation = &climbAnim;
			}
		}
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
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
		playerCollider->rect.w = 2;
		temp = 5;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && isGround == true)
	{
		speed.y -= 30.0f;
		if (currentAnimation != &jumpAnim)
		{
			currentAnimation = &jumpAnim;
		}
		isGround = false;
	}

	// If last movement was left, set the current animation back to left idle
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_UP)
		currentAnimation = &leftIdleAnim;
	// If last movement was right, set the current animation back to left idle
	else if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_UP)
		currentAnimation = &rightIdleAnim;

	else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_UP)
		currentAnimation = &rightIdleAnim;

	//Gravity
	if (isLadder == false )
	{ 
		////	Update position 
		//position.y = position.y + speedY * deltaTime + (1 / 2) * gravity * deltaTime * deltaTime;
		////	Upadte velocity
		//speedY = speedY + gravity * deltaTime;
		position.y += speed.y * deltaTime;      // Apply vertical velocity to X position
		speed.y += gravity * deltaTime;

		//printf("Position is: %d\n", position.y);
		//printf("Speed is: %d\n\n", speedY);
	}

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




	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Detect collision with a wall. If so, destroy the player.
	if (destroyed == false)
	{

		if (c2->type == Collider::Type::LADDER)
		{
			if (position.x + 4 <= c2->rect.x && position.x + 9 >= c2->rect.x + 1) 
				isLadder = true;
			if (position.y < c2->rect.y-15)
				isLadder = false;
		}
		else
			isLadder = false;

		//if(c2->type == Collider::Type::GROUND  )
		//{
		//	isGround = true;
		//	if (isLadder == true) {
		//		if (position.y < c2->rect.y - 16)
		//		{
		//			speedY = 0;
		//			position.y = c2->rect.y - 16;
		//		}
		//	}
		//	else {
		//		if (position.y + 16 > c2->rect.y && position.y < c2->rect.y) {
		//			position.y = c2->rect.y - 15;
		//			speedY = 0;
		//		}
		//	}
		//}

		if (c2->type == Collider::Type::GROUND)
		{
			isGround = true;
			if (isLadder == true) 
			{

			}
			else if (isLadder == false)
			{
				if (position.y + 16 > c2->rect.y ) // Collision to maintain the player to the ground
				{ 
					position.y = c2->rect.y - 15;
					speed.y = 0;
				}
				
			}
		}

		

		if (c2->type == Collider::Type::WALL)
		{
			if (position.x < c2->rect.x)
			{
				position.x = c2->rect.x - 13;
			}
			else
			{
				position.x = c2->rect.x + c2->rect.w;
			}
		}

		
	}
}