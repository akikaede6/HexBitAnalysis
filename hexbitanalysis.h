#ifndef HEXBITANALYSIS_H
#define HEXBITANALYSIS_H

#include <QDialog>

namespace Ui {
class HexBitAnalysis;
}

class HexBitAnalysis : public QDialog
{
    Q_OBJECT
    
public:
    explicit HexBitAnalysis(QWidget *parent = 0);
    ~HexBitAnalysis();
    
private:
    Ui::HexBitAnalysis *ui;
};

#endif // HEXBITANALYSIS_H
