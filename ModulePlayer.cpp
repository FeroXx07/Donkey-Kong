#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"


#include "Game/SDL/include/SDL_scancode.h"


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

	jumpAnim.PushBack({ 66, 24, 12, 16 });
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

	playerCollider = App->collisions->AddCollider({ position.x-1,position.y,13,16 }, Collider::Type::PLAYER, App->player);
	currentAnimation = &rightIdleAnim; 

	return ret;
}

update_status ModulePlayer::Update()
{

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &climbAnim)
		{
			rightAnim.Reset();
			currentAnimation = &climbAnim;
		}
	}

	// If last movement was left, set the current animation back to left idle
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_UP)
		currentAnimation = &leftIdleAnim;
	// If last movement was right, set the current animation back to left idle
	else if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_UP)
		currentAnimation = &rightIdleAnim;

	else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_UP)
		currentAnimation = &rightIdleAnim;

	playerCollider->SetPos(position.x, position.y);

	currentAnimation->Update();

	//The camera limits for the player
	//if (position.x < 0) position.x = 0;
	//if (position.x > 211) position.x = 211;
	//if (position.y < 0) position.y = 0;


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
		if (c2->type == Collider::Type::GROUND)
		{
			if (position.y < c2->rect.y)
				position.y = c2->rect.y - 16;
			else
				position.y = c2->rect.y + c2->rect.h;
		}

		if (c2->type == Collider::Type::WALL)
		{
			if (position.x < c2->rect.x)
				position.x = c2->rect.x - 13;
			else
				position.x = c2->rect.x +c2->rect.w;
		}
	}
}