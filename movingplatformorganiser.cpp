#include "movingplatformorganiser.h"

QString movingPlatformOrganiser::addMovingPlatform(MovingPlatform r)
{
	QString str = "MovingPlatform_" + QString::number(movPlatCount++);
	movPlatMap.insert(std::pair<QString,MovingPlatform>(str,r));
	//rectMap.at(str).setColour(Colour(0,1,0));

	return str;
}
