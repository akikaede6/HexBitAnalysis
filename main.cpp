#include "hexbitanalysis.h"
#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInfo() << QStyleFactory::keys();
    a.setStyle(QStyleFactory::create("Fusion"));
    //    HexBitAnalysis w;
    MainWindow w;
    //    w.setFixedSize(600, 400);
    w.setWindowFlags(Qt::Dialog /* | Qt::WindowMinimizeButtonHint*/);
    w.show();

    return a.exec();
}
