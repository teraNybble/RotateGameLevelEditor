#ifndef MOVINGPLATFORMORGANISER_H
#define MOVINGPLATFORMORGANISER_H


#include "movingplatform.h"
#include <map>

class movingPlatformOrganiser
{
private:
	static inline std::map<QString,MovingPlatform> movPlatMap;
	static inline unsigned int movPlatCount = 0;
public:
	//rectOrganiser();
//	static QString addWall(Rect r);
	static QString addMovingPlatform(MovingPlatform r);

	static const std::map<QString,MovingPlatform> getMap() { return movPlatMap; }
	static inline void* getRect(QString id) { return &movPlatMap.at(id); }
};

#endif // MOVINGPLATFORMORGANISER_H
