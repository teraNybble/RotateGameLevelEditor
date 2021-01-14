#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include "rect.h"
#include <QDebug>

class MovingPlatform : public Rect
{
private:
	float time;
	float pauseTime;
protected:
	float endX, endY;
public:
	MovingPlatform();
	MovingPlatform(float x, float y, float width, float height, float endX, float endY);

	inline void setEndX(float endX) { this->endX = endX; }
	inline void setEndY(float endY) { this->endY = endY; }
	inline void setTime(float time) { this->time = time; }
	inline void setPauseTime(float pauseTime) { this->pauseTime = pauseTime; }

	inline float getEndX() const { return endX; }
	inline float getEndY() const { return endY; }
	inline float getTime() const { return time; }
	inline float getPauseTime() const { return pauseTime; }

	virtual void draw(int mode = GL_POLYGON) override;
};

#endif // MOVINGPLATFORM_H
