#include "Enemy.h"

class Item_Iron : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Item_Iron(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The enemy animation
	Animation ironAnim;
};
