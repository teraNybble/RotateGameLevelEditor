#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QOpenGLFunctions>
#include <QImage>
//#include <qpng>
#include "rect.h"

class TextureManager
{
private:
	//should be std::map
	static inline std::map<int, GLuint> textures;
	static bool loadPNGFromFile(const char* name, Rect& rect, bool& outHasAlpha, GLubyte** outData);
	static GLuint loadPNG(const char* path,int filter);
public:
	static void loadTextures(std::string path, int identifier, int filter = GL_LINEAR);
	static GLuint getTexture(int identifier) { return textures.at(identifier); }
};

#endif // TEXTUREMANAGER_H
