#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include "appsession.h"

int main(int argc, char *argv[])
{	
	QApplication a(argc, argv);
	AppSession apps(a);
	apps.enter();
	if(!apps.active()){

		return 0;
	}	
	return a.exec();
}
