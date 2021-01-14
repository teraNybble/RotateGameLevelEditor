#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QDebug>
#include <QListWidget>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QFile>
#include <QComboBox>
#include "rectorganiser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_actionWall_triggered();
	void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
	void on_doubleSpinBox_posx_valueChanged(double arg1);
	void on_doubleSpinBox_posy_valueChanged(double arg1);
	void on_doubleSpinBox_width_valueChanged(double arg1);
	void on_doubleSpinBox_height_valueChanged(double arg1);
	void on_actionEnemy_triggered();
	void on_actionMoving_Platform_triggered();
	void on_doubleSpinBox_endposx_valueChanged(double arg1);
	void on_doubleSpinBox_endposy_valueChanged(double arg1);
	void on_pushButton_delete_clicked();
	void on_actionSave_As_triggered();
	void on_actionNew_triggered();
	void on_actionKill_Plane_triggered();
	void on_comboBox_headDir_currentIndexChanged(int index);
	void on_comboBox_enyType_currentIndexChanged(int index);
	void on_actionSave_triggered();
	void on_doubleSpinBox_attackSpeed_valueChanged(double arg1);
	void on_doubleSpinBox_attackRadius_valueChanged(double arg1);
	void on_actionNo_Rotate_Zone_triggered();
	void on_actionSprite_triggered();
	void on_actionOpen_triggered();
	void on_checkBox_sidwaysExit_stateChanged(int arg1);
	void on_doubleSpinBox_spriteX_valueChanged(double arg1);
	void on_doubleSpinBox_spriteY_valueChanged(double arg1);
	void on_doubleSpinBox_spriteWidth_valueChanged(double arg1);
	void on_doubleSpinBox_spriteHeight_valueChanged(double arg1);
	void on_checkBox_spriteFlipX_stateChanged(int arg1);
	void on_checkBox_spriteFlipY_stateChanged(int arg1);
	void on_checkBox_spriteRotate_stateChanged(int arg1);
	void on_actionReset_Pan_triggered();

	void on_actionReset_Zoom_triggered();

private:
	Ui::MainWindow *ui;
	QListWidgetItem* selectedListItem;
	//QFile file;
	QString savePath;

	void hideListBoxItems();
	void newFile();
	void saveAs();
	void save();
	void saveFile();

	void actionPerformed();
};
#endif // MAINWINDOW_H
