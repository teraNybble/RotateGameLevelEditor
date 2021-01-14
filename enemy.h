#ifndef ENEMY_H
#define ENEMY_H

#include "movingplatform.h"

class Enemy : public MovingPlatform
{
private:
	int type;
	int headDir;
	float radius;
	float attackSpeed;
public:
	Enemy();
	Enemy(float x, float y, float endX, float endY);

	inline void setType(int type) { this->type = type; }
	inline void setHeadDir(int dir) { this->headDir = dir; }
	inline void setRadius(float r) { this->radius = r; }
	inline void setAttackSpeed(float s) { this->attackSpeed = s; }

	inline int getType() { return type; }
	inline int getHeadDir() { return headDir; }
	inline float getRadius() { return radius; }
	inline float getAttackSpeed() { return attackSpeed; }
};

#endif // ENEMY_H
