#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "Game/SDL/include/SDL_Rect.h"
#include "Globals.h"

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		GROUND,
		PLAYER,
		ENEMY,
		WALL,
		LADDER,
		HAMMER,

		MAX=6
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
};


#endif // !__COLLIDER_H__

