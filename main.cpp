#include "mainwindow.h"
#include <QApplication>
#include "joysticksdl.h"
#include <QDebug>

#undef main
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //  joysticksdl s(0);
    //s.ShowJoystickData();
    //s.ShowAvailableJoysticks();
    //    s.setKind(1,4);
    MainWindow w;
    w.show();


    return a.exec();
}
