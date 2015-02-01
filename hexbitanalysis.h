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
    void on_lineEdit_Input_textChanged(const QString &arg1);

    void slot_out0_clicked(void);

    void on_pushButton_Restore_clicked();

    void on_pushButton_Clear_clicked();

private:
    void input_changed(QString input);

private:
    Ui::HexBitAnalysis *ui;

    QList<QLabel *> LabelOrig0;
    QList<QPushButton *> PushButtonOut0;
    QMap<QPushButton *, QString> styleSheet;
};

#endif // HEXBITANALYSIS_H
