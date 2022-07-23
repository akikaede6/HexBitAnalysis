#ifndef ANALSISWIDGET_H
#define ANALSISWIDGET_H

#include <QWidget>

class QLineEdit;
class QVBoxLayout;
class BinaryWidget;
class SelectedWidget;
class QPushButton;
class AnalsisWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnalsisWidget(QWidget *parent = nullptr);

private:
    void initConnection();

signals:
    void restoreBinary(const QString &input);

public slots:
    void onInputChanged(const QString &input);
    void onBtnClicked(ulong hex);
    void onResetBtnClicked();
    void onRestoreBtnClicked();

private:
    QLineEdit *m_inputEdit;
    QLineEdit *m_outputEdit;
    QPushButton *m_restoreBtn;
    QPushButton *m_clearBtn;
    QPushButton *m_resetBtn;
    QVBoxLayout *m_mainLayout;
    BinaryWidget *m_binaryWidget;
    SelectedWidget *m_selectedLabelWidget;
    SelectedWidget *m_selectedBtnWidget;
};

#endif // ANALSISWIDGET_H
