#ifndef __ENEMY_REDBIRD_H__
#define __ENEMY_REDBIRD_H__

#include "Enemy.h"

class Enemy_FireMinion : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_FireMinion(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:

	int spawnDelay = 0;


	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The enemy animation
	Animation enemy_FireMinionLeftAnim;
	Animation enemy_FireMinionRightAnim;
	Animation enemy_FireMinionLeftAnimHammer;
	Animation enemy_FireMinionRightAnimHammer;
	
	int enemyFireMinionSpeed = 1;
};

#endif // __ENEMY_REDBIRD_H__