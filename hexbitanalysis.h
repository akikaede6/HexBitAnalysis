#ifndef HEXBITANALYSIS_H
#define HEXBITANALYSIS_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class HexBitAnalysis;
}

class HexBitAnalysis : public QDialog
{
    Q_OBJECT
    
public:
    explicit HexBitAnalysis(QWidget *parent = 0);
    ~HexBitAnalysis();

private slots:
    void on_lineEdit_Input0_textChanged(const QString &arg1);

    void slot_out0_clicked(void);
    void slot_sel0_clicked(void);

    void on_pushButton_Restore0_clicked();

    void on_pushButton_Clear0_clicked();

    void on_pushButton_Reset0_clicked();

private:
    void input_changed(QString input);

private:
    Ui::HexBitAnalysis *ui;

    QList<QLabel *> LabelOrig0;
    QList<QPushButton *> PushButtonOut0;
    QList<QCheckBox *> CheckBoxSel0;

    QMap<QPushButton *, QString> styleSheetMap;
    QMap<QCheckBox *, QPushButton *> ChkBtnPair;
    QMap<QCheckBox *, QLabel *> ChkLblPair;
};

#endif // HEXBITANALYSIS_H
