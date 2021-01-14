#include "movingplatform.h"

MovingPlatform::MovingPlatform()
{
	MovingPlatform(0,0,30,5,20,0);
}

MovingPlatform::MovingPlatform(float x, float y, float width, float height, float endX, float endY) : Rect(x,y,width,height)
{
	this->endX = endX;
	this->endY = endY;
	this->time = 1.0;
	this->pauseTime = 1.0;
	setType(RectType::MOVING_PLATFORM);
	setColour(Colour(0.49,0.31,0.19));
}

void MovingPlatform::draw(int mode)
{
	//qDebug() << "Drawing a moving platform";
	glPushMatrix();

		//glColor3f(0,1,0);
		Colour(1,1,1).draw();

		//glTranslatef(x,y,0);
		//rotate?
		glLineWidth(1.0f);
		glBegin(GL_LINES);
			glVertex2f(x,y);
			glVertex2f(endX,endY);
		glEnd();

	glPopMatrix();

	Rect::draw(mode);

	Rect tempRect(endX,endY,width,height);
	Colour tempColour = getColour();
	tempColour.setAlpha(0.5f);
	tempRect.setColour(tempColour);
	tempRect.draw();
}
