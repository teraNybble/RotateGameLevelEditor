#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	selectedListItem = nullptr;

	hideListBoxItems();
	savePath = "";

	ui->listWidget->addItem(rectOrganiser::addPlayer(Rect(0,0,5,10)));
	ui->listWidget->addItem(rectOrganiser::addExit(Rect(0,0,6,11)));
	ui->listWidget->sortItems();
	//savePath = "NULL";
	/*
	ui->doubleSpinBox_posx->hide();
	ui->doubleSpinBox_posy->hide();
	ui->label_posx->hide();
	ui->label_posy->hide();
	ui->doubleSpinBox_width->hide();
	ui->doubleSpinBox_height->hide();
	ui->label_width->hide();
	ui->label_height->hide();
	*/
	//std::vector<std::pair>
	//std::map<Qstring,Rect> items;
	//ui->listWidget->addItem("Lable 0");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::hideListBoxItems()
{
	QRegularExpression r("doubleSpinBox_[\\S]*");
	//find all double spinboxes
	QList<QDoubleSpinBox*> spinBoxes = ui->scrollArea->findChildren<QDoubleSpinBox*>(r);
	//set all min and max to 0 and uint max respectivly
	for(auto it : spinBoxes){
		//it->setMinimum(0);
		it->hide();
		it->setMaximum(FLT_MAX);
		it->setMinimum(-FLT_MAX);
	}

	r.setPattern("label_[\\S]*");
	QList<QLabel*> labels = ui->scrollArea->findChildren<QLabel*>(r);
	//sets the maximum value an above ground treasure counter can be to ubyte max
	//and the minimum to 0
	for(auto it : labels){
		it->hide();
	}

	r.setPattern("comboBox_[\\S]*");
	QList<QComboBox*> dropDowns = ui->scrollArea->findChildren<QComboBox*>(r);
	//sets the maximum value an above ground treasure counter can be to ubyte max
	//and the minimum to 0
	for(auto it : dropDowns){
		it->hide();
	}

	r.setPattern("checkBox_[\\S]*");
	QList<QCheckBox*> checks = ui->scrollArea->findChildren<QCheckBox*>(r);
	//sets the maximum value an above ground treasure counter can be to ubyte max
	//and the minimum to 0
	for(auto it : checks){
		it->hide();
	}

	//ui->checkBox_sidwaysExit->hide();
	ui->pushButton_delete->hide();
}

void MainWindow::newFile()
{
	rectOrganiser::clear();
	ui->listWidget->blockSignals(true);
	ui->listWidget->clear();
	ui->listWidget->blockSignals(false);

	ui->listWidget->addItem(rectOrganiser::addPlayer(Rect(0,0,5,10)));
	ui->listWidget->addItem(rectOrganiser::addExit(Rect(0,0,6,11)));
	ui->listWidget->sortItems();
	ui->checkBox_sidwaysExit->setChecked(false);

	ui->widget->resetAll();

	this->setWindowTitle("New Level");

	hideListBoxItems();
}

void MainWindow::saveAs()
{
	savePath = QFileDialog::getSaveFileName(this,"Save As","","*.rld");
	qDebug() << savePath;
	if(savePath == "") { return; }
	//do save shit
	saveFile();
}

void MainWindow::save()
{
	if(savePath == "") { saveAs(); }

	saveFile();
}

