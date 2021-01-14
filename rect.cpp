#include "rect.h"

Rect::Rect()
{
	Rect(0,0,0,0);
}

Rect::Rect(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = WALL;
	this->colour = Colour(0,1,0);
	this->selected = false;
}

void Rect::draw(int mode)
{
	glPushMatrix();

		//glColor3f(0,1,0);
		colour.draw();

		glTranslatef(x,y,0);
		//rotate?
		glLineWidth(2.0f);
		glBegin(mode);
			glVertex2f(0 - (width/2.0),0 - (height/2.0));
			glVertex2f(0 - (width/2.0),0 + (height/2.0));
			glVertex2f(0 + (width/2.0),0 + (height/2.0));
			glVertex2f(0 + (width/2.0),0 - (height/2.0));
		glEnd();

	glPopMatrix();
	if(selected){
		glPushMatrix();

			//glColor3f(0,1,0);
			//colour.draw();
			Colour(1,1,1).draw();

			glTranslatef(x,y,0);
			//rotate?
			glLineWidth(3.0f);
			glBegin(GL_LINE_LOOP);
				glVertex2f(0 - (width/2.0),0 - (height/2.0));
				glVertex2f(0 - (width/2.0),0 + (height/2.0));
				glVertex2f(0 + (width/2.0),0 + (height/2.0));
				glVertex2f(0 + (width/2.0),0 - (height/2.0));
			glEnd();

		glPopMatrix();
	}
}
