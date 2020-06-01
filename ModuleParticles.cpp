#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "Game/SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Background2.png");
	++activeTextures;  ++totalTextures;

	// Explosion particle
	plasma.anim.PushBack({753, 106, 14, 12});
	plasma.anim.PushBack({780, 108, 10, 8});

	plasma.anim.PushBack({ 753, 106, 14, 12 });
	plasma.anim.PushBack({ 780, 108, 10, 8 });

	plasma.anim.PushBack({ 753, 106, 14, 12 });
	plasma.anim.PushBack({ 780, 108, 10, 8 });

	plasma.anim.PushBack({ 804, 109, 6, 6 });
	plasma.anim.PushBack({ 824, 105, 16, 14 });

	plasma.anim.loop = false;
	plasma.anim.speed = 0.1f;
	plasma.lifetime = 60;

	score100.anim.PushBack({ 457, 108, 15, 7 });
	score100.anim.loop = false;
	score100.anim.speed = 0.1f;
	score100.lifetime = 60;

	score300.anim.PushBack({ 505, 108, 15, 7 });
	score300.anim.loop = false;
	score300.anim.speed = 0.1f;
	score300.lifetime = 60;

	score500.anim.PushBack({ 529, 108, 16, 7 });
	score500.anim.loop = false;
	score500.anim.speed = 0.1f;
	score500.lifetime = 60;

	wall.anim.PushBack({ 0,0,4,3 });
	wall.anim.loop = true;
	wall.anim.speed = 0.1f;
	wall.lifetime = 10000;

	marioDeath.anim.PushBack({ 424, 24, 16, 15}); // Facing up
	marioDeath.anim.PushBack({ 449, 5, 16, 16 }); // Facing left
	marioDeath.anim.PushBack({ 424, 6, 16, 15 }); // Facing down
	marioDeath.anim.PushBack({ 448, 24, 16, 16 }); // Facing right

	marioDeath.anim.PushBack({ 424, 24, 16, 15 }); // Facing up
	marioDeath.anim.PushBack({ 449, 5, 16, 16 }); // Facing left
	marioDeath.anim.PushBack({ 424, 6, 16, 15 }); // Facing down
	marioDeath.anim.PushBack({ 448, 24, 16, 16 }); // Facing right

	marioDeath.anim.PushBack({ 424, 24, 16, 15 }); // Facing up
	marioDeath.anim.PushBack({ 449, 5, 16, 16 }); // Facing left
	marioDeath.anim.PushBack({ 424, 6, 16, 15 }); // Facing down
	marioDeath.anim.PushBack({ 448, 24, 16, 16 }); // Facing right

	marioDeath.anim.PushBack({ 424, 24, 16, 15 }); // Facing up
	marioDeath.anim.PushBack({ 449, 5, 16, 16 }); // Facing left
	marioDeath.anim.PushBack({ 424, 6, 16, 15 }); // Facing down
	marioDeath.anim.PushBack({ 448, 24, 16, 16 }); // Facing right

	marioDeath.anim.PushBack({ 472, 24, 16, 16 }); // Facing up
	marioDeath.anim.loop = false;
	marioDeath.anim.speed = 0.1f;
	marioDeath.lifetime = 300;
	return true;
}

bool ModuleParticles::CleanUp()
{
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	App->textures->Unload(texture);
	--totalTextures;

	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1 && particles[i]->collider->type != Collider::Type::WALL) // Will not destroy walls
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}