void MainWindow::saveFile()
{
	QFile file(savePath);

	if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)){
		return;
	}

	QTextStream out(&file);

	out << ((Rect*)rectOrganiser::getRect("Player"))->getX() << " " << ((Rect*)rectOrganiser::getRect("Player"))->getY() << "\n";
	out << ((Rect*)rectOrganiser::getRect("Exit"))->getX() << " " << ((Rect*)rectOrganiser::getRect("Exit"))->getY() << (((Rect*)rectOrganiser::getRect("Exit"))->getWidth() == 6 ? " 0" : " 1") << "\n";

	for(const auto& it : rectOrganiser::getMap()){
		switch (it.second->getType()) {
		case Rect::MOVING_PLATFORM:
			out << it.second->getType() << " " << it.second->getX() << " " << it.second->getY() << " " << it.second->getWidth() << " " << it.second->getHeight() << " " << ((MovingPlatform*)it.second)->getTime() << " " << ((MovingPlatform*)it.second)->getEndX() << " " <<  ((MovingPlatform*)it.second)->getEndY() << " " <<  ((MovingPlatform*)it.second)->getPauseTime() << "\n";
			break;
		case Rect::ENEMY:
			//qDebug() << it.second->getType() << " " << it.second->getX() << " " << it.second->getY() << " " << ((Enemy*)it.second)->getTime() << " " << ((Enemy*)it.second)->getEndX() << " " << ((Enemy*)it.second)->getEndY() << " " << ((Enemy*)it.second)->getHeadDir() << " " << ((Enemy*)it.second)->getRadius() << " " << ((Enemy*)it.second)->getType() << " " << ((Enemy*)it.second)->getAttackSpeed() << "\n";
			out << it.second->getType() << " " << it.second->getX() << " " << it.second->getY() << " " << ((Enemy*)it.second)->getTime() << " " << ((Enemy*)it.second)->getEndX() << " " << ((Enemy*)it.second)->getEndY() << " " << ((Enemy*)it.second)->getHeadDir() << " " << ((Enemy*)it.second)->getRadius() << " " << ((Enemy*)it.second)->getType() << " " << ((Enemy*)it.second)->getAttackSpeed() << "\n";
			break;
		case Rect::SPRITE:
		{
			int temp = 0;
			temp |= ((Sprite*)it.second)->getFlipX();
			temp |= ((Sprite*)it.second)->getFlipY() << 1;
			temp |= ((Sprite*)it.second)->getRot() << 2;
			out << it.second->getType() << " " << it.second->getX() << " " << it.second->getY() << " " << it.second->getWidth() << " " << it.second->getHeight() << " " << ((Sprite*)it.second)->getTexRect().getX() << " " << ((Sprite*)it.second)->getTexRect().getY() << " " << ((Sprite*)it.second)->getTexRect().getWidth() << " " << ((Sprite*)it.second)->getTexRect().getHeight() << " " << temp << "\n";
			break;
		}
		case Rect::PLAYER:
		case Rect::EXIT:
			break;
		default:
			out << it.second->getType() << " " << it.second->getX() << " " << it.second->getY() << " " << it.second->getWidth() << " " << it.second->getHeight() << "\n";
			break;
		}
	}

	file.close();

	int i = savePath.size()-1;
	while(savePath[i] != '/'){
		i--;
		//qDebug() << savePath[i];
	}

	this->setWindowTitle(QString::fromStdString(savePath.toStdString().substr(i+1,savePath.size()-i)));

}

void MainWindow::on_actionWall_triggered()
{
	qDebug() << "Adding wall";
	ui->listWidget->addItem(rectOrganiser::addWall(Rect(0,0,10,10)));
	ui->listWidget->sortItems();

	actionPerformed();
}

void MainWindow::on_actionKill_Plane_triggered()
{
	qDebug() << "Adding kill plane";
	ui->listWidget->addItem(rectOrganiser::addKillPlane(Rect(0,0,10,10)));
	ui->listWidget->sortItems();

	actionPerformed();
}

void MainWindow::on_actionEnemy_triggered()
{
	qDebug() << "Adding enemy";
	ui->listWidget->addItem(rectOrganiser::addEnemy(Enemy(0,0,0,0)));
	ui->listWidget->sortItems();

	actionPerformed();
}

void MainWindow::on_actionSprite_triggered()
{
	qDebug() << "Adding Sprite";
	ui->listWidget->addItem(rectOrganiser::addSprite(Sprite(0,0,5,5)));
	ui->listWidget->sortItems();

	actionPerformed();
}

