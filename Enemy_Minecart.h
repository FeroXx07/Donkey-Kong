#ifndef __ENEMY_Minecart_H__
#define __ENEMY_Minecart_H__

#include "Enemy.h"

class Enemy_Minecart : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Minecart(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:

	int spawnDelay = 0;


	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The enemy animation
	Animation mineCartAnim;

	int enemyFireMinionSpeed = 1;
};

#endif // __ENEMY_REDBIRD_H__