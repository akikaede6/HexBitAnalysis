#include "hexbitanalysis.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HexBitAnalysis w;
    w.setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint);
    w.show();
    
    return a.exec();
}
