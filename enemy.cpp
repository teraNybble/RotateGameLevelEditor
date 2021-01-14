#include "enemy.h"

Enemy::Enemy()
{
	Enemy(0,0,0,0);
}

Enemy::Enemy(float x, float y, float endX, float endY) : MovingPlatform(x,y,5.1,5.1,endX,endY)
{
	headDir = 0;
	type = 0;
	radius = 0.0;
	attackSpeed = 0.0;
	setColour(Colour(1,0,0));
	setType(Rect::ENEMY);
}
