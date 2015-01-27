#include <QDebug>
#include <QtGui>
#include "hexbitanalysis.h"
#include "ui_hexbitanalysis.h"

HexBitAnalysis::HexBitAnalysis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HexBitAnalysis)
{
    int i;

    ui->setupUi(this);

    LabelOrig0.clear();
    LabelOrig0.append(ui->label_orig0_0);
    LabelOrig0.append(ui->label_orig0_1);
    LabelOrig0.append(ui->label_orig0_2);
    LabelOrig0.append(ui->label_orig0_3);
    LabelOrig0.append(ui->label_orig0_4);
    LabelOrig0.append(ui->label_orig0_5);
    LabelOrig0.append(ui->label_orig0_6);
    LabelOrig0.append(ui->label_orig0_7);
    LabelOrig0.append(ui->label_orig0_8);
    LabelOrig0.append(ui->label_orig0_9);
    LabelOrig0.append(ui->label_orig0_10);
    LabelOrig0.append(ui->label_orig0_11);
    LabelOrig0.append(ui->label_orig0_12);
    LabelOrig0.append(ui->label_orig0_13);
    LabelOrig0.append(ui->label_orig0_14);
    LabelOrig0.append(ui->label_orig0_15);
    LabelOrig0.append(ui->label_orig0_16);
    LabelOrig0.append(ui->label_orig0_17);
    LabelOrig0.append(ui->label_orig0_18);
    LabelOrig0.append(ui->label_orig0_19);
    LabelOrig0.append(ui->label_orig0_20);
    LabelOrig0.append(ui->label_orig0_21);
    LabelOrig0.append(ui->label_orig0_22);
    LabelOrig0.append(ui->label_orig0_23);
    LabelOrig0.append(ui->label_orig0_24);
    LabelOrig0.append(ui->label_orig0_25);
    LabelOrig0.append(ui->label_orig0_26);
    LabelOrig0.append(ui->label_orig0_27);
    LabelOrig0.append(ui->label_orig0_28);
    LabelOrig0.append(ui->label_orig0_29);
    LabelOrig0.append(ui->label_orig0_30);
    LabelOrig0.append(ui->label_orig0_31);

    GrpboxOrig0.clear();
    GrpboxOrig0.append(ui->groupBox_0_0);
    GrpboxOrig0.append(ui->groupBox_0_1);
    GrpboxOrig0.append(ui->groupBox_0_2);
    GrpboxOrig0.append(ui->groupBox_0_3);
    GrpboxOrig0.append(ui->groupBox_0_4);
    GrpboxOrig0.append(ui->groupBox_0_5);
    GrpboxOrig0.append(ui->groupBox_0_6);
    GrpboxOrig0.append(ui->groupBox_0_7);
    GrpboxOrig0.append(ui->groupBox_0_8);
    GrpboxOrig0.append(ui->groupBox_0_9);
    GrpboxOrig0.append(ui->groupBox_0_10);
    GrpboxOrig0.append(ui->groupBox_0_11);
    GrpboxOrig0.append(ui->groupBox_0_12);
    GrpboxOrig0.append(ui->groupBox_0_13);
    GrpboxOrig0.append(ui->groupBox_0_14);
    GrpboxOrig0.append(ui->groupBox_0_15);
    GrpboxOrig0.append(ui->groupBox_0_16);
    GrpboxOrig0.append(ui->groupBox_0_17);
    GrpboxOrig0.append(ui->groupBox_0_18);
    GrpboxOrig0.append(ui->groupBox_0_19);
    GrpboxOrig0.append(ui->groupBox_0_20);
    GrpboxOrig0.append(ui->groupBox_0_21);
    GrpboxOrig0.append(ui->groupBox_0_22);
    GrpboxOrig0.append(ui->groupBox_0_23);
    GrpboxOrig0.append(ui->groupBox_0_24);
    GrpboxOrig0.append(ui->groupBox_0_25);
    GrpboxOrig0.append(ui->groupBox_0_26);
    GrpboxOrig0.append(ui->groupBox_0_27);
    GrpboxOrig0.append(ui->groupBox_0_28);
    GrpboxOrig0.append(ui->groupBox_0_29);
    GrpboxOrig0.append(ui->groupBox_0_30);
    GrpboxOrig0.append(ui->groupBox_0_31);
}

HexBitAnalysis::~HexBitAnalysis()
{
    delete ui;
}

void HexBitAnalysis::on_lineEdit_Input_textChanged(const QString &arg1)
{
    QString input;
    int i;
    ulong hex;
    bool ok;

    input = ui->lineEdit_Input->text().trimmed();
    if (input.startsWith("0x"))
        ui->lineEdit_Input->setText(input.remove(0, 2));

    hex = input.toULong(&ok, 16);

    for (i = 0; i < 32; i++) {
        if ((1 << i) & hex) {
            LabelOrig0[i]->setText("1");
            LabelOrig0[i]->setStyleSheet(QString::fromUtf8("QLabel{\n"
                                            "	background-color:rgb(255, 0, 0);\n"
                                            "}"));
            GrpboxOrig0[i]->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
                                                            "	border:4px inset lightGray;\n"
                                                            "	border-radius: 3px;\n"
                                                            "	background: white\n"
                                                            "}"));
        } else {
            LabelOrig0[i]->setText("0");
            LabelOrig0[i]->setStyleSheet(QString::fromUtf8("QLabel{\n"
                                            "	background-color:rgb(85, 170, 255);\n"
                                            "}"));
            GrpboxOrig0[i]->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
                                                            "	border:4px outset lightGray;\n"
                                                            "	border-radius: 3px;\n"
                                                            "	background: white\n"
                                                            "}"));
        }
    }
}
