#include "hexbitanalysis.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HexBitAnalysis w;
    w.show();
    
    return a.exec();
}