void MainWindow::on_actionMoving_Platform_triggered()
{
	qDebug() << "Adding moving platform";
	ui->listWidget->addItem(rectOrganiser::addMovingPlatform(MovingPlatform(0,0,30,5,0,0)));
	ui->listWidget->sortItems();

	actionPerformed();
}

void MainWindow::on_actionNo_Rotate_Zone_triggered()
{
	qDebug() << "Adding no Rotate Zone";
	ui->listWidget->addItem(rectOrganiser::addNoRotateZone(Rect(0,0,10,10)));
	ui->listWidget->sortItems();

	actionPerformed();
}

void MainWindow::on_pushButton_delete_clicked()
{
	if(selectedListItem != nullptr){
		rectOrganiser::remove(selectedListItem->text());
		ui->listWidget->blockSignals(true);
		ui->listWidget->clear();
		ui->listWidget->blockSignals(false);

		for(auto& it : rectOrganiser::getMap()){
			ui->listWidget->addItem(it.first);
		}
		selectedListItem = nullptr;
		hideListBoxItems();
	}
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
	//ui->scrollArea->
	//qDebug() << current->text();
	hideListBoxItems();
	selectedListItem = current;

	ui->doubleSpinBox_posx->show();
	ui->doubleSpinBox_posy->show();
	ui->label_posx->show();
	ui->label_posy->show();

	((Rect*)rectOrganiser::getRect(current->text()))->select();
	if(previous != nullptr){
		((Rect*)rectOrganiser::getRect(previous->text()))->deselect();
	}

	Rect* tempRect = (Rect*)rectOrganiser::getRect(current->text());
	//tempRect->select();
	if(!(tempRect->getType() == Rect::PLAYER || tempRect->getType() == Rect::EXIT)){
		ui->pushButton_delete->show();
	}

	//qDebug() << tempRect->getType();

	switch (tempRect->getType()) {
	case Rect::MOVING_PLATFORM:
	{
		ui->doubleSpinBox_endposx->show();
		ui->doubleSpinBox_endposy->show();
		ui->label_endposx->show();
		ui->label_endposy->show();
		ui->doubleSpinBox_speed->show();
		ui->doubleSpinBox_pauseTime->show();
		ui->label_speed->show();
		ui->label_pauseTime->show();
		MovingPlatform* tempPlat = (MovingPlatform*)rectOrganiser::getRect(current->text());
		ui->doubleSpinBox_endposx->setValue(tempPlat->getEndX());
		ui->doubleSpinBox_endposy->setValue(tempPlat->getEndY());
		ui->doubleSpinBox_speed->setValue(tempPlat->getTime());
		ui->doubleSpinBox_pauseTime->setValue(tempPlat->getPauseTime());
	}
	case Rect::NO_ROTATE_ZONE:
	case Rect::KILLPLANE:
	case Rect::WALL:
		ui->doubleSpinBox_width->show();
		ui->doubleSpinBox_height->show();
		ui->label_width->show();
		ui->label_height->show();
		break;
	case Rect::ENEMY:
	{
		ui->doubleSpinBox_endposx->show();
		ui->doubleSpinBox_endposy->show();
		ui->label_endposx->show();
		ui->label_endposy->show();
		ui->doubleSpinBox_speed->show();
		ui->label_speed->show();
		ui->doubleSpinBox_attackSpeed->show();
		ui->doubleSpinBox_attackRadius->show();
		ui->comboBox_headDir->show();
		ui->comboBox_enyType->show();
		ui->label_attackSpeed->show();
		ui->label_attackRadius->show();
		ui->label_enyType->show();
		ui->label_headDir->show();
		Enemy* tempEny = (Enemy*)rectOrganiser::getRect(current->text());
		ui->doubleSpinBox_endposx->setValue(tempEny->getEndX());
		ui->doubleSpinBox_endposy->setValue(tempEny->getEndY());
		ui->doubleSpinBox_speed->setValue(tempEny->getTime());
		ui->doubleSpinBox_attackSpeed->setValue(tempEny->getAttackSpeed());
		ui->doubleSpinBox_attackRadius->setValue(tempEny->getRadius());
		ui->comboBox_enyType->setCurrentIndex(tempEny->getType());
		ui->comboBox_headDir->setCurrentIndex(tempEny->getHeadDir());
		break;
	}
	case Rect::SPRITE:
	{
		ui->doubleSpinBox_width->show();
		ui->doubleSpinBox_height->show();
		ui->label_width->show();
		ui->label_height->show();
		ui->doubleSpinBox_spriteX->show();
		ui->doubleSpinBox_spriteY->show();
		ui->doubleSpinBox_spriteWidth->show();
		ui->doubleSpinBox_spriteHeight->show();
		ui->label_spriteX->show();
		ui->label_spriteY->show();
		ui->label_spriteWidth->show();
		ui->label_spriteHeight->show();
		ui->checkBox_spriteFlipX->show();
		ui->checkBox_spriteFlipY->show();
		ui->checkBox_spriteRotate->show();
		ui->label_spriteFlipX->show();
		ui->label_spriteFlipY->show();
		ui->label_spriteRotate->show();
		Sprite* tempSprite = (Sprite*)rectOrganiser::getRect(current->text());
		ui->doubleSpinBox_spriteX->setValue(tempSprite->getTexRect().getX());
		ui->doubleSpinBox_spriteY->setValue(tempSprite->getTexRect().getY());
		ui->doubleSpinBox_spriteWidth->setValue(tempSprite->getTexRect().getWidth());
		ui->doubleSpinBox_spriteHeight->setValue(tempSprite->getTexRect().getHeight());
		ui->checkBox_spriteFlipX->setChecked(tempSprite->getFlipX());
		ui->checkBox_spriteFlipY->setChecked(tempSprite->getFlipY());
		ui->checkBox_spriteRotate->setChecked(tempSprite->getRot());
		break;
	}
	default:
		break;
	}

	ui->doubleSpinBox_posx->setValue(tempRect->getX());
	ui->doubleSpinBox_posy->setValue(tempRect->getY());
	ui->doubleSpinBox_width->setValue(tempRect->getWidth());
	ui->doubleSpinBox_height->setValue(tempRect->getHeight());

	if(tempRect->getType() == Rect::EXIT){
		ui->label_sidewaysExit->show();
		ui->checkBox_sidwaysExit->show();
	}
}

