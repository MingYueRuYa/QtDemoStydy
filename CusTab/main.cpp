#include "customtab.h"
#include "application.h"

#include <QtCore/QDir>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
	Application app(argc, argv);
	QStringList arguments = QCoreApplication::arguments();

    CustomTab custom_tab(nullptr);
    custom_tab.show();

	int nRes = app.exec();

	return nRes;
}
