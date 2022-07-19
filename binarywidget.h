#ifndef BINARYWIDGET_H
#define BINARYWIDGET_H

#include <QWidget>

class QHBoxLayout;
class QGridLayout;
class QLabel;
class QButtonGroup;
class QCheckBox;
class QAbstractButton;
class QFrame;
class BinaryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BinaryWidget(QWidget *parent = nullptr);

public slots:
    void onInputChanged(const QString &input);
    void onBtnClicked(QAbstractButton *clickedBtn);

signals:
    void btnClicked(ulong hex);

private:
    void initConnection();
    QFrame *createLine();

private:
    QHBoxLayout *m_mainLayout;
    QGridLayout *m_binaryLayout_1;
    QGridLayout *m_binaryLayout_2;
    QGridLayout *m_binaryLayout_3;
    QGridLayout *m_binaryLayout_4;
    QList<QLabel *> m_labelList;
    QButtonGroup *m_binaryBtnGroup;
    QList<QCheckBox *> m_checkBoxList;
};

#endif // BINARYWIDGET_H
