#include "hexbitanalysis.h"
#include "ui_hexbitanalysis.h"

HexBitAnalysis::HexBitAnalysis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HexBitAnalysis)
{
    int i;
    ui->setupUi(this);

//    for (i = ui->LabelOrigLayout->layout()->count() - 1; i >= 0; i--) {
//        QLayoutItem *it = ui->LabelOrigLayout->layout()->itemAt(i);
//        QLabel *orig = qobject_cast<QLabel *>(it->widget());
//        orig->setStyleSheet("background-color:rgbrgb(85, 170, 255)");
//    }

   // ui->pushButton_5->setDown(true);
}

HexBitAnalysis::~HexBitAnalysis()
{
    delete ui;
}
