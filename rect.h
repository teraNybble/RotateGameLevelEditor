#ifndef RECT_H
#define RECT_H

#include <QOpenGLFunctions>
#include "colour.h"

class Rect
{
public:
	enum RectType { WALL, KILLPLANE, MOVING_PLATFORM, SPRITE, ENEMY, NO_ROTATE_ZONE, PLAYER, EXIT };
private:
	RectType type;
protected:
	Colour colour;
	bool selected;
	float x,y,width,height;
public:
	Rect();
	Rect(float x, float y, float width, float height);

	inline void setX(float x) { this->x = x; }
	inline void setY(float y) { this->y = y; }
	inline void setWidth(float width) { this->width = width; }
	inline void setHeight(float height) { this->height = height; }
	inline void setPos(float x, float y) { this->x = x; this->y = y; }
	inline void setRect(float x, float y, float width, float height) { this->x = x; this->y = y; this->width = width; this->height = height; }
	inline void setColour(Colour colour) { this->colour = colour; }
	inline void setType(RectType type) { this->type = type; }
	inline void select() { this->selected = true; }
	inline void deselect() { this->selected = false; }

	inline float getX() const { return x; }
	inline float getY() const { return y; }
	inline float getWidth() const { return width; }
	inline float getHeight() const { return height; }
	inline RectType getType() const { return type; }
	inline Colour getColour() const { return colour; }

	virtual void draw(int mode = GL_POLYGON);
};

#endif // RECT_H
