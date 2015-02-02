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
    QDialog(parent),
    ui(new Ui::HexBitAnalysis)
{
    int i;

    ui->setupUi(this);

    ui->lineEdit_Output0->setText("00000000");

    LabelOrig0.clear();
    for (i = 0; i < 32; i++) {
        QLabel *L = (QLabel *)get_widget_by_name(QString("label_orig0_%1").arg(i));
        LabelOrig0.append(L);
    }

    PushButtonOut0.clear();
    for (i = 0; i < 32; i++) {
        QPushButton *PB = (QPushButton *)get_widget_by_name(QString("pushbutton_out0_%1").arg(i));
        PushButtonOut0.append(PB);
    }

    CheckBoxSel0.clear();
    for (i = 0; i < 32; i++) {
        QCheckBox *PB = (QCheckBox *)get_widget_by_name(QString("checkBox_0_%1").arg(i));
        CheckBoxSel0.append(PB);
    }

    ChkBtnPair.clear();
    ChkLblPair.clear();
    for (i = 0; i < 32; i++) {
        ChkBtnPair.insert(CheckBoxSel0[i], PushButtonOut0[i]);
        ChkLblPair.insert(CheckBoxSel0[i], LabelOrig0[i]);
    }

    for (i = 0; i < 32; i++) {
        connect(PushButtonOut0[i], SIGNAL(clicked()),
                this, SLOT(slot_out0_clicked()));
        connect(PushButtonOut0[i], SIGNAL(clicked()),
                this, SLOT(slot_sel0_clicked()));
        connect(CheckBoxSel0[i], SIGNAL(clicked()),
                this, SLOT(slot_sel0_clicked()));
    }

    connect(ui->pushButton_Restore0, SIGNAL(clicked()), this, SLOT(slot_sel0_clicked()));
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

    styleSheetMap.clear();

    input = input.trimmed();
    if (input.startsWith("0x"))
        input = input.remove(0, 2);

    hex = input.toULong(&ok, 16);

    ui->lineEdit_Input0->setText(input.toUpper());
    ui->lineEdit_Output0->setText(QString("%1").arg(hex, 8, 16, QChar('0')).toUpper());

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

void HexBitAnalysis::on_lineEdit_Input0_textChanged(const QString &arg1)
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

    if (!styleSheetMap.contains(BTN) || styleSheetMap[BTN].isEmpty()) {
        styleSheetMap.insert(BTN, BTN->styleSheet());
        BTN->setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                        "	background-color:rgb(255, 170, 0);\n"
                                        "}"));
    } else {
        BTN->setStyleSheet(styleSheetMap[BTN]);
        styleSheetMap.remove(BTN);
    }

    for (i = 0; i < 32; i++) {
        hex |= (PushButtonOut0[i]->text().toUInt(0, 2)) << i;
    }

    ui->lineEdit_Output0->setText(QString("%1").arg(hex, 8, 16, QChar('0')).toUpper());
}

void HexBitAnalysis::slot_sel0_clicked(void)
{
    QCheckBox *Chk;
    ulong hexInput = 0, hexOutput = 0;
    int from = 0;
    bool checked = false;

    for (int i = 0; i < 32; i++) {
        Chk = CheckBoxSel0[i];
        if (Chk->isChecked()) {
            hexInput |= ChkLblPair[Chk]->text().toUInt(0, 2) << from;
            hexOutput |= ChkBtnPair[Chk]->text().toUInt(0, 2) << from;
            from++;
            checked = true;
        }
    }

    if (checked) {
        ui->InputSel0Hex->setText(QString("0x") + QString("%1").arg(hexInput, 0, 16).toUpper());
        ui->InputSel0Dec->setText(QString("%1").arg(hexInput));
        ui->OutputSel0Hex->setText(QString("0x") + QString("%1").arg(hexOutput, 0, 16).toUpper());
        ui->OutputSel0Dec->setText(QString("%1").arg(hexOutput));
    } else {
        ui->InputSel0Hex->setText("");
        ui->InputSel0Dec->setText("");
        ui->OutputSel0Hex->setText("");
        ui->OutputSel0Dec->setText("");
    }
}

void HexBitAnalysis::on_pushButton_Restore0_clicked()
{
    input_changed(ui->lineEdit_Input0->text());
}

void HexBitAnalysis::on_pushButton_Clear0_clicked()
{
    for (int i = 0; i < 32; i++) {
        CheckBoxSel0[i]->setCheckState(Qt::Unchecked);
    }

    slot_sel0_clicked();
}

void HexBitAnalysis::on_pushButton_Reset0_clicked()
{
    ui->lineEdit_Input0->setText("");
    on_pushButton_Restore0_clicked();
    on_pushButton_Clear0_clicked();
}
