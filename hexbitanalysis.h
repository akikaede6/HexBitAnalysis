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

private:
    Ui::HexBitAnalysis *ui;

    QList<QLabel *> LabelOrig0;
    QList<QGroupBox *> GrpboxOrig0;
};

#endif // HEXBITANALYSIS_H
