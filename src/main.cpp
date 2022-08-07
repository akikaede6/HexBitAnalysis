#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication::setWindowIcon(QIcon(":/icon/app.png"));
    MainWindow w;
    w.setWindowFlags(Qt::Dialog);
    w.show();
    return a.exec();
}
