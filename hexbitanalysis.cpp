#include <QDebug>
#include <QtGui>
#include "hexbitanalysis.h"
#include "ui_hexbitanalysis.h"

void* get_widget_by_name(const QString name)
{
    QWidget *widget = 0;

    foreach(widget, QApplication::allWidgets()) {
        if (widget->objectName() == name) {
            break;
        }
    }

    return ((void*)widget);
}

HexBitAnalysis::HexBitAnalysis(QWidget *parent) :
//    QDialog(parent),
    ui(new Ui::HexBitAnalysis)
{
    int i;

    ui->setupUi(this);

    LblIn0.clear();
    LblIn1.clear();
    LblIn2.clear();
    for (i = 0; i < 32; i++) {
        QLabel *L;
        L = (QLabel *)get_widget_by_name(QString("label_orig0_%1").arg(i));
        LblIn0.append(L);
        L = (QLabel *)get_widget_by_name(QString("label_orig1_%1").arg(i));
        LblIn1.append(L);
        L = (QLabel *)get_widget_by_name(QString("label_orig2_%1").arg(i));
        LblIn2.append(L);
    }

    BtnOut0.clear();
    BtnOut1.clear();
    BtnOut2.clear();
    for (i = 0; i < 32; i++) {
        MyPushButton *Btn;
        Btn = (MyPushButton *)get_widget_by_name(QString("pushbutton_out0_%1").arg(i));
        BtnOut0.append(Btn);
        Btn = (MyPushButton *)get_widget_by_name(QString("pushbutton_out1_%1").arg(i));
        BtnOut1.append(Btn);
        Btn = (MyPushButton *)get_widget_by_name(QString("pushbutton_out2_%1").arg(i));
        BtnOut2.append(Btn);
    }

    CheckBoxSel0.clear();
    CheckBoxSel1.clear();
    CheckBoxSel2.clear();
    for (i = 0; i < 32; i++) {
        QCheckBox *Chk;
        Chk = (QCheckBox *)get_widget_by_name(QString("checkBox_0_%1").arg(i));
        CheckBoxSel0.append(Chk);
        Chk = (QCheckBox *)get_widget_by_name(QString("checkBox_1_%1").arg(i));
        CheckBoxSel1.append(Chk);
        Chk = (QCheckBox *)get_widget_by_name(QString("checkBox_2_%1").arg(i));
        CheckBoxSel2.append(Chk);
    }

    ChkBtnPair0.clear();
    ChkLblPair0.clear();
    ChkBtnPair1.clear();
    ChkLblPair1.clear();
    ChkBtnPair2.clear();
    ChkLblPair2.clear();
    for (i = 0; i < 32; i++) {
        ChkBtnPair0.insert(CheckBoxSel0[i], BtnOut0[i]);
        ChkLblPair0.insert(CheckBoxSel0[i], LblIn0[i]);
        ChkBtnPair1.insert(CheckBoxSel1[i], BtnOut1[i]);
        ChkLblPair1.insert(CheckBoxSel1[i], LblIn1[i]);
        ChkBtnPair2.insert(CheckBoxSel2[i], BtnOut2[i]);
        ChkLblPair2.insert(CheckBoxSel2[i], LblIn2[i]);
    }

    for (i = 0; i < 32; i++) {
        connect(BtnOut0[i], SIGNAL(clicked()),
                this, SLOT(slot_BtnOut_clicked()));
        connect(BtnOut0[i], SIGNAL(clicked()),
                this, SLOT(slot_BtnSel_clicked()));
        connect(CheckBoxSel0[i], SIGNAL(clicked()),
                this, SLOT(slot_ChkSel_clicked()));

        connect(BtnOut1[i], SIGNAL(clicked()),
                this, SLOT(slot_BtnOut_clicked()));
        connect(BtnOut1[i], SIGNAL(clicked()),
                this, SLOT(slot_BtnSel_clicked()));
        connect(CheckBoxSel1[i], SIGNAL(clicked()),
                this, SLOT(slot_ChkSel_clicked()));

        connect(BtnOut2[i], SIGNAL(clicked()),
                this, SLOT(slot_BtnOut_clicked()));
        connect(BtnOut2[i], SIGNAL(clicked()),
                this, SLOT(slot_BtnSel_clicked()));
        connect(CheckBoxSel2[i], SIGNAL(clicked()),
                this, SLOT(slot_ChkSel_clicked()));
    }

    ui->lineEdit_Output0->setText("00000000");
    ui->groupBox0->addBtnList(BtnOut0);
    ui->groupBox0->addChkList(CheckBoxSel0);
    ui->groupBox1->addBtnList(BtnOut1);
    ui->groupBox1->addChkList(CheckBoxSel1);
    ui->groupBox2->addBtnList(BtnOut2);
    ui->groupBox2->addChkList(CheckBoxSel2);

    on_pushButton_Reset0_clicked();
    on_pushButton_Reset1_clicked();
    on_pushButton_Reset2_clicked();

    num = 1;
    increase_hight = ui->groupBox_1->size().height() + 300;
    ui->groupBox_1->setVisible(false);
    ui->groupBox_2->setVisible(false);
}

