#ifndef HEXBITANALYSIS_H
#define HEXBITANALYSIS_H

#include <QDialog>
#include <QtGui>
#include "mywidget.h"

namespace Ui {
class HexBitAnalysis;
}

class HexBitAnalysis : public QDialog
{
    Q_OBJECT
    
public:
    explicit HexBitAnalysis(QWidget *parent = 0);
    ~HexBitAnalysis();

signals:
    void signal_input_changed(ulong hex);

protected:

private slots:
    void on_lineEdit_Input0_textChanged(const QString &arg1);
    void on_lineEdit_Input1_textChanged(const QString &arg1);
    void on_lineEdit_Input2_textChanged(const QString &arg1);

    void slot_BtnOut_clicked(void);
    void slot_BtnSel_clicked(void);
    void slot_ChkSel_clicked(void);

    void on_pushButton_Restore0_clicked();
    void on_pushButton_Clear0_clicked();
    void on_pushButton_Reset0_clicked();
    void on_pushButton_Restore1_clicked();
    void on_pushButton_Clear1_clicked();
    void on_pushButton_Reset1_clicked();
    void on_pushButton_Restore2_clicked();
    void on_pushButton_Clear2_clicked();
    void on_pushButton_Reset2_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_minus_clicked();

private:
    void input_changed(int id, QString input);
    void sel_clicked(int id);

private:
    Ui::HexBitAnalysis *ui;

    int num;
    int increase_hight;

    QList<MyPushButton *> BtnOut0;
    QList<QLabel *> LblIn0;
    QList<QCheckBox *> CheckBoxSel0;

    QList<MyPushButton *> BtnOut1;
    QList<QLabel *> LblIn1;
    QList<QCheckBox *> CheckBoxSel1;

    QList<MyPushButton *> BtnOut2;
    QList<QLabel *> LblIn2;
    QList<QCheckBox *> CheckBoxSel2;

    QMap<QCheckBox *, MyPushButton *> ChkBtnPair0;
    QMap<QCheckBox *, QLabel *> ChkLblPair0;

    QMap<QCheckBox *, MyPushButton *> ChkBtnPair1;
    QMap<QCheckBox *, QLabel *> ChkLblPair1;

    QMap<QCheckBox *, MyPushButton *> ChkBtnPair2;
    QMap<QCheckBox *, QLabel *> ChkLblPair2;
};

#endif // HEXBITANALYSIS_H
