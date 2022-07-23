#ifndef BINARYWIDGET_H
#define BINARYWIDGET_H

#include <QWidget>

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
    void onCheckBoxClicked();
    void onClearBtnClicked();
    void onResetBtnClicked();

signals:
    void btnClicked(ulong hex);
    void checkLabelOutput(const ulong &dec);
    void checkBtnOutput(const ulong &dec);

private:
    void initConnection();
    static QFrame *createLine();

private:
    QList<QLabel *> m_labelList;
    QButtonGroup *m_binaryBtnGroup;
    QList<QCheckBox *> m_checkBoxList;
};

#endif // BINARYWIDGET_H
