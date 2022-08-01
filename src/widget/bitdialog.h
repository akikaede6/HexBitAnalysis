#ifndef BITDIALOG_H
#define BITDIALOG_H

#include <QDialog>

class QRadioButton;
class QPushButton;
class QButtonGroup;
class BitDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BitDialog(QWidget *parent = nullptr);

signals:
    void bitChanged(int bit);

public slots:
    void onConfirmBtnClicked();

private:
    QPushButton *m_confirmBtn;
    QPushButton *m_cancelBtn;
    QButtonGroup *m_btnGroup{};
};

#endif // BITDIALOG_H