HexBitAnalysis::~HexBitAnalysis()
{
    delete ui;
}

void HexBitAnalysis::input_changed(int id, QString input)
{
    QList<MyPushButton *> BtnOut;
    QList<QLabel *> LblIn;
    QLineEdit *In, *Out;
    int i;
    ulong hex;
    bool ok;

    switch (id) {
    case 2:
        BtnOut = BtnOut2;
        LblIn = LblIn2;
        In = ui->lineEdit_Input2;
        Out = ui->lineEdit_Output2;
        break;
    case 1:
        BtnOut = BtnOut1;
        LblIn = LblIn1;
        In = ui->lineEdit_Input1;
        Out = ui->lineEdit_Output1;
        break;
    case 0:
    default:
        BtnOut = BtnOut0;
        LblIn = LblIn0;
        In = ui->lineEdit_Input0;
        Out = ui->lineEdit_Output0;
        break;
    }

    for (i = 0; i < 32; i++)
        BtnOut[i]->style_sheet = QString();

    input = input.trimmed();
    if (input.startsWith("0x"))
        input = input.remove(0, 2);

    hex = input.toULong(&ok, 16);

    In->setText(input.toUpper());
    Out->setText(QString("%1").arg(hex, 8, 16, QChar('0')).toUpper());

    for (i = 0; i < 32; i++) {
        if ((1 << i) & hex) {
            LblIn[i]->setText("1");
            LblIn[i]->setStyleSheet(QString::fromUtf8("QLabel{\n"
                                            "	background-color:rgb(255, 0, 0);\n"
                                            "}"));

            BtnOut[i]->setText("1");
            BtnOut[i]->setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                            "	background-color:rgb(255, 0, 0);\n"
                                            "}"));
        } else {
            LblIn[i]->setText("0");
            LblIn[i]->setStyleSheet(QString::fromUtf8("QLabel{\n"
                                            "	background-color:rgb(85, 170, 255);\n"
                                            "}"));

            BtnOut[i]->setText("0");
            BtnOut[i]->setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                            "	background-color:rgb(85, 170, 255);\n"
                                            "}"));
        }
    }

    sel_clicked(id);
}

void HexBitAnalysis::on_lineEdit_Input0_textChanged(const QString &arg1)
{
    input_changed(0, arg1);
}

void HexBitAnalysis::slot_BtnOut_clicked(void)
{
    QList<MyPushButton *> BtnOut;
    QLineEdit *Out;
    MyPushButton *Btn;
    ulong hex = 0;
    int i;

    Btn = qobject_cast<MyPushButton *>(this->sender());
    Btn->text_toggle();

    if (BtnOut0.contains(Btn)) {
        BtnOut = BtnOut0;
        Out = ui->lineEdit_Output0;
    } else if (BtnOut1.contains(Btn)) {
        BtnOut = BtnOut1;
        Out = ui->lineEdit_Output1;
    } else if (BtnOut2.contains(Btn)) {
        BtnOut = BtnOut2;
        Out = ui->lineEdit_Output2;
    } else {
        return;
    }

    for (i = 0; i < 32; i++) {
        hex |= (BtnOut[i]->text().toUInt(0, 2)) << i;
    }

    Out->setText(QString("%1").arg(hex, 8, 16, QChar('0')).toUpper());
}

void HexBitAnalysis::slot_BtnSel_clicked(void)
{
    MyPushButton *Btn;
    int id;

    Btn = qobject_cast<MyPushButton *>(this->sender());

    if (BtnOut0.contains(Btn))
        id = 0;
    else if (BtnOut1.contains(Btn))
        id = 1;
    else if (BtnOut2.contains(Btn))
        id = 2;
    else
        return;

    sel_clicked(id);
}

void HexBitAnalysis::slot_ChkSel_clicked(void)
{
    QCheckBox *Chk = qobject_cast<QCheckBox *>(this->sender());
    int id;

    if (CheckBoxSel0.contains(Chk))
        id = 0;
    else if (CheckBoxSel1.contains(Chk))
        id = 1;
    else if (CheckBoxSel2.contains(Chk))
        id = 2;
    else
        return;

    sel_clicked(id);
}

