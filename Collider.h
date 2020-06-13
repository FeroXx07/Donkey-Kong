#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "Game/SDL/include/SDL_Rect.h"
#include "Globals.h"

class Module;



struct Collider
{
	enum Items
	{
		None = -1,
		SCOREITEMS,
		IMPORTANTITEMS,
		POWERITEMS,
		MINECART,
		ELEVATINGLADDER
	};

	enum Type
	{
		NONE = -1,
		GROUND,
		PLAYER,
		ENEMY,
		WALL,
		LADDER,
		HAMMER,
		Item_Type,
		FIREBARREL,
		LOWERGROUND,
		ENEMYWALL,
		CONVEYORGROUND,
		
		MAX=11
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr, Items item = Items::None);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
	Items item;
};


#endif // !__COLLIDER_H__

