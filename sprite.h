#ifndef SPRITE_H
#define SPRITE_H

#include "rect.h"
#include "QDebug"

class Sprite : public Rect
{
private:
	Rect drawCoords;
	Rect texCoords;
	bool rot;
	bool xFlipped, yFlipped;

	inline void flipX(){
		drawCoords.setX(drawCoords.getX() + drawCoords.getWidth());
		drawCoords.setWidth(-drawCoords.getWidth());
		xFlipped = !xFlipped;
	}

	inline void flipY(){
		drawCoords.setY(drawCoords.getY() + drawCoords.getHeight());
		drawCoords.setHeight(-drawCoords.getHeight());
		yFlipped = !yFlipped;
	}

	inline void rotate(){
		rot = !rot;
	}
public:
	Sprite();
	Sprite(float x, float y, float width, float height);

	Rect& getTexRect() { return texCoords; }//simpler than adding accesor methods for this

	//void setTexRect(float x, float y, float width, float height);

	void setFlipX(bool b);
	void setFlipY(bool b);
	void setRot(bool b);

	inline bool getFlipX() const { return xFlipped; }
	inline bool getFlipY() const { return yFlipped; }
	inline bool getRot() const { return rot; }

	virtual void draw(int mode = GL_POLYGON);
};

#endif // SPRITE_H