void HexBitAnalysis::sel_clicked(int id)
{
    QList<QCheckBox *> CheckBoxSel;
    QMap<QCheckBox *, MyPushButton *> ChkBtnPair;
    QMap<QCheckBox *, QLabel *> ChkLblPair;
    QLineEdit *InHex, *InDec, *OutHex, *OutDec;
    QCheckBox *Chk;
    ulong hexInput = 0, hexOutput = 0;
    int from = 0;
    bool checked = false;

    Chk = qobject_cast<QCheckBox *>(this->sender());

    switch (id) {
    case 2:
        CheckBoxSel = CheckBoxSel2;
        ChkBtnPair = ChkBtnPair2;
        ChkLblPair = ChkLblPair2;
        InHex = ui->InputSel2Hex;
        InDec = ui->InputSel2Dec;
        OutHex = ui->OutputSel2Hex;
        OutDec = ui->OutputSel2Dec;
        break;
    case 1:
        CheckBoxSel = CheckBoxSel1;
        ChkBtnPair = ChkBtnPair1;
        ChkLblPair = ChkLblPair1;
        InHex = ui->InputSel1Hex;
        InDec = ui->InputSel1Dec;
        OutHex = ui->OutputSel1Hex;
        OutDec = ui->OutputSel1Dec;
        break;
    case 0:
    default:
        CheckBoxSel = CheckBoxSel0;
        ChkBtnPair = ChkBtnPair0;
        ChkLblPair = ChkLblPair0;
        InHex = ui->InputSel0Hex;
        InDec = ui->InputSel0Dec;
        OutHex = ui->OutputSel0Hex;
        OutDec = ui->OutputSel0Dec;
        break;
    }

    for (int i = 0; i < 32; i++) {
        Chk = CheckBoxSel[i];
        if (Chk->isChecked()) {
            hexInput |= ChkLblPair[Chk]->text().toUInt(0, 2) << from;
            hexOutput |= ChkBtnPair[Chk]->text().toUInt(0, 2) << from;
            from++;
            checked = true;
        }
    }

    if (checked) {
        InHex->setText(QString("0x") + QString("%1").arg(hexInput, 0, 16).toUpper());
        InDec->setText(QString("%1").arg(hexInput));
        OutHex->setText(QString("0x") + QString("%1").arg(hexOutput, 0, 16).toUpper());
        OutDec->setText(QString("%1").arg(hexOutput));
    } else {
        InHex->setText("");
        InDec->setText("");
        OutHex->setText("");
        OutDec->setText("");
    }
}

void HexBitAnalysis::on_pushButton_Restore0_clicked()
{
    input_changed(0, ui->lineEdit_Input0->text());
}

void HexBitAnalysis::on_pushButton_Clear0_clicked()
{
    for (int i = 0; i < 32; i++) {
        CheckBoxSel0[i]->setCheckState(Qt::Unchecked);
    }

    sel_clicked(0);
}

void HexBitAnalysis::on_pushButton_Reset0_clicked()
{
    ui->lineEdit_Input0->setText("");
    on_pushButton_Restore0_clicked();
    on_pushButton_Clear0_clicked();
}

void HexBitAnalysis::on_lineEdit_Input1_textChanged(const QString &arg1)
{
    input_changed(1, arg1);
}

void HexBitAnalysis::on_pushButton_Restore1_clicked()
{
    input_changed(1, ui->lineEdit_Input1->text());
}

void HexBitAnalysis::on_pushButton_Clear1_clicked()
{
    for (int i = 0; i < 32; i++) {
        CheckBoxSel1[i]->setCheckState(Qt::Unchecked);
    }

    sel_clicked(1);
}

void HexBitAnalysis::on_pushButton_Reset1_clicked()
{
    ui->lineEdit_Input1->setText("");
    on_pushButton_Restore1_clicked();
    on_pushButton_Clear1_clicked();
}

void HexBitAnalysis::on_lineEdit_Input2_textChanged(const QString &arg1)
{
    input_changed(2, arg1);
}

void HexBitAnalysis::on_pushButton_Restore2_clicked()
{
    input_changed(2, ui->lineEdit_Input2->text());
}

void HexBitAnalysis::on_pushButton_Clear2_clicked()
{
    for (int i = 0; i < 32; i++) {
        CheckBoxSel2[i]->setCheckState(Qt::Unchecked);
    }

    sel_clicked(2);
}

void HexBitAnalysis::on_pushButton_Reset2_clicked()
{
    ui->lineEdit_Input2->setText("");
    on_pushButton_Restore2_clicked();
    on_pushButton_Clear2_clicked();
}




void HexBitAnalysis::on_pushButton_plus_clicked()
{
    if (num == 1)
        ui->groupBox_1->setVisible(true);
    else if (num == 2)
        ui->groupBox_2->setVisible(true);
    else
        return;

    num++;
    if (num >= 3)
        ui->pushButton_plus->setEnabled(false);

    ui->pushButton_minus->setEnabled(true);

    resize(geometry().width(), geometry().height() + increase_hight);
}

void HexBitAnalysis::on_pushButton_minus_clicked()
{
    if (num == 3)
        ui->groupBox_2->setVisible(false);
    else if (num == 2)
        ui->groupBox_1->setVisible(false);
    else
        return;

    num--;
    if (num <= 1)
        ui->pushButton_minus->setEnabled(false);

    ui->pushButton_plus->setEnabled(true);
}
