#include "leveleditorwindow.h"

LevelEditorWindow::LevelEditorWindow(QWidget* parent) : QOpenGLWidget(parent)
{
	panX = panY = oldPanX = oldPanY = 0;
	scale = 0;
	connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
	timer.start(16);
}

LevelEditorWindow::~LevelEditorWindow()
{

}

void LevelEditorWindow::resizeOrtho()
{
	float coordWidth = ((100 + (2*scale)) * ((float)width/(float)height))/2.0f;
	//float coordWidth = ((200) * ((float)w/(float)h))/2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//qDebug() << "New ortho" << (50+scale);

	glOrtho(-coordWidth,+coordWidth,-(50+scale),(50+scale),-50,50);

	//glOrtho(-coordWidth,+coordWidth,-100,100,-50,50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void LevelEditorWindow::initializeGL()
{
	initializeOpenGLFunctions();

	texture = new QOpenGLTexture(QImage("LevelSprites.png").mirrored());

	texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	texture->setWrapMode(QOpenGLTexture::WrapMode::Repeat);
}

void LevelEditorWindow::resizeGL(int w, int h)
{
	width = w;
	height = h;
	glViewport(0,0,w,h);
	float coordWidth = ((100 + (2*scale)) * ((float)w/(float)h))/2.0f;
	//float coordWidth = ((200) * ((float)w/(float)h))/2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//qDebug() << "New ortho" << (50+scale);

	glOrtho(-coordWidth,+coordWidth,-(50+scale),(50+scale),-50,50);

	//glOrtho(-coordWidth,+coordWidth,-100,100,-50,50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void LevelEditorWindow::paintGL()
{
	resizeOrtho();
	//draw
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//glClearColor(1.0f,0.0f,0.0f,1.0f);
	glClearColor(0.118f,0.118f,0.118f,1.0f);
	glLoadIdentity();

	texture->bind();
	//draw stuff here

	glTranslatef(panX,panY,0);

	for(const auto& it : rectOrganiser::getMap()){
		it.second->draw();
		//qDebug() << "drawing somthing";
	}

	glDisable(GL_BLEND);
	glFlush();
}

void LevelEditorWindow::mouseMoveEvent(QMouseEvent* event)
{
//	qDebug() << "mouse move event";
	QPoint newPos = QPoint((event->x()/(float)width * (100+(2*scale)) * (width/(float)height)) - (((100.0f+(2*scale)) * (width/(float)height))/2.0f),
						   (((height - event->y())/(float)height)*(100+(2*scale)))-(50+scale));

	QPoint movePos = (newPos - startPos);

//	qDebug() << movePos;

	panX = movePos.x() + oldPanX;
	panY = movePos.y() + oldPanY;

	QWidget::mouseMoveEvent(event);
}

void LevelEditorWindow::mousePressEvent(QMouseEvent* event)
{
//	qDebug() << "mouse press event" << event->pos();
	startPos = QPoint((event->x()/(float)width * (100+(2*scale)) * (width/(float)height)) - (((100+(2*scale)) * (width/(float)height))/2.0f),
						  (((height - event->y())/(float)height)*(100+(2*scale)))-(50+scale));
//	qDebug() << startPos;
	QWidget::mousePressEvent(event);
}

void LevelEditorWindow::mouseReleaseEvent(QMouseEvent* event)
{
	oldPanX = panX;
	oldPanY = panY;
	QWidget::mouseReleaseEvent(event);
}

void LevelEditorWindow::wheelEvent(QWheelEvent* event)
{
	//qDebug() << event->delta();
//	qDebug() << event->angleDelta().y();
	scale += event->angleDelta().y()/100;
	qDebug() << scale;
	//scale += event->delta()/100;
	//resizeGL(width,height);
	resizeOrtho();
	QWidget::wheelEvent(event);
}