void MainWindow::on_doubleSpinBox_posx_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Rect*)rectOrganiser::getRect(selectedListItem->text()))->setX(arg1);
		actionPerformed();
	}
}

void MainWindow::on_doubleSpinBox_posy_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Rect*)rectOrganiser::getRect(selectedListItem->text()))->setY(arg1);
		actionPerformed();
	}
}

void MainWindow::on_doubleSpinBox_width_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Rect*)rectOrganiser::getRect(selectedListItem->text()))->setWidth(arg1);
		actionPerformed();
	}
}

void MainWindow::on_doubleSpinBox_height_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Rect*)rectOrganiser::getRect(selectedListItem->text()))->setHeight(arg1);
		actionPerformed();
	}
}


void MainWindow::on_doubleSpinBox_endposx_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((MovingPlatform*)rectOrganiser::getRect(selectedListItem->text()))->setEndX(arg1);
		actionPerformed();
	}
}

void MainWindow::on_doubleSpinBox_endposy_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((MovingPlatform*)rectOrganiser::getRect(selectedListItem->text()))->setEndY(arg1);
		actionPerformed();
	}
}


void MainWindow::on_doubleSpinBox_attackSpeed_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Enemy*)rectOrganiser::getRect(selectedListItem->text()))->setAttackSpeed(arg1);
		actionPerformed();
	}
}

void MainWindow::on_doubleSpinBox_attackRadius_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Enemy*)rectOrganiser::getRect(selectedListItem->text()))->setRadius(arg1);
		actionPerformed();
	}
}

