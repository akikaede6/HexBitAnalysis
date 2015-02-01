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

    ui->lineEdit_Output->setText("00000000");

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

    PushButtonOut0.clear();
    PushButtonOut0.append(ui->pushbutton_out0_0);
    PushButtonOut0.append(ui->pushbutton_out0_1);
    PushButtonOut0.append(ui->pushbutton_out0_2);
    PushButtonOut0.append(ui->pushbutton_out0_3);
    PushButtonOut0.append(ui->pushbutton_out0_4);
    PushButtonOut0.append(ui->pushbutton_out0_5);
    PushButtonOut0.append(ui->pushbutton_out0_6);
    PushButtonOut0.append(ui->pushbutton_out0_7);
    PushButtonOut0.append(ui->pushbutton_out0_8);
    PushButtonOut0.append(ui->pushbutton_out0_9);
    PushButtonOut0.append(ui->pushbutton_out0_10);
    PushButtonOut0.append(ui->pushbutton_out0_11);
    PushButtonOut0.append(ui->pushbutton_out0_12);
    PushButtonOut0.append(ui->pushbutton_out0_13);
    PushButtonOut0.append(ui->pushbutton_out0_14);
    PushButtonOut0.append(ui->pushbutton_out0_15);
    PushButtonOut0.append(ui->pushbutton_out0_16);
    PushButtonOut0.append(ui->pushbutton_out0_17);
    PushButtonOut0.append(ui->pushbutton_out0_18);
    PushButtonOut0.append(ui->pushbutton_out0_19);
    PushButtonOut0.append(ui->pushbutton_out0_20);
    PushButtonOut0.append(ui->pushbutton_out0_21);
    PushButtonOut0.append(ui->pushbutton_out0_22);
    PushButtonOut0.append(ui->pushbutton_out0_23);
    PushButtonOut0.append(ui->pushbutton_out0_24);
    PushButtonOut0.append(ui->pushbutton_out0_25);
    PushButtonOut0.append(ui->pushbutton_out0_26);
    PushButtonOut0.append(ui->pushbutton_out0_27);
    PushButtonOut0.append(ui->pushbutton_out0_28);
    PushButtonOut0.append(ui->pushbutton_out0_29);
    PushButtonOut0.append(ui->pushbutton_out0_30);
    PushButtonOut0.append(ui->pushbutton_out0_31);

    for (i = 0; i < 32; i++) {
        connect(PushButtonOut0[i], SIGNAL(clicked()),
                this, SLOT(slot_out0_clicked()));
    }
}

HexBitAnalysis::~HexBitAnalysis()
{
    delete ui;
}

void HexBitAnalysis::input_changed(QString input)
{
    int i;
    ulong hex;
    bool ok;

    styleSheet.clear();

    input = input.trimmed();
    if (input.startsWith("0x"))
        input = input.remove(0, 2);

    hex = input.toULong(&ok, 16);

    ui->lineEdit_Input->setText(input.toUpper());
    ui->lineEdit_Output->setText(QString("%1").arg(hex, 8, 16, QChar('0')).toUpper());

    for (i = 0; i < 32; i++) {
        if ((1 << i) & hex) {
            LabelOrig0[i]->setText("1");
            LabelOrig0[i]->setStyleSheet(QString::fromUtf8("QLabel{\n"
                                            "	background-color:rgb(255, 0, 0);\n"
                                            "}"));

            PushButtonOut0[i]->setText("1");
            PushButtonOut0[i]->setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                            "	background-color:rgb(255, 0, 0);\n"
                                            "}"));
        } else {
            LabelOrig0[i]->setText("0");
            LabelOrig0[i]->setStyleSheet(QString::fromUtf8("QLabel{\n"
                                            "	background-color:rgb(85, 170, 255);\n"
                                            "}"));

            PushButtonOut0[i]->setText("0");
            PushButtonOut0[i]->setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                            "	background-color:rgb(85, 170, 255);\n"
                                            "}"));
        }
    }

}

void HexBitAnalysis::on_lineEdit_Input_textChanged(const QString &arg1)
{
    input_changed(arg1);
}

void HexBitAnalysis::slot_out0_clicked(void)
{
    int i;
    ulong hex = 0;
    QPushButton *BTN = qobject_cast<QPushButton *>(this->sender());

    if (BTN->text().toUInt() == 0)
        BTN->setText("1");
    else
        BTN->setText("0");

    if (!styleSheet.contains(BTN) || styleSheet[BTN].isEmpty()) {
        styleSheet.insert(BTN, BTN->styleSheet());
        BTN->setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                        "	background-color:rgb(255, 170, 0);\n"
                                        "}"));
    } else {
        BTN->setStyleSheet(styleSheet[BTN]);
        styleSheet.remove(BTN);
    }

    for (i = 0; i < 32; i++) {
        hex |= (PushButtonOut0[i]->text().toUInt(0, 2)) << i;
    }

    ui->lineEdit_Output->setText(QString("%1").arg(hex, 8, 16, QChar('0')).toUpper());
}

void HexBitAnalysis::on_pushButton_Restore_clicked()
{
    input_changed(ui->lineEdit_Input->text());
}

void HexBitAnalysis::on_pushButton_Clear_clicked()
{
    ui->lineEdit_Input->setText("");
    input_changed(ui->lineEdit_Input->text());
}
