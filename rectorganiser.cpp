#include "rectorganiser.h"

void rectOrganiser::clear()
{
	for(auto& it : rectMap){
		delete it.second;
	}

	rectMap.clear();
	
	//qDebug() << "Clear has been called";
	wallCount = killPlaneCount = movPlatCount = SpriteCount = enyCount = nrzCount = 0;
}

QString rectOrganiser::addWall(Rect r)
{
	//QString str = "Wall_" + QString::number(wallCount++);
	QString str = "Wall_" + QStringLiteral("%1").arg(wallCount++,2,10,QLatin1Char('0'));
	rectMap.insert(std::pair<QString,Rect*>(str,new Rect(r)));
	rectMap.at(str)->setColour(Colour(0,1,0));

	return str;
}

QString rectOrganiser::addKillPlane(Rect r)
{
	//QString str = "KillPlane_" + QString::number(killPlaneCount++);
	QString str = "KillPlane_" + QStringLiteral("%1").arg(killPlaneCount++,2,10,QLatin1Char('0'));
	rectMap.insert(std::pair<QString,Rect*>(str,new Rect(r)));
	rectMap.at(str)->setColour(Colour(1,0,1,0.5));
	rectMap.at(str)->setType(Rect::KILLPLANE);

	return str;
}

QString rectOrganiser::addMovingPlatform(MovingPlatform r)
{
	//QString str = "MovingPlatform_" + QString::number(movPlatCount++);
	QString str = "MovingPlatform_" + QStringLiteral("%1").arg(movPlatCount++,2,10,QLatin1Char('0'));
	rectMap.insert(std::pair<QString,Rect*>(str,new MovingPlatform(r)));
	//rectMap.at(str).setColour(Colour(0,1,0));

	return str;
}

QString rectOrganiser::addSprite(Sprite r)
{
	//QString str = "Sprite_" + QString::number(SpriteCount++);
	QString str = "Sprite_" + QStringLiteral("%1").arg(SpriteCount++,2,10,QLatin1Char('0'));
	rectMap.insert(std::pair<QString,Rect*>(str,new Sprite(r)));
	rectMap.at(str)->setColour(Colour(1,1,1));
	rectMap.at(str)->setType(Rect::SPRITE);

	return str;
}

QString rectOrganiser::addEnemy(Enemy r)
{
	//QString str = "Enemy_" + QString::number(enyCount++);
	QString str = "Enemy_" + QStringLiteral("%1").arg(enyCount++,2,10,QLatin1Char('0'));
	rectMap.insert(std::pair<QString,Rect*>(str,new Enemy(r)));
	rectMap.at(str)->setType(Rect::ENEMY);
	//rectMap.at(str).setColour(Colour(0,1,0));

	return str;
}

QString rectOrganiser::addNoRotateZone(Rect r)
{
	//QString str = "NoRotateZone_" + QString::number(nrzCount++);
	QString str = "NoRotateZone_" + QStringLiteral("%1").arg(nrzCount++,2,10,QLatin1Char('0'));
	rectMap.insert(std::pair<QString,Rect*>(str,new Rect(r)));
	rectMap.at(str)->setColour(Colour(1,0,0,0.5));
	rectMap.at(str)->setType(Rect::NO_ROTATE_ZONE);

	return str;
}

QString rectOrganiser::addPlayer(Rect r)
{
	rectMap.insert(std::pair<QString,Rect*>("Player",new Rect(r)));
	rectMap.at("Player")->setColour(Colour(0,1,1));
	rectMap.at("Player")->setType(Rect::PLAYER);

	return "Player";
}

QString rectOrganiser::addExit(Rect r)
{
	rectMap.insert(std::pair<QString,Rect*>("Exit",new Rect(r)));
	rectMap.at("Exit")->setColour(Colour(0,0,0));
	rectMap.at("Exit")->setType(Rect::EXIT);

	return "Exit";
}