void MainWindow::on_comboBox_headDir_currentIndexChanged(int index)
{
	if(selectedListItem != nullptr){
		((Enemy*)rectOrganiser::getRect(selectedListItem->text()))->setHeadDir(index);
		actionPerformed();
	}
}

void MainWindow::on_comboBox_enyType_currentIndexChanged(int index)
{
	if(selectedListItem != nullptr){
		((Enemy*)rectOrganiser::getRect(selectedListItem->text()))->setType(index);
		actionPerformed();
	}
}


void MainWindow::on_checkBox_sidwaysExit_stateChanged(int arg1)
{
	float tempX = ((Rect*)rectOrganiser::getRect("Exit"))->getX();
	float tempY = ((Rect*)rectOrganiser::getRect("Exit"))->getY();
	if(arg1 == 0){
		((Rect*)rectOrganiser::getRect("Exit"))->setRect(tempX,tempY,6,11);
	} else {
		((Rect*)rectOrganiser::getRect("Exit"))->setRect(tempX,tempY,11,6);
	}

	actionPerformed();
}

void MainWindow::on_doubleSpinBox_spriteX_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Sprite*)rectOrganiser::getRect(selectedListItem->text()))->getTexRect().setX(arg1);
		actionPerformed();
	}
}

void MainWindow::on_doubleSpinBox_spriteY_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Sprite*)rectOrganiser::getRect(selectedListItem->text()))->getTexRect().setY(arg1);
		actionPerformed();
	}
}

void MainWindow::on_doubleSpinBox_spriteWidth_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Sprite*)rectOrganiser::getRect(selectedListItem->text()))->getTexRect().setWidth(arg1);
		actionPerformed();
	}
}

void MainWindow::on_doubleSpinBox_spriteHeight_valueChanged(double arg1)
{
	if(selectedListItem != nullptr){
		((Sprite*)rectOrganiser::getRect(selectedListItem->text()))->getTexRect().setHeight(arg1);
		actionPerformed();
	}
}

void MainWindow::on_checkBox_spriteFlipX_stateChanged(int arg1)
{
	if(selectedListItem != nullptr){
		((Sprite*)rectOrganiser::getRect(selectedListItem->text()))->setFlipX(arg1);
		actionPerformed();
	}
}

void MainWindow::on_checkBox_spriteFlipY_stateChanged(int arg1)
{
	if(selectedListItem != nullptr){
		((Sprite*)rectOrganiser::getRect(selectedListItem->text()))->setFlipY(arg1);
		actionPerformed();
	}
}

void MainWindow::on_checkBox_spriteRotate_stateChanged(int arg1)
{
	if(selectedListItem != nullptr){
		((Sprite*)rectOrganiser::getRect(selectedListItem->text()))->setRot(arg1);
	}

	actionPerformed();
}

void MainWindow::on_actionSave_As_triggered()
{
	saveAs();
}

void MainWindow::on_actionNew_triggered()
{
	newFile();
}

void MainWindow::on_actionSave_triggered()
{
	save();
}

