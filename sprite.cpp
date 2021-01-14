#include "sprite.h"

Sprite::Sprite()
{
	Sprite(0,0,0,0);
}

Sprite::Sprite(float x, float y, float width, float height) :  Rect(x,y,width,height)
{
	drawCoords = Rect(0,0,0,0);
	texCoords = Rect(0,0,0,0);
	setColour(Colour(1,1,1));
	setType(Rect::SPRITE);
	xFlipped = yFlipped = rot = false;
}

/*
void Sprite::setTexRect(float x, float y, float width, float height)
{
	texCoords.setX(x);
	texCoords.setY(y);
	texCoords.setWidth(width);
	texCoords.setHeight(height);

	drawCoords.setX(x);
	drawCoords.setY(y);
	drawCoords.setWidth(width);
	drawCoords.setHeight(height);
}*/

void Sprite::setFlipX(bool b)
{
	if(b != xFlipped){
		flipX();
	}
}

void Sprite::setFlipY(bool b)
{
	if(b != yFlipped){
		flipY();
	}

	//qDebug() << "Y is flipped(" << yFlipped <<") and it should be flipped(" << b << ")";
}

void Sprite::setRot(bool b)
{
	if(b != rot){
		rotate();
	}
}

void Sprite::draw(int mode)
{
	drawCoords = texCoords;
	if(xFlipped) {
		drawCoords.setX(drawCoords.getX() + drawCoords.getWidth());
		drawCoords.setWidth(-drawCoords.getWidth());
	}
	if(yFlipped) {
		drawCoords.setY(drawCoords.getY() + drawCoords.getHeight());
		drawCoords.setHeight(-drawCoords.getHeight());
	}
	//if(rot) { rotate(); }

	glEnable(GL_TEXTURE_2D);
	//qDebug() << "Drawing a sprite";
	glPushMatrix();

		//glColor3f(0,1,0);
		colour.draw();

		glTranslatef(x,y,0);
		if(rot){
			//qDebug() << "Drawing with a rot";
			glRotatef(90,0,0,1);
		}
		//rotate?
		glLineWidth(2.0f);
		glBegin(mode);
			glTexCoord2f(drawCoords.getX(),drawCoords.getY());												glVertex2f(0 - (width/2.0),0 - (height/2.0));
			glTexCoord2f(drawCoords.getX(),drawCoords.getY() + drawCoords.getHeight());						glVertex2f(0 - (width/2.0),0 + (height/2.0));
			glTexCoord2f(drawCoords.getX() + drawCoords.getWidth(),drawCoords.getY() + drawCoords.getHeight());	glVertex2f(0 + (width/2.0),0 + (height/2.0));
			glTexCoord2f(drawCoords.getX() + drawCoords.getWidth(),drawCoords.getY());							glVertex2f(0 + (width/2.0),0 - (height/2.0));
		glEnd();

	glPopMatrix();
	if(selected){
		glPushMatrix();

			//glColor3f(0,1,0);
			//colour.draw();
			Colour(1,1,1).draw();

			glTranslatef(x,y,0);
			//rotate?
			if(rot){
				//qDebug() << "Drawing with a rot";
				glRotatef(90,0,0,1);
			}
			glLineWidth(3.0f);
			glBegin(GL_LINE_LOOP);
				glVertex2f(0 - (width/2.0),0 - (height/2.0));
				glVertex2f(0 - (width/2.0),0 + (height/2.0));
				glVertex2f(0 + (width/2.0),0 + (height/2.0));
				glVertex2f(0 + (width/2.0),0 - (height/2.0));
			glEnd();

		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);
}
