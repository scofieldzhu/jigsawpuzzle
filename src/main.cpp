#include <QApplication>
#include "appsession.h"
#include "applogger.h"

int main(int argc, char *argv[])
{	
    InitLogger();
    slog_info(applogger) << "Enter main..." << std::endl;
	QApplication a(argc, argv);
	AppSession apps(a);
	apps.enter();
	if(!apps.active()){
        slog_err(applogger) << "AppSession enter failed!" << endl;
		return 0;
	}	
	return a.exec();
}
