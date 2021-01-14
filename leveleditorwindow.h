#ifndef LEVELEDITORWINDOW_H
#define LEVELEDITORWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QGLFramebufferObjectFormat>
#include <QTimer>
#include <QMouseEvent>
#include "rectorganiser.h"
#include <QDebug>

class LevelEditorWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
	//Q_OBJECT
private:
	QTimer timer;
	int width, height;
	float panX, panY;
	float oldPanX, oldPanY;
	QPoint startPos;
	QOpenGLTexture* texture;
	int scale;

	void resizeOrtho();
protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;

	void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

	void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;
public:
	explicit LevelEditorWindow(QWidget* parent = 0);
	~LevelEditorWindow();
	//LevelEditorWindow();
	inline void resetPan() { panX = panY = oldPanX = oldPanY = 0; }
	inline void resetZoom() { scale = 0; }

	inline void resetAll() { resetPan(); resetZoom(); }
};

#endif // LEVELEDITORWINDOW_H
