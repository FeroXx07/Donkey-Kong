#include "Collider.h"

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener, Items item): rect(rectangle), type(type), listener(listener), item(item)
{

}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	// TODO 1:	Return true if there is an overlap
	//			between argument "r" and property "rect"
	//Condition 1: When left edge of R1 is on the right of R2's right edge. ( That is , R1 is completely on the right of R2).
	//Condition 2: When right edge of R1 is on the left of R2's left edge. ( That is , R1 is completely on the left of R2).
	//Condition 3: When top edge of R1 is on bottom of R2's bottom edge ( That is , R1 is completely under R2).
	//Condition 4 : When bottom edge of R1 is on top of R2's top edge ( That is , R1 is completely over R2).

	if ((rect.x > r.x + r.w) || (rect.x + rect.w < r.x) || (rect.y > r.y + r.h) || (rect.y + rect.h < r.y))
	{
		return false;
	}
	LOG("A collision is happening!\n");
	return true;
}