void MainWindow::on_actionOpen_triggered()
{
	QString openPath = QFileDialog::getOpenFileName(this,"Open","","*.rld");

	int i = openPath.size()-1;
	while(i > 0 && openPath[i] != '/'){
		i--;
		//qDebug() << openPath[i];
	}

	//std::string temp = openPath.toStdString().substr(openPath.size()-1-i,i);

	//QString qTemp = temp;



	qDebug() << openPath;
	if(openPath == "") { return; }

	savePath = openPath;

	QFile file(openPath);

	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug() << "Couldn't open file";
		return;
	}
	newFile();

	//this->setWindowTitle(QString::fromStdString(openPath.toStdString().substr(i+1,openPath.size()-i)));

	QTextStream in(&file);
	QString line = in.readLine();

	float a, b;

	std::sscanf(line.toStdString().c_str(),"%f %f", &a, &b);
	((Rect*)rectOrganiser::getRect("Player"))->setX(a);
	((Rect*)rectOrganiser::getRect("Player"))->setY(b);

	line = in.readLine();

	float exitType;

	std::sscanf(line.toStdString().c_str(),"%f %f %f", &a, &b, &exitType);
	((Rect*)rectOrganiser::getRect("Exit"))->setX(a);
	((Rect*)rectOrganiser::getRect("Exit"))->setY(b);

	if(exitType == 0){
		((Rect*)rectOrganiser::getRect("Exit"))->setWidth(6);
		((Rect*)rectOrganiser::getRect("Exit"))->setHeight(11);
	} else {
		((Rect*)rectOrganiser::getRect("Exit"))->setWidth(11);
		((Rect*)rectOrganiser::getRect("Exit"))->setHeight(6);
	}

	line = in.readLine();
	while(!line.isNull()){
		//
		float a, b, c, d, e, f, g, h, i, j;
		switch(line.toStdString()[0])
		{
		case '0':
			std::sscanf(line.toStdString().c_str(), "%f %f %f %f %f", &e, &a, &b, &c, &d);
			ui->listWidget->addItem(rectOrganiser::addWall(Rect(a,b,c,d)));
			break;
		case '1':
			std::sscanf(line.toStdString().c_str(), "%f %f %f %f %f", &e, &a, &b, &c, &d);
			ui->listWidget->addItem(rectOrganiser::addKillPlane(Rect(a,b,c,d)));
			break;
		case '2':
		{
			std::sscanf(line.toStdString().c_str(), "%f %f %f %f %f %f %f %f", &e, &a, &b, &c, &d, &f, &g, &h);
			MovingPlatform temp = MovingPlatform(a,b,c,d,g,h);
			temp.setTime(f);
			ui->listWidget->addItem(rectOrganiser::addMovingPlatform(temp));
			break;
		}
		case '3':
		{
			std::sscanf(line.toStdString().c_str(), "%f %f %f %f %f %f %f %f %f %f", &e, &a, &b, &c, &d, &f, &g, &h, &i, &j);
			Sprite temp = Sprite(a,b,c,d);
			temp.getTexRect().setRect(f,g,h,i);
			int flip = j;
			//qDebug() << flip;
			if(flip & 0b001) { temp.setFlipX(true); }
			if(flip & 0b010) { temp.setFlipY(true); }
			if(flip & 0b100) { temp.setRot(true); }
			ui->listWidget->addItem(rectOrganiser::addSprite(temp));
			temp.draw();
			break;
		}
		case '4':
		{
			std::sscanf(line.toStdString().c_str(), "%f %f %f %f %f %f %f %f %f %f", &e, &a, &b, &c, &d, &f, &g, &h, &i, &j);
			Enemy temp = Enemy(a,b,d,f);
			temp.setTime(c);
			temp.setType(i);
			temp.setHeadDir(g);
			temp.setRadius(h);
			temp.setAttackSpeed(j);
			ui->listWidget->addItem(rectOrganiser::addEnemy(temp));
			break;
		}
		case '5':
			std::sscanf(line.toStdString().c_str(), "%f %f %f %f %f", &e, &a, &b, &c, &d);
			ui->listWidget->addItem(rectOrganiser::addNoRotateZone(Rect(a,b,c,d)));
		break;
		default:
			qDebug() << "FUCK!";
			break;
		}

		//qDebug() << "done a switch statement";
		line = in.readLine();
	}

	ui->listWidget->sortItems();
	this->setWindowTitle(QString::fromStdString(openPath.toStdString().substr(i+1,openPath.size()-i)));
}

void MainWindow::actionPerformed()
{
	/*
	if(this->windowTitle()[0] != '*'){
		this->setWindowTitle("*" + this->windowTitle());
	}*/
}

void MainWindow::on_actionReset_Pan_triggered()
{
	ui->widget->resetPan();
}

void MainWindow::on_actionReset_Zoom_triggered()
{
	ui->widget->resetZoom();
}
