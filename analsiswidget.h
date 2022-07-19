#ifndef ANALSISWIDGET_H
#define ANALSISWIDGET_H

#include <QWidget>

class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;
class BinaryWidget;
class AnalsisWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnalsisWidget(QWidget *parent = nullptr);

private:
    void initConnection();

public slots:
    void onInputChanged(const QString &input);
    void onBtnClicked(ulong hex);

private:
    QLineEdit *m_inputEdit;
    QLineEdit *m_outputEdit;
    QVBoxLayout *m_mainLayout;
    BinaryWidget *m_binaryWidget;
};

#endif // ANALSISWIDGET_H
