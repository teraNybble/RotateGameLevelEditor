#ifndef RECTORGANISER_H
#define RECTORGANISER_H

#include "enemy.h"
#include "sprite.h"
#include <map>

class rectOrganiser
{
private:
	static inline std::map<QString,Rect*> rectMap;
	static inline unsigned int wallCount = 0;
	static inline unsigned int killPlaneCount = 0;
	static inline unsigned int movPlatCount = 0;
	static inline unsigned int SpriteCount = 0;
	static inline unsigned int enyCount = 0;
	static inline unsigned int nrzCount = 0;
public:
	//rectOrganiser();
	static inline void remove(QString s) { delete rectMap.at(s);rectMap.erase(s); }
	static void clear();

	static QString addWall(Rect r);
	static QString addKillPlane(Rect r);
	static QString addMovingPlatform(MovingPlatform r);
	static QString addSprite(Sprite r);
	static QString addEnemy(Enemy r);
	static QString addNoRotateZone(Rect r);
	static QString addPlayer(Rect r);
	static QString addExit(Rect r);

	static const std::map<QString,Rect*> getMap() { return rectMap; }
	static inline void* getRect(QString id) { return rectMap.at(id); }
};

#endif // RECTORGANISER_H
