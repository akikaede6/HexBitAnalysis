#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QDialog>
#include <QWidget>

class QLineEdit;
class FontDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FontDialog(QWidget *parent = nullptr);

signals:
    void fontChanged();

public slots:
    void onConfirmBtnClicked();

private:
    QLineEdit *m_fontEdit;
    QPushButton *m_confirmBtn;
    QPushButton *m_cancelBtn;
};

#endif // FONTDIALOG_H
