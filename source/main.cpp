#include <QtWidgets/QApplication>
#include "mainpanel/mainpanel.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainPanel window;
    window.show();
    return app.exec();